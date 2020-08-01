/**********************************************
 * sim_system_glcd_firmware.h
 * Header for GLCD firmware drivers.
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#ifndef SIM_SYSTEM_GLCD_FIRMWARE_H_
#define SIM_SYSTEM_GLCD_FIRMWARE_H_


#include <asf.h>
#include <SIM_PIN_DEF.h>

/************************************************************************/
/*                                Defines                               */
/************************************************************************/
#define NO_PARAM 0

// checks that the addresses of a and b are different before XOR-ing
#define XORSWAP(a, b)   ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))

#define GLCD_W          800
#define GLCD_H          480

#define DEBUG_FONT      27
#define DEBUG_FONT_H    20
#define DEBUG_FONT_W    15


/************************************************************************/
/*                                typedefs                              */
/************************************************************************/
typedef uint32_t LCD_ADDRESS;

typedef enum LCD_HOST_CMD_TYPE{
    ACTIVE    = 0x00,
    STANDBY   = 0x41,
    SLEEP     = 0x42,
    PWRDOWN   = 0x43,
    PD_ROMS   = 0x49,
    CLKEXT    = 0x44,
    CLKINT    = 0x48,
    CLKSEL    = 0x61,
    RST_PULSE = 0x68,
    PINDRIVE  = 0x70,
    PIN_PD_STATE = 0x71
}LCD_HOST_CMD;

typedef enum LCD_XFER_DIR_TYPE{
    READ, WRT
} LCD_XFER_DIR;


/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
/* Function Name    : lcd_spi_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initialzize the SPI SERCOM for communicating with the LCD
 */
void lcd_spi_init(void);


/* Function Name    : lcd_spi_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Disables the LCD SPI SERCOM. For use in the FT library.
 */
void lcd_spi_deinit(void);


/* Function Name    : lcd_start_xfer
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Starts the SPI transfer by selecting the slave (pulling 
 *  CS low) and sending LCD address. For use in the FT library.
 */
status_code_genare_t lcd_start_xfer(LCD_ADDRESS param_addr, LCD_XFER_DIR dir);


/* Function Name    : lcd_stop_xfer
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Stops the SPI transfer by deselecting the slave (letting 
 *  CS float high). For use in the FT library.
 */
status_code_genare_t lcd_stop_xfer(void);


/* Function Name    : lcd_host_read
 * Parameters       : read_addr (22-bit address), read_buff (pointer to
 *					  the buffer), amount_bytes (length of buffer)
 * Return Values(s) : ASF general status code
 * Description      : Reads a given amount of bytes to the LCD.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 *  Refer to DS_FT81x datasheet pg 15.
 */
status_code_genare_t lcd_host_read(uint8_t* read_buff, \
uint16_t amount_bytes);


/* Function Name    : lcd_rd8
 * Parameters       : read_addr (22-bit address)
 * Return Values(s) : uint8_t
 * Description      : Reads a 8-bit value from the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
uint8_t lcd_rd8(LCD_ADDRESS read_addr);


/* Function Name    : lcd_rd16
 * Parameters       : read_addr (22-bit address)
 * Return Values(s) : uint16_t
 * Description      : Reads a 16-bit value from the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
uint16_t lcd_rd16(LCD_ADDRESS read_addr);


/* Function Name    : lcd_rd32
 * Parameters       : read_addr (22-bit address)
 * Return Values(s) : uint32_t
 * Description      : Reads a 32-bit value from the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
uint32_t lcd_rd32(LCD_ADDRESS read_addr);


/* Function Name    : lcd_host_write
 * Parameters       : wrt_addr (22-bit address), wrt_buff (pointer to
 *					  the buffer), amount_bytes (length of buffer)
 * Return Values(s) : ASF general status code
 * Description      : Writes a given amount of bytes to the LCD. 
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 *  Refer to DS_FT81x datasheet pg 16.
 */
status_code_genare_t lcd_host_write(uint8_t* wrt_buff, \
uint16_t amount_bytes);


/* Function Name    : lcd_wr8
 * Parameters       : wrt_addr (22-bit address), wrt_word (8-bit byte to write)
 * Return Values(s) : ASF general status code
 * Description      : Writes a 8-bit value to the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
status_code_genare_t lcd_wr8(LCD_ADDRESS wrt_addr, uint8_t wrt_byte);


/* Function Name    : lcd_wr16
 * Parameters       : wrt_addr (22-bit address), wrt_word (16-bit word 
 *					  to write)
 * Return Values(s) : ASF general status code
 * Description      : Writes a 16-bit value to the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
status_code_genare_t lcd_wr16(LCD_ADDRESS wrt_addr, uint16_t wrt_word);


/* Function Name    : lcd_wr32
 * Parameters       : wrt_addr (22-bit address), wrt_dword (32-bit double word
 *					  to write)
 * Return Values(s) : ASF general status code
 * Description      : Writes a 32-bit value to the LCD at the given address.
 *  Used in combination with lcd_start_xfer() and lcd_stop_xfer().
 */
status_code_genare_t lcd_wr32(LCD_ADDRESS wrt_addr, uint32_t wrt_dword);


/* Function Name    : lcd_host_cmd
 * Parameters       : cmd (host command type), param_byte (command parameter
 *                    if necessary)
 * Return Values(s) : ASF general status code
 * Description      : Sends a host command to the LCD. Host commands are
 *  for basic hardware configurations (like power mode, clock stuff, etc.).
 *  Refer to DS-FT81x datasheet pg 16 if the command has a parameter byte.
 */
status_code_genare_t lcd_host_cmd(uint8_t cmd, uint8_t param_byte);


/* Function Name    : lcd_powerdown
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Pull down the LCD_PD pin to force power down the LCD
 */
void lcd_powerdown(void);


/* Function Name    : lcd_powerup
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Pull up the LCD_PD pin to force power up the LCD
 */
void lcd_powerup(void);

#endif /* SIM_SYSTEM_GLCD_FIRMWARE_H_ */