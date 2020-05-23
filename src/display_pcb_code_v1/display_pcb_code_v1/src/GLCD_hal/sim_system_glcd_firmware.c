/**********************************************
 * sim_system_glcd_firmware.c
 * Function definitions for SPI drivers
 * and other firmware for the GLCD.
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#include "sim_system_glcd_firmware.h"
#undef ENABLE


/************************************************************************/
/*                                Changes from original                 */
/************************************************************************/
/*
1. Changes to SPI init. Changed to manually initializing SPI rather
	than utilizing ASF functions.
2. Changed SPI

*/


/************************************************************************/
/*                                Globals                               */
/************************************************************************/
struct spi_module lcd_master;
struct spi_slave_inst lcd_slave;
bool lcd_init_complete = false;


/************************************************************************/
/*                                Functions                             */
/************************************************************************/
/* Function Name    : lcd_spi_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initialize the SPI SERCOM for communicating with the LCD
 */
void lcd_spi_init(void)
{
    if(lcd_init_complete == true)
        return;
    
    // initialize struct for master config
    struct spi_config lcd_init_master_config;
    // initialize struct for slave config
    struct spi_slave_inst_config lcd_init_slave_config;
    // initialize card detect pin
    struct port_config pin_conf;

    // get default configs for slave
    spi_slave_inst_get_config_defaults(&lcd_init_slave_config);
    // change configs as necessary
    lcd_init_slave_config.ss_pin = LCD_CS;
    // attach the slave configs to the slave
    spi_attach_slave(&lcd_slave, &lcd_init_slave_config);
    
	
	// initialize the slave select pin
    //port_get_config_defaults(&pin_conf); commented out because 
    
	
	
    // get defaults for lcd master config
    spi_get_config_defaults(&lcd_init_master_config);

    lcd_init_master_config.mux_setting = LCD_PINMUX_SETTING;
    lcd_init_master_config.pinmux_pad0 = LCD_MISO_PAD;
    lcd_init_master_config.pinmux_pad1 = LCD_UNUSED; 
    lcd_init_master_config.pinmux_pad2 = LCD_MOSI_PAD;
    lcd_init_master_config.pinmux_pad3 = LCD_SCK_PAD;
    
	
	
    //clock source should always be GLCK0
	lcd_init_master_config.generator_source = LCD_SPI_SOURCE_CLOCK;
	lcd_init_master_config.mode_specific.master.baudrate = LCD_SPI_MAX_CLOCK;
    
	// enable the master
    spi_init(&lcd_master, LCD_SPI, &lcd_init_master_config);
    spi_enable(&lcd_master);
	

    
    lcd_init_complete = true;
}


/* Function Name    : lcd_spi_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Disables the LCD SPI SERCOM. For use in the FT library.
 */
void lcd_spi_deinit(void)
{
    // disable it
    spi_disable(&lcd_master);
}


/* Function Name    : lcd_start_xfer
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Starts the SPI transfer by selecting the slave (pulling 
 *  CS low) and sending LCD address. For use in the FT library.
 */
status_code_genare_t lcd_start_xfer(LCD_ADDRESS param_addr, LCD_XFER_DIR dir)
{
    union{
        LCD_ADDRESS addr;
        uint8_t preamble[4];
    } lcd_xfer_preamble;
    
    status_code_genare_t read_status;
    
    if(dir == READ)
        // LCD read address should only be 22 bits
        lcd_xfer_preamble.addr = (0x3FFFFF & param_addr) << 8;
    else if(dir == WRT)
        /* LCD read address should only be 22 bits. Also OR 0x800000 because the
         * host must send a 1-bit and then a 0-bit to indicate a write */
         lcd_xfer_preamble.addr = ((0x3FFFFF & param_addr) | 0x800000) << 8;
    
    // preamble bytes need to be swapped so MSB is transmitted first
    XORSWAP(lcd_xfer_preamble.preamble[0], lcd_xfer_preamble.preamble[3]);
    XORSWAP(lcd_xfer_preamble.preamble[1], lcd_xfer_preamble.preamble[2]);
    
    do{
        // select the slave
        read_status = spi_select_slave(&lcd_master, &lcd_slave, true);
    }while(read_status == STATUS_BUSY);
    
    if(dir == READ)
        // send preamble = two read bits, 22 bit address, and dummy byte
        read_status = spi_write_buffer_wait(&lcd_master, lcd_xfer_preamble.preamble, 4);
    else if(dir == WRT)
        // send preamble = two wrt bits and 22 bit address
        read_status = spi_write_buffer_wait(&lcd_master, lcd_xfer_preamble.preamble, 3);
    
    return read_status;
}


