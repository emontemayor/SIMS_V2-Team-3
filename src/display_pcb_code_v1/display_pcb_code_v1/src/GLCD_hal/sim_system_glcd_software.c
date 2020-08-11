/**********************************************
 * sim_system_glcd_software.c
 * Function definitions for higher level software
 * functions for the GLCD.
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#include "sim_system_glcd_software.h"


/************************************************************************/
/*                                Globals                               */
/************************************************************************/
bool lcd_new_int_flag = false;

static uint32_t ramg_buff_wp = 0;
static Ft_Gpu_Hal_Context_t* lcd_firmware_phost;
static volatile uint8_t lcd_int_flags = 0xff;


/************************************************************************/
/*                                Functions                             */
/************************************************************************/
/* Function Name    : lcd_init_seq
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Initialization sequence as described by the 
 *  FT81X_Series_Programmer_Guide datasheet pg 11.
 */
void lcd_init_seq(void)
{
    uint8_t result;
    
    /* medium rare power cycle to get the LCD into a known state.
     * Medium rare because it resets a lot of things, but sometimes display
     * list behavior is funky even after this power cycle. It is recommended
     * that the user performs a hard power reset when testing display 
     * list stuff. */
    lcd_powerdown();
    delay_ms(20);
    lcd_powerup();
    delay_ms(20);
    
    // indicate that an external clock is being used
    lcd_host_cmd(CLKEXT, NO_PARAM);
    
    // wait a little bit, because CLKEXT triggers a software reset
    delay_ms(50);
    // wake up the LCD
    lcd_host_cmd(ACTIVE, NO_PARAM);
    
    // wait until the LCD is active
	do{
	    result = lcd_rd16(REG_ID);
	} while(result != 0x7c);  
    
    // Register settings, refer to NHD-5.0-800480FT-CTXL-CTP datasheet:
    // horizontal configuration registers
    lcd_wr16(REG_HSIZE, 800);
    lcd_wr16(REG_HCYCLE, 928);
    lcd_wr16(REG_HOFFSET, 88);
    lcd_wr16(REG_HSYNC0, 0);
    lcd_wr16(REG_HSYNC1, 48);
    
    // vertical configuration registers
    lcd_wr16(REG_VSIZE, 480);
    lcd_wr16(REG_VCYCLE, 525);
    lcd_wr16(REG_VOFFSET, 32);
    lcd_wr16(REG_VSYNC0, 0);
    lcd_wr16(REG_VSYNC1, 3);

    // misc. screen configuration registers
	lcd_wr8(REG_SWIZZLE, 0);
	lcd_wr8(REG_PCLK_POL, 0);
	lcd_wr8(REG_CSPREAD, 1);
	lcd_wr8(REG_DITHER, 1);

    // clear the display
    lcd_wr32(RAM_DL+0, CLEAR_COLOR_RGB(1, 1, 1));
    lcd_wr32(RAM_DL+4, COLOR_RGB(255,255,255));
    lcd_wr32(RAM_DL+8, CLEAR(1,1,1));
    lcd_wr32(RAM_DL+12, DISPLAY());

    // display list swap
    lcd_wr8(REG_DLSWAP,DLSWAP_FRAME);

    // set the pin drive strength
    lcd_wr16(REG_GPIOX_DIR, 0xffff);
    lcd_wr16(REG_GPIOX, 0xffff);

    // enable the clock
    lcd_wr8(REG_PCLK,2);
}


/* Function Name    : lcd_test
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Displays a test image for the LCD. Reference 
 *  FT81X_Series_Programmer_Guide datasheet pg 14.
 */
void lcd_test(void)
{
    // clear screen
	lcd_wr32(RAM_DL + 0, CLEAR(1, 1, 1)); 
    // start drawing bitmaps
	lcd_wr32(RAM_DL + 4, BEGIN(BITMAPS)); 
    // ascii F in font 31
	lcd_wr32(RAM_DL + 8, VERTEX2II(220, 110, 31, 'F'));  
    // ascii T
	lcd_wr32(RAM_DL + 12, VERTEX2II(244, 110, 31, 'T')); 
    // ascii D
	lcd_wr32(RAM_DL + 16, VERTEX2II(270, 110, 31, 'D')); 
    // ascii I
	lcd_wr32(RAM_DL + 20, VERTEX2II(299, 110, 31, 'I')); 
    // end of drawing bitmaps
	lcd_wr32(RAM_DL + 24, END());
    // change colour to red
	lcd_wr32(RAM_DL + 28, COLOR_RGB(160, 22, 22));  
    // set point size to 20 pixels in radius     
	lcd_wr32(RAM_DL + 32, POINT_SIZE(320));   
    // start drawing points
	lcd_wr32(RAM_DL + 36, BEGIN(CMD_TOGGLE)); 
    // red, filled circle
	lcd_wr32(RAM_DL + 40, VERTEX2II(192, 133, 0, 0)); 
    // end of drawing points
	lcd_wr32(RAM_DL + 44, END());
    // end of current display list
	lcd_wr32(RAM_DL + 48, DISPLAY()); 
    
    // display list swap
    lcd_wr8(REG_DLSWAP, DLSWAP_FRAME);
}


