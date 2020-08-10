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

//Struct used to store a single shield measurement
struct measurement {
	uint8_t MHz70RSSI;
	uint8_t MHz169RSSI;
	uint8_t MHz915RSSI;
	uint8_t GHz24RSSI;
	};
struct shield_data {
	struct rtc_calendar_time timestamp;
	struct measurement;
	};


void uartfiber_init(void);
void uartfiber_deinit(void);

void fiber1_callback(void);
void fiber2_callback(void);


status_code_genare_t uartfiber_get_169_rssi(rssi_t* new_rssi);
status_code_genare_t uartfiber_get_915_rssi(rssi_t* new_rssi);
status_code_genare_t uartfiber_get_245_rssi(rssi_t* new_rssi);
void uartfiber_test(void);


#endif /* UART_FIBER_H_ */