/**********************************************
 * uart_fiber.c
 * Function definitions for the UART driver for the fiber optic
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#include "uart_fiber.h"

/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
static void uartfiber_read_callback(struct usart_module *const usart_module);
static void uartfiber_parse_cmd(uint8_t cmd_char);


/************************************************************************/
/*                                Globals                               */
/************************************************************************/
static struct usart_module uartfiber_inst;
static uint8_t uartfiber_rx_read;
static rssi_vals* uartfiber_rssi;


/************************************************************************/
/*                                Functions                             */
/************************************************************************/
/* Function Name    : uartfiber_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes the UART SERCOM for communicating over 
 *  fiber optic.
 */
void uartfiber_init(void)
{
    struct usart_config config_usart;
    usart_get_config_defaults(&config_usart);
    
    config_usart.baudrate = UART_FIBER_BAUD;
    config_usart.mux_setting = UART_FIBER_PINMUX;
    config_usart.pinmux_pad0 = PINMUX_UNUSED;
    config_usart.pinmux_pad1 = PINMUX_UNUSED;
    config_usart.pinmux_pad2 = UTX_FIBER;
    config_usart.pinmux_pad3 = PINMUX_UNUSED;
    config_usart.generator_source = UART_FIBER_CLK;
    config_usart.transfer_mode = USART_TRANSFER_ASYNCHRONOUSLY;
    
    while (usart_init(&uartfiber_inst, UART_FIBER, &config_usart) != STATUS_OK);
    
    // enable the uart
    usart_enable(&uartfiber_inst);
    
    // configure the callback(s) for this module
    configure_uartfiber_callbacks();
}


/* Function Name    : uartfiber_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Deinitializes the UART.
 */
void uartfiber_deinit(void)
{
    usart_disable(&uartfiber_inst);
}




/*2020 update: Following functions commented out since uartib_inst does not exist in their code.
Will investigate later.

/* Function Name    : uartib_get_169_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 169 MHz RSSI and returns it as a 2 byte int.
 */

/*
int16_t uartib_get_169_rssi(void)
{
    union{
        rssi_t f_val;
        uint8_t f_bytes[RSSI_SIZE];
    }float_bytes;
    
    usart_write_wait(&uartib_inst, 'A');
    usart_read_buffer_wait(&uartib_inst, float_bytes.f_bytes, RSSI_SIZE);
    
    
    return float_bytes.f_val;
}

*/

/* Function Name    : uartib_get_915_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 915 MHz RSSI and returns it as a 2 byte int.
 
int16_t uartib_get_915_rssi(void)
{
    union{
        rssi_t f_val;
        uint8_t f_bytes[RSSI_SIZE];
    }float_bytes;
    
    usart_write_wait(&uartib_inst, 'M');
    usart_read_buffer_wait(&uartib_inst, float_bytes.f_bytes, RSSI_SIZE);
    
    return float_bytes.f_val;
}
*/

/* Function Name    : uartib_get_245_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Polls the receiver that is in the same box as the display
 *  controller. Gets the 2.45 GHz RSSI and returns it as a 2 byte int.
 
int16_t uartib_get_245_rssi(void)
{
    union{
        rssi_t f_val;
        uint8_t f_bytes[RSSI_SIZE];
    }float_bytes;
    
    usart_write_wait(&uartib_inst, 'R');
    usart_read_buffer_wait(&uartib_inst, float_bytes.f_bytes, RSSI_SIZE);
    
    return float_bytes.f_val;
}
*/

/* Function Name    : configure_uartfiber_callbacks
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Configures the asynchronous callback function for the
 *  UART. Callback function is executed when the receiver/transmitter
 *  (depending on which callback is registered) receives/transmits a character.
 *  Kind of like an ISR, but executed in the actual ISR for the UART (handled
 *  by the ASF library).
 */