/* Function Name    : lcd_stop_xfer
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Stops the SPI transfer by deselecting the slave (letting 
 *  CS float high). For use in the FT library.
 */
status_code_genare_t lcd_stop_xfer(void)
{
    // deselect slave
    return spi_select_slave(&lcd_master, &lcd_slave, false);
}


/* Function Name    : lcd_host_read
 * Parameters       : read_addr (22-bit address), read_buff (pointer to
 *					  the buffer), amount_bytes (length of buffer)
 * Return Values(s) : ASF general status code
 * Description      : Reads a given amount of bytes to the LCD.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 *  Refer to DS_FT81x datasheet pg 15.
 */
status_code_genare_t lcd_host_read(uint8_t* read_buff, \
    uint16_t amount_bytes)
{
    status_code_genare_t read_status;
    
    // data read
    read_status = spi_read_buffer_wait(&lcd_master, \
                        read_buff, amount_bytes, 0x0000);
    
    return read_status;
}


/* Function Name    : lcd_rd8
 * Parameters       : read_addr (22-bit address)
 * Return Values(s) : uint8_t
 * Description      : Reads a 8-bit value from the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
uint8_t lcd_rd8(LCD_ADDRESS read_addr)
{
    uint8_t read_byte = 0;
    
    lcd_start_xfer(read_addr, READ);
    
    // specify the buffer length to be one byte
    lcd_host_read(&read_byte, 1);
    
    lcd_stop_xfer();
    
    return read_byte; 
}


/* Function Name    : lcd_rd16
 * Parameters       : read_addr (22-bit address)
 * Return Values(s) : uint16_t
 * Description      : Reads a 16-bit value from the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
uint16_t lcd_rd16(LCD_ADDRESS read_addr)
{
    uint16_t read_word = 0;
    
    lcd_start_xfer(read_addr, READ);
    
    // cast the word pointer to an 8-bit pointer and use a 2 byte length
    lcd_host_read((uint8_t*) &read_word, 2);
    
    lcd_stop_xfer();
    
    return read_word;
}    


/* Function Name    : lcd_rd32
 * Parameters       : read_addr (22-bit address)
 * Return Values(s) : uint32_t
 * Description      : Reads a 32-bit value from the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
uint32_t lcd_rd32(LCD_ADDRESS read_addr)
{
    uint32_t read_dword = 0;
    
    lcd_start_xfer(read_addr, READ);
    
    // cast the dword pointer to an 8-bit pointer and use a 4 byte length
    lcd_host_read((uint8_t*) &read_dword, 4);
    
    lcd_stop_xfer();
    
    return read_dword;
}


/* Function Name    : lcd_host_write
 * Parameters       : wrt_addr (22-bit address), wrt_buff (pointer to
 *					  the buffer), amount_bytes (length of buffer)
 * Return Values(s) : ASF general status code
 * Description      : Writes a given amount of bytes to the LCD. 
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 *  Refer to DS_FT81x datasheet pg 16.
 */
status_code_genare_t lcd_host_write(uint8_t* wrt_buff, \
    uint16_t amount_bytes)
{
    status_code_genare_t wrt_status;
    
    // write to the LCD
    wrt_status = spi_write_buffer_wait(&lcd_master, \
                        wrt_buff, amount_bytes);
    
    return wrt_status;
    
}


