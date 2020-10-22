/*
 * uart_fiber.h
 *
 * Created: Spring 2020
 *  Author: Sander Sieglaff
 */ 


#ifndef UART_FIBER_H_
#define UART_FIBER_H_


#include <asf.h>
#include "rssi_mngr.h"

//Structs used to store shield data
extern struct measurement {
	uint8_t MHz27RSSI;
	uint8_t MHz169RSSI;
	uint8_t MHz915RSSI;
	uint8_t GHz24RSSI;
	};
	
extern struct shield_data {
	struct rtc_calendar_time timestamp;
	struct measurement rssi_values;
	}shield_data;
	
	//Since the ASF buffer code seems too unnecessarily complicated we will manage our own data buffers
	//This union of data types allows easy access of our struct's data as separate bytes
union fiber_data {
		volatile struct measurement data;
		volatile uint8_t bytes[sizeof(struct measurement)];
	};
	
enum fiber_data_status {data_not_ready, data_ready, data_being_processed}fiber_data_status;



void uartfiber_init(void);
void uartfiber_deinit(void);

void fiber1_callback(void);
void fiber2_callback(void);

struct measurement get_fiber1_data(void);
enum fiber_data_status get_fiber1_status(void);

struct measurement get_fiber2_data(void);
enum fiber_data_status get_fiber2_status(void);

void reset_fiber1_status(void);
void reset_fiber2_status(void);


status_code_genare_t uartfiber_get_169_rssi(rssi_t* new_rssi);
status_code_genare_t uartfiber_get_915_rssi(rssi_t* new_rssi);
status_code_genare_t uartfiber_get_245_rssi(rssi_t* new_rssi);
void uartfiber_test(void);


#endif /* UART_FIBER_H_ */