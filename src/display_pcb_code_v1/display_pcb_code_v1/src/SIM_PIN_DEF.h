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
#define LCD_CS        PIN_PB13
#define LCD_MISO_PAD  PINMUX_PB12C_SERCOM4_PAD0
#define LCD_MOSI_PAD	PINMUX_PB14C_SERCOM4_PAD2
#define LCD_SCK_PAD   PINMUX_PB15C_SERCOM4_PAD3
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

// Fiberoptic UART config
#define UART_FIBER  	SERCOM0
#define UTX_FIBER		PINMUX_PA04D_SERCOM0_PAD0
#define URX_FIBER		PINMUX_PA05D_SERCOM0_PAD1
#define UART_FIBER_BAUD 9600
#define UART_FIBER_PINMUX  USART_RX_1_TX_0_RTS_2_CTS_3
#define UART_FIBER_CLK  GCLK_GENERATOR_0

// Interboard UART config
#define UART_IB  	    SERCOM2
#define UTX_IB		    PINMUX_PA08D_SERCOM2_PAD0
#define URX_IB		    PINMUX_PA09D_SERCOM2_PAD1
#define UART_IB_BAUD    9600
#define UART_IB_PINMUX  USART_RX_1_TX_0_RTS_2_CTS_3
#define UART_IB_CLK     GCLK_GENERATOR_0

#endif /* SIM_PIN_DEF_H_ */
