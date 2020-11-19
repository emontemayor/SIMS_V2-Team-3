/*
 * spi_eeprom.h
 *
 * Created: 8/10/2020 10:25:56 AM
 *  Author: Sander
 */ 
#include "asf.h"
#include "uart_fiber.h"


#ifndef SPI_EEPROM_H_
#define SPI_EEPROM_H_

//structs to represent the arrangement of the the SPI frame
typedef struct {
	uint8_t cmd; //command to write to memory is 0x02
	uint8_t addr_high; //top 6 bits are truncated, only the lower 2 bits will be considered
	uint8_t addr_mid;
	uint8_t addr_low;
	struct shield_data data;
} write_frame;
typedef struct {
	uint8_t cmd; //EEPROM commands are written 
	uint8_t addr_high; //top 6 bits are truncated, only the lower 2 bits will be considered
	uint8_t addr_mid;
	uint8_t addr_low;
	uint8_t;
} read_frame;

//union types to make feeding the buffer function easier

typedef union{
	write_frame frame;
	uint8_t databytes[sizeof(write_frame)];
} write_frame_union;
typedef union{
	read_frame frame;
	uint8_t databytes[sizeof(read_frame)];
} read_frame_union;

union shield_data_union{
	struct shield_data data;
	uint8_t databytes[sizeof(shield_data)];
};

/************************************************************************/
/*                           Functions                                  */
/************************************************************************/

void spieeprom_init();

//writes a single byte to the eeprom chip
//writes a byte at a time to avoid encountering the page wrap "feature" of the eeprom chip
void eeprom_write_data(struct shield_data* data);

void spi_eeprom_write_address(uint32_t address, struct shield_data *data);

struct shield_data spi_eeprom_read_address(uint32_t address);

//returns data from an address
struct shield_data eeprom_read_address(uint32_t address);

//returns true if time1 is later than time2
bool is_timestamp_later(struct rtc_calendar_time time1, struct rtc_calendar_time time2);

//returns the address of the first byte of the newest shield_data
uint32_t eeprom_find_latest_data();

#endif /* SPI_EEPROM_H_ */