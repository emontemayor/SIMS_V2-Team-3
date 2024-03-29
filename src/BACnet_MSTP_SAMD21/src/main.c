/**********************************************
 * main.c
 * Main program for Display board.
 *
 * Author : Emiliano Montemayor
 * Capstone Project 2017 - 2018
 **********************************************/
/************************************************************************/
/*                                include headers                       */
/************************************************************************/
#include "uart_fiber.h"
#include <SIM_PIN_DEF.h>
#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	
#include <math.h>
#include <sim_system_glcd_software.h>
#include <ff.h>
#include <sim_gui.h>
#include "bacnet.h"
#include "rs485.h"
#include "bacnet/basic/sys/mstimer.h"
#include "spi_eeprom.h"



void sim_system_init(void);
void sys_clock_init(void);
void clock_osc8m_init(void);
void clock_gclk0_init(void);
void configure_port_pins(void);


/************************************************************************/
/*                                Globals                               */
/************************************************************************/

extern struct rtc_module rtc_instance;		//declare rtc instance for calendar 
extern struct rtc_calendar_time time;		//time instance to get and set time

//global values 
extern Ft_Gpu_Hal_Context_t host, *phost;
extern ft_uint8_t  tag, tempTag, font, alert, sound;		

//used to put commands to RAM_DL
extern ft_uint32_t attnStart, attnEnd, rssiStart, rssiEnd, histStart, histEnd;

//2D array for history
extern int16_t** history;

/* task timer */
static struct mstimer Blink_Timer;
/* LED toggle tracker */
static bool LED_Status;

//current rssi values
struct shield_data current_fiber1_data;
struct shield_data current_fiber2_data;


