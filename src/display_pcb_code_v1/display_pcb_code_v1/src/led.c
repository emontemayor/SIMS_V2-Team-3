/**
 * @file
 * @author Steve Karg
 * @date 2019
 * @brief Handle the configuration and set/clear of the LEDs.
 *
 * @section LICENSE
 *
 * Copyright (C) 2011 Steve Karg <skarg@users.sourceforge.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <stdint.h>
#include "asf.h"
#include "led.h"

/**
 * @brief Turn on LED
 */
void led_on(void)
{
    port_pin_set_output_level(PIN_PA17, true);
}

/**
 * @brief Turn off LED
 */
void led_off(void)
{
    port_pin_set_output_level(PIN_PA17, false);
}

/**
 * @brief Turn on Transmit LED
 */
void led_tx_on(void)
{
    port_pin_set_output_level(PIN_PA27, false);
}

/**
 * @brief Turn off Transmit LED
 */
void led_tx_off(void)
{
    port_pin_set_output_level(PIN_PA27, true);
}

/**
 * @brief Turn on Transmit LED
 */
void led_rx_on(void)
{
    port_pin_set_output_level(PIN_PB03, false);
}

/**
 * @brief Turn off Transmit LED
 */
void led_rx_off(void)
{
    port_pin_set_output_level(PIN_PB03, true);
}

/**
 * @brief Initialize the LED hardware
 */
void led_init(void)
{
    struct port_config LED_Port_Config;

    /* Configure LEDs */
    port_get_config_defaults(&LED_Port_Config);
    LED_Port_Config.direction = PORT_PIN_DIR_OUTPUT;
    LED_Port_Config.input_pull = PORT_PIN_PULL_NONE;
    port_pin_set_config(PIN_PB03, &LED_Port_Config);
    port_pin_set_output_level(PIN_PB03, false);

    port_get_config_defaults(&LED_Port_Config);
    LED_Port_Config.direction = PORT_PIN_DIR_OUTPUT;
    LED_Port_Config.input_pull = PORT_PIN_PULL_NONE;
    port_pin_set_config(PIN_PA27, &LED_Port_Config);
    port_pin_set_output_level(PIN_PA27, false);

    port_get_config_defaults(&LED_Port_Config);
    LED_Port_Config.direction = PORT_PIN_DIR_OUTPUT;
    LED_Port_Config.input_pull = PORT_PIN_PULL_NONE;
    port_pin_set_config(PIN_PA17, &LED_Port_Config);
    port_pin_set_output_level(PIN_PA17, false);
}
