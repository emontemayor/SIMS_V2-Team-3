/*

Copyright (c) Bridgetek Pte Ltd

THIS SOFTWARE IS PROVIDED BY BRIDGETEK PTE LTD "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
BRIDGETEK PTE LTD BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES LOSS OF USE, DATA, OR PROFITS OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

BRIDGETEK DRIVERS MAY BE USED ONLY IN CONJUNCTION WITH PRODUCTS BASED ON BRIDGETEK PARTS.

BRIDGETEK DRIVERS MAY BE DISTRIBUTED IN ANY FORM AS LONG AS LICENSE INFORMATION IS NOT MODIFIED.

IF A CUSTOM VENDOR ID AND/OR PRODUCT ID OR DESCRIPTION STRING ARE USED, IT IS THE
RESPONSIBILITY OF THE PRODUCT MANUFACTURER TO MAINTAIN ANY CHANGES AND SUBSEQUENT WHQL
RE-CERTIFICATION AS A RESULT OF MAKING THESE CHANGES.

Abstract:

This file contains is functions for all UI fields.

Author : BRIDGETEK

Revision History:
0.1 - date 2013.04.24 - Initial version
0.2 - date 2014.04.28 - Split in individual files according to platform
1.0 - date 2014.11.24 - Addition of FT81X
1.1 - date 2015.01.15 - Addition of module specific configurations switches. Especially for MM900 modules
1.2 - data 2017.03.24 - Addition of GPIOs pin definitions
*/

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

/*================ Configuration ================*/

/* FT900 Platform */
#define FT900_PLATFORM                                (1)

/* Module specific configurations */
#define MM900EV1A                                    (1)
//#define MM900EV2A                                    (1)
//#define MM900EV3A                                    (1)
//#define MM900EV_LITE                                 (1)

#if (defined(MM900EV1A) || defined(MM900EV2A) || defined(MM900EV3A) || defined(MM900EV_LITE))

/* RTC configurations */
#define FT900_PLATFORM_RTC_I2C                         (1)
#define RTC_PRESENT                                    (1) 

#endif

//#define ME800A_HV35R                                (1)
//#define ME810A_HV35R                                (1)
//#define ME813A_WV7C                                 (1)
//#define ME812A_WH50R                                (1)
#define ME813A_WH50C                                (1)
//#define ME810A_WH70R                                (1)    
//#define ME811A_WH70C                                (1)


#ifdef ME800A_HV35R
#define ENABLE_SPI_SINGLE                           (1)
#define FT800_ENABLE                                (1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT            (1)
#define ENABLE_ILI9488_HVGA_PORTRAIT                (1)
#define RESISTANCE_THRESHOLD                        (1800)
#endif /* #ifdef ME800A_HV35R */

#ifdef ME810A_HV35R
#define ENABLE_SPI_QUAD                             (1)
#define FT810_ENABLE                                (1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT            (1)
#define ENABLE_ILI9488_HVGA_PORTRAIT                (1)
#define RESISTANCE_THRESHOLD                        (1800)
#endif /* #ifdef ME800A_HV35R */

#ifdef ME813A_WV7C
#define ENABLE_SPI_QUAD                             (1)
#define FT813_ENABLE                                (1)
#define DISPLAY_RESOLUTION_WVGA                     (1)
#endif /* #ifdef ME813A_WV7C */

#ifdef ME812A_WH50R
#define ENABLE_SPI_QUAD                             (1)
#define FT812_ENABLE                                (1)
#define DISPLAY_RESOLUTION_WVGA                     (1)
#define RESISTANCE_THRESHOLD                        (1800)
#endif /* #ifdef ME812A_WH50R */

#ifdef ME813A_WH50C
#define ENABLE_SPI_QUAD                             (1)
#define FT813_ENABLE                                (1)
#define DISPLAY_RESOLUTION_WVGA                     (1)
#endif /* #ifdef ME813A_WH50C */

#ifdef ME810A_WH70R
#define ENABLE_SPI_QUAD                             (1)
#define FT810_ENABLE                                (1)
#define DISPLAY_RESOLUTION_WVGA                     (1)
#define RESISTANCE_THRESHOLD                        (1800)
#endif /* #ifdef ME810A_WH70R */

#ifdef ME811A_WH70C
#define ENABLE_SPI_QUAD                             (1)
#define FT811_ENABLE                                (1)
#define DISPLAY_RESOLUTION_WVGA                     (1)
#endif /* #ifdef ME811A_WH70C */

/* Individual configurations if module specific configurations are not defined */
/* Enable the respective macros based on the custom platform */
#if (!defined(ME800A_HV35R) && !defined(ME810A_HV35R) && !defined(ME813A_WV7C) && !defined(ME812A_WH50R) && !defined(ME813A_WH50C) && !defined(ME810A_WH70R) && !defined(ME811A_WH70C))

