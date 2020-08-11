/**********************************************
 * spi_169_driver.h
 * Function definitions for the SPI driver for the AX5043
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#include "spi_169_driver.h"


/************************************************************************/
/*                                Globals                               */
/************************************************************************/
struct spi_module spi169Master;
struct spi_slave_inst spi169Slave;
bool spi169InitComp = false;
static uint16_t spi169_status_bits = 0;


/************************************************************************/
/*                                Functions                             */
/************************************************************************/
/* Function Name    : spi169_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initialize the SPI SERCOM for the 169 MHz module
 */
void spi169_init(void)
{
	if (spi169InitComp == true)
		return;
		
	struct spi_config spi169MasterConf;
	struct spi_slave_inst_config spi169SlaveConf;
	struct port_config pinConf;
	
    // initialize the slave select pin
	port_get_config_defaults(&pinConf);
    
    // get defaults for lcd master config
	spi_get_config_defaults(&spi169MasterConf);
    
    spi169MasterConf.mux_setting = SPI169_PINXMUX;
    spi169MasterConf.pinmux_pad0 = MOSI169;
    spi169MasterConf.pinmux_pad1 = SCK169;
    spi169MasterConf.pinmux_pad2 = PINMUX_UNUSED;
    spi169MasterConf.pinmux_pad3 = MISO169;
	
	// clock source should always be GLCK0
	spi169MasterConf.generator_source = SPI169_CLK;
	spi169MasterConf.mode_specific.master.baudrate = SPI169MAXCLK;

	// enable the master
	spi_init(&spi169Master, SPI169, &spi169MasterConf);
	spi_enable(&spi169Master);

	// get default configs for slave
	spi_slave_inst_get_config_defaults(&spi169SlaveConf);
	// change configs as necessary
	spi169SlaveConf.ss_pin = SS169;
	// attach the slave configs to the slave
	spi_attach_slave(&spi169Slave, &spi169SlaveConf);
    
    spi169InitComp = true;
}


/* Function Name    : spi169_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Disables the SPI SERCOM.
 */
void spi169_deinit(void)
{
    // disable it
    spi_disable(&spi169Master);
}


/* Function Name    : spi169_start_xfer
 * Parameters       : paramAddr (16 bit address), dir (read or write)
 * Return Values(s) : ASF general status code
 * Description      : Begins a SPI transfer with the 169 MHz module. Sends the
 *  starting address of the read/write and reads the status bits of the module.
 */
status_code_genare_t spi169_start_xfer(spiAddr169 paramAddr, xferDir169 dir)
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
        read_status = spi_select_slave(&spi169Master, &spi169Slave, true);
    }while(read_status == STATUS_BUSY);
    
    /* perform a SPI transceive (write AND read). Write the param address and
     * read the status bits from the module */
    read_status = spi_transceive_buffer_wait(&spi169Master, (uint8_t*) &paramAddr, 
                    (uint8_t*) &spi169_status_bits, 2);
    
    return read_status;
}


/* Function Name    : spi169_stop_xfer
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Stops a transfer, i.e. releases slave select.
 */
status_code_genare_t spi169_stop_xfer(void)
{
    // deselect slave
    return spi_select_slave(&spi169Master, &spi169Slave, false);
}


/* Function Name    : spi169_get_sbits
 * Parameters       : void
 * Return Values(s) : the status bits (16 bits)
 * Description      : Returns the status bits, updated at the start of
 *  a transfer.
 */
uint16_t spi169_get_sbits(void)
{
    return spi169_status_bits;
}


/* Function Name    : spi169_read
 * Parameters       : read_buff (buffer for reading), amount_bytes
 * Return Values(s) : ASF general status code
 * Description      : Reads a number of bytes specified by amount_bytes into
 *  read_buff. Used with spi169_start_xfer and spi169_stop_xfer().
 */
status_code_genare_t spi169_read(uint8_t* read_buff, \
    uint16_t amount_bytes)
{
    status_code_genare_t read_status;
    
    // data read
    read_status = spi_read_buffer_wait(&spi169Master, \
                    read_buff, amount_bytes, 0x0000);
    
    return read_status;
}


/* Function Name    : spi169_rd8
 * Parameters       : read_addr (address to read from)
 * Return Values(s) : a byte
 * Description      : Reads a single byte from the 169 MHz module at read_addr.
 */
uint8_t spi169_rd8(spiAddr169 read_addr)
{
    uint8_t read_byte = 0;
    
    spi169_start_xfer(read_addr, READ);
    
    // read one byte
    spi169_read(&read_byte, 1);
    
    spi169_stop_xfer();
    
    return read_byte;
}


/* Function Name    : spi169_rd16
 * Parameters       : read_addr (address to read from)
 * Return Values(s) : two bytes
 * Description      : Reads two bytes from the 169 MHz module at read_addr.
 */
