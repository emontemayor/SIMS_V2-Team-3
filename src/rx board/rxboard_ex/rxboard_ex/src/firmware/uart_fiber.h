/**********************************************
 * uart_fiber.h
 * Header for the UART driver for the fiber optic
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#ifndef UART_FIBER_H_
#define UART_FIBER_H_


#include <asf.h>
#include <stdarg.h>
#include <string.h>
#include "rssi_mngr.h"

//Struct used to store a single shield measurement
struct measurement {
	uint8_t MHz70RSSI;
	uint8_t MHz169RSSI;
	uint8_t MHz915RSSI;
	uint8_t GHz24RSSI;
};
struct fiber_packet {
	const uint8_t head = '$';
	struct measurement data;
	const uint8_t tail = '\r';
};


/* Function Name    : uartfiber_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes the UART SERCOM for communicating over 
 *  fiber optic.
 */
void uartfiber_init(void);


/* Function Name    : uartfiber_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Deinitializes the UART.
 */
void uartfiber_deinit(void);


/* Function Name    : uartib_get_169_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 169 MHz RSSI and returns it as a 2 byte int.
 */
int16_t uartib_get_169_rssi(void);

/** 
 * Asynchronous buffer write to transmit single shield measurement
 * Simply calls "usart_write_buffer_job" with specific parameters
 */
void usart_fiber_write(struct measurement temp);


/* Function Name    : uartib_get_915_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 915 MHz RSSI and returns it as a 2 byte int.
 */
int16_t uartib_get_915_rssi(void);


/* Function Name    : uartib_get_245_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 245 MHz RSSI and returns it as a 2 byte int.
 */
int16_t uartib_get_245_rssi(void);


/* Function Name    : configure_uartfiber_callbacks
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Configures the asynchronous callback function for the
 *  UART. Callback function is executed when the receiver/transmitter
 *  (depending on which callback is registered) receives/transmits a character.
 *  Kind of like an ISR, but executed in the actual ISR for the UART (handled
 *  by the ASF library).
 */
void configure_uartfiber_callbacks(void);


/* Function Name    : uartfiber_printf
 * Parameters       : fmt (formatted string), ... (vargs)
 * Return Values(s) : void
 * Description      : Printf function for this UART. Used as a debug terminal.
 */
void uartfiber_printf(const char *fmt, ...) __attribute__((format(printf, 1, 0)));


/* Function Name    : uartfiber_init_rssi
 * Parameters       : user_rssi (rssi_vals struct from rssi_mngr.h)
 * Return Values(s) : void
 * Description      : Initializes the local rssi_vals struct (uartfiber_rssi)
 *  to a user defined rssi_vals struct (user_rssi). Thus, user can change the
 *  values of user_rssi elsewhere and the changes will be reflected when the 
 *  display controller sends the rssi polling commands over the fiber optic.
 */
void uartfiber_init_rssi(rssi_vals* user_rssi);

#endif /* UART_FIBER_H_ */