/************************************************************************/
/*  initialization for SPI and USART                                    */
/*                                                                      */
/*  Author: Dan Filbey, Khang Vu                                        */
/*  Capstone project - Team 10                                          */
/************************************************************************/

#include "spi_40_driver.h"


/************************************************************************/
/*                                Globals                               */
/************************************************************************/
struct spi_module spi40Master;
struct spi_slave_inst spi40Slave;
bool spi40InitComp = false;
static uint16_t spi40_status_bits = 0;


/************************************************************************/
/*                                Functions                             */
/************************************************************************/
/* Function Name    : spi40_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initialize the SPI SERCOM for the 40 MHz module
 */
void spi40_init(void)
{
	if (spi40InitComp == true)
		return;
		
	struct spi_config spi40MasterConf;
	struct spi_slave_inst_config spi40SlaveConf;
	struct port_config pinConf;
	
    // initialize the slave select pin
	port_get_config_defaults(&pinConf);
    
    // get defaults for lcd master config
	spi_get_config_defaults(&spi40MasterConf);
    
    spi40MasterConf.mux_setting = SPI40_PINXMUX;
    spi40MasterConf.pinmux_pad0 = MOSI40;
    spi40MasterConf.pinmux_pad1 = SCK40;
    spi40MasterConf.pinmux_pad2 = PINMUX_UNUSED;
    spi40MasterConf.pinmux_pad3 = MISO40;
	
	// clock source should always be GLCK0
	spi40MasterConf.generator_source = SPI40_CLK;
	spi40MasterConf.mode_specific.master.baudrate = SPI40MAXCLK;

	// enable the master
	spi_init(&spi40Master, SPI40, &spi40MasterConf);
	spi_enable(&spi40Master);

	// get default configs for slave
	spi_slave_inst_get_config_defaults(&spi40SlaveConf);
	// change configs as necessary
	spi40SlaveConf.ss_pin = SS40;
	// attach the slave configs to the slave
	spi_attach_slave(&spi40Slave, &spi40SlaveConf);
    
    spi40InitComp = true;
}


/* Function Name    : spi40_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Disables the SPI SERCOM.
 */
void spi40_deinit(void)
{
    // disable it
    spi_disable(&spi40Master);
}


/* Function Name    : spi40_start_xfer
 * Parameters       : paramAddr (16 bit address), dir (read or write)
 * Return Values(s) : ASF general status code
 * Description      : Begins a SPI transfer with the 40 MHz module. Sends the
 *  starting address of the read/write and reads the status bits of the module.
 */
status_code_genare_t spi40_start_xfer(spiAddr40 paramAddr, xferDir40 dir)
{
    
    status_code_genare_t read_status;

    // set the upper nibble of the address to all ones
    paramAddr |= 0xF000;
    
    if(dir == READ)
    {
        //clear the MSB of the address if it's a read
        paramAddr &= 0x7FFF;
    }        
    // else leave it unchanged, because the MSB = 1 if it's a write
    
    // swap the address bytes so the most significant byte is transferred first
    paramAddr = ((paramAddr >> 8) & 0x00FF) | (paramAddr << 8);
    
    do{
        // select the slave
        read_status = spi_select_slave(&spi40Master, &spi40Slave, true);
    }while(read_status == STATUS_BUSY);
    
    /* perform a SPI transceive (write AND read). Write the param address and
     * read the status bits from the module */
    read_status = spi_transceive_buffer_wait(&spi40Master, (uint8_t*) &paramAddr, 
                    (uint8_t*) &spi40_status_bits, 2);
    
    return read_status;
}


/* Function Name    : spi40_stop_xfer
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Stops a transfer, i.e. releases slave select.
 */
status_code_genare_t spi40_stop_xfer(void)
{
    // deselect slave
    return spi_select_slave(&spi40Master, &spi40Slave, false);
}


/* Function Name    : spi40_get_sbits
 * Parameters       : void
 * Return Values(s) : the status bits (16 bits)
 * Description      : Returns the status bits, updated at the start of
 *  a transfer.
 */
uint16_t spi40_get_sbits(void)
{
    return spi40_status_bits;
}