uint8_t spi169_rd16(spiAddr169 read_addr)
{
    uint16_t read_byte = 0;
    
    spi169_start_xfer(read_addr, READ);
    
    // read two bytes
    spi169_read((uint8_t*) &read_byte, 2);
    
    spi169_stop_xfer();
    
    return read_byte;
    
}


/* Function Name    : spi169_write
 * Parameters       : wrt_buff (buffer for writing), amount_bytes
 * Return Values(s) : ASF general status code
 * Description      : Writes a number of bytes specified by amount_bytes to
 *  the 169 MHz module. Used with spi169_start_xfer and spi169_stop_xfer().
 */
status_code_genare_t spi169_write(uint8_t* wrt_buff, \
    uint16_t amount_bytes)
{
    status_code_genare_t wrt_status;
    
    // write to the LCD
    wrt_status = spi_write_buffer_wait(&spi169Master, \
                        wrt_buff, amount_bytes);
    
    return wrt_status;
}


/* Function Name    : spi169_wr8
 * Parameters       : wrt_addr (address to write to), wrt_byte
 * Return Values(s) : ASF general status code
 * Description      : Writes a single byte to the 169 MHz module at wrt_addr.
 */
status_code_genare_t spi169_wr8(spiAddr169 wrt_addr, uint8_t wrt_byte)
{
    status_code_genare_t status_result;
    
    spi169_start_xfer(wrt_addr, WRT);
    
    // specify the buffer length to be one byte
    status_result = spi169_write(&wrt_byte, 1);
    
    spi169_stop_xfer();
    
    return status_result;
}


/* Function Name    : spi169_wr16
 * Parameters       : wrt_addr (address to write to), wrt_byte
 * Return Values(s) : ASF general status code
 * Description      : Writes two bytes to the 169 MHz module at wrt_addr.
 */
status_code_genare_t spi169_wr16(spiAddr169 wrt_addr, uint16_t wrt_byte)
{
    status_code_genare_t status_result;
    
    spi169_start_xfer(wrt_addr, WRT);
    
    // specify the buffer length to be two byte
    status_result = spi169_write((uint8_t*) &wrt_byte, 2);
    
    spi169_stop_xfer();
    
    return status_result;
}


/* Function Name    : spi169_autorange
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Performs autoranging on the AX5043 PLL. See
 *  pg13 of the AX043 programmer's manual for more information.
 */
void spi169_autorange(void)
{
    spi169_wr8(AX5043_PLLRANGINGA, 0xFF);
    
    while(spi169_rd8(AX5043_PLLRANGINGA) & 0x10);   
    
}


/* Function Name    : spi169_tx_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes a 169 MHz module for transmitting.
 */
