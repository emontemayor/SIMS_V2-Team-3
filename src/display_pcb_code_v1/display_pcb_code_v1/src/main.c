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
#include <SIM_PIN_DEF.h>
#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	
#include <math.h>
#include <sim_system_glcd_software.h>
#include <ff.h>
#include <sim_gui.h>


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
	
	//put static portions into ram_g/*
	appAttn();
	appRssi();
	appHist();
	//bacnet_task();


/*Debug screen. Displays 'FTDI' anda red circle. 
while(1){	
	disStart();
	lcd_wr32(RAM_DL +0,CLEAR(1,1,1));// clear screen
	lcd_wr32(RAM_DL +4,BEGIN(BITMAPS));// start drawing bitmaps
	lcd_wr32(RAM_DL +8,VERTEX2II(220,110,31,'F'));// ascii F in font 31
	lcd_wr32(RAM_DL +12,VERTEX2II(244,110,31,'T'));// ascii T
	lcd_wr32(RAM_DL +16,VERTEX2II(270,110,31,'D'));// ascii D
	lcd_wr32(RAM_DL +20,VERTEX2II(299,110,31,'I'));// ascii I
	lcd_wr32(RAM_DL +24,END());
	lcd_wr32(RAM_DL +28,COLOR_RGB(160,22,22));// change colourto red
	lcd_wr32(RAM_DL +32,POINT_SIZE(320));// set point size to 20 pixels in
	lcd_wr32(RAM_DL +36,BEGIN(FTPOINTS));// start drawing points
	lcd_wr32(RAM_DL +40,VERTEX2II(192,133,0,0));// red point
	lcd_wr32(RAM_DL +44,END());
	lcd_wr32(RAM_DL +48,DISPLAY());// display the image
	disEnd();
}
*/


/*
while(1){
	disStart();
	Ft_Gpu_CoCmd_Scrollbar(phost, 20, 30, 120, 8, 0, 10, 40, 100);
	Ft_Gpu_CoCmd_FgColor(phost,0x703800);
	Ft_Gpu_CoCmd_Scrollbar(phost,20, 60, 120, 8, 0, 30, 40, 100);
	Ft_Gpu_CoCmd_FgColor(phost,0x387000);
	Ft_Gpu_CoCmd_Scrollbar(phost,20, 90, 120, 8, 0, 50, 40, 100);
	disEnd();	
}
*/

	//main home menu and GUI
	while(1){
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
		
attnOp(NULL);
        tag = sett;
        //check tag value and determine further action
		if(tag!=0)		tempTag = tag;
		if (tempTag != tag && tag == 0 && tag!=back){
			if(tempTag == attn)				attnOp(NULL);
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
    
    uartfiber_init();
    uartib_init();
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


	// configure outputs
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	config_port_pin.input_pull = LCD_PD_PULL;
	port_pin_set_config(LCD_PD, &config_port_pin);
	
	port_pin_set_output_level(LCD_PD, LCD_PD_DIS);
	
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