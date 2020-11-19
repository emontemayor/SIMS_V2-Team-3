/*
 * spi_eeprom.c
 *
 * Created: 8/10/2020 10:18:52 AM
 *  Author: Sander Sieglaff
 * Contains functions to interact with the EEPROM chip on the control unit for non-volatile long term data storage
 */ 
#include "SIM_PIN_DEF.h"
#include "spi_eeprom.h"

//variable to track current write location in memory.
//THIS POINTER REPRESENTS BYTES, SO IT SHOULD ALWAYS
//BE INCREMENTED BY sizeof(shield_data) AFTER EACH WRITE
uint32_t eeprom_data_pointer;



static struct spi_module spieeprom_inst; // ASF instance of SPI SERCOM module
struct spi_slave_inst spieeprom_slave;

void spieeprom_init()
{
	struct spi_config config_spi;
	
	spi_get_config_defaults(&config_spi);
	config_spi.mux_setting = EEPROM_PINMUX;
	config_spi.pinmux_pad0 = EEPROM_MISO;
	config_spi.pinmux_pad1 = PINMUX_UNUSED;
	config_spi.pinmux_pad2 = EEPROM_MOSI;
	config_spi.pinmux_pad3 = EEPROM_SCK;
	
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(EEPROM_CS, &config_port_pin);
	port_pin_set_config(EEPROM_WP, &config_port_pin);
	port_pin_set_config(EEPROM_HOLD, &config_port_pin);
	
	port_pin_set_output_level(EEPROM_CS, 1);
	port_pin_set_output_level(EEPROM_WP, 1);
	port_pin_set_output_level(EEPROM_HOLD, 1);
	
	config_spi.generator_source = SPI_EEPROM_CLOCK_SOURCE;
	config_spi.mode_specific.master.baudrate = SPI_EEPROM_MAX_CLOCK;
	
	spi_init(&spieeprom_inst, SPI_EEPROM, &config_spi);
	spi_enable(&spieeprom_inst);
	
	//Enable writing on the memory chip
	uint8_t writeEnable = EEPROM_WREN;
	port_pin_set_output_level(EEPROM_CS, 0);
	spi_write_buffer_wait(&spieeprom_inst, &writeEnable, 1);
	port_pin_set_output_level(EEPROM_CS, 1);
	
	/*
	//update pointer with most recent data address
	eeprom_data_pointer = eeprom_find_latest_data() + sizeof(struct shield_data);
	if(eeprom_data_pointer > (EEPROM_BYTE_TOTAL - sizeof(struct shield_data)))
		eeprom_data_pointer = 0;
	*/
}

void spi_eeprom_write_address(uint32_t address, struct shield_data *data)
{
	write_frame_union curr_frame;
	curr_frame.frame.cmd = EEPROM_WRITE;
	curr_frame.frame.addr_high = address & (2<<16);
	curr_frame.frame.addr_mid = address & (0xFF<<8);
	curr_frame.frame.addr_low = address & 0xFF;
	curr_frame.frame.data.rssi_values.GHz24RSSI = data->rssi_values.GHz24RSSI;
	curr_frame.frame.data.rssi_values.MHz169RSSI = data->rssi_values.MHz169RSSI;
	curr_frame.frame.data.rssi_values.MHz27RSSI = data->rssi_values.MHz27RSSI;
	curr_frame.frame.data.rssi_values.MHz915RSSI = data->rssi_values.MHz915RSSI;
	curr_frame.frame.data.timestamp.year = data->timestamp.year;
	curr_frame.frame.data.timestamp.month = data->timestamp.month;
	curr_frame.frame.data.timestamp.day = data->timestamp.day;
	curr_frame.frame.data.timestamp.pm = data->timestamp.pm;
	curr_frame.frame.data.timestamp.hour = data->timestamp.hour;
	curr_frame.frame.data.timestamp.minute = data->timestamp.minute;
	curr_frame.frame.data.timestamp.second = data->timestamp.second;
	port_pin_set_output_level(EEPROM_CS, 0);
	spi_write_buffer_wait(&spieeprom_inst, &curr_frame.databytes, sizeof(write_frame_union));
	port_pin_set_output_level(EEPROM_CS, 1);
}

struct shield_data spi_eeprom_read_address(uint32_t address)
{
	struct shield_data ret_data;
	write_frame_union curr_frame;
	curr_frame.frame.cmd = EEPROM_READ;
	curr_frame.frame.addr_high = address & (2<<16);
	curr_frame.frame.addr_mid = address & (0xFF<<8);
	curr_frame.frame.addr_low = address & 0xFF;
	port_pin_set_output_level(EEPROM_CS, 0);
	spi_transceive_buffer_wait(&spieeprom_inst, &curr_frame.databytes, &curr_frame.databytes, sizeof(write_frame_union));
	port_pin_set_output_level(EEPROM_CS, 1);
	return curr_frame.frame.data;
}

//returns true if time1 is later than time2
bool is_timestamp_later(struct rtc_calendar_time time1, struct rtc_calendar_time time2)
{
	if(time1.year > time2.year)
		return true;
	else if(time1.year == time2.year)
		if(time1.month > time2.month)
			return true;
		else if(time1.month == time2.month)
			if(time1.day > time2.day)
				return true;
			else if(time1.day == time2.day)
				if(time1.hour > time2.hour)
					return true;
				else if(time1.hour == time2.hour)
					if(time1.minute > time2.minute)
						return true;
					else if(time1.minute == time2.hour)
						if(time1.second > time2.second)
							return true;
	return false;
}

//returns the address of the first byte of the newest shield_data
uint32_t eeprom_find_latest_data()
{
	//prepare the return data type
	union shield_data_union ret_data;
	ret_data.data.timestamp.year = 0;
	uint32_t address = 0;
	
	//begin a for loop to test all possible memory locations
	for(uint32_t i = 0; i < EEPROM_BYTE_TOTAL; i += sizeof(struct shield_data))
	{
		struct shield_data temp = eeprom_read_address(i);
		if (is_timestamp_later(ret_data.data.timestamp, temp.timestamp))
		{
			ret_data.data = temp;
			address = i;
		}
	}
	
	//return location of most recent data
	return address;
}