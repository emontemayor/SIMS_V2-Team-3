/*
 * uart_ib.c
 *
 * Created: 4/8/2018 4:54:00 PM
 *  Author: Dan
 */ 

#include "uart_ib.h"

/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/


/************************************************************************/
/*                                Globals                               */
/************************************************************************/
static struct usart_module uartib_inst;



void uartib_init(void)
{
    struct usart_config config_usart;
    usart_get_config_defaults(&config_usart);
    
    config_usart.baudrate    = UART_IB_BAUD;
    config_usart.mux_setting = UART_IB_PINMUX;
    config_usart.pinmux_pad0 = UTX_IB;
    config_usart.pinmux_pad1 = URX_IB;
    config_usart.pinmux_pad2 = PINMUX_UNUSED;
    config_usart.pinmux_pad3 = PINMUX_UNUSED;
    config_usart.generator_source = UART_IB_CLK;
    config_usart.transfer_mode = USART_TRANSFER_ASYNCHRONOUSLY;
    
    while (usart_init(&uartib_inst, UART_IB, &config_usart) != STATUS_OK);
    
    // enable the uart
    usart_enable(&uartib_inst);
}


void uartib_deinit(void)
{
    usart_disable(&uartib_inst);
}

uint8_t uartib_get_169_rssi(void)
{
    uint16_t read_val;
    
    usart_write_wait(&uartib_inst, 'A');
    usart_read_wait(&uartib_inst, &read_val);
    
    return (uint8_t) read_val;
}

uint8_t uartib_get_915_rssi(void)
{
    uint16_t read_val;
    
    usart_write_wait(&uartib_inst, 'M');
    usart_read_wait(&uartib_inst, &read_val);
    
    return (uint8_t) read_val;
}

uint8_t uartib_get_245_rssi(void)
{
    uint16_t read_val;
    
    usart_write_wait(&uartib_inst, 'R');
    usart_read_wait(&uartib_inst, &read_val);
    
    return (uint8_t) read_val;
}

