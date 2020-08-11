/**********************************************
 * spi_27_driver.h
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
typedef uint16_t spiAddr27;

typedef enum xferDirType27{
	READ, WRT
}xferDir27;

/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
// init spi
/* Function Name    : spi27_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initialize the SPI SERCOM for the 27 MHz module
 */
void spi27_init(void);


/* Function Name    : spi27_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Disables the SPI SERCOM.
 */
void spi27_deinit(void);


// spi27 spi transfer related functions:
/* Function Name    : spi27_start_xfer
 * Parameters       : paramAddr (16 bit address), dir (read or write)
 * Return Values(s) : ASF general status code
 * Description      : Begins a SPI transfer with the 27 MHz module. Sends the
 *  starting address of the read/write and reads the status bits of the module.
 */
status_code_genare_t spi27_start_xfer(spiAddr27 paramAddr, xferDir27 dir);


/* Function Name    : spi27_stop_xfer
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Stops a transfer, i.e. releases slave select.
 */
status_code_genare_t spi27_stop_xfer(void);


/* Function Name    : spi27_get_sbits
 * Parameters       : void
 * Return Values(s) : the status bits (16 bits)
 * Description      : Returns the status bits, updated at the start of
 *  a transfer.
 */
uint16_t spi27_get_sbits(void);


// spi27 read functions:
/* Function Name    : spi27_read
 * Parameters       : read_buff (buffer for reading), amount_bytes
 * Return Values(s) : ASF general status code
 * Description      : Reads a number of bytes specified by amount_bytes into
 *  read_buff. Used with spi27_start_xfer and spi27_stop_xfer().
 */
status_code_genare_t spi27_read(uint8_t* read_buff, uint16_t amount_bytes);


/* Function Name    : spi27_rd8
 * Parameters       : read_addr (address to read from)
 * Return Values(s) : a byte
 * Description      : Reads a single byte from the 27 MHz module at read_addr.
 */
uint8_t spi27_rd8(spiAddr27 read_addr);


/* Function Name    : spi27_rd16
 * Parameters       : read_addr (address to read from)
 * Return Values(s) : two bytes
 * Description      : Reads two bytes from the 27 MHz module at read_addr.
 */
uint8_t spi27_rd16(spiAddr27 read_addr);


// spi27 write functions:
/* Function Name    : spi27_write
 * Parameters       : wrt_buff (buffer for writing), amount_bytes
 * Return Values(s) : ASF general status code
 * Description      : Writes a number of bytes specified by amount_bytes to
 *  the 27 MHz module. Used with spi27_start_xfer and spi27_stop_xfer().
 */
status_code_genare_t spi27_write(uint8_t* wrt_buff, uint16_t amount_bytes);


/* Function Name    : spi27_wr8
 * Parameters       : wrt_addr (address to write to), wrt_byte
 * Return Values(s) : ASF general status code
 * Description      : Writes a single byte to the 27 MHz module at wrt_addr.
 */
status_code_genare_t spi27_wr8(spiAddr27 wrt_addr, uint8_t wrt_byte);


/* Function Name    : spi27_wr16
 * Parameters       : wrt_addr (address to write to), wrt_byte
 * Return Values(s) : ASF general status code
 * Description      : Writes two bytes to the 27 MHz module at wrt_addr.
 */
status_code_genare_t spi27_wr16(spiAddr27 wrt_addr, uint16_t wrt_byte);


/* Function Name    : spi27_autorange
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Performs autoranging on the AX5043 PLL. See
 *  pg13 of the AX043 programmer's manual for more information.
 */
void spi27_autorange(void);


/* Function Name    : spi27_tx_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes a 27 MHz module for transmitting.
 */
void spi27_tx_init(void);

/* Function Name    : spi27_connect
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes a 27 MHz module for transmitting.
 */
void spi27_connect(void);

#endif /* DRIVER_H_ */