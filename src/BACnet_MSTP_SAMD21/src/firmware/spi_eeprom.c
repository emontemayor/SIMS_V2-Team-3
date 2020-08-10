/*
 * spi_eeprom.c
 *
 * Created: 8/10/2020 10:18:52 AM
 *  Author: Sander
 * Contains functions to interact with the EEPROM chip on the control unit for non-volatile long term data storage
 */ 
#include "SIM_PIN_DEF.h"

static struct spi_module spieeprom_inst; // ASF instance of SPI SERCOM module

void spieeprom_init();
{
	struct spi_config config_spi;
	
	spi_get_config_defaults(&config_spi);
	
	config_spi.pinmux_pad0 = EEPROM_MISO;
	config_spi.pinmux_pad1 = EEPROM_CS;
	config_spi.pinmux_pad2 = EEPROM_MOSI;
	config_spi.pinmux_pad3 = EEPROM_SCK;
	
}