/* Function Name    : spi40_read
 * Parameters       : read_buff (buffer for reading), amount_bytes
 * Return Values(s) : ASF general status code
 * Description      : Reads a number of bytes specified by amount_bytes into
 *  read_buff. Used with spi40_start_xfer and spi40_stop_xfer().
 */
status_code_genare_t spi40_read(uint8_t* read_buff, \
    uint16_t amount_bytes)
{
    status_code_genare_t read_status;
    
    // data read
    read_status = spi_read_buffer_wait(&spi40Master, \
                    read_buff, amount_bytes, 0x0000);
    
    return read_status;
}


/* Function Name    : spi40_rd8
 * Parameters       : read_addr (address to read from)
 * Return Values(s) : a byte
 * Description      : Reads a single byte from the 40 MHz module at read_addr.
 */
uint8_t spi40_rd8(spiAddr40 read_addr)
{
    uint8_t read_byte = 0;
    
    spi40_start_xfer(read_addr, READ);
    
    // read one byte
    spi40_read(&read_byte, 1);
    
    spi40_stop_xfer();
    
    return read_byte;
}


/* Function Name    : spi40_rd16
 * Parameters       : read_addr (address to read from)
 * Return Values(s) : two bytes
 * Description      : Reads two bytes from the 40 MHz module at read_addr.
 */
uint8_t spi40_rd16(spiAddr40 read_addr)
{
    uint16_t read_byte = 0;
    
    spi40_start_xfer(read_addr, READ);
    
    // read two bytes
    spi40_read((uint8_t*) &read_byte, 2);
    
    spi40_stop_xfer();
    
    return read_byte;
    
}


/* Function Name    : spi40_write
 * Parameters       : wrt_buff (buffer for writing), amount_bytes
 * Return Values(s) : ASF general status code
 * Description      : Writes a number of bytes specified by amount_bytes to
 *  the 40 MHz module. Used with spi40_start_xfer and spi40_stop_xfer().
 */
status_code_genare_t spi40_write(uint8_t* wrt_buff, \
    uint16_t amount_bytes)
{
    status_code_genare_t wrt_status;
    
    // write to the LCD
    wrt_status = spi_write_buffer_wait(&spi40Master, \
                        wrt_buff, amount_bytes);
    
    return wrt_status;
}


/* Function Name    : spi40_wr8
 * Parameters       : wrt_addr (address to write to), wrt_byte
 * Return Values(s) : ASF general status code
 * Description      : Writes a single byte to the 40 MHz module at wrt_addr.
 */
status_code_genare_t spi40_wr8(spiAddr40 wrt_addr, uint8_t wrt_byte)
{
    status_code_genare_t status_result;
    
    spi40_start_xfer(wrt_addr, WRT);
    
    // specify the buffer length to be one byte
    status_result = spi40_write(&wrt_byte, 1);
    
    spi40_stop_xfer();
    
    return status_result;
}


/* Function Name    : spi40_wr16
 * Parameters       : wrt_addr (address to write to), wrt_byte
 * Return Values(s) : ASF general status code
 * Description      : Writes two bytes to the 40 MHz module at wrt_addr.
 */
status_code_genare_t spi40_wr16(spiAddr40 wrt_addr, uint16_t wrt_byte)
{
    status_code_genare_t status_result;
    
    spi40_start_xfer(wrt_addr, WRT);
    
    // specify the buffer length to be two byte
    status_result = spi40_write((uint8_t*) &wrt_byte, 2);
    
    spi40_stop_xfer();
    
    return status_result;
}


/* Function Name    : spi40_autorange
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Performs autoranging on the AX5043 PLL. See
 *  pg13 of the AX043 programmer's manual for more information.
 */
void spi40_autorange(void)
{
    spi40_wr8(AX5043_PLLRANGINGA, 0x18);
    
    while(spi40_rd8(AX5043_PLLRANGINGA) & 0x10);   
    
}


/* Function Name    : spi40_rx_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes a 40 MHz module for transmitting.
 */