void configure_uartfiber_callbacks(void)
{
    usart_register_callback(&uartfiber_inst, uartfiber_read_callback, USART_CALLBACK_BUFFER_RECEIVED);
    
    usart_enable_callback(&uartfiber_inst, USART_CALLBACK_BUFFER_RECEIVED);
    
    // start a read buffer job so the receiver is ready
    usart_read_buffer_job(&uartfiber_inst, &uartfiber_rx_read, 1);
}


/* Function Name    : configure_uartfiber_callbacks
 * Parameters       : usart_module (uart module using the callback)
 * Return Values(s) : void
 * Description      : The callback function for the UART. Parses a character
 *  and determines if it's one of three characters that should be sent from the
 *  display controller.
 *  Starts another UART buffer job (setting up an asynchronous read).
 */
static void uartfiber_read_callback(struct usart_module *const usart_module)
{
    // passed the received character to the 
    uartfiber_parse_cmd(uartfiber_rx_read);
    
    // start a read buffer job so the receiver is ready
    usart_read_buffer_job(&uartfiber_inst, &uartfiber_rx_read, 1);
}


/* Function Name    : uartfiber_parse_cmd
 * Parameters       : cmd_char (char that represents a command)
 * Return Values(s) : void
 * Description      : Parses the passed character as a command. The char
 *  should be 'A' (for AX5043), 'M' (for MTXDOT), or 'R' (for RC2500HP).
 *  Sends the RSSI of the respective module over fiber to the
 *  display controller.
 */
static void uartfiber_parse_cmd(uint8_t cmd_char)
{
    
    union{
        rssi_t f_val;
        uint8_t f_bytes[RSSI_SIZE]; 
    }float_bytes;
    
    switch(cmd_char)
    {
        // send RSSI of 169MHz module
        case 'A':
            float_bytes.f_val = uartfiber_rssi->rssi169;
            while(usart_write_buffer_job(&uartfiber_inst, float_bytes.f_bytes, RSSI_SIZE) != STATUS_BUSY);
            break;
        
        // send RSSI of 915 MHz module
        case 'M':
            float_bytes.f_val = uartfiber_rssi->rssi915;
            while(usart_write_buffer_job(&uartfiber_inst, float_bytes.f_bytes, RSSI_SIZE) != STATUS_BUSY);
            break;
        
        // send RSSI of 2.45 GHz module
        case 'R':
            float_bytes.f_val = uartfiber_rssi->rssi245;
            while(usart_write_buffer_job(&uartfiber_inst, float_bytes.f_bytes, RSSI_SIZE) != STATUS_BUSY);
            break;
    }
}

/** 
 * Asynchronous buffer write to transmit single shield measurement
 * Simply calls "usart_write_buffer_job" with specific parameters
 */
void usart_fiber_write(struct measurement temp)
{
	struct fiber_packet pckt;
	pckt.data = temp;
	usart_write_buffer_job(&uartfiber_inst, (uint8_t*) &pckt, sizeof(pckt));
};


/* Function Name    : uartfiber_printf
 * Parameters       : fmt (formatted string), ... (vargs)
 * Return Values(s) : void
 * Description      : Printf function for this UART. Used as a debug terminal.
 */
void uartfiber_printf(const char *fmt, ...)
{
    char buf[256], *p;
    uint16_t len = 0;
    
    va_list ap;
    
    // va_args stuff.
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    len = strlen(buf);
    for(p = buf; *p; ++p)
        usart_write_buffer_job(&uartfiber_inst, (uint8_t*) buf, len);
    va_end(ap);
}


/* Function Name    : uartfiber_init_rssi
 * Parameters       : user_rssi (rssi_vals struct from rssi_mngr.h)
 * Return Values(s) : void
 * Description      : Initializes the local rssi_vals struct (uartfiber_rssi)
 *  to a user defined rssi_vals struct (user_rssi). Thus, user can change the
 *  values of user_rssi elsewhere and the changes will be reflected when the 
 *  display controller sends the rssi polling commands over the fiber optic.
 */
void uartfiber_init_rssi(rssi_vals* user_rssi)
{
    uartfiber_rssi = user_rssi;
}