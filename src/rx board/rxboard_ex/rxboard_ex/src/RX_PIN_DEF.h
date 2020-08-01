/*		txPinDef.h
 * define pinout for tx board
 *
 * Author : Khang Vu and Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/

#ifndef SIM_PIN_DEF_H_
#define SIM_PIN_DEF_H_

#include <asf.h>

/******************pin out for transceiver module**********/
/* 2.45 GHz module defines */
#define UART245			SERCOM0
#define PAEN245			PIN_PA01
#define CONFIG245		PIN_PA02
#define RESET245		PIN_PA03
#define UTX245			PINMUX_PA04D_SERCOM0_PAD0
#define URX245			PINMUX_PA05D_SERCOM0_PAD1
#define RTS245			PIN_PA06 
#define CTS245			PIN_PA07
#define UART245_BAUD    19200
#define UART245_PINMUX  USART_RX_1_TX_0_RTS_2_CTS_3
// UART245 clock source
#define UART245_CLK	    GCLK_GENERATOR_0
/* End of 2.45 GHz module defines */


// 915 module
#define UART915			SERCOM2
#define UTX915			((12L << 16) | 2L) //PINMUX_PA12C_SERCOM2_PAD0
#define URX915			((13L << 16) | 2L) //PINMUX_PA13C_SERCOM2_PAD1
#define RTS915			PIN_PA14
#define CTS915			PIN_PA15
#define WAKE915			47 //PIN_PB15
#define UART915_BAUD    115200
#define UART915_PINMUX  USART_RX_1_TX_0_RTS_2_CTS_3
#define UART915_CLK	    GCLK_GENERATOR_0
/* end of 915 MHz module defines */

//40 module
#define SPI40			SERCOM3
#define SPI40_PINXMUX   SPI_SIGNAL_MUX_SETTING_D
#define MOSI40			PINMUX_PA22C_SERCOM3_PAD0
#define SCK40			PINMUX_PA23C_SERCOM3_PAD1
#define SS40			PIN_PA24
#define MISO40			PINMUX_PA25C_SERCOM3_PAD3
#define IRQ40			PIN_PA27

// SPI clock source
#define SPI40_CLK	    GCLK_GENERATOR_0

// Define the SPI max clock
#define SPI40MAXCLK     1000000//4000000
/* End of 40 module defines */

// Fiberoptic UART config
#define UART_FIBER  	SERCOM1
#define UTX_FIBER		PINMUX_PA16C_SERCOM1_PAD0
#define URX_FIBER		PINMUX_PA17C_SERCOM1_PAD1
#define UART_FIBER_BAUD 9600
#define UART_FIBER_PINMUX  USART_RX_1_TX_0_RTS_2_CTS_3
#define UART_FIBER_CLK  GCLK_GENERATOR_0
#endif /* SIM_PIN_DEF_H_ */