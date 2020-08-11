/**********************************************
 * sim_system_glcd_software.h
 * Header for higher level software
 * functions for the GLCD.
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#ifndef SIM_SYSTEM_GLCD_SOFTWARE_H_
#define SIM_SYSTEM_GLCD_SOFTWARE_H_

#include <stdarg.h>
#include "sim_system_glcd_firmware.h"
#include "FT_Platform.h"

/************************************************************************/
/*                                Defines                               */
/************************************************************************/
#define LCD_INT_CONVCOMPLETE    0b10000000
#define LCD_INT_CMDFLAG         0b01000000
#define LCD_INT_CMDEMPTY        0b00100000
#define LCD_INT_PLAYBACK        0b00010000
#define LCD_INT_SOUND           0b00001000
#define LCD_INT_TAG             0b00000100
#define LCD_INT_TOUCH           0b00000010
#define LCD_INT_SWAP            0b00000001
#define LCD_DEFAULT_MASK        (LCD_INT_TAG)

#define lcd_int_enable()        lcd_wr8(REG_INT_EN, 1)
#define lcd_int_disable()       lcd_wr8(REG_INT_EN, 0)
#define lcd_int_mask(_MASK_)    lcd_wr8(REG_INT_MASK, _MASK_)

/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
/* Function Name    : lcd_init_seq
 * Parameters       : void
 * Return Values(s) : ASF general status code
 * Description      : Initializaion sequence as described by the 
 *  FT81X_Series_Programmer_Guide datasheet pg 11.
 */
void lcd_init_seq(void);


/* Function Name    : lcd_test
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Displays a test image for the LCD. Reference 
 *  FT81X_Series_Programmer_Guide datasheet pg 14.
 */
void lcd_test(void);


/* Function Name    : lcd_clear
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Clears the LCD to a black screen
 */
void lcd_clear(void);


/* Function Name    : lcd_putchar_ramg
 * Parameters       : ch (char)
 * Return Values(s) : void
 * Description      : The putchar function for lcd_printf. Writes the character
 *  to the GLCD's RAM_G (general purpose RAM).
 */
void lcd_putchar_ramg(char ch);


/* Function Name    : lcd_printf
 * Parameters       : fmt (const string) and va_args
 * Return Values(s) : void
 * Description      : Custom printf for the GLCD. Writes formatted string 
 *  to the the GLCD's RAM_G memory space. This memory space (at the
 *  time of writing this) is used to keep text persistent on the GLCD when
 *  using this function more than once. Will not work with other GLCD display
 *  list commands. Used for debugging purposes only.
 *  Compiler throws a warning without the __attribute__, which
 *  tells the compiler the function is like printf with va_args. 
 */
void lcd_printf(const char *fmt, ...) __attribute__((format(printf, 1, 0)));


/* Function Name    : lcd_get_ramg_size
 * Parameters       : void
 * Return Values(s) : uint32_t
 * Description      : Returns the current number of 4-byte display list
 *  commands in the GLCD's RAM_G memory space. This probably won't ever 
 *  be used, but it briefly was at one point. Kept for documentation 
 *  reasons if deprecated.
 */
uint32_t lcd_get_ramg_size(void);


/* Function Name    : lcd_set_ft_host_ptr
 * Parameters       : phost (struct pointer from FTDI library)
 * Return Values(s) : void
 * Description      : Sets the sim_system_glcd_software global pointer for the
 *  FTDI context struct.
 */
void lcd_set_ft_host_ptr(Ft_Gpu_Hal_Context_t* phost);


/* Function Name    : lcd_interrupt_callback
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Callback for the LCD interrupt. Reads the LCD's flag
 *  register.
 */
void lcd_interrupt_callback(void);


/* Function Name    : lcd_get_flags
 * Parameters       : void
 * Return Values(s) : uint8_t
 * Description      : Returns the flags acquired by the callback function.
 */
uint8_t lcd_get_flags(void);

#endif /* SIM_SYSTEM_GLCD_SOFTWARE_H_ */