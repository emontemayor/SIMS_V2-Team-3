/*
 * uart_fiber.c
 *
 * Created: 4/8/2018 4:54:00 PM
 *  Author: Dan
 */ 

#include "uart_fiber.h"
#include "SIM_PIN_DEF.h"


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

status_code_genare_t uartfiber_get_169_rssi(rssi_t* new_rssi)
{
    union{
        rssi_t f_val;
        uint8_t f_bytes[RSSI_SIZE];
    }float_bytes;
    
    status_code_genare_t ret_val = 0;
    
    usart_write_wait(&uartfiber_inst, 'A');
    ret_val = usart_read_buffer_wait(&uartfiber_inst, float_bytes.f_bytes, RSSI_SIZE);
    
    *new_rssi = float_bytes.f_val;
    
    return ret_val;
}

status_code_genare_t uartfiber_get_915_rssi(rssi_t* new_rssi)
{
    union{
        rssi_t f_val;
        uint8_t f_bytes[RSSI_SIZE];
    }float_bytes;
     
    status_code_genare_t ret_val = 0;
    
    usart_write_wait(&uartfiber_inst, 'M');
    ret_val = usart_read_buffer_wait(&uartfiber_inst, float_bytes.f_bytes, RSSI_SIZE);
    
    *new_rssi = float_bytes.f_val;
    
    return ret_val;
}

status_code_genare_t uartfiber_get_245_rssi(rssi_t* new_rssi)
{
    union{
        rssi_t f_val;
        uint8_t f_bytes[RSSI_SIZE];
    }float_bytes;
     
    status_code_genare_t ret_val = 0;
    
    usart_write_wait(&uartfiber_inst, 'R');
    ret_val = usart_read_buffer_wait(&uartfiber_inst, float_bytes.f_bytes, RSSI_SIZE);
    
    *new_rssi = float_bytes.f_val;
    
    return ret_val;
}

void uartfiber_test(void)
{
    
    usart_write_wait(&uartfiber_inst, 'A');
}

