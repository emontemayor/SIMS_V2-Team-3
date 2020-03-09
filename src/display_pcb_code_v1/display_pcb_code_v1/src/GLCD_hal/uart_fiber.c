/*
 * uart_fiber.c
 *
 * Created: 4/8/2018 4:54:00 PM
 *  Author: Dan
 */ 

#include "uart_fiber.h"

/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/


/************************************************************************/
/*                                Globals                               */
/************************************************************************/
static struct usart_module uartfiber_inst;


void uartfiber_init(void)
{
    struct usart_config config_usart;
    usart_get_config_defaults(&config_usart);
    
    config_usart.baudrate    = UART_FIBER_BAUD;
    config_usart.mux_setting = UART_FIBER_PINMUX;
    config_usart.pinmux_pad0 = UTX_FIBER;
    config_usart.pinmux_pad1 = URX_FIBER;
    config_usart.pinmux_pad2 = PINMUX_UNUSED;
    config_usart.pinmux_pad3 = PINMUX_UNUSED;
    config_usart.generator_source = UART_FIBER_CLK;
    config_usart.transfer_mode = USART_TRANSFER_ASYNCHRONOUSLY;
    
    while (usart_init(&uartfiber_inst, UART_FIBER, &config_usart) != STATUS_OK);
    
    // enable the uart
    usart_enable(&uartfiber_inst);
}


void uartfiber_deinit(void)
{
    usart_disable(&uartfiber_inst);
}

uint8_t uartfiber_get_169_rssi(void)
{
    uint16_t read_val;
    
    usart_write_wait(&uartfiber_inst, 'A');
    usart_read_wait(&uartfiber_inst, &read_val);
    
    return (uint8_t) read_val;
}

uint8_t uartfiber_get_915_rssi(void)
{
    uint16_t read_val;
    
    usart_write_wait(&uartfiber_inst, 'M');
    usart_read_wait(&uartfiber_inst, &read_val);
    
    return (uint8_t) read_val;
}

uint8_t uartfiber_get_245_rssi(void)
{
    uint16_t read_val;
    
    usart_write_wait(&uartfiber_inst, 'R');
    usart_read_wait(&uartfiber_inst, &read_val);
    
    return (uint8_t) read_val;
}

