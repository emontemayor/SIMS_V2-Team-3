/*
 * uart_915_driver.h
 *
 * Created: 3/23/2018 12:58:14 AM
 *  Author: Dan Filbey
 */ 


#ifndef UART_915_DRIVER_H_
#define UART_915_DRIVER_H_

#include <asf.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define UART915_RX_BUFF_SIZE 128

/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
/* Function Name    : uart915_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes the SERCOM UART for communication with the
 *  MTXDOT module.
 */
void uart915_init(void);


/* Function Name    : uart915_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Deinitializes the SERCOM UART.
 */
void uart915_deinit(void);


/* Function Name    : configure_uart915_callbacks
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Configures the asynchronous callback function for the 
 *  UART. Callback function is executed when the receiver/transmitter 
 *  (depending on which callback is registered) receives/transmits a character.
 *  Kind of like an ISR, but executed in the actual ISR for the UART (handled
 *  by the ASF library).
 */
void configure_915uart_callbacks(void);


/* Function Name    : uart915_write_cmd
 * Parameters       : cmd_str (command string sent to MTXDOT)
 * Return Values(s) : void
 * Description      : Sends a string to the MTXDOT and waits for an 
 *  "OK\r\n" response.
 */
void uart915_write_cmd(const char* cmd_str);


/* Function Name    : uart915_get_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Gets the RSSI value from the MTXDOT and returns it as a
 *  2 byte int.
 */
int16_t uart915_get_rssi(void);


/* Function Name    : uart915_preconnect
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Sends 10 "AT" and "AT+SEND" commands to he MTXDOT module.
 *  Used during receiver initialization to ensure there is a connection between 
 *  the receiver and transmitter at start up.
 */
void uart915_preconnect(void);

#endif /* UART_915_DRIVER_H_ */