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
struct write_frame{
	uint8_t cmd; //command to write to memory is 0x02
	uint8_t addr_high; //top 6 bits are truncated, only the lower 2 bits will be considered
	uint16_t addr_low;
	uint8_t data;
};
struct read_frame{
	uint8_t cmd; //command to read from memory is 0x03
	uint8_t addr_high; //top 6 bits are truncated, only the lower 2 bits will be considered
	uint16_t addr_low;
};

//union types to make feeding the buffer function easier
union write_frame_union{
	struct write_frame frame;
	uint8_t databytes[sizeof(struct write_frame)];
};
union read_frame_union{
	struct read_frame frame;
	uint8_t databytes[sizeof(struct read_frame)];
};
union shield_data_union{
	struct shield_data data;
	uint8_t databytes[sizeof(struct shield_data)];
};

/************************************************************************/
/*                           Functions                                  */
/************************************************************************/

void spieeprom_init();

//writes a single byte to the eeprom chip
//writes a byte at a time to avoid encountering the page wrap "feature" of the eeprom chip
void eeprom_write_data(uint8_t* data[sizeof(struct shield_data)]);

//returns data from an address
struct shield_data eeprom_read_address(uint32_t address);

//returns true if time1 is later than time2
bool is_timestamp_later(struct rtc_calendar_time time1, struct rtc_calendar_time time2);

//returns the address of the first byte of the newest shield_data
uint32_t eeprom_find_latest_data();

#endif /* SPI_EEPROM_H_ */