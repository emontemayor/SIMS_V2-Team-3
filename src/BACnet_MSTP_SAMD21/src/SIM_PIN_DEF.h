/**********************************************
 * SIM_PIN_DEF.h
 * Header for pin definitions
 *
 * Author : Emil Montemayor
 * Capstone Project 2017 - 2018
 **********************************************/
#ifndef SIM_PIN_DEF_H_
#define SIM_PIN_DEF_H_


/* The following define is here because I'm using ASF 3.36, which doesn't 
 * support the SAMHA1E. I'd rather not comment out the section of code that
 * actually throws an error due to SAMHA1E not being defined, for portability
 * reasons.
 
#define SAMHA1E (                          \
        SAM_PART_IS_DEFINED(SAMHA1E18A) || \
        SAM_PART_IS_DEFINED(SAMHA1E15B) || \
        SAM_PART_IS_DEFINED(SAMHA1E16B) || \
        SAM_PART_IS_DEFINED(SAMHA1E17B) || \
        SAM_PART_IS_DEFINED(SAMHA1E18B)    \
    )
*/

// LCD defines:
// SPI pin configs for LCD:
#define LCD_SPI       SERCOM4
#define LCD_CS        45 //PIN_PB13
#define LCD_MISO_PAD  ((44L << 16) | 2L) //PINMUX_PB12C_SERCOM4_PAD0 
#define LCD_MOSI_PAD	((46L << 16) | 2L) //PINMUX_PB14C_SERCOM4_PAD2
#define LCD_SCK_PAD   ((47L << 16) | 2L) //PINMUX_PB15C_SERCOM4_PAD3
#define LCD_UNUSED    PINMUX_UNUSED
// SPI MUX combination E.
#define LCD_PINMUX_SETTING SPI_SIGNAL_MUX_SETTING_E
// LCD clock source
#define LCD_SPI_SOURCE_CLOCK    GCLK_GENERATOR_0
// Define the SPI max clock
#define LCD_SPI_MAX_CLOCK       1000000//4000000


// GPIO configs for LCD:
// the LCD's power down (PD) pin
#define LCD_PD          PIN_PA08
						
// the LCD's PD pin pup, no internal PUP because the LCD has a 47k PUP on it
#define LCD_PD_PULL     PORT_PIN_PULL_NONE
// logical value for enabling the power down pin (LCD = off)
#define LCD_PD_EN       0
// logical value for disabling the power down pin (LCD = on)
#define LCD_PD_DIS      1

// the LCD's interrupt pin
#define LCD_INT         PIN_PA09
// the pinmux for the external interrupt
#define LCD_INT_PINMUX  PIN_PA09A_EIC_EXTINT9
// the pin's pull value, none because the LCD has a 47k PUP on it
#define LCD_INT_PULL    EXTINT_PULL_NONE
// the detection value for the external interrupt
#define LCD_INT_DETECT  EXTINT_DETECT_LOW
// the external interrupt channel for PA09
#define LCD_INT_LINE    0x09

/* End of LCD defines */


//RS485 Configuration
//RE is active low! 
#define RS485_RE		PIN_PA25
#define RS485_DE		PIN_PA24
#define	RS485_RX		PINMUX_PA23C_SERCOM3_PAD1
#define	RS485_TX		PINMUX_PA22C_SERCOM3_PAD0
#define RS485_USART		SERCOM3

// Fiberoptic UART config, generic
#define UART_FIBER_BAUD 14400
#define UART_FIBER_CLK  GCLK_GENERATOR_0

// Fiberoptic UART config, Receiver 1
#define UART_FIBER1  	SERCOM1
#define UTX_FIBER1		PINMUX_UNUSED
#define URX_FIBER1		PINMUX_PA19C_SERCOM1_PAD3
#define UART_FIBER_PINMUX1  USART_RX_3_TX_0_XCK_1

// Fiberoptic UART config, Receiver 2
#define UART_FIBER2  	SERCOM5
#define UTX_FIBER2		PINMUX_UNUSED
#define URX_FIBER2		PINMUX_PB16C_SERCOM5_PAD0
#define UART_FIBER_PINMUX2  USART_RX_0_TX_2_XCK_3

// EEPROM SPI config
#define SPI_EEPROM		SERCOM2
#define EEPROM_SCK		PINMUX_PA15C_SERCOM2_PAD3
#define EEPROM_MOSI		PINMUX_PA14C_SERCOM2_PAD2
#define EEPROM_CS		PINMUX_PA13C_SERCOM2_PAD1
#define EEPROM_MISO		PINMUX_PA12C_SERCOM2_PAD0
#define EEPROM_PINMUX	SPI_SIGNAL_MUX_SETTING_E
// These signals are optional
#define EEPROM_WP		PIN_PA16
#define EEPROM_HOLD		PIN_PA17
// EEPROM chip's max clock speed is 5MHz
#define SPI_EEPROM_MAX_CLOCK 5000000
#define SPI_EEPROM_CLOCK_SOURCE GCLK_GENERATOR_0
// EEPROM chip operation codes
#define EEPROM_READ	0x03
#define EEPROM_WRITE	0x02
#define EEPROM_WREN	0x06
#define EEPROM_WRDI	0x04
#define EEPROM_RDSR	0x05
#define EEPROM_WRSR	0x01
#define EEPROM_LPWP	0x08

#endif /* SIM_PIN_DEF_H_ */
