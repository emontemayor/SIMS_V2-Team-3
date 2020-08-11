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
#define CONFIG245		PIN_PA06
#define RESET245		PIN_PA07
#define UTX245			PINMUX_PA08C_SERCOM0_PAD0
#define URX245			PINMUX_PA09C_SERCOM0_PAD1
#define RTS245			PIN_PA10
#define CTS245			PIN_PA11
#define UART245_BAUD    19200
#define UART245_PINMUX  USART_RX_1_TX_0_RTS_2_CTS_3
// UART245 clock source
#define UART245_CLK	    GCLK_GENERATOR_0
/* End of 2.45 GHz module defines */

// 915 module
#define UART915			SERCOM2
#define UTX915			PINMUX_PA12C_SERCOM2_PAD0 
#define URX915			PINMUX_PA13C_SERCOM2_PAD1 
#define RTS915			PIN_PA14
#define CTS915			PIN_PA15
#define WAKE915			PIN_PB15
#define UART915_BAUD    115200
#define UART915_PINMUX  USART_RX_1_TX_0_RTS_2_CTS_3
#define UART915_CLK	    GCLK_GENERATOR_0

//169 module
#define SPI169			SERCOM1
#define SPI169_PINXMUX   SPI_SIGNAL_MUX_SETTING_N
#define MOSI169			PINMUX_PA16C_SERCOM1_PAD0
#define SCK169			PINMUX_PA19C_SERCOM1_PAD3
#define SS169			PIN_PA17
#define MISO169			PINMUX_PA18C_SERCOM1_PAD2
#define IRQ169			PIN_PB16



// SPI clock source
#define SPI169_CLK	    GCLK_GENERATOR_0
// Define the SPI max clock
#define SPI169MAXCLK     1000000//4000000

//27 module
#define SPI27			SERCOM3
#define SPI27_PINXMUX   SPI_SIGNAL_MUX_SETTING_D
#define MISO27			PINMUX_PA22C_SERCOM3_PAD0
#define SCK27			PINMUX_PA25C_SERCOM3_PAD3
#define SS27			PIN_PA23
#define MOSI27			PINMUX_PA24C_SERCOM3_PAD2
#define IRQ27			PIN_PA27
#define SEN				PIN_PA28

// SPI clock source

#define SPI169_CLK	    GCLK_GENERATOR_0
#define SPI27_CLK	    GCLK_GENERATOR_0


// Define the SPI max clock
#define SPI169MAXCLK     1000000//4000000

#define SPI27_CLK	    GCLK_GENERATOR_0

// Define the SPI max clock

#define SPI27MAXCLK     1000000//4000000

#endif /* SIM_PIN_DEF_H_ */