/* platform specific macros */
#define FT900_PLATFORM                              (1)
/* Display configuration specific macros */
#define DISPLAY_RESOLUTION_QVGA                     (1)
#define DISPLAY_RESOLUTION_WQVGA                    (1)
#define DISPLAY_RESOLUTION_WVGA                     (1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT            (1)

/* Chip configuration specific macros */
#define FT800_ENABLE                                (1)
#define FT801_ENABLE                                (1)
#define FT810_ENABLE                                (1)
#define FT811_ENABLE                                (1)
#define FT812_ENABLE                                (1)
#define FT813_ENABLE                                (1)

/* SPI specific macros - compile time switches for SPI single, dial and quad use cases */
#define ENABLE_SPI_SINGLE                            (1)
#define ENABLE_SPI_DUAL                              (1)
#define ENABLE_SPI_QUAD                              (1)

/* Display driver configurations - mainly for ME900EV1 modules */
#define ENABLE_ILI9488_HVGA_PORTRAIT                (1)

#endif /* #if (!defined(ME800A) && !defined(ME813A)) */


#if (defined(FT800_ENABLE) || defined(FT801_ENABLE))
#define FT80X_ENABLE                                (1)
#endif

#if (defined(FT810_ENABLE) || defined(FT811_ENABLE) || defined(FT812_ENABLE) || defined(FT813_ENABLE))
#define FT81X_ENABLE                                (1)
#endif

#if (defined(FT900_PLATFORM) || defined(FT93X_PLATFORM))
#define FT9XX_PLATFORM                                (1)
#endif

/* Type of file to load from SDCard or Windows file system */
#define LOADIMAGE 1  //loadimage command takes destination address and options before the actual bitmap data
#define INFLATE 2    //inflate command takes destination address before the actual bitmap
#define LOAD 3       //load bitmaps directly

/* Standard C libraries */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* FT900 libraries */
#include "ft900_uart_simple.h"
#include "ft900_sdhost.h"
#include "ft900_spi.h"
#include "ft900_gpio.h"
#include "ft900_rtc.h"
#include "ft900_interrupt.h"
#include "ft900_i2cm.h"
#include "ft900.h"
#include "ft900_delay.h"


/*================ Type definition ================*/
typedef char             bool_t;
#define TRUE     (1)
#define FALSE    (0)

typedef char             char8_t;
typedef unsigned char    uchar8_t;
typedef signed char      schar8_t;
typedef float            float_t;

#define prog_uchar8_t  uchar8_t __flash__ const
#define prog_char8_t   char8_t __flash__ const
#define prog_uint8_t uint8_t __flash__ const
#define prog_int8_t int8_t __flash__ const
#define prog_uint16_t  uint16_t __flash__ const
#define prog_int16_t  int16_t __flash__ const
#define PROGMEM __flash__


/* HAL inclusions */

#include "Gpu.h"
#include "Gpu_Hal.h"
#include "CoPro_Cmds.h"
#include "Hal_Utils.h"
#include "ILI9488.h"

/* Hardware or Module specific macros for gpio line numbers  */
#if (defined(MM900EV1A) || defined(MM900EV2A) || defined(MM900EV3A) || defined(MM900EV_LITE))
#define FT800_SEL_PIN   0  /* This specify SPI channel number (0-7) in FT9xx platform */
#define FT800_PD_N      43
#undef RESISTANCE_THRESHOLD
#define RESISTANCE_THRESHOLD                        (2100)

/* Timer 1 is been utilized in case of FT900 platform */
#define    FT900_MILLIS_TIMER                    (timer_select_b)
#define FT900_TIMER_MAX_VALUE                     (65536L)
#define FT900_TIMER_PRESCALE_VALUE                 (100)
#define FT900_TIMER_OVERFLOW_VALUE                 (1000)

#endif


#define GPIO_UART0_TX     48
#define GPIO_UART0_RX     49

#define GPIO_SPIM_CLK     27
#define GPIO_SPIM_SS0     28
#define GPIO_SPIM_MOSI    29
#define GPIO_SPIM_MISO    30

#define GPIO_SPIM_IO2   31
#define GPIO_SPIM_IO3   32

#define GPIO_SPIM_SS1    33
#define GPIO_SPIM_SS2    34

#define GPIO_ILI9488_CS1 33
#define GPIO_ILI9488_DCX 34
#define GPIO_PWD 43

#define pad_ili9488_dcx  pad_gpio34
#define pad_ili9488_cs1  pad_gpio33
#define pad_pwd          pad_gpio43

#define GPIO_SD_CLK  (19)
#define GPIO_SD_CMD  (20)
#define GPIO_SD_DAT3 (21)
#define GPIO_SD_DAT2 (22)
#define GPIO_SD_DAT1 (23)
#define GPIO_SD_DAT0 (24)
#define GPIO_SD_CD   (25)
#define GPIO_SD_WP   (26)
    
#endif /*_PLATFORM_H_*/
/* Nothing beyond this*/




