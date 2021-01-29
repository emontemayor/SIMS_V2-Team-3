/*
 * spi_eeprom.c
 *
 * Created: 8/10/2020 10:18:52 AM
 *  Author: Sander Sieglaff
 * Contains functions to interact with the EEPROM chip on the control unit for non-volatile long term data storage
 */ 
#include "SIM_PIN_DEF.h"
#include "spi_eeprom.h"

// Pointer to track current write location in memory.
struct shield_data *eeprom_data_pointer;

// ASF instance of SPI SERCOM module
static struct spi_module spieeprom_inst;

void spieeprom_init()
{
	struct spi_config config_spi;
	spi_get_config_defaults(&config_spi);
	config_spi.mux_setting = EEPROM_PINMUX;
	config_spi.pinmux_pad0 = EEPROM_MISO;
	config_spi.pinmux_pad1 = PINMUX_UNUSED;
	config_spi.pinmux_pad2 = EEPROM_MOSI;
	config_spi.pinmux_pad3 = EEPROM_SCK;
	config_spi.transfer_mode = SPI_TRANSFER_MODE_3;
	config_spi.generator_source = SPI_EEPROM_CLOCK_SOURCE;
	config_spi.mode_specific.master.baudrate = SPI_EEPROM_MAX_CLOCK;
	
	spi_init(&spieeprom_inst, SPI_EEPROM, &config_spi);
	spi_enable(&spieeprom_inst);
	
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(EEPROM_CS, &config_port_pin);
	port_pin_set_config(EEPROM_WP, &config_port_pin);
	port_pin_set_config(EEPROM_HOLD, &config_port_pin);
	
	port_pin_set_output_level(EEPROM_CS, 1);
	port_pin_set_output_level(EEPROM_WP, 1);
	port_pin_set_output_level(EEPROM_HOLD, 1);
	
	eeprom_data_pointer = 0x20EC23F5;
	
	
	//update pointer with most recent write address
	//eeprom_data_pointer = eeprom_find_latest_data();
}

struct shield_data *get_eeprom_data_pointer(void)
{
	return eeprom_data_pointer;
}

//zeros out the memory in the eeprom chip
void spi_eeprom_clear()
{
	typedef struct {
		uint8_t cmd;
		uint8_t addr_high;
		uint8_t addr_mid;
		uint8_t addr_low;
		uint8_t bytes[256];
	} clear_frame;
	clear_frame frame = {0};
	frame.cmd = EEPROM_WRITE;
	
	for(uint16_t row = 0; row < 0x400; row++)
	{
		frame.addr_high = (row >> 8) & 0x3;
		frame.addr_mid = row & 0xFF;
		spi_eeprom_enable_write(&frame, sizeof(clear_frame));
	}
}

//writes data of size to the eeprom chip following the chip's data write enable procedure
void spi_eeprom_enable_write(uint8_t *data, uint8_t size)
{
	spi_eeprom_wait();
	
	uint8_t command = EEPROM_WREN;
	port_pin_set_output_level(EEPROM_CS, 0);
	spi_write_buffer_wait(&spieeprom_inst, &command, 1);
	port_pin_set_output_level(EEPROM_CS, 1);
	
	spi_eeprom_wait();
	
	port_pin_set_output_level(EEPROM_CS, 0);
	spi_write_buffer_wait(&spieeprom_inst, data, size);
	port_pin_set_output_level(EEPROM_CS, 1);
}

//waits until eeprom chip says it is done with the write cycle
void spi_eeprom_wait()
{
	struct command_frame 
	{
		uint8_t command;
		uint8_t data;
	};
	struct command_frame command_data;
	command_data.command = EEPROM_RDSR;
	do
	{
		port_pin_set_output_level(EEPROM_CS, 0);
		spi_transceive_buffer_wait(&spieeprom_inst, &command_data, &command_data, sizeof(struct command_frame));
		port_pin_set_output_level(EEPROM_CS, 1);
	} while((command_data.data & 1) == 1);
}

//writes shield data to a specific address
void spi_eeprom_write_address(struct shield_data *address, struct shield_data *data)
{
	write_frame_union curr_frame;
	curr_frame.frame.cmd = EEPROM_WRITE;
	curr_frame.frame.addr_high = (((uint32_t) address) >> 16) & 0x3;
	curr_frame.frame.addr_mid = (((uint32_t) address) >> 8) & 0xFF;
	curr_frame.frame.addr_low = ((uint32_t) address) & 0xFF;
	memcpy(&curr_frame.frame.data, data, sizeof(struct shield_data));
	spi_eeprom_enable_write(&curr_frame.databytes, sizeof(write_frame_union));
}

//reads shield data from a specific address
struct shield_data spi_eeprom_read_address(struct shield_data *address)
{
	struct shield_data ret_data;
	write_frame_union curr_frame;
	curr_frame.frame.cmd = EEPROM_READ;
	curr_frame.frame.addr_high = (((uint32_t) address) >> 16) & 0x3;
	curr_frame.frame.addr_mid = (((uint32_t) address) >> 8) & 0xFF;
	curr_frame.frame.addr_low = ((uint32_t) address) & 0xFF;
	spi_eeprom_wait();
	port_pin_set_output_level(EEPROM_CS, 0);
	spi_transceive_buffer_wait(&spieeprom_inst, &curr_frame.databytes, &curr_frame.databytes, sizeof(write_frame_union));
	port_pin_set_output_level(EEPROM_CS, 1);
	return curr_frame.frame.data;
}

//returns true if time1 is later than time2
bool is_timestamp_later(struct rtc_calendar_time *time1, struct rtc_calendar_time *time2)
{
	if(time1->year > time2->year)
		return true;
	else if(time1->year == time2->year)
		if(time1->month > time2->month)
			return true;
		else if(time1->month == time2->month)
			if(time1->day > time2->day)
				return true;
			else if(time1->day == time2->day)
				if(time1->hour > time2->hour)
					return true;
				else if(time1->hour == time2->hour)
					if(time1->minute > time2->minute)
						return true;
					else if(time1->minute == time2->hour)
						if(time1->second > time2->second)
							return true;
	return false;
}

//sets eeprom_data_pointer to point to the most recent shield data entry in eeprom
void eeprom_find_latest_data()
{
	struct shield_data *latest_data = 0;
	for(uint16_t i = 0; i < 20/*EEPROM_BYTE_TOTAL/sizeof(struct shield_data)*/; i++)
	{
		struct shield_data temp = spi_eeprom_read_address(latest_data++);
		if(is_timestamp_later(&temp.timestamp, &latest_data->timestamp))
			eeprom_data_pointer = latest_data;
	}
}

//writes data to eeprom and self-manages write address
void eeprom_write_data(struct shield_data *data)
{
	//uint8_t pointerval = ((uint32_t) eeprom_data_pointer) & 0xFF;
	uint16_t temp = 5;
	if(((((uint32_t) eeprom_data_pointer) & 0xFF) + sizeof(shield_data)) <= 0x100)
	{
		spi_eeprom_write_address(++eeprom_data_pointer, data);
	}
	else
	{
		temp = 1;
		eeprom_data_pointer = (((uint32_t) eeprom_data_pointer) & 0xFFFFFF00) + 0x100;
		spi_eeprom_write_address(++eeprom_data_pointer, data);
	}
}