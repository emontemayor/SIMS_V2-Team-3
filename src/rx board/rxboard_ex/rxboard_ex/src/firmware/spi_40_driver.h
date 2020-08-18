/************************************************************************/
/*  initialization for SPI and USART                                    */
/*                                                                      */
/*  Author: Dan Filbey, Khang Vu                                        */
/*  Capstone project - Team 10                                          */
/************************************************************************/


#ifndef DRIVER_H_
#define DRIVER_H_

#include <asf.h>
#include <RX_PIN_DEF.h>
#include "AX5043_regs.h"
#include <stdbool.h>
#include <string.h>

/************************************************************************/
/*                                Defines                               */
/************************************************************************/
// checks that the addresses of a and b are different before XOR-ing
#define XORSWAP(a, b)   ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))
#define PKTLEN  4
#define PKTLEN_MAX ((4) + 3)


/************************************************************************/
/*                                typedefs                              */
/************************************************************************/
typedef uint16_t spiAddr40;
typedef enum xferDirType40
{
    READ, WRT
} xferDir40;

/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
/* Function Name    : spi40_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initialize the SPI SERCOM for the 40 MHz module
 */
void spi40_init(void);


/* Function Name    : spi40_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Disables the SPI SERCOM.
 */
void spi40_deinit(void);


/* Function Name    : spi40_start_xfer
 * Parameters       : paramAddr (16 bit address), dir (read or write)
 * Return Values(s) : ASF general status code
 * Description      : Begins a SPI transfer with the 40 MHz module. Sends the
 *  starting address of the read/write and reads the status bits of the module.
 */
status_code_genare_t spi40_start_xfer(spiAddr40 paramAddr, xferDir40 dir);


/* Function Name    : spi40_stop_xfer
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Stops a transfer, i.e. releases slave select.
 */
status_code_genare_t spi40_stop_xfer(void);


/* Function Name    : spi40_get_sbits
 * Parameters       : void
 * Return Values(s) : the status bits (16 bits)
 * Description      : Returns the status bits, updated at the start of
 *  a transfer.
 */
uint16_t spi40_get_sbits(void);


/* Function Name    : spi40_read
 * Parameters       : read_buff (buffer for reading), amount_bytes
 * Return Values(s) : ASF general status code
 * Description      : Reads a number of bytes specified by amount_bytes into
 *  read_buff. Used with spi40_start_xfer and spi40_stop_xfer().
 */
status_code_genare_t spi40_read(uint8_t* read_buff, uint16_t amount_bytes);


/* Function Name    : spi40_rd8
 * Parameters       : read_addr (address to read from)
 * Return Values(s) : a byte
 * Description      : Reads a single byte from the 40 MHz module at read_addr.
 */
uint8_t spi40_rd8(spiAddr40 read_addr);


/* Function Name    : spi40_rd16
 * Parameters       : read_addr (address to read from)
 * Return Values(s) : two bytes
 * Description      : Reads two bytes from the 40 MHz module at read_addr.
 */
uint8_t spi40_rd16(spiAddr40 read_addr);


/* Function Name    : spi40_write
 * Parameters       : wrt_buff (buffer for writing), amount_bytes
 * Return Values(s) : ASF general status code
 * Description      : Writes a number of bytes specified by amount_bytes to
 *  the 40 MHz module. Used with spi40_start_xfer and spi40_stop_xfer().
 */
status_code_genare_t spi40_write(uint8_t* wrt_buff, uint16_t amount_bytes);


/* Function Name    : spi40_wr8
 * Parameters       : wrt_addr (address to write to), wrt_byte
 * Return Values(s) : ASF general status code
 * Description      : Writes a single byte to the 40 MHz module at wrt_addr.
 */
status_code_genare_t spi40_wr8(spiAddr40 wrt_addr, uint8_t wrt_byte);


/* Function Name    : spi40_wr16
 * Parameters       : wrt_addr (address to write to), wrt_byte
 * Return Values(s) : ASF general status code
 * Description      : Writes two bytes to the 40 MHz module at wrt_addr.
 */
status_code_genare_t spi40_wr16(spiAddr40 wrt_addr, uint16_t wrt_byte);


/* Function Name    : spi40_autorange
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Performs autoranging on the AX5043 PLL. See
 *  pg13 of the AX043 programmer's manual for more information.
 */
void spi40_autorange(void);


/* Function Name    : spi40_rx_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes a 40 MHz module for transmitting.
 */
void spi40_rx_init(void);


/* Function Name    : spi40_rollavg
 * Parameters       : new_val (value to be added to average)
 * Return Values(s) : uint8_t
 * Description      : Performs a rolling average on 9 previous and 1 new value
 *  (10 total) and returns the average as a uint8_t.
 */
uint8_t spi40_rollavg(uint8_t new_val);


/* Function Name    : spi40_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Gets the RSSI value from the AX5043 and performs
 *  a rolling average on it. Returns the averaged RSSI as a 2 byte int.
 */
uint16_t spi40_rssi(void);


#endif /* DRIVER_H_ */