void spi169_tx_init(void)
{
    // set 169 MHz module to standby power mode
    spi169_wr8(AX5043_PWRMODE, 0x60 | AX5043_STANDBY);
    delay_ms(100);
    
    // register settings generated by Radiolab software
    spi169_wr8(AX5043_MODULATION, 0x08);
    spi169_wr8(AX5043_ENCODING, 0x00);
    spi169_wr8(AX5043_FRAMING, 0x06);
    spi169_wr8(AX5043_PINFUNCSYSCLK, 0x02);
    spi169_wr8(AX5043_PINFUNCDCLK, 0x02);
    spi169_wr8(AX5043_PINFUNCDATA, 0x02);
    spi169_wr8(AX5043_PINFUNCANTSEL, 0x02);
    spi169_wr8(AX5043_PINFUNCPWRAMP, 0x02);
    spi169_wr8(AX5043_WAKEUPXOEARLY, 0x01);
    spi169_wr8(AX5043_IFFREQ1, 0x06);
    spi169_wr8(AX5043_IFFREQ0, 0x66);
    spi169_wr8(AX5043_DECIMATION, 0x05);
    spi169_wr8(AX5043_RXDATARATE2, 0x05);
    spi169_wr8(AX5043_RXDATARATE1, 0x35);
    spi169_wr8(AX5043_RXDATARATE0, 0x55);
    spi169_wr8(AX5043_MAXDROFFSET2, 0x00);
    spi169_wr8(AX5043_MAXDROFFSET1, 0x00);
    spi169_wr8(AX5043_MAXDROFFSET0, 0x00);
    spi169_wr8(AX5043_MAXRFOFFSET2, 0x80);
    spi169_wr8(AX5043_MAXRFOFFSET1, 0x29);
    spi169_wr8(AX5043_MAXRFOFFSET0, 0x89);
    spi169_wr8(AX5043_FSKDMAX1, 0x22);
    spi169_wr8(AX5043_FSKDMAX0, 0xC0);
    spi169_wr8(AX5043_FSKDMIN1, 0xDD);
    spi169_wr8(AX5043_FSKDMIN0, 0x40);
    spi169_wr8(AX5043_AMPLFILTER, 0x00);
    spi169_wr8(AX5043_RXPARAMSETS, 0xF4);
    spi169_wr8(AX5043_AGCGAIN0, 0xE8);
    spi169_wr8(AX5043_AGCTARGET0, 0x84);
    spi169_wr8(AX5043_TIMEGAIN0, 0xAD);
    spi169_wr8(AX5043_DRGAIN0, 0xA7);
    spi169_wr8(AX5043_PHASEGAIN0, 0xC3);
    spi169_wr8(AX5043_FREQGAINA0, 0x0F);
    spi169_wr8(AX5043_FREQGAINB0, 0x1F);
    spi169_wr8(AX5043_FREQGAINC0, 0x0A);
    spi169_wr8(AX5043_FREQGAIND0, 0x0A);
    spi169_wr8(AX5043_AMPLGAIN0, 0x06);
    spi169_wr8(AX5043_FREQDEV10, 0x00);
    spi169_wr8(AX5043_FREQDEV00, 0x00);
    spi169_wr8(AX5043_BBOFFSRES0, 0x00);
    spi169_wr8(AX5043_AGCGAIN1, 0xE8);
    spi169_wr8(AX5043_AGCTARGET1, 0x84);
    spi169_wr8(AX5043_AGCAHYST1, 0x00);
    spi169_wr8(AX5043_AGCMINMAX1, 0x00);
    spi169_wr8(AX5043_TIMEGAIN1, 0xAB);
    spi169_wr8(AX5043_DRGAIN1, 0xA6);
    spi169_wr8(AX5043_PHASEGAIN1, 0xC3);
    spi169_wr8(AX5043_FREQGAINA1, 0x0F);
    spi169_wr8(AX5043_FREQGAINB1, 0x1F);
    spi169_wr8(AX5043_FREQGAINC1, 0x0A);
    spi169_wr8(AX5043_FREQGAIND1, 0x0A);
    spi169_wr8(AX5043_AMPLGAIN1, 0x06);
    spi169_wr8(AX5043_FREQDEV11, 0x00);
    spi169_wr8(AX5043_FREQDEV01, 0x4B);
    spi169_wr8(AX5043_FOURFSK1, 0x16);
    spi169_wr8(AX5043_BBOFFSRES1, 0x00);
    spi169_wr8(AX5043_AGCGAIN3, 0xFF);
    spi169_wr8(AX5043_AGCTARGET3, 0x84);
    spi169_wr8(AX5043_AGCAHYST3, 0x00);
    spi169_wr8(AX5043_AGCMINMAX3, 0x00);
    spi169_wr8(AX5043_TIMEGAIN3, 0xAA);
    spi169_wr8(AX5043_DRGAIN3, 0xA5);
    spi169_wr8(AX5043_PHASEGAIN3, 0xC3);
    spi169_wr8(AX5043_FREQGAINA3, 0x0F);
    spi169_wr8(AX5043_FREQGAINB3, 0x1F);
    spi169_wr8(AX5043_FREQGAINC3, 0x0D);
    spi169_wr8(AX5043_FREQGAIND3, 0x0D);
    spi169_wr8(AX5043_AMPLGAIN3, 0x06);
    spi169_wr8(AX5043_FREQDEV13, 0x00);
    spi169_wr8(AX5043_FREQDEV03, 0x4B);
    spi169_wr8(AX5043_FOURFSK3, 0x16);
    spi169_wr8(AX5043_BBOFFSRES3, 0x00);
    spi169_wr8(AX5043_MODCFGF, 0x00);
    spi169_wr8(AX5043_FSKDEV2, 0x00);
    spi169_wr8(AX5043_FSKDEV1, 0x02);
    spi169_wr8(AX5043_FSKDEV0, 0x0C);
    spi169_wr8(AX5043_MODCFGA, 0x01);
    spi169_wr8(AX5043_TXRATE2, 0x00);
    spi169_wr8(AX5043_TXRATE1, 0x04);
    spi169_wr8(AX5043_TXRATE0, 0xEA);
    spi169_wr8(AX5043_TXPWRCOEFFA1, TXPWR1); //0 = 0x207, -10 = 0x0AA
    spi169_wr8(AX5043_TXPWRCOEFFA0, TXPWR0);
    spi169_wr8(AX5043_TXPWRCOEFFB1, TXPWR1); //0 = 0x207, -10 = 0x0AA
    spi169_wr8(AX5043_TXPWRCOEFFB0, TXPWR0);
    spi169_wr8(AX5043_TXPWRCOEFFC1, TXPWR1); //0 = 0x207, -10 = 0x0AA
    spi169_wr8(AX5043_TXPWRCOEFFC0, TXPWR0);
    spi169_wr8(AX5043_TXPWRCOEFFD1, TXPWR1); //0 = 0x207, -10 = 0x0AA
    spi169_wr8(AX5043_TXPWRCOEFFD0, TXPWR0);
    spi169_wr8(AX5043_PLLVCOI, 0x8A);
    spi169_wr8(AX5043_PLLRNGCLK, 0x03);
    spi169_wr8(AX5043_BBTUNE, 0x0F);
    spi169_wr8(AX5043_BBOFFSCAP, 0x77);
    spi169_wr8(AX5043_PKTADDRCFG, 0x80);
    spi169_wr8(AX5043_PKTLENCFG, 0x00);
    spi169_wr8(AX5043_PKTLENOFFSET, 0x04);
    spi169_wr8(AX5043_PKTMAXLEN, 0xC8);
    spi169_wr8(AX5043_MATCH0PAT3, 0xAA);
    spi169_wr8(AX5043_MATCH0PAT2, 0xCC);
    spi169_wr8(AX5043_MATCH0PAT1, 0xAA);
    spi169_wr8(AX5043_MATCH0PAT0, 0xCC);
    spi169_wr8(AX5043_MATCH0LEN, 0x9F);
    spi169_wr8(AX5043_MATCH0MAX, 0x1F);
    spi169_wr8(AX5043_MATCH1PAT1, 0x55);
    spi169_wr8(AX5043_MATCH1PAT0, 0x55);
    spi169_wr8(AX5043_MATCH1LEN, 0x8A);
    spi169_wr8(AX5043_MATCH1MAX, 0x0A);
    spi169_wr8(AX5043_TMGTXBOOST, 0x32);
    spi169_wr8(AX5043_TMGTXSETTLE, 0x14);
    spi169_wr8(AX5043_TMGRXBOOST, 0x32);
    spi169_wr8(AX5043_TMGRXSETTLE, 0x14);
    spi169_wr8(AX5043_TMGRXOFFSACQ, 0x00);
    spi169_wr8(AX5043_TMGRXCOARSEAGC, 0x73);
    spi169_wr8(AX5043_TMGRXRSSI, 0x03);
    spi169_wr8(AX5043_TMGRXPREAMBLE2, 0x35);
    spi169_wr8(AX5043_RSSIABSTHR, 0xE6);
    spi169_wr8(AX5043_BGNDRSSITHR, 0x00);
    spi169_wr8(AX5043_PKTCHUNKSIZE, 0x0D);
    spi169_wr8(AX5043_PKTACCEPTFLAGS, 0x20);
    spi169_wr8(AX5043_DACVALUE1, 0x00);
    spi169_wr8(AX5043_DACVALUE0, 0x00);
    spi169_wr8(AX5043_DACCONFIG, 0x00);
    spi169_wr8(AX5043_REF, 0x03);
    spi169_wr8(AX5043_XTALOSC, 0x03);
    spi169_wr8(AX5043_XTALAMPL, 0x07);
    spi169_wr8(AX5043_0xF1C, 0x07);
    spi169_wr8(AX5043_0xF21, 0x68);
    spi169_wr8(AX5043_0xF22, 0xFF);
    spi169_wr8(AX5043_0xF23, 0x84);
    spi169_wr8(AX5043_0xF26, 0x98);
    spi169_wr8(AX5043_0xF34, 0x08);
    spi169_wr8(AX5043_0xF35, 0x10);
    spi169_wr8(AX5043_0xF44, 0x25);
    
    spi169_wr8(AX5043_PLLLOOP, 0x09);
    spi169_wr8(AX5043_PLLCPI, 0x02);
    spi169_wr8(AX5043_PLLVCODIV, 0x30);
    spi169_wr8(AX5043_XTALCAP, 0x13);
    spi169_wr8(AX5043_0xF00, 0x0F);
    spi169_wr8(AX5043_0xF18, 0x06);
    
    //set the freqeuency (169 MHz)
    spi169_wr8(AX5043_FREQA0, 0x01);
    spi169_wr8(AX5043_FREQA1, 0x00);
    spi169_wr8(AX5043_FREQA2, 0x90);
    spi169_wr8(AX5043_FREQA3, 0x0A);
    
    // wait for crystal to start
    while((spi169_rd8(AX5043_XTALSTATUS) & 0x01) != 1);
    
    // autorange the PLL once crystal has settled
    spi169_autorange();
    
    // clear the FIFO
    spi169_wr8(AX5043_FIFOSTAT, (1 << 7));

    // set to full transmit power mode
    spi169_wr8(AX5043_PWRMODE, 0x60 | AX5043_FULLTX);
    delay_ms(100);
}    