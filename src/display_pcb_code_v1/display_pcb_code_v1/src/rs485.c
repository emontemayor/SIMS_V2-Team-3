/*
 * @file
 * @brief RS-485 Interface
 *
 * Copyright (C) 2019 Steve Karg <skarg@users.sourceforge.net>
 *
 * @page License
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
#include <string.h>
#include "bacnet/basic/sys/mstimer.h"
#include "bacnet/bits.h"
#include "bacnet/basic/sys/fifo.h"
#include "bacnet/datalink/mstpdef.h"
#include "asf.h"
#include "led.h"
#include "rs485.h"

/**
 * RS-485 bus:
 *  NOTE! RobotDyn SAMD21 shares PA14_TCC0-W4 with USB!
 *  If powered by USB, RE/DE won't work! Use the Auto DIP on RS485 shield.
 *  RE/DE pin is 14 or PA14 - 
 *
 *  Tx pin is 15 or PA10
 *  Rx pin is 16 or PA11
 */

/* buffer for storing received bytes - size must be power of two */
/* BACnet MAX_MPDU for MS/TP is 501 bytes */
static uint8_t Receive_Queue_Data[512];
static FIFO_BUFFER Receive_Queue;
/* buffer for storing bytes to transmit */
/* BACnet MAX_MPDU for MS/TP is 501 bytes */
static uint8_t RS485_Transmit_Buffer[512];
/* baud rate of the UART interface */
static uint32_t Baud_Rate;
/* flag to track RTS status */
static volatile bool Transmitting;
/* statistics */
static volatile uint32_t RS485_Transmit_Bytes;
static volatile uint32_t RS485_Receive_Bytes;

/* SAM-D21 ASF driver for USART */
static Sercom *const sercom = SERCOM0;
static struct usart_module RS485_USART_Module;
static struct usart_config RS485_USART_Config;
static struct port_config RS485_Port_Config;

/* buffer for Rx Callback */
volatile uint16_t rx_buffer[1];
volatile uint16_t tx_buffer[1];

/* amount of silence on the wire */
static struct mstimer Silence_Timer;

/**
 * @brief Reset the silence on the wire timer.
 */
void rs485_silence_reset(void)
{
    mstimer_set(&Silence_Timer, 0);
}

/**
 * @brief Determine the amount of silence on the wire from the timer.
 * @param amount of time that might have elapsed
 * @return true if the amount of time has elapsed
 */
bool rs485_silence_elapsed(uint32_t interval)
{
    return (mstimer_elapsed(&Silence_Timer) > interval);
}

/**
 * @brief Determine the turnaround time
 * @return amount of milliseconds
 */
static uint16_t rs485_turnaround_time(void)
{
    /* delay after reception before transmitting - per MS/TP spec */
    /* wait a minimum  40 bit times since reception */
    /* at least 2 ms for errors: rounding, clock tick */
    if (Baud_Rate) {
        return (2 + ((Tturnaround * 1000UL) / Baud_Rate));
    } else {
        return 2;
    }
}

/**
 * @brief Use the silence timer to determine turnaround time
 * @return true if turnaround time has expired
 */
bool rs485_turnaround_elapsed(void)
{
    return (mstimer_elapsed(&Silence_Timer) > rs485_turnaround_time());
}

/**
 * @brief RS485 RX Callback
 */
#ifdef USART_CALLBACK_MODE
static void usart_read_callback(struct usart_module *const usart_instance)
{
    if (!Transmitting) {
        FIFO_Put(&Receive_Queue, rx_buffer[0]);
        RS485_Receive_Bytes++;
    }
    usart_read_job(&RS485_USART_Module, (uint16_t *)rx_buffer);
}
#endif

/**
 * @brief RS485 RX Callback
 */
static void usart_write_callback(struct usart_module *const usart_module)
{
    /* end of packet */
    rs485_rts_enable(false);
}

/**
 * @brief Control the DE and /RE pins on the RS-485 transceiver
 * @param enable - true to set DE and /RE high, false to set /DE and RE low
 * @note  DE and /RE are controlled by pin is PA23
 */
void rs485_rts_enable(bool enable)
{
    if (enable) {
        /* DE, /RE */
        Transmitting = true;
        port_pin_set_output_level(PIN_PA14, true);
        led_tx_on();
    } else {
        /* /DE, RE */
        port_pin_set_output_level(PIN_PA14, false);
        led_tx_off();
        Transmitting = false;
    }
}

/**
 * @brief Determine the status of the transmit-enable line on the RS-485
 * transceiver
 * @return true if RTS is enabled, false if RTS is disabled
 */
bool rs485_rts_enabled(void)
{
    return Transmitting;
}

/**
 * @brief Checks for data on the receive UART, and handles errors
 * @param data register to store the byte, if available (can be NULL)
 * @return true if a byte is available
 */
bool rs485_byte_available(uint8_t *data_register)
{
    bool data_available = false; /* return value */

    if (!FIFO_Empty(&Receive_Queue)) {
        if (data_register) {
            *data_register = FIFO_Get(&Receive_Queue);
        }
        data_available = true;
    }

    return data_available;
}

/**
 * @brief returns an error indication if errors are enabled
 * @return returns true if error is detected and errors are enabled
 */
bool rs485_receive_error(void)
{
    return false;
}

/**
 * @brief Transmit one or more bytes on RS-485.
 * @param buffer - array of one or more bytes to transmit
 * @param nbytes - number of bytes to transmit
 */
