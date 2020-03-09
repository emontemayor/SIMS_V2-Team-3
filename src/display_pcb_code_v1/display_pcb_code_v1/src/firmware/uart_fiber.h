/*
 * uart_fiber.h
 *
 * Created: 4/8/2018 4:54:14 PM
 *  Author: Dan
 */ 


#ifndef UART_FIBER_H_
#define UART_FIBER_H_


#include <asf.h>
#include "rssi_mngr.h"


void uartfiber_init(void);
void uartfiber_deinit(void);


status_code_genare_t uartfiber_get_169_rssi(rssi_t* new_rssi);
status_code_genare_t uartfiber_get_915_rssi(rssi_t* new_rssi);
status_code_genare_t uartfiber_get_245_rssi(rssi_t* new_rssi);
void uartfiber_test(void);


#endif /* UART_FIBER_H_ */