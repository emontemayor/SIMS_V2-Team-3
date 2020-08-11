/*
 * uart_fiber.h
 *
 * Created: 4/8/2018 4:54:14 PM
 *  Author: Dan
 */ 


#ifndef UART_IB_H_
#define UART_IB_H_


#include <asf.h>


void uartib_init(void);
void uartib_deinit(void);

uint8_t uartib_get_169_rssi(void);
uint8_t uartib_get_915_rssi(void);
uint8_t uartib_get_245_rssi(void);


#endif /* UART_IB_H_ */