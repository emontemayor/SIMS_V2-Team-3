#include <SIM_PIN_DEF.h>
#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	
#include <sim_system_glcd_software.h>
#include <ff.h>


/************************************************************************/
/*                                Defines                               */
/************************************************************************/
#define SD_SLOT     0
#define DEV_MMC     0

#define disWid			800
#define disHei			480
#define boxWid			300
#define boxHei			100		
#define attn			1
#define hist			2
#define rssi			3
#define sett			4
#define back			6
/************************************************************************/
/*                                typedefs                              */
/************************************************************************/


/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
void sim_system_init(void);
void sys_clock_init(void);
void clock_osc8m_init(void);
void clock_gclk0_init(void);
void configure_port_pins(void);
void configure_ext_ints(void);
void configure_ext_int_callback(void);

		// Vu's
void home(void);
void disStart(void);
void disEnd(void);
void mainMenu(void);
void attnOp(void);
void manualOp(void);
void historyOp(void);
void settingOp(void);
void creditOp(void);
void calScreen(void);
void rssiOp(void);
void drawRect(int x, int y, double freq);
void appMainMenu(void);
void drawTitle(char *title);
void drawBack(void);
void appBack(void);
void appAttn(void);
/************************************************************************/
/*                                Globals                               */
/************************************************************************/
//FATFS fat_fs;   /* FatFs work area needed for each volume */
//FIL file_obj;   /* File object needed for each open file */

Ft_Gpu_Hal_Context_t host, *phost;
ft_uint32_t tracker;
ft_uint16_t val=32768;
ft_uint8_t tag =0, font = 28;

ft_uint16_t	mainMenuStart=0, mainMenuEnd=0, backStart=0, backEnd=0, \
			attnStart=0, attnEnd=0;
/************************************************************************/
/*                                Main                                  */
/************************************************************************/
int main(void){
    phost = &host;
    //UINT bw;
    //FRESULT fat_result;

    // system init
    sim_system_init();
	system_interrupt_enable_global();
    
    //open display host
    Ft_Gpu_Hal_Open(phost);
	// enable the dislay interrupt
	Ft_Gpu_Hal_Wr8(phost, REG_INT_EN, 1);
	// mask all interrupt but TAG
	Ft_Gpu_Hal_Wr8(phost, REG_INT_MASK, 4);
	// calibrate the screen
//	calScreen();
	
	//put static commands into ram_g
	appMainMenu();
	backStart = mainMenuEnd + 4;
	appBack();
	attnStart = backEnd + backStart + 4;
	appAttn();
	
	//main home menu and GUI
	while(1){
		tag = 0;
		
		disStart();
		Ft_Gpu_CoCmd_Gradient(phost, 0, 0, 0xCCCCCC, disWid, disHei, 0xB2B2B2);
		// store value to tag
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		Ft_Gpu_CoCmd_Append(phost,mainMenuStart,mainMenuEnd);
		disEnd();
		
/*
		Ft_Gpu_Hal_Wr16(phost, REG_SOUND, 0x60);
		Ft_Gpu_Hal_Wr8(phost, REG_PLAY, 0);*/
		if(tag == attn)			attnOp();
		else if(tag == hist)	historyOp();
		else if(tag == sett)	settingOp();
		else if(tag == rssi)	rssiOp();
	}
}//end main


/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void sim_system_init(void)
{
    system_init();
    // config system clocks
    sys_clock_init();
    // config LCD spi
    lcd_spi_init();
    configure_port_pins();
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
    
	
}


/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void sys_clock_init(void)
{
    //init the system clock first
    clock_osc8m_init();
    
    //init GLCK0 after that
    clock_gclk0_init();
    
    delay_init();
}


/* Function Name    : clock_osc8m_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes the 8 MHz oscillator to be used as the
 *  system clock source.
 */
void clock_osc8m_init(void)
{
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
}


/* Function Name    : clock_gclk0_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes GCLK0, so it can be used by 
 *  peripherals. Uses the 8 MHz oscillator as its source.
 */
void clock_gclk0_init(void)
{
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
}


/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void configure_port_pins(void)
{
    struct port_config config_port_pin;
    port_get_config_defaults(&config_port_pin);

    // configure inputs
    config_port_pin.direction = PORT_PIN_DIR_INPUT;
    config_port_pin.input_pull = PORT_PIN_PULL_UP;
    port_pin_set_config(SD_CD, &config_port_pin);
    port_pin_set_config(SD_WP, &config_port_pin);
    
    // configure outputs
    config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
    config_port_pin.input_pull = LCD_PD_PULL;
	port_pin_set_config(LCD_PD, &config_port_pin);
    
    port_pin_set_output_level(LCD_PD, LCD_PD_DIS);
}

