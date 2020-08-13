/*
 * spi_eeprom.c
 *
 * Created: 8/10/2020 10:18:52 AM
 *  Author: Sander Sieglaff
 * Contains functions to interact with the EEPROM chip on the control unit for non-volatile long term data storage
 */ 
#include "SIM_PIN_DEF.h"
#include "uart_fiber.h"

//variable to track current write location in memory.
//THIS POINTS TO THE BEGINNING OF A SINGLE DATA POINT, SO IT SHOULD 
//ALWAYS BE INCREMENTED BY sizeof(shield_data) AFTER EACH WRITE
uint16_t eeprom_data_pointer;

static struct spi_module spieeprom_inst; // ASF instance of SPI SERCOM module

//structs to represent the arrangement of the the SPI frame
struct write_frame{
	uint8_t cmd = 0x2; //command to write to memory
	uint8_t addr_high; //top 6 bits are truncated, only the lower 2 bits will be considered
	uint16_t addr_low;
	uint8_t data;
	};
struct read_frame{
	uint8_t cmd = 0x3; //command to read from memory
	uint8_t addr_high; //top 6 bits are truncated, only the lower 2 bits will be considered
	uint16_t addr_low;
	};
	
//union types to make feeding the buffer function easier
union write_frame_union{
	struct write_frame frame;
	uint8_t databytes[sizeof(frame)];
	};
union read_frame_union{
	struct read_frame frame;
	uint8_t databytes[sizeof(frame)];
	};
union shield_data_union{
	struct shield_data data;
	uint8_t databytes[sizeof(data)];
	};

void spieeprom_init();
{
	struct spi_config config_spi;
	
	spi_get_config_defaults(&config_spi);
	
	config_spi.pinmux_pad0 = EEPROM_MISO;
	config_spi.pinmux_pad1 = EEPROM_CS;
	config_spi.pinmux_pad2 = EEPROM_MOSI;
	config_spi.pinmux_pad3 = EEPROM_SCK;
	
	config_spi.generator_source = SPI_EEPROM_CLOCK_SOURCE;
	config_spi.mode_specific.master.baudrate = SPI_EEPROM_MAX_CLOCK;
	config_spi.mux_setting = EEPROM_PINMUX;
	
	spi_init(&spieeprom_inst, SPI_EEPROM, &config_spi);
	spi_enable(&spieeprom_inst);
	
	
}


void eeprom_write_data(uint8_t* data[sizeof(shield_data)], uint32_t address)
{
	for(uint8_t i = 0; i < sizeof(shield_data), i++)
	{
		spi_write(&spieeprom_inst, WREN);
		spi_write_buffer_job(&spieeprom_inst, )
	}
}

//returns the latest shield reading
struct shield_data eeprom_read_most_recent(uint32_t address)
{
	//prepare a struct to receive the return data
	union shield_data_union ret_data;
	
	//prepare the read data frame
	struct read_frame read_instructions;
	read_instructions.addr_high = (address & 0xFF00) << 8;
	read_instructions.addr_low = address & 0xFF;
	
	//load the frame into a union to be easily passed
	union read_frame_union read_instr;
	read_instr.frame = read_instructions;
	
	//begin the transceiver function
	spi_transceive_buffer_wait(&spieeprom_inst, &read_instr.databytes, &ret_data.databytes, sizeof(ret_data));
	return ret_data;
}
