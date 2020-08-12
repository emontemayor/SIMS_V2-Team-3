/**********************************************
 * spi_27_driver.h
 * Function definitions for the SPI driver for the AS3900
 *
 * Author : Emiliano Montemayor
 * Capstone Project 2019 - 2020
 **********************************************/
#include "spi_27_driver.h"
#include "AS3900_regs.h"

/************************************************************************/
/*                                Globals                               */
/************************************************************************/
struct spi_module spi27Master;
struct spi_slave_inst spi27Slave;
bool spi27InitComp = false;
static uint16_t spi27_status_bits = 0;

/************************************************************************/
/*                                Functions                             */
/************************************************************************/
/* Function Name    : spi27_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initialize the SPI SERCOM for the 27 MHz module
 */
void spi27_init(void)
{
	if (spi27InitComp == true)
		return;
		
	struct spi_config spi27MasterConf;
	struct spi_slave_inst_config spi27SlaveConf;
	struct port_config pinConf;
	
    // initialize the slave select pin
	port_get_config_defaults(&pinConf);
    
    // get defaults for lcd master config
	spi_get_config_defaults(&spi27MasterConf);
    
    spi27MasterConf.mux_setting = SPI27_PINXMUX;
    spi27MasterConf.pinmux_pad0 = MOSI27;
    spi27MasterConf.pinmux_pad1 = SCK27;
    spi27MasterConf.pinmux_pad2 = PINMUX_UNUSED;
    spi27MasterConf.pinmux_pad3 = MISO27;
	
	// clock source should always be GLCK0
	spi27MasterConf.generator_source = SPI27_CLK;
	spi27MasterConf.mode_specific.master.baudrate = SPI27MAXCLK;

	// enable the master
	spi_init(&spi27Master, SPI27, &spi27MasterConf);
	spi_enable(&spi27Master);

	// get default configs for slave
	spi_slave_inst_get_config_defaults(&spi27SlaveConf);
	// change configs as necessary
	spi27SlaveConf.ss_pin = SS27;
	// attach the slave configs to the slave
	spi_attach_slave(&spi27Slave, &spi27SlaveConf);
    
    spi27InitComp = true;
	spi27_connect();
}

void spi27_connect (){
	//register set up. Common data-rate, frequency deviation and communication mode must be configured in the MAIN Register of all devices which have to be paired
	spi27_write_byte_to_reg(0x80, 0x00); //set reciever unit as master
	spi27_write_byte_to_reg(0x12, 0x04); //set waketm bits (sequence b00010011 for waketm bits and to set long wake_tx bit 0x04 for REG.) (pg. 25)
	spi27_write_byte_to_reg(0x00, 0x01); //DISABLE all timers
	spi27_write_byte_to_reg(0x02, 0x06); //set bitrate to 53 kbit per sec
	
	//write client ID
	spi27_write_byte_to_reg(0, 0x08);
	spi27_write_byte_to_reg(0, 0x09);
	spi27_write_byte_to_reg(0x02, 0x0A);
	
	//wake procedure
	spi27_write_cmd(WAKE_TX); //begin wakeup call 
	delay_s(1); //delay for 1 sec, listen for client
	
	//pairing procedure
	
	//wait for dat_rtx interrupt, signaling signaling data has been succesfully transmitted and can be read.
	char *byte;
	while(1){
		spi27_read_byte_from_reg(*byte,0x2A);
		char y = *byte;
		if (y && 0b01000000){
			break;
		}
	};
	 
	 
}

void spi27_write_cmd (char *cmd){
	status_code_genare_t write_status;

	//Add 1s to put module in COMMAND mode
	*cmd = *cmd || 0b11000000;
	
	//read byte from address
	write_status = spi_write_buffer_wait(&spi27Master, *cmd, 1);
	//set sen = 0;
	//set sen = 1;
}

void spi27_read_byte_from_reg (char *read_byte, uint8_t *reg){
	status_code_genare_t read_status;

	//Add 1 leading 0s to put module in READ mode
	*reg =+ 0b01000000;
	
	//read byte from address
	read_status = spi_transceive_buffer_wait(&spi27Master, *reg, *read_byte,  2);
	//set sen = 0;
	//set sen = 1; 
}

void spi27_write_byte_to_reg (char byte, uint8_t *reg){
	 status_code_genare_t write_status;
	 uint16_t *buf;
	 
	//Add 2 leading 0s to put module in WRITE mode
	*reg = *reg && 0b00111111;
	//prepare buffer with address and data
	*buf = *reg;
	*buf = *buf<<8;
	*buf = *buf || byte;
	
	//write byte to address
	write_status = spi_write_buffer_wait(&spi27Master, *buf, 2);
		//set sen = 0;
		//set sen = 1;
	
}

/* Function Name    : spi27_start_xfer
 * Parameters       : paramAddr (16 bit address), dir (read or write)
 * Return Values(s) : ASF general status code
 * Description      : Begins a SPI transfer with the 27 MHz module. Sends the
 *  starting address of the read/write and reads the status bits of the module.
 */
status_code_genare_t spi27_start_xfer(spiAddr27 paramAddr, xferDir27 dir)
{
    
    status_code_genare_t read_status;
    do{
        // select the slave
        read_status = spi_select_slave(&spi27Master, &spi27Slave, true);
    }while(read_status == STATUS_BUSY);
    
    /* perform a SPI transceive (write AND read). Write the param address and
     * read the status bits from the module */
    read_status = spi_transceive_buffer_wait(&spi27Master, (uint8_t*) &paramAddr, 
                    (uint8_t*) &spi27_status_bits, 2);
    
    return read_status;
}