void configure_ext_ints(void)
{
    // struct for external interrupt config
    struct extint_chan_conf ext_int_config;
    
    // configure the external interrupt
    ext_int_config.gpio_pin            = LCD_INT;
    ext_int_config.gpio_pin_mux        = LCD_INT_PINMUX;
    ext_int_config.gpio_pin_pull       = LCD_INT_PULL;
    ext_int_config.wake_if_sleeping    = true;
    ext_int_config.filter_input_signal = false;
    ext_int_config.detection_criteria  = LCD_INT_DETECT;

    extint_chan_set_config(LCD_INT_LINE, &ext_int_config);
}

void configure_ext_int_callback(void)
{
    // register callback for the LCD's interrupt
    extint_register_callback(lcd_interrupt_callback, LCD_INT_LINE, \
        LCD_INT_DETECT);
}


/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void appMainMenu(void){
	Ft_Gpu_CoCmd_Dlstart(phost);
	Ft_Gpu_Hal_WrCmd32(phost,CLEAR_COLOR_RGB(0,0,0));		//change this for initial bg
	Ft_Gpu_Hal_WrCmd32(phost, CLEAR(0,0,0));
	mainMenu();
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

	mainMenuEnd = Ft_Gpu_Hal_Rd16(phost,REG_CMD_DL) - 3*4;
	Ft_Gpu_Hal_WrCmd32(phost,CMD_MEMCPY);
	Ft_Gpu_Hal_WrCmd32(phost,mainMenuStart);
	Ft_Gpu_Hal_WrCmd32(phost,RAM_DL);
	Ft_Gpu_Hal_WrCmd32(phost,mainMenuEnd);
}

/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void appBack(void){
	Ft_Gpu_CoCmd_Dlstart(phost);
	Ft_Gpu_Hal_WrCmd32(phost,CLEAR_COLOR_RGB(0,0,0));		//change this for initial bg
	Ft_Gpu_Hal_WrCmd32(phost, CLEAR(0,0,0));
	drawBack();
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

	backEnd = Ft_Gpu_Hal_Rd16(phost,REG_CMD_DL) - 3*4;
	Ft_Gpu_Hal_WrCmd32(phost,CMD_MEMCPY);
	Ft_Gpu_Hal_WrCmd32(phost,backStart);
	Ft_Gpu_Hal_WrCmd32(phost,RAM_DL);
	Ft_Gpu_Hal_WrCmd32(phost,backEnd);
}

/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void appAttn(void){
	Ft_Gpu_CoCmd_Dlstart(phost);
	Ft_Gpu_Hal_WrCmd32(phost,CLEAR_COLOR_RGB(0,0,0));		//change this for initial bg
	Ft_Gpu_Hal_WrCmd32(phost, CLEAR(0,0,0));
	drawRect(400, 100, 40.68);
	drawRect(400, 230, 915);
	drawRect(400, 360, 2.45);
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

	attnEnd = Ft_Gpu_Hal_Rd16(phost,REG_CMD_DL) - 3*4;
	Ft_Gpu_Hal_WrCmd32(phost,CMD_MEMCPY);
	Ft_Gpu_Hal_WrCmd32(phost,attnStart);
	Ft_Gpu_Hal_WrCmd32(phost,RAM_DL);
	Ft_Gpu_Hal_WrCmd32(phost,attnEnd);
}

/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void disStart(){
	Ft_Gpu_CoCmd_Dlstart(phost);
	Ft_Gpu_Hal_WrCmd32(phost,CLEAR_COLOR_RGB(0,0,0));		//change this for initial bg
	Ft_Gpu_Hal_WrCmd32(phost, CLEAR(1,1,1));
}

/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void disEnd(){
	Ft_Gpu_Hal_WrCmd32(phost,DISPLAY());
	Ft_Gpu_CoCmd_Swap(phost);
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
}

/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void mainMenu(){
	// assign tag value to button 
	// create button 
	Ft_Gpu_Hal_WrCmd32(phost,TAG(attn));
	Ft_Gpu_CoCmd_Button(phost,disWid/2 - disWid*0.25/2,(disHei*0.29),(disWid*0.25),(disHei*0.112),font,0,"  Attenuation  ");
	
	Ft_Gpu_Hal_WrCmd32(phost,TAG(hist));
	Ft_Gpu_CoCmd_Button(phost,disWid/2 - disWid*0.25/2,(disHei*0.42),(disWid*0.25),(disHei*0.112),font,0,"  History  ");
	
	Ft_Gpu_Hal_WrCmd32(phost,TAG(sett));
	Ft_Gpu_CoCmd_Button(phost,disWid/2 - disWid*0.25/2,(disHei*0.55),(disWid*0.25),(disHei*0.112),font,0,"  Setting  ");
}