void spi40_rx_init(void)
{
    // set power mode to standby
    spi40_wr8(AX5043_PWRMODE, 0x60 | AX5043_STANDBY);
    delay_ms(100);
    
    spi40_wr8(AX5043_MODULATION, 0x08);
    spi40_wr8(AX5043_ENCODING, 0x00);
    spi40_wr8(AX5043_FRAMING, 0x06);
    spi40_wr8(AX5043_PINFUNCSYSCLK, 0x02);
    spi40_wr8(AX5043_PINFUNCDCLK, 0x02);
    spi40_wr8(AX5043_PINFUNCDATA, 0x02);
    spi40_wr8(AX5043_PINFUNCANTSEL, 0x02);
    spi40_wr8(AX5043_PINFUNCPWRAMP, 0x02);
    spi40_wr8(AX5043_WAKEUPXOEARLY, 0x01);
    spi40_wr8(AX5043_IFFREQ1, 0x06);
    spi40_wr8(AX5043_IFFREQ0, 0x66);
    spi40_wr8(AX5043_DECIMATION, 0x05);
    spi40_wr8(AX5043_RXDATARATE2, 0x05);
    spi40_wr8(AX5043_RXDATARATE1, 0x35);
    spi40_wr8(AX5043_RXDATARATE0, 0x55);
    spi40_wr8(AX5043_MAXDROFFSET2, 0x00);
    spi40_wr8(AX5043_MAXDROFFSET1, 0x00);
    spi40_wr8(AX5043_MAXDROFFSET0, 0x00);
    spi40_wr8(AX5043_MAXRFOFFSET2, 0x80);
    spi40_wr8(AX5043_MAXRFOFFSET1, 0x29);
    spi40_wr8(AX5043_MAXRFOFFSET0, 0x89);
    spi40_wr8(AX5043_FSKDMAX1, 0x22);
    spi40_wr8(AX5043_FSKDMAX0, 0xC0);
    spi40_wr8(AX5043_FSKDMIN1, 0xDD);
    spi40_wr8(AX5043_FSKDMIN0, 0x40);
    spi40_wr8(AX5043_AMPLFILTER, 0x00);
    spi40_wr8(AX5043_RXPARAMSETS, 0xF4);
    spi40_wr8(AX5043_AGCGAIN0, 0xE8);
    spi40_wr8(AX5043_AGCTARGET0, 0x8F); //org val: 0x84
    spi40_wr8(AX5043_AGCAHYST0, 0x00); 
    spi40_wr8(AX5043_TIMEGAIN0, 0xAD);
    spi40_wr8(AX5043_DRGAIN0, 0xA7);
    spi40_wr8(AX5043_PHASEGAIN0, 0xC3);
    spi40_wr8(AX5043_FREQGAINA0, 0x0F);
    spi40_wr8(AX5043_FREQGAINB0, 0x1F);
    spi40_wr8(AX5043_FREQGAINC0, 0x0A);
    spi40_wr8(AX5043_FREQGAIND0, 0x0A);
    spi40_wr8(AX5043_AMPLGAIN0, 0x01); //org val: 0x06
    spi40_wr8(AX5043_FREQDEV10, 0x00);
    spi40_wr8(AX5043_FREQDEV00, 0x00);
    spi40_wr8(AX5043_FOURFSK0, 0x16); //org value: 0x16
    spi40_wr8(AX5043_BBOFFSRES0, 0x00);
    spi40_wr8(AX5043_AGCGAIN1, 0xE8);
    spi40_wr8(AX5043_AGCTARGET1, 0x8F); //org val: 0x84
    spi40_wr8(AX5043_AGCAHYST1, 0x00); 
    spi40_wr8(AX5043_AGCMINMAX1, 0x00);
    spi40_wr8(AX5043_TIMEGAIN1, 0xAB);
    spi40_wr8(AX5043_DRGAIN1, 0xA6);
    spi40_wr8(AX5043_PHASEGAIN1, 0xC3);
    spi40_wr8(AX5043_FREQGAINA1, 0x0F);
    spi40_wr8(AX5043_FREQGAINB1, 0x1F);
    spi40_wr8(AX5043_FREQGAINC1, 0x0A);
    spi40_wr8(AX5043_FREQGAIND1, 0x0A);
    spi40_wr8(AX5043_AMPLGAIN1, 0x01); //org val: 0x06
    spi40_wr8(AX5043_FREQDEV11, 0x00);
    spi40_wr8(AX5043_FREQDEV01, 0x4B);
    spi40_wr8(AX5043_FOURFSK1, 0x16); //org value: 0x16
    spi40_wr8(AX5043_BBOFFSRES1, 0x00);
    spi40_wr8(AX5043_AGCGAIN3, 0xFF);
    spi40_wr8(AX5043_AGCTARGET3, 0x8F); //org val: 0x84
    spi40_wr8(AX5043_AGCAHYST3, 0x00); 
    spi40_wr8(AX5043_AGCMINMAX3, 0x00);
    spi40_wr8(AX5043_TIMEGAIN3, 0xAA);
    spi40_wr8(AX5043_DRGAIN3, 0xA5);
    spi40_wr8(AX5043_PHASEGAIN3, 0xC3);
    spi40_wr8(AX5043_FREQGAINA3, 0x0F);
    spi40_wr8(AX5043_FREQGAINB3, 0x1F);
    spi40_wr8(AX5043_FREQGAINC3, 0x0D);
    spi40_wr8(AX5043_FREQGAIND3, 0x0D);
    spi40_wr8(AX5043_AMPLGAIN3, 0x01); //org val: 0x06
    spi40_wr8(AX5043_FREQDEV13, 0x00);
    spi40_wr8(AX5043_FREQDEV03, 0x4B);
    spi40_wr8(AX5043_FOURFSK3, 0x16); //org value: 0x16
    spi40_wr8(AX5043_BBOFFSRES3, 0x00);
    spi40_wr8(AX5043_MODCFGF, 0x00);
    spi40_wr8(AX5043_FSKDEV2, 0x00);
    spi40_wr8(AX5043_FSKDEV1, 0x02);
    spi40_wr8(AX5043_FSKDEV0, 0x0C);
    spi40_wr8(AX5043_MODCFGA, 0x05);
    spi40_wr8(AX5043_TXRATE2, 0x00);
    spi40_wr8(AX5043_TXRATE1, 0x04);
    spi40_wr8(AX5043_TXRATE0, 0xEA);
    spi40_wr8(AX5043_TXPWRCOEFFB1, 0x02);
    spi40_wr8(AX5043_TXPWRCOEFFB0, 0x07);
    spi40_wr8(AX5043_PLLVCOI, 0x8A);
    spi40_wr8(AX5043_PLLRNGCLK, 0x03);
    spi40_wr8(AX5043_BBTUNE, 0x0F);
    spi40_wr8(AX5043_BBOFFSCAP, 0x77);
    spi40_wr8(AX5043_PKTADDRCFG, 0x80);
    spi40_wr8(AX5043_PKTLENCFG, 0x00);
    spi40_wr8(AX5043_PKTLENOFFSET, 0x04);
    spi40_wr8(AX5043_PKTMAXLEN, 0xC8);
    spi40_wr8(AX5043_MATCH0PAT3, 0xAA);
    spi40_wr8(AX5043_MATCH0PAT2, 0xCC);
    spi40_wr8(AX5043_MATCH0PAT1, 0xAA);
    spi40_wr8(AX5043_MATCH0PAT0, 0xCC);
    spi40_wr8(AX5043_MATCH0LEN, 0x9F);
    spi40_wr8(AX5043_MATCH0MAX, 0x1F);
    spi40_wr8(AX5043_MATCH1PAT1, 0x55);
    spi40_wr8(AX5043_MATCH1PAT0, 0x55);
    spi40_wr8(AX5043_MATCH1LEN, 0x8A);
    spi40_wr8(AX5043_MATCH1MAX, 0x0A);
    spi40_wr8(AX5043_TMGTXBOOST, 0x32);
    spi40_wr8(AX5043_TMGTXSETTLE, 0x14);
    spi40_wr8(AX5043_TMGRXBOOST, 0x32);
    spi40_wr8(AX5043_TMGRXSETTLE, 0x14);
    spi40_wr8(AX5043_TMGRXOFFSACQ, 0x00);
    spi40_wr8(AX5043_TMGRXCOARSEAGC, 0x73);
    spi40_wr8(AX5043_TMGRXRSSI, 0x03);
    spi40_wr8(AX5043_TMGRXPREAMBLE2, 0x35);
    spi40_wr8(AX5043_RSSIABSTHR, 0x84); //org val: 0xE6
    spi40_wr8(AX5043_BGNDRSSITHR, 0x84);
    spi40_wr8(AX5043_PKTCHUNKSIZE, 0x0D);
    spi40_wr8(AX5043_PKTACCEPTFLAGS, 0x20);
    spi40_wr8(AX5043_DACVALUE1, 0x00);
    spi40_wr8(AX5043_DACVALUE0, 0x00);
    spi40_wr8(AX5043_DACCONFIG, 0x00);
    spi40_wr8(AX5043_REF, 0x03);
    spi40_wr8(AX5043_XTALOSC, 0x03);
    spi40_wr8(AX5043_XTALAMPL, 0x07);
    spi40_wr8(AX5043_0xF1C, 0x07);
    spi40_wr8(AX5043_0xF21, 0x68);
    spi40_wr8(AX5043_0xF22, 0xFF);
    spi40_wr8(AX5043_0xF23, 0x84);
    spi40_wr8(AX5043_0xF26, 0x98);
    spi40_wr8(AX5043_0xF34, 0x08);
    spi40_wr8(AX5043_0xF35, 0x10);
    spi40_wr8(AX5043_0xF44, 0x25);
    
    spi40_wr8(AX5043_PLLLOOP, 0x0A);
    spi40_wr8(AX5043_PLLCPI, 0x10);
    spi40_wr8(AX5043_PLLVCODIV, 0x30); //org val = 0x30
    spi40_wr8(AX5043_XTALCAP, 0x13);
    spi40_wr8(AX5043_0xF00, 0x0F);
    spi40_wr8(AX5043_0xF18, 0x06);
    
    //set frqeuency
    spi40_wr8(AX5043_FREQA0, 0x01);
    spi40_wr8(AX5043_FREQA1, 0x00);
    spi40_wr8(AX5043_FREQA2, 0x90);
    spi40_wr8(AX5043_FREQA3, 0x0A);
    
    // Settings unique to receiver:
    spi40_wr8(AX5043_TMGRXAGC, 0x00);
    spi40_wr8(AX5043_TMGRXPREAMBLE1, 0x00);
    spi40_wr8(AX5043_PKTMISCFLAGS, 0x00 | (1 << 2)); //org value = 0x00
    
    
    // wait for crystal to settle
    while((spi40_rd8(AX5043_XTALSTATUS) & 0x01) != 1);
    
    // autorange the PLL
    spi40_autorange();
    
    // accept no invalid packets
    spi40_wr8(AX5043_PKTACCEPTFLAGS, 0x00);
    
    // append RSSI reading to end of packet
    spi40_wr8(AX5043_PKTSTOREFLAGS, 0x10);
    
    // set power mode to full receive, i.e. always receive
    spi40_wr8(AX5043_PWRMODE, 0x60 | AX5043_FULLRX);
    delay_ms(100);
    
    // clear FIFO
    spi40_wr8(AX5043_FIFOSTAT, FIFOCMD_CLRFIFO);
}


/* Function Name    : spi40_rollavg
 * Parameters       : new_val (value to be added to average)
 * Return Values(s) : uint8_t
 * Description      : Performs a rolling average on 9 previous and 1 new value
 *  (10 total) and returns the average as a uint8_t.
 */
uint8_t spi40_rollavg(uint8_t new_val)
{
    static uint8_t sample_arr[10];
    static uint8_t count;
    uint8_t i;
    uint32_t avg = 0;
    
    sample_arr[count] = new_val;
    
    count = (count + 1) % 10;
    
    for(i = 0; i < 10; i++)
    {
        avg += sample_arr[i];
    }
    
    return (avg / 10);
}


/* Function Name    : spi40_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Gets the RSSI value from the AX5043 and performs
 *  a rolling average on it. Returns the averaged RSSI as a 2 byte int.
 */
int16_t spi40_rssi(void)
{
    /* read the RSSI register, put it in the rolling average, and
     * return the new average */
    return ((int16_t) ((int8_t) spi40_rollavg(spi40_rd8(AX5043_RSSI))));
}

