/*
 * uart_245_driver.h
 *
 * Created: 3/23/2018 12:59:08 AM
 *  Author: Dan Filbey
 */ 


#ifndef UART_245_DRIVER_H_
#define UART_245_DRIVER_H_

#include <asf.h>
#include <stdint.h>
//#include "simsys_ringbuff.h"

#define UART245_RX_BUFF_SIZE   32 
#define UART245_TX_BUFF_SIZE   32

/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
/* Function Name    : uart245_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes the UART SERCOM for communicating with the
 *  RC2500HP.
 */
void uart245_init(void);


/* Function Name    : uart245_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Deinitializes the UART SERCOM for communicating with the
 *  RC2500HP.
 */
void uart245_deinit(void);


/* Function Name    : uart245_wait_prompt
 * Parameters       : void
 * Return Values(s) : status_code_genare_t
 * Description      : Waits for the prompt character from the RC2500HP,
 *  the '>' character. Returns a ASF status code based on the result of UART
 *  functions.
 */
status_code_genare_t uart245_wait_prompt(void);


/* Function Name    : uart245_wait_prompt
 * Parameters       : void
 * Return Values(s) : status_code_genare_t
 * Description      : Enters the config mode of the RC2500HP. Refer to pg44 of
 *  the RC2500HP datasheet for enter/exiting configuration mode. Returns a ASF 
 *  status code based on the result of UART functions.
 */
status_code_genare_t uart245_enter_config(void);


/* Function Name    : uart245_exit_config
 * Parameters       : void
 * Return Values(s) : status_code_genare_t
 * Description      : Exits the config mode of the RC2500HP. Refer to pg44 of
 *  the RC2500HP datasheet for enter/exiting configuration mode. Returns a ASF
 *  status code based on the result of UART functions.
 */
status_code_genare_t uart245_exit_config(void);


/* Function Name    : uart245_config_get_rssi
 * Parameters       : void
 * Return Values(s) : float
 * Description      : Sends an RSSI read config command to
 *  the RC2500HP, reads the output RSSI byte, converts it based on the equation
 *  on pg 51 of the RC2500HP datasheet, and returns the float.
 */
float uart245_config_get_rssi(void);


/* Function Name    : uart245_config_read_mem
 * Parameters       : mem_addr (address of config memory)
 * Return Values(s) : uint8_t
 * Description      : Reads a byte from the RC2500HP's configuration memory
 *  and returns the byte.
 */
uint8_t uart245_config_read_mem(uint8_t mem_addr);


/* Function Name    : uart245_config_wrt_mem
 * Parameters       : mem_addr (config address to write to), wrt_byte (byte to
 *                      write)
 * Return Values(s) : void
 * Description      : Writes a byte to the RC2500HP's configuration memory.
 *  Refer to page 52 of the RC2500HP's datasheet.
 */
void uart245_config_wrt_mem(uint8_t mem_addr, uint8_t wrt_byte);


/* Function Name    : uart245_config_test1
 * Parameters       : void
 * Return Values(s) : void
 * Description      : RC2500HP configuration command to put the module in test
 *  mode 1. This mode continuously transmits a carrier until another
 *  config command is received.
 */
void uart245_config_test1(void);


/* Function Name    : uart245_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Gets an RSSI value from the RC2500HP and returns
 *  it as a 2 byte int.
 */
int16_t uart245_rssi(void);

#endif /* UART_245_DRIVER_H_ */