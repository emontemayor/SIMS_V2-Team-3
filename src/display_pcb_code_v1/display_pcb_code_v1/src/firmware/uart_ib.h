/**********************************************
 * uart_ib.c
 * Header file for inter-board UART. Only
 * used by the display controller.
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#ifndef UART_IB_H_
#define UART_IB_H_


#include <asf.h>
#include "rssi_mngr.h"


/* Function Name    : uartib_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes the UART SERCOM for inter-board communication
 */
void uartib_init(void);


/* Function Name    : uartib_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Deinitializes the inter-board UART SERCOM
 */
void uartib_deinit(void);


/* Function Name    : uartib_get_169_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 169 MHz RSSI and returns it as a 2 byte int.
 */
status_code_genare_t uartib_get_169_rssi(rssi_t* new_rssi);


/* Function Name    : uartib_get_915_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 915 MHz RSSI and returns it as a 2 byte int.
 */
status_code_genare_t uartib_get_915_rssi(rssi_t* new_rssi);


/* Function Name    : uartib_get_245_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 245 MHz RSSI and returns it as a 2 byte int.
 */
status_code_genare_t uartib_get_245_rssi(rssi_t* new_rssi);


#endif /* UART_IB_H_ */