/* Function Name    : lcd_clear
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Clears the LCD to a black screen
 */
void lcd_clear(void)
{
    lcd_wr32(RAM_DL+0, CLEAR_COLOR_RGB(1, 1, 1));
    lcd_wr32(RAM_DL+4, CLEAR(1,1,1));
    lcd_wr32(RAM_DL+8, DISPLAY());
    lcd_wr8(REG_DLSWAP, DLSWAP_FRAME);
    delay_ms(20);
}


/* Function Name    : lcd_putchar_ramg
 * Parameters       : ch (char)
 * Return Values(s) : void
 * Description      : The putchar function for lcd_printf. Writes the character
 *  to the GLCD's RAM_G (general purpose RAM).
 */
void lcd_putchar_ramg(char ch)
{
    static uint16_t x_coord = 0;
    static uint16_t y_coord = 0;
    
    // if it's a newline, go to next line by adjusting the coordinates
    if(ch == '\n')
    {
        x_coord = 0;
        y_coord += DEBUG_FONT_H;
    }      
    else if(ch == '\r')
    {
        return;
    }  
    else
    {
        // put the next character in the string
        lcd_wr32(RAM_G + ramg_buff_wp, VERTEX2II(x_coord, y_coord, DEBUG_FONT, ch));
        
        // increment the ramg pointer by 4
        ramg_buff_wp += 4;
        
        // increment the x coordinate variable
        x_coord += DEBUG_FONT_W;
    }        
        
    // check the bounds of the x coordinate
    if (x_coord > GLCD_W)
    {
        x_coord = 0;
        y_coord += DEBUG_FONT_H;
    }        
    
    // check the bounds of the y coordinate
    if(y_coord > GLCD_H)
    {
        x_coord = 0;
        y_coord = 0;
        ramg_buff_wp = 0;
    }        
}


/* Function Name    : lcd_printf
 * Parameters       : fmt (const string) and va_args
 * Return Values(s) : void
 * Description      : Custom printf for the GLCD. Writes formatted string 
 *  to the the GLCD's RAM_G memory space. This memory space (at the
 *  time of writing this) is used to keep text persistent on the GLCD when
 *  using this function more than once. Will not work with other GLCD display
 *  list commands. Used for debugging purposes only.
 */
void lcd_printf(const char *fmt, ...)
{
    char buf[128], *p;
    
    va_list ap;
    
    // va_args stuff. How it works? Idk, look it up.
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    for(p = buf; *p; ++p)
        lcd_putchar_ramg(*p);
    va_end(ap);
    
    // GLCD display list start, using coprocessor commands
    Ft_Gpu_CoCmd_Dlstart(lcd_firmware_phost);
    // clear the GLCD
    Ft_Gpu_Hal_WrCmd32(lcd_firmware_phost,CLEAR(1,1,1));
    // indicate bitmaps are going to be drawn (i.e. the GLCD's ROM fonts)
    Ft_Gpu_Hal_WrCmd32(lcd_firmware_phost, BEGIN(BITMAPS));
    /* append the character write commands stored in RAM_G to the current
     * display list. */
    Ft_Gpu_CoCmd_Append(lcd_firmware_phost, RAM_G, ramg_buff_wp);
    // indicate end of bitmap drawing
    Ft_Gpu_Hal_WrCmd32(lcd_firmware_phost, END());
    // indicate end of current display list
    Ft_Gpu_Hal_WrCmd32(lcd_firmware_phost, DISPLAY());
    // swap in the display list
    Ft_Gpu_CoCmd_Swap(lcd_firmware_phost);
    // update the coprocessor FIFO to write all that ^ in
    Ft_Gpu_Hal_WaitCmdfifo_empty(lcd_firmware_phost);
}


/* Function Name    : lcd_get_ramg_size
 * Parameters       : void
 * Return Values(s) : uint32_t
 * Description      : Returns the current number of 4-byte display list
 *  commands in the GLCD's RAM_G memory space. This probably won't ever 
 *  be used, but it briefly was at one point. Kept for documentation 
 *  reasons if deprecated.
 */
uint32_t lcd_get_ramg_size(void)
{
    return ramg_buff_wp;
}


/* Function Name    : lcd_set_ft_host_ptr
 * Parameters       : phost (struct pointer from FTDI library)
 * Return Values(s) : void
 * Description      : Sets the sim_system_glcd_software global pointer for the
 *  FTDI context struct.
 */
void lcd_set_ft_host_ptr(Ft_Gpu_Hal_Context_t* phost)
{
    lcd_firmware_phost = phost;
}


/* Function Name    : lcd_interrupt_callback
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Callback for the LCD interrupt. Reads the LCD's flag
 *  register.
 */
void lcd_interrupt_callback(void)
{
    lcd_int_flags = lcd_rd8(REG_INT_FLAGS);
}


/* Function Name    : lcd_get_flags
 * Parameters       : void
 * Return Values(s) : uint8_t
 * Description      : Returns the flags acquired by the callback function.
 */
uint8_t lcd_get_flags(void)
{
    return lcd_int_flags;
}