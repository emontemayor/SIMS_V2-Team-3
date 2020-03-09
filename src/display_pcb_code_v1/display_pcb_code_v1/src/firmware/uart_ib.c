/**********************************************
 * uart_ib.c
 * Function definitions for inter-board UART. Only
 * used by the display controller.
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/

#include "uart_ib.h"

/************************************************************************/
/*                                Globals                               */
/************************************************************************/
static struct usart_module uartib_inst;


/* Function Name    : uartib_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes the UART SERCOM for inter-board communication
 */
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


/* Function Name    : uartib_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Deinitializes the inter-board UART SERCOM
 */
void uartib_deinit(void)
{
    usart_disable(&uartib_inst);
}


/* Function Name    : uartib_get_169_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 169 MHz RSSI and returns it as a 2 byte int.
 */
status_code_genare_t uartib_get_169_rssi(rssi_t* new_rssi)
{
    union{
        rssi_t f_val;
        uint8_t f_bytes[RSSI_SIZE];
    }float_bytes;
    
    status_code_genare_t ret_val = 0;
    
    usart_write_wait(&uartib_inst, 'A');
    ret_val = usart_read_buffer_wait(&uartib_inst, float_bytes.f_bytes, RSSI_SIZE);
    
    *new_rssi = float_bytes.f_val;
    
    return ret_val;
}


/* Function Name    : uartib_get_915_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 915 MHz RSSI and returns it as a 2 byte int.
 */
status_code_genare_t uartib_get_915_rssi(rssi_t* new_rssi)
{
    union{
        rssi_t f_val;
        uint8_t f_bytes[RSSI_SIZE];
    }float_bytes;
    
    status_code_genare_t ret_val = 0;
    
    usart_write_wait(&uartib_inst, 'M');
    ret_val = usart_read_buffer_wait(&uartib_inst, float_bytes.f_bytes, RSSI_SIZE);
    
    *new_rssi = float_bytes.f_val;
    
    return ret_val;
}

/* Function Name    : uartib_get_245_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 2.45 GHz RSSI and returns it as a 2 byte int.
 */
status_code_genare_t uartib_get_245_rssi(rssi_t* new_rssi)
{
    union{
        rssi_t f_val;
        uint8_t f_bytes[RSSI_SIZE];
    }float_bytes;
    
    status_code_genare_t ret_val = 0;
    
    usart_write_wait(&uartib_inst, 'R');
    ret_val = usart_read_buffer_wait(&uartib_inst, float_bytes.f_bytes, RSSI_SIZE);
    
    *new_rssi = float_bytes.f_val;
    
    return ret_val;
}

