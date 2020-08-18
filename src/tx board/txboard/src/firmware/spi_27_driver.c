/**********************************************
 * spi_27_driver.h
 * Function definitions for the SPI driver for the AS3900
 *
 * Author : Emiliano Montemayor
 * Capstone Project 2019 - 2020
 **********************************************/
#include "spi_27_driver.h"
#include "AS3900_regs.h"
/*
Note: The AS3900 needs a master and a client to transmit
The transmitter board will function as the client. The
reciever will function as the master. 

*/
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
	spi27MasterConf.transfer_mode = SPI_TRANSFER_MODE_1;
	spi27MasterConf.data_order = SPI_DATA_ORDER_MSB;
	
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

void spi27_connect(){
	spi27_write_cmd(CHIP_RESET); //Reset the chip
	
	//register set up. Common data-rate, frequency deviation and communication mode must be configured in the MAIN Register of all devices which have to be paired
	spi27_write_byte_to_reg(0x00, 0x00); //set transmitter unit as client
	spi27_write_byte_to_reg(0x10, 0x04); //set wakecyc bits (wake cycle every 1 second) (pg. 25)
	spi27_write_byte_to_reg(0x81, 0x0C); //set cyctim0 bits ( cycle every 1 second) (pg. 25) and mdpt0 random pointer 
	spi27_write_byte_to_reg(0x00, 0x01); //DISABLE all timers
	spi27_write_byte_to_reg(0x02, 0x06); //set bitrate to 53 kbit per sec
	
	//write client ID
	spi27_write_byte_to_reg(0, 0x08);
	spi27_write_byte_to_reg(0, 0x09);
	spi27_write_byte_to_reg(0x02, 0x0A);
	
		int8_t test;
	test = spi27_read_byte_from_reg(0x04);
	test = spi27_read_byte_from_reg(0x06);
	
	
	//wake procedure
	spi27_write_cmd(WAKE_RX_ON); //begin wakeup call
	delay_s(1); //delay for 1 sec, listen for client
	
	//wait for wake_call interrupt, signaling wakeup signal has been identified
	while(1){
		uint8_t x = spi27_read_byte_from_reg(0x2A);
			if (x & 0b01000000){
				break;
			} 
		};
	//load data (0xFF) into dbuf
	spi27_write_byte_to_reg (0xFF,0x38); 	
	spi27_write_byte_to_reg(0x01,0x37); //set datalen to 1 in dlen
	
	//begin firstt transmission 
	spi27_write_cmd(TRANSMIT);
	
	//wait for ack_rtx interrupt, signaling ack from master (ID approved)
	while(1){
		uint8_t y = spi27_read_byte_from_reg(0x2B);
		if (y & 0b00000001){
			break;
		}
	};
	
	//if no ack is recieved, interrupt rxend is generated. The client can
	//transmit again by issuing a TRANSMIT command after a bit of a delay.
	//Otherwise if the end of this method is reached, boards are paired 
		
		//Set the transmission mode to streaming (pg. 30)
		spi27_write_byte_to_reg(0xBA,0x00);
}

uint8_t spi27_read_byte_from_reg (uint8_t reg){
	uint8_t arr = 0;
	int *read_byte = &arr;
	int value;
	
	status_code_genare_t read_status;
	int8_t *val;
	//Add 1 leading 0s to put module in READ mode
	reg = reg | 0b01000000;
	val = &reg;
	
	
	//read byte from address
	port_pin_set_output_level(SS27, true);
	//Note: added a line to ASF module to assign recieved value to buffer. 
	//ASF implementation was not working.
	read_status = spi_transceive_buffer_wait(&spi27Master, val, read_byte, 2);
	port_pin_set_output_level(SS27, false);
	return arr;
	//set sen = 0;
	//set sen = 1; 
}

void spi27_write_cmd (char cmd){
	status_code_genare_t write_status;
	int8_t *val;
	//Add 1s to put module in COMMAND mode
	cmd = cmd | 0b11000000;
	val = &cmd;
	//read byte from address
	port_pin_set_output_level(SS27, true);	
	write_status = spi_write_buffer_wait(&spi27Master,val,1);
	port_pin_set_output_level(SS27, false);	
	//set sen = 0;
	//set sen = 1;
}

uint16_t spi27_rssi(){
	uint16_t rssi;
	char *byte;
	rssi = spi27_read_byte_from_reg(0x23);
	rssi = rssi & 0x0F;
	return rssi;
}

void spi27_write_byte_to_reg (char byte, uint8_t reg){
	//address on the right, data on the left.
	
	 status_code_genare_t write_status;
	 uint16_t *buf;
	 uint16_t val; 
	 val = 0;
	
	//Add 2 leading 0s to put module in WRITE mode
	reg &= 0x3F;
	val = (byte<<8) | reg;
	
	//val = 0x5ABF;
	//prepare buffer with address and data
	buf = &val;
	//write byte to address
	port_pin_set_output_level(SS27, true);	
		spi_write_buffer_wait(&spi27Master, buf, 2);
	port_pin_set_output_level(SS27, false);	
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