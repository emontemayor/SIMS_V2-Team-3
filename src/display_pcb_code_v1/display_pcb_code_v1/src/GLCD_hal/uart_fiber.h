/*
 * uart_fiber.h
 *
 * Created: 4/8/2018 4:54:14 PM
 *  Author: Dan
 */ 


#ifndef UART_FIBER_H_
#define UART_FIBER_H_


#include <asf.h>


void uartfiber_init(void);
void uartfiber_deinit(void);


uint8_t uartfiber_get_169_rssi(void);
uint8_t uartfiber_get_915_rssi(void);
uint8_t uartfiber_get_245_rssi(void);


#endif /* UART_FIBER_H_ */