/* Function Name    : lcd_wr8
 * Parameters       : wrt_addr (22-bit address), wrt_word (8-bit byte to write)
 * Return Values(s) : ASF general status code
 * Description      : Writes a 8-bit value to the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
status_code_genare_t lcd_wr8(LCD_ADDRESS wrt_addr, uint8_t wrt_byte)
{
    status_code_genare_t status_result;
    
    lcd_start_xfer(wrt_addr, WRT);    
    
    // specify the buffer length to be one byte
    status_result = lcd_host_write(&wrt_byte, 1);
    
    lcd_stop_xfer();
    
    return status_result;
}


/* Function Name    : lcd_wr16
 * Parameters       : wrt_addr (22-bit address), wrt_word (16-bit word 
 *					  to write)
 * Return Values(s) : ASF general status code
 * Description      : Writes a 16-bit value to the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
status_code_genare_t lcd_wr16(LCD_ADDRESS wrt_addr, uint16_t wrt_word)
{
    status_code_genare_t status_result;
    
    lcd_start_xfer(wrt_addr, WRT);
    
    // cast the word pointer to an 8-bit pointer and use a 2 byte length
    status_result = lcd_host_write((uint8_t*) &wrt_word, 2);
    
    lcd_stop_xfer();
    
    return status_result;
}


/* Function Name    : lcd_wr32
 * Parameters       : wrt_addr (22-bit address), wrt_dword (32-bit double word
 *					  to write)
 * Return Values(s) : ASF general status code
 * Description      : Writes a 32-bit value to the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
status_code_genare_t lcd_wr32(LCD_ADDRESS wrt_addr, uint32_t wrt_dword)
{
    status_code_genare_t status_result;
    
    lcd_start_xfer(wrt_addr, WRT);
    
    // cast the dword pointer to an 8-bit pointer and use a 4 byte length
    status_result = lcd_host_write((uint8_t *) &wrt_dword, 4);
    
    lcd_stop_xfer();
    
    return status_result;
}


/* Function Name    : lcd_host_cmd
 * Parameters       : cmd (host command type), param_byte (command parameter
 *                    if necessary)
 * Return Values(s) : ASF general status code
 * Description      : Sends a host command to the LCD. Host commands are
 *  for basic hardware configurations (like power mode, clock stuff, etc.).
 *  Refer to DS-FT81x datasheet pg 16 if the command has a parameter byte.
 */
status_code_genare_t lcd_host_cmd(uint8_t cmd, uint8_t param_byte)
{
    // variable for holding ASF status code
    status_code_genare_t wrt_status;
    
    // 3 byte array for sending host command to the LCD
    uint8_t cmd_packet[3] = {cmd, param_byte, 0x00};
   
    // select the slave
    do{
        // select the slave
        wrt_status = spi_select_slave(&lcd_master, &lcd_slave, true);
		//port_pin_set_output_level(PIN_PA10, true);
    }while(wrt_status == STATUS_BUSY);
    
    // send host command
    wrt_status = spi_write_buffer_wait(&lcd_master, cmd_packet, 3);

    // status check
    if(wrt_status != STATUS_OK)
    {
        // deselect slave
        lcd_stop_xfer();
        // return an error
        return wrt_status;
    }
    else
        // deselect slave
        wrt_status = lcd_stop_xfer();
    
    return wrt_status;
}


/* Function Name    : lcd_powerdown
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Pull down the LCD_PD pin to force power down the LCD
 */
void lcd_powerdown(void)
{
    port_pin_set_output_level(LCD_PD, LCD_PD_EN);
}


/* Function Name    : lcd_powerup
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Pull up the LCD_PD pin to force power up the LCD
 */
void lcd_powerup(void)
{
    port_pin_set_output_level(LCD_PD, LCD_PD_DIS);
}