/************************************************************************/
/*                                Main                                  */
/************************************************************************/
int main(void){
	// system init
	sim_system_init();
	system_interrupt_enable_global();
	// config and setup calendar
	configure_rtc_calendar();
    
    // setup display
	phost = &host;
	//open display host
	Ft_Gpu_Hal_Open(phost);
	// enable the dislay interrupt
	Ft_Gpu_Hal_Wr8(phost, REG_INT_EN, 1);
	// mask all interrupt but TAG
	Ft_Gpu_Hal_Wr8(phost, REG_INT_MASK, 6);
	
	delay_ms(2000);
	
	/*
	//put static portions into ram_g
	appAttn();
	appRssi();
	appHist();
	*/
	
	cpu_irq_enable();
	
	//enable our hardware
	mstimer_init();
	//led_init();
	// set baud before init
	rs485_baud_rate_set(38400);
	rs485_init();
	//initialize the BACnet stack
	//bacnet_init();
	mstimer_set(&Blink_Timer, 125);
	
	//shield data test structs (used for eeprom debugging)
	
	
	struct shield_data data1, data2, data3, data4, temp;
	struct shield_data zerodout = {0};
	
	data1.rssi_values.GHz24RSSI = 0x45;
	data1.rssi_values.MHz169RSSI = 0x45;
	data1.rssi_values.MHz27RSSI = 0x45;
	data1.rssi_values.MHz915RSSI = 0x45;
	data1.timestamp.year = 2021;
	data1.timestamp.month = 3;
	data1.timestamp.day = 12;
	data1.timestamp.pm = true;
	data1.timestamp.hour = 5;
	data1.timestamp.minute = 33;
	
	data2.rssi_values.GHz24RSSI = 0x10;
	data2.rssi_values.MHz169RSSI = 0x20;
	data2.rssi_values.MHz27RSSI = 0x30;
	data2.rssi_values.MHz915RSSI = 0x40;
	data2.timestamp.year = 2015;
	data2.timestamp.month = 4;
	data2.timestamp.day = 20;
	data2.timestamp.pm = true;
	data2.timestamp.hour = 6;
	data2.timestamp.minute = 9;
	
	data3.rssi_values.GHz24RSSI = 0x69;
	data3.rssi_values.MHz169RSSI = 0x55;
	data3.rssi_values.MHz27RSSI = 0x69;
	data3.rssi_values.MHz915RSSI = 0xAA;
	data3.timestamp.year = 2021;
	data3.timestamp.month = 3;
	data3.timestamp.day = 12;
	data3.timestamp.pm = true;
	data3.timestamp.hour = 4;
	data3.timestamp.minute = 21;
	
	data4.rssi_values.GHz24RSSI = 0x96;
	data4.rssi_values.MHz169RSSI = 0x69;
	data4.rssi_values.MHz27RSSI = 0x3D;
	data4.rssi_values.MHz915RSSI = 0xD3;
	data4.timestamp.year = 2021;
	data4.timestamp.month = 3;
	data4.timestamp.day = 12;
	data4.timestamp.pm = true;
	data4.timestamp.hour = 4;
	data4.timestamp.minute = 20;
	
	
	
	for(struct shield_data *i = sizeof(struct shield_data) * 560; i < (sizeof(struct shield_data) * 90) + sizeof(struct shield_data) * 11; i++)
	{
		spi_eeprom_write_address(i, &data1);
		data1.timestamp.minute++;
		data1.rssi_values.GHz24RSSI += 1;
		data1.rssi_values.MHz169RSSI += 1;
		data1.rssi_values.MHz27RSSI -= 1;
	}
	
	
	spi_eeprom_write_address((struct shield_data *) (sizeof(struct shield_data) * 10), &data1);


	//main home menu and GUI
	while(1){
		
		
		/*
		if(get_fiber1_status() == data_ready)
		{
			current_fiber1_data.rssi_values = get_fiber1_data();
			reset_fiber1_status();
		}
		
		if(get_fiber2_status() == data_ready)
		{
			current_fiber2_data.rssi_values = get_fiber2_data();
			reset_fiber2_status();
		}
		*/
		
		//uint32_t test_meme = eeprom_write_byte(0x69);
		
		//struct shield_data newData = spi_eeprom_read_address(0xF0);
		
		port_pin_set_output_level(PIN_PB16, 1);
		delay_ms(1);
		port_pin_set_output_level(PIN_PB16, 0);
		delay_ms(1);
		port_pin_set_output_level(PIN_PA19, 1);
		delay_ms(1);
		port_pin_set_output_level(PIN_PA19, 0);
		
		/*
		if(newData.rssi_values.GHz24RSSI == 0)
		{
			delay_ms(1);
		}
		*/
		//bacnet_task();
		
		
		tag = 0;
		disStart();
		//set background
		Ft_Gpu_CoCmd_Gradient(phost, 0, 0x060A39, 0, disWid, disHei, 0x0A4F7A);
		//get time and put it on display
		Ft_Gpu_Hal_WrCmd32(phost,COLOR_RGB(0,0,0));
		printTime();
		
		// store value to tag
		Ft_Gpu_Hal_WrCmd32(phost,COLOR_RGB(255,255,255));
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		
		//assign tag value to each button and display it
		Ft_Gpu_Hal_WrCmd32(phost,TAG(attn));
		Ft_Gpu_CoCmd_Button(phost, disWid*.23,disHei*0.23,(disWid*0.25),(disHei*0.25),30, (tag == attn)? OPT_FLAT:0,"  Attenuation  ");
		    
		Ft_Gpu_Hal_WrCmd32(phost,TAG(hist));
		Ft_Gpu_CoCmd_Button(phost, disWid*.52,disHei*0.23,(disWid*0.25),(disHei*0.25),30, (tag == hist)? OPT_FLAT:0,"  History  ");
		    
		Ft_Gpu_Hal_WrCmd32(phost,TAG(rssi));
		Ft_Gpu_CoCmd_Button(phost, disWid*.23,disHei*0.52, disWid*0.25,disHei*0.25,30, (tag == rssi)? OPT_FLAT:0,"  RSSI  ");
		    
		Ft_Gpu_Hal_WrCmd32(phost,TAG(sett));
		Ft_Gpu_CoCmd_Button(phost, disWid*.52,(disHei*0.52),(disWid*0.25),(disHei*0.25),30, (tag == sett)? OPT_FLAT:0,"  Settings  ");
	    
		disEnd();
		
		
        //check tag value and determine further action
		if(tag!=0)		tempTag = tag;
		if (tempTag != tag && tag == 0 && tag!=back){
			if(tempTag == attn)			    attnOp(&current_fiber1_data);	//attnOp(current_fiber1_data, current_fiber2_data);
			else if(tempTag == hist)		historyOp();
			else if(tempTag == sett)		settingOp();
			else if(tempTag == rssi)		rssiOp();
			tempTag = 0;
			delay_ms(50);
		}
		
	}
	
}//end main

/****************************************************************************************************************************
													System Init 
****************************************************************************************************************************/

/* Function Name    : sim_system_init
	* Parameters       : void
	* Return Values(s) : void
	* Description      : init system clock, spi, int...
	*/