/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void attnOp(){
	tag = 0;
	do {
		disStart();
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		// draw RSSI boxes
		Ft_Gpu_CoCmd_Append(phost, attnStart, attnEnd);
		// draw back button
		Ft_Gpu_CoCmd_Append(phost, backStart, backEnd);
		//draw title
		drawTitle("Attenuation");
		disEnd();
		delay_ms(50);
	} while (tag != back);
}

/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void historyOp(){
	tag = 0;
	do {
		disStart();
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		Ft_Gpu_CoCmd_Append(phost,backStart,backEnd);
		drawTitle("History");
		disEnd();
		delay_ms(50);
	} while (tag != back);
}

void rssiOp(){
	
}

/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
void settingOp(){
	tag = 0;
	do {
		disStart();
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		Ft_Gpu_CoCmd_Append(phost, backStart, backEnd);
		drawTitle("Setting");
		disEnd();
		delay_ms(50);
	} while (tag != back);
}

// calibrate the screen, always good to do 
void calScreen(){
	disStart();
	Ft_Gpu_CoCmd_Text(phost,disWid/2,disHei/2,30,OPT_CENTERX|OPT_CENTERY,"Please tap on the dot");

	/* Calibration */
	Ft_Gpu_CoCmd_Calibrate(phost,0);
	disEnd();
}

// draw box for RSSI value based on x y cord 
void drawRect(int x, int y, double freq){
	// draw rounded rectangles
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(RECTS));
 	Ft_Gpu_Hal_WrCmd32(phost, LINE_WIDTH(10 * 16));
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(50));		// transparency apparently
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_RGB(255,255,255));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x * 16, y * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F((x + boxWid) * 16, (y + boxHei) * 16));
	//draw lines
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(LINES));
	Ft_Gpu_Hal_WrCmd32(phost, LINE_WIDTH(2 * 16));
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(100));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F((x + boxWid/4) * 16, (y + 10) * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F((x + boxWid/4) * 16, (y+boxHei - 10) * 16) );
	// put the labels on
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(255));
	if (freq == 2.45){
		Ft_Gpu_CoCmd_Text(phost,x+boxWid/8-1,y+boxHei-20,26,OPT_CENTERX|OPT_CENTERY,"GHz");
		Ft_Gpu_CoCmd_Text(phost,x+boxWid/8-1,y+boxHei-75,29,OPT_CENTERX|OPT_CENTERY,"2.45");
	}else {
		Ft_Gpu_CoCmd_Text(phost,x+boxWid/8-1,y+boxHei-20,26,OPT_CENTERX|OPT_CENTERY,"MHz");
		if (freq == 915)
			Ft_Gpu_CoCmd_Text(phost,x+boxWid/8-1,y+boxHei-75,29,OPT_CENTERX|OPT_CENTERY,"915");
		else	Ft_Gpu_CoCmd_Text(phost,x+boxWid/8-1,y+boxHei-75,29,OPT_CENTERX|OPT_CENTERY,"40.68");
	}
	Ft_Gpu_CoCmd_Text(phost,x+boxWid-60,y+boxHei/2,31,OPT_CENTERX|OPT_CENTERY," dB ");
}

void drawTitle(char *title){
	Ft_Gpu_Hal_WrCmd32(phost, SCISSOR_XY(disWid/3,0));
	Ft_Gpu_Hal_WrCmd32(phost, SCISSOR_SIZE((disWid*3/2), 50));
	Ft_Gpu_CoCmd_Gradient(phost, disWid/3*2,0, 0x8B90FF, disWid/3*2, 50,0x2933FF);
//	Ft_Gpu_CoCmd_Gradient(phost, disWid/3,0, 0x2933FF, disWid, 50,0x8B90FF);
	Ft_Gpu_CoCmd_Text(phost, (disWid/3*2), 30, 30, OPT_CENTER, title);
	Ft_Gpu_Hal_WrCmd32(phost, CLEAR(0,1,1));
}

void drawBack(){
	Ft_Gpu_Hal_WrCmd32(phost,TAG(back));
	Ft_Gpu_CoCmd_Button(phost,0, 0,(disWid*0.125),(disHei*0.112),font,0,"  Back  ");
}

void drawOrder(char start, int xloc, int yloc){
	for(char i = start; i < start + 10; i++){
		Ft_Gpu_CoCmd_Number(phost, xloc, yloc, font, 3, i);
		yloc += 30;
	}
}

/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */

