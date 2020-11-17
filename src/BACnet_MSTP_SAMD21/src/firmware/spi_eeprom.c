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
	//struct spi_slave_inst_config config_spi_slave;
	
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
	
	// Configure the slave with no address
	//config_spi_slave.address_enabled = false;
	//config_spi_slave.ss_pin = EEPROM_CS;
	// attach the slave settings to the slave
	//spi_attach_slave(&spieeprom_slave, &config_spi_slave);

	/*
    status_code_genare_t read_status;		
	    do{
        // select the slave
        read_status = spi_select_slave(&spieeprom_inst, &spieeprom_slave, true);
    }while(read_status == STATUS_BUSY);
	*/
	
	/*
	//update pointer with most recent data address
	eeprom_data_pointer = eeprom_find_latest_data() + sizeof(struct shield_data);
	if(eeprom_data_pointer > (EEPROM_BYTE_TOTAL - sizeof(struct shield_data)))
		eeprom_data_pointer = 0;
	*/
}

//writes a single byte to the eeprom chip
//writes a byte at a time to avoid encountering the page wrap "feature" of the eeprom chip
void eeprom_write_data(struct shield_data* data)
{
	//prepare the write data frame
	/*
	struct write_frame write_instructions;
	write_instructions.cmd = EEPROM_WRITE;
	if(eeprom_data_pointer > (EEPROM_BYTE_TOTAL - sizeof(data)))
		eeprom_data_pointer = 0;
	write_instructions.addr_high = (eeprom_data_pointer & 0xFF0000) >> 16;
	write_instructions.addr_low = eeprom_data_pointer & 0xFFFF;
	
	union write_frame_union write_instr;
	
	for(uint8_t i = 0; i < sizeof(data); i++)
	{
		write_instructions.data = data[i];
		write_instr.frame = write_instructions;
		spi_write_buffer_wait(&spieeprom_inst, &write_instr.databytes, sizeof(write_instr));
		if(write_instructions.addr_low++ == 0xFFFF)
			write_instructions.addr_high++;
		if((write_instructions.addr_high << 16) + write_instructions.addr_low == EEPROM_BYTE_TOTAL)
			write_instructions.addr_high = write_instructions.addr_low = 0;
		eeprom_data_pointer++;
	}
	*/
}

void eeprom_write_byte(uint32_t address, uint8_t data)
{
	write_frame_union curr_frame;
	curr_frame.frame.cmd = EEPROM_WRITE;
	curr_frame.frame.addr_high = address & (2<<16);
	curr_frame.frame.addr_mid = address & (0xFF<<8);
	curr_frame.frame.addr_low = address & 0xFF;
	curr_frame.frame.data = data;
	port_pin_set_output_level(EEPROM_CS, 0);
	spi_write_buffer_wait(&spieeprom_inst, &curr_frame.databytes, sizeof(write_frame_union));
	port_pin_set_output_level(EEPROM_CS, 1);
}

uint8_t eeprom_read_byte(uint32_t address)
{
	uint8_t ret_data[sizeof(write_frame_union)];
	write_frame_union curr_frame;
	curr_frame.frame.cmd = EEPROM_READ;
	curr_frame.frame.addr_high = address & (2<<16);
	curr_frame.frame.addr_mid = address & (0xFF<<8);
	curr_frame.frame.addr_low = address & 0xFF;
	curr_frame.frame.data = 0xFF;
	port_pin_set_output_level(EEPROM_CS, 0);
	spi_transceive_buffer_wait(&spieeprom_inst, &curr_frame.databytes, &ret_data, sizeof(write_frame_union));
	port_pin_set_output_level(EEPROM_CS, 1);
	return ret_data[sizeof(write_frame_union) - 1];
}

//returns data from an address
struct shield_data eeprom_read_address(uint32_t address)
{
	struct shield_data data;
	/*
	//prepare a struct to receive the return data
	union shield_data_union ret_data;
	
	//prepare the read data frame
	read_frame read_instructions;
	read_instructions.cmd = EEPROM_READ;
	read_instructions.addr_high = (address & 0xFF0000) << 16;
	read_instructions.addr_low = address & 0xFFFF;
	
	//load the frame into a union to be easily passed
	union read_frame_union read_instr;
	read_instr.frame = read_instructions;
	
	//begin the transceiver function
	spi_transceive_buffer_wait(&spieeprom_inst, &read_instr.databytes, &ret_data.databytes, sizeof(ret_data));
	return ret_data.data;
	*/
	return data;
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