void sim_system_init(void){
	system_init();
	// config system clocks
	sys_clock_init();
	
	//configure port pins
	configure_port_pins();
	
	// config LCD spi
	lcd_spi_init();
	
	// configure the external interrupt pins
	configure_ext_ints();
	// configure the callback functions for external interrupts
	configure_ext_int_callback();

	// initialize the LCD
	lcd_init_seq(); 
	
	
	// set the interrupt masks for the LCD interrupts
	lcd_int_mask(LCD_DEFAULT_MASK);
	// write 1 to the LCD REG_INT_EN register to enable it
	lcd_int_enable();
    
	spieeprom_init();
	
    uartfiber_init();

    //uartib_init();
}//end sim_system_init


/* Function Name    : sys_clock_init
	* Parameters       : void
	* Return Values(s) : void
	* Description      : init clk speed and general clk
	*/
void sys_clock_init(void){
	//init the system clock first
	clock_osc8m_init();
	    
	//init GLCK0 after that
	clock_gclk0_init();
		
	// init internal osc32k and gclk2 for calendar
	clock_osc32k_init();
	clock_gclk2_init();
	delay_init();
}//end sys_clock_init


/* Function Name    : clock_osc8m_init
	* Parameters       : void
	* Return Values(s) : void
	* Description      : Initializes the 8 MHz oscillator to be used as the
	*  system clock source.
	*/
void clock_osc8m_init(void){
	//create system clock config struct
	struct system_clock_source_osc8m_config osc8_config;

	//config the 8 MHz oscillator
	//divide by 1 = 8 MHz clock
	osc8_config.prescaler = SYSTEM_OSC8M_DIV_1;
	//run on demand
	osc8_config.on_demand = true;
	//don't run in standby
	osc8_config.run_in_standby = false;
	    
	//set the 8MHz internal oscillator config
	system_clock_source_osc8m_set_config(&osc8_config);
}//end clock_osc8m_init


/* Function Name    : clock_gclk0_init
	* Parameters       : void
	* Return Values(s) : void
	* Description      : Initializes GCLK0, so it can be used by 
	*  peripherals. Uses the 8 MHz oscillator as its source.
	*/
void clock_gclk0_init(void){
	//create GLCK0 config struct (for driving peripherals)
	struct system_gclk_gen_config gclk0_config;

	//init MCLK
	system_gclk_init();
	    
	//set CPU clock division factor to 1 = 8 MHz CPU
	system_cpu_clock_set_divider(SYSTEM_MAIN_CLOCK_DIV_1);
	    
	//use the 8 MHz source
	gclk0_config.source_clock = SYSTEM_CLOCK_SOURCE_OSC8M;
	//don't output it to a pin (requires additional config)
	gclk0_config.output_enable = false;
	//We're not outputting it to a pin, so don't need to set it high when disabled
	gclk0_config.high_when_disabled = false;
	//division factor of 1, we're already at 8 MHz
	gclk0_config.division_factor = 1;
	//don't run in standby
	gclk0_config.run_in_standby = false;
	//set GCLK0's config
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &gclk0_config);
	//enable GCLK0
	system_gclk_gen_enable(GCLK_GENERATOR_0);
}//end clock_gclk0_init

	
/* Function Name    : configure_port_pins
	* Parameters       : void
	* Return Values(s) : void
	* Description      : config select pins for lcd 
	*/
void configure_port_pins(void){
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);

	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PB16, &config_port_pin);
	port_pin_set_output_level(PIN_PB16, 1);

	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA19, &config_port_pin);
	port_pin_set_output_level(PIN_PA19, 1);

	// configure outputs
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	config_port_pin.input_pull = LCD_PD_PULL;
	port_pin_set_config(LCD_PD, &config_port_pin);
	
	port_pin_set_output_level(LCD_PD, LCD_PD_DIS);
	
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(EEPROM_CS,&config_port_pin);
	
/*

	//Debugging routine used to find that pins on uC were defunct. 
	uC was replaced, this routine was run, and 
	port_pin_set_config(PIN_PA10, &config_port_pin);    
	port_pin_set_output_level(PIN_PA10, true);
	
	//MISO
	port_pin_set_config(PIN_PB12, &config_port_pin);    
	port_pin_set_output_level(PIN_PB12, true);
	
	//EN
	port_pin_set_config(PIN_PB13, &config_port_pin); 
	port_pin_set_output_level(PIN_PB13, true);
	
	//MOSI
	port_pin_set_config(PIN_PB14, &config_port_pin); 
	port_pin_set_output_level(PIN_PB14, true);	
		
	//SCK
	port_pin_set_config(PIN_PB15, &config_port_pin); 
	port_pin_set_output_level(PIN_PB15, true);	
	
*/


}//end configure_port_pins

/****************************************************************************************************************************
													Nothing beyond this point
****************************************************************************************************************************/