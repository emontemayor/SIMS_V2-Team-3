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

void spieeprom_init(void);

struct shield_data *get_eeprom_data_pointer(void);

void spi_eeprom_clear(void);

void spi_eeprom_enable_write(uint8_t *data, uint16_t size);

void spi_eeprom_wait(void);

void spi_eeprom_write_address(struct shield_data *address, struct shield_data *data);

struct shield_data spi_eeprom_read_address(struct shield_data *address);

bool is_timestamp_later(struct rtc_calendar_time *time1, struct rtc_calendar_time *time2);

void eeprom_find_latest_data(void);

//Writes a single shield_data instance to eeprom.
//This is the function that should be used in other files
//to put data in eeprom memory. The data will order itself.
void eeprom_write_data(struct shield_data* data);

//Retrieves the most recent data entry from the EEPROM chip.
//This behavior is undefined if eeprom_find_latest_data()
//was not called at some point before this function.
struct shield_data eeprom_read_latest_data(void);

void eeprom_read_ten_data(struct shield_data target[10], struct shield_data *address);

#endif /* SPI_EEPROM_H_ */