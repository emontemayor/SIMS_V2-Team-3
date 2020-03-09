/**********************************************
 * spi_169_driver.h
 * Header for the SPI driver for the AX5043
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#ifndef DRIVER_H_
#define DRIVER_H_

#include <asf.h>
#include <txPinDef.h>
#include "AX5043_regs.h"

/************************************************************************/
/*                                Defines                               */
/************************************************************************/
// checks that the addresses of a and b are different before XOR-ing
#define XORSWAP(a, b)   ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))
#define TXPWR1  0x0F
#define TXPWR0  0xFF

/************************************************************************/
/*                                typedefs                              */
/************************************************************************/
typedef uint16_t spiAddr169;

typedef enum xferDirType169{
	READ, WRT
}xferDir169;

/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
// init spi
/* Function Name    : spi169_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initialize the SPI SERCOM for the 169 MHz module
 */
void spi169_init(void);


/* Function Name    : spi169_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Disables the SPI SERCOM.
 */
void spi169_deinit(void);


// spi169 spi transfer related functions:
/* Function Name    : spi169_start_xfer
 * Parameters       : paramAddr (16 bit address), dir (read or write)
 * Return Values(s) : ASF general status code
 * Description      : Begins a SPI transfer with the 169 MHz module. Sends the
 *  starting address of the read/write and reads the status bits of the module.
 */
status_code_genare_t spi169_start_xfer(spiAddr169 paramAddr, xferDir169 dir);


/* Function Name    : spi169_stop_xfer
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Stops a transfer, i.e. releases slave select.
 */
status_code_genare_t spi169_stop_xfer(void);


/* Function Name    : spi169_get_sbits
 * Parameters       : void
 * Return Values(s) : the status bits (16 bits)
 * Description      : Returns the status bits, updated at the start of
 *  a transfer.
 */
uint16_t spi169_get_sbits(void);


// spi169 read functions:
/* Function Name    : spi169_read
 * Parameters       : read_buff (buffer for reading), amount_bytes
 * Return Values(s) : ASF general status code
 * Description      : Reads a number of bytes specified by amount_bytes into
 *  read_buff. Used with spi169_start_xfer and spi169_stop_xfer().
 */
status_code_genare_t spi169_read(uint8_t* read_buff, uint16_t amount_bytes);


/* Function Name    : spi169_rd8
 * Parameters       : read_addr (address to read from)
 * Return Values(s) : a byte
 * Description      : Reads a single byte from the 169 MHz module at read_addr.
 */
uint8_t spi169_rd8(spiAddr169 read_addr);


/* Function Name    : spi169_rd16
 * Parameters       : read_addr (address to read from)
 * Return Values(s) : two bytes
 * Description      : Reads two bytes from the 169 MHz module at read_addr.
 */
uint8_t spi169_rd16(spiAddr169 read_addr);


// spi169 write functions:
/* Function Name    : spi169_write
 * Parameters       : wrt_buff (buffer for writing), amount_bytes
 * Return Values(s) : ASF general status code
 * Description      : Writes a number of bytes specified by amount_bytes to
 *  the 169 MHz module. Used with spi169_start_xfer and spi169_stop_xfer().
 */
status_code_genare_t spi169_write(uint8_t* wrt_buff, uint16_t amount_bytes);


/* Function Name    : spi169_wr8
 * Parameters       : wrt_addr (address to write to), wrt_byte
 * Return Values(s) : ASF general status code
 * Description      : Writes a single byte to the 169 MHz module at wrt_addr.
 */
status_code_genare_t spi169_wr8(spiAddr169 wrt_addr, uint8_t wrt_byte);


/* Function Name    : spi169_wr16
 * Parameters       : wrt_addr (address to write to), wrt_byte
 * Return Values(s) : ASF general status code
 * Description      : Writes two bytes to the 169 MHz module at wrt_addr.
 */
status_code_genare_t spi169_wr16(spiAddr169 wrt_addr, uint16_t wrt_byte);


/* Function Name    : spi169_autorange
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Performs autoranging on the AX5043 PLL. See
 *  pg13 of the AX043 programmer's manual for more information.
 */
void spi169_autorange(void);


/* Function Name    : spi169_tx_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes a 169 MHz module for transmitting.
 */
void spi169_tx_init(void);


#endif /* DRIVER_H_ */