bool rs485_bytes_send(uint8_t *buffer, uint16_t nbytes)
{
    enum status_code status = STATUS_OK;

    if (buffer && (nbytes > 0) && (nbytes < sizeof(RS485_Transmit_Buffer))) {
        memcpy(RS485_Transmit_Buffer, buffer, nbytes);
        rs485_rts_enable(true);
        status = usart_write_buffer_job(
            &RS485_USART_Module, RS485_Transmit_Buffer, nbytes);
        if (status == STATUS_OK) {
            RS485_Transmit_Bytes += nbytes;
        } else {
            rs485_rts_enable(false);
        }
    }

    return (status == STATUS_OK);
}

/**
 * Return the RS-485 baud rate
 *
 * @return baud - RS-485 baud rate in bits per second (bps)
 */
uint32_t rs485_baud_rate(void)
{
    return Baud_Rate;
}

/**
 * Initialize the RS-485 baud rate
 *
 * @param baudrate - RS-485 baud rate in bits per second (bps)
 *
 * @return true if set and valid
 */
bool rs485_baud_rate_set(uint32_t baudrate)
{
    bool valid = true;

    switch (baudrate) {
        case 9600:
        case 19200:
        case 38400:
        case 57600:
        case 76800:
        case 115200:
            Baud_Rate = baudrate;
            break;
        default:
            valid = false;
            break;
    }

    return valid;
}

/**
 * @brief Return the RS-485 statistics for transmit bytes
 * @return number of bytes transmitted
 */
uint32_t rs485_bytes_transmitted(void)
{
    return RS485_Transmit_Bytes;
}

/**
 * @brief Return the RS-485 statistics for receive bytes
 * @return number of bytes received
 */
uint32_t rs485_bytes_received(void)
{
    return RS485_Receive_Bytes;
}

/**
 * Initialize the USART SERCOM module clock
 */
static void rs485_clock_init(void)
{
    struct system_gclk_chan_config gclk_chan_conf;
    uint32_t gclk_index = SERCOM0_GCLK_ID_CORE;
    /* Turn on module in PM */
    system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, PM_APBCMASK_SERCOM0);
    /* Turn on Generic clock for USART */
    system_gclk_chan_get_config_defaults(&gclk_chan_conf);
    /*Default is generator 0. Other wise need to configure like below */
    /* gclk_chan_conf.source_generator = GCLK_GENERATOR_1; */
    system_gclk_chan_set_config(gclk_index, &gclk_chan_conf);
    system_gclk_chan_enable(gclk_index);
}

/**
 * Initialize the RTS pin
 */
static void rs485_pin_init(void)
{
    port_get_config_defaults(&RS485_Port_Config);
    RS485_Port_Config.direction = PORT_PIN_DIR_OUTPUT;
    RS485_Port_Config.input_pull = PORT_PIN_PULL_NONE;
    port_pin_set_config(PIN_PA14, &RS485_Port_Config);
    port_pin_set_output_level(PIN_PA14, false);
}

/**
 * Initialize the USART SERCOM module for RS485
 */
static void rs485_usart_init(void)
{
    enum status_code status;

    /* Disable this module since ASF expects it to be disabled. */
    sercom->USART.CTRLA.reg &= ~SERCOM_USART_CTRLA_ENABLE;
    // Get default settings
    usart_get_config_defaults(&RS485_USART_Config);
    RS485_USART_Config.baudrate = Baud_Rate;
    RS485_USART_Config.mux_setting = USART_RX_3_TX_2_XCK_3;
    RS485_USART_Config.pinmux_pad0 = PINMUX_UNUSED;
    RS485_USART_Config.pinmux_pad1 = PINMUX_UNUSED;
    RS485_USART_Config.pinmux_pad2 = PINMUX_PA10C_SERCOM0_PAD2;
    RS485_USART_Config.pinmux_pad3 = PINMUX_PA11C_SERCOM0_PAD3;
    status = usart_init(&RS485_USART_Module, sercom, &RS485_USART_Config);
    while (status != STATUS_OK) {
        /* hardware not initialized correctly - figure out why! */
    }
    usart_enable(&RS485_USART_Module);
#ifdef USART_CALLBACK_MODE
    usart_register_callback(&RS485_USART_Module, usart_read_callback,
        USART_CALLBACK_BUFFER_RECEIVED);
    usart_enable_callback(&RS485_USART_Module, USART_CALLBACK_BUFFER_RECEIVED);
    usart_register_callback(&RS485_USART_Module, usart_write_callback,
        USART_CALLBACK_BUFFER_TRANSMITTED);
    usart_enable_callback(
        &RS485_USART_Module, USART_CALLBACK_BUFFER_TRANSMITTED);
    system_interrupt_set_priority(
        SYSTEM_INTERRUPT_MODULE_SERCOM0, SYSTEM_INTERRUPT_PRIORITY_LEVEL_0);
    /* initial callback call to prepare to begin receiving data */
    usart_read_job(&RS485_USART_Module, (uint16_t *)rx_buffer);
#endif    
}

/* SERCOM0 UART initialization */
void rs485_init(void)
{
    /* initialize the Rx and Tx byte queues */
    FIFO_Init(&Receive_Queue, &Receive_Queue_Data[0],
        (unsigned)sizeof(Receive_Queue_Data));
    rs485_clock_init();
    rs485_pin_init();
    rs485_usart_init();
}
