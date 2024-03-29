/*
 * uart_915_driver.c
 *
 * Created: 3/23/2018 12:57:58 AM
 *  Author: Dan Filbey
 */ 


#include "uart_915_driver.h"
#include "simsys_ringbuff.h"


/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
static void uart915_read_callback(struct usart_module *const usart_module);
static bool uart915_parse_response(uint8_t next_char);


/************************************************************************/
/*                                Globals                               */
/************************************************************************/
// UART instance (struct) for interacting with ASF UART functions
static struct usart_module uart915_inst;
// single byte read buffer
static uint8_t uart915_rx_read;
// array for a ring buffer
static uint8_t uart915_rx_buff[UART915_RX_BUFF_SIZE];
// ring buffer instance (struct)
static ringbuff_t uart915_ringbuff = {uart915_rx_buff, 0, 0, UART915_RX_BUFF_SIZE};
// states for the state machine
static volatile enum RX_STATES{START = 0, O_RX, K_RX, CR_RX} rx_state;
// flag for determing if a "OK\r\n" response was received
static volatile bool flag_ok_received = false;


/************************************************************************/
/*                                Functions                             */
/************************************************************************/
/* Function Name    : uart915_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes the SERCOM UART for communication with the
 *  MTXDOT module.
 */
void uart915_init(void)
{
    struct usart_config config_usart;
    usart_get_config_defaults(&config_usart);
    
    // configure the UART
    config_usart.baudrate    = UART915_BAUD;
    config_usart.mux_setting = UART915_PINMUX;
    config_usart.pinmux_pad0 = UTX915;
    config_usart.pinmux_pad1 = URX915;
    config_usart.pinmux_pad2 = PINMUX_UNUSED;
    config_usart.pinmux_pad3 = PINMUX_UNUSED;
    config_usart.generator_source = UART915_CLK;
    config_usart.transfer_mode = USART_TRANSFER_ASYNCHRONOUSLY;
    
    // initialize the uart module until an STATUS_OK is returned
    while (usart_init(&uart915_inst, UART915, &config_usart) != STATUS_OK);
    
    // enable the uart
    usart_enable(&uart915_inst);
    
    // configure the callback(s) for this module
    configure_915uart_callbacks();
}


/* Function Name    : uart915_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Deinitializes the SERCOM UART.
 */
void uart915_deinit(void)
{
    usart_disable(&uart915_inst);
}


/* Function Name    : configure_uart915_callbacks
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Configures the asynchronous callback function for the 
 *  UART. Callback function is executed when the receiver/transmitter 
 *  (depending on which callback is registered) receives/transmits a character.
 *  Kind of like an ISR, but executed in the actual ISR for the UART (handled
 *  by the ASF library).
 */
void configure_915uart_callbacks(void)
{
    usart_register_callback(&uart915_inst, uart915_read_callback, USART_CALLBACK_BUFFER_RECEIVED);
    
    usart_enable_callback(&uart915_inst, USART_CALLBACK_BUFFER_RECEIVED);
    
    // start a read buffer job so the receiver is ready
    usart_read_buffer_job(&uart915_inst, &uart915_rx_read, 1);
}


/* Function Name    : uart915_read_callback
 * Parameters       : usart_module (uart module using the callback)
 * Return Values(s) : void
 * Description      : The callback function for the UART. Puts the received
 *  character into a ring buffer and parses the character to find out if the 
 *  character is a part of a "OK\r\n" response from the MTXDOT module. Starts
 *  another UART buffer job (setting up an asynchronous read). 
 */
static void uart915_read_callback(struct usart_module *const usart_module)
{
    // put the received byte into the ring buffer
    ringbuff_put(&uart915_ringbuff, uart915_rx_read);
    
    // parse the character to see if it is an OK
    flag_ok_received = uart915_parse_response(uart915_rx_read);
    
    // start another read buffer job
    usart_read_buffer_job(usart_module, &uart915_rx_read, 1);
}


/* Function Name    : uart915_parse_response
 * Parameters       : next_char (next char received by the UART)
 * Return Values(s) : bool
 * Description      : Parses characters and updates a state machine depending
 *  on the characters received. An "OK\r\n" sequence indicates the
 *  MTXDOT received and responded to a command sent by uart915_write_cmd().
 *  Anything else resets the state machine back to its starting state.
 *  Returns true if an "OK\r\n" sequence was found, else false.
 */
static bool uart915_parse_response(uint8_t next_char)
{
    switch(rx_state)
    {
        case START:
            switch(next_char)
            {
                case 'O':
                   rx_state = O_RX;
                   break; //end of 'O' case
            
                default:
                    rx_state = START;
                    break; //end of default case
            }
            break; //end of START case
        
        case O_RX:
            switch(next_char)
            {
                case 'K':
                    rx_state = K_RX;
                    break; //end of 'K' case
            
                default:
                    rx_state = START;
                    break; //end of default case
            }
            
            break; //end of O_RX case
        
        case K_RX:
            switch(next_char)
            {
                case '\r':
                    rx_state = CR_RX;
                    break; //end of '\r' case
            
                default:
                    rx_state = START;
                    break; //end of default case
            }
            
        break; //end of K_RX case
        
        case CR_RX:
        switch(next_char)
        {
            case '\n':
                //reset state
                rx_state = START;
                //return true, because response is OK
                return true;
                break; //end of '\n' case
            
            default:
                rx_state = START;
                break; //end of default case
        }
        break; //end of CR_RX case
        
        default:
            rx_state = START;
            break;
    }
    
    return false;
}


/* Function Name    : uart915_write_cmd
 * Parameters       : cmd_str (command string sent to MTXDOT)
 * Return Values(s) : void
 * Description      : Sends a string to the MTXDOT and waits for an 
 *  "OK\r\n" response.
 */
void uart915_write_cmd(const char* cmd_str)
{
    // clear the flag
    flag_ok_received = false;
    
    // reset state machine for determining okay_received
    rx_state = START;
    
    // clear the ring buffer
    ringbuff_clear(&uart915_ringbuff);
    
    // write the AT command
    usart_write_buffer_wait(&uart915_inst, (const uint8_t*) cmd_str, strlen(cmd_str));
    
	
	
    while(!flag_ok_received){
		usart_write_buffer_wait(&uart915_inst, (const uint8_t*) cmd_str, strlen(cmd_str));
	};
}


/* Function Name    : uart915_get_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Gets the RSSI value from the MTXDOT and returns it as a
 *  2 byte int.
 */
int16_t uart915_get_rssi(void)
{
    uint8_t rspns_buff[64] = {0};
    uint8_t i = 0;
    static int16_t ret_val;
    
    //uart915_write_cmd("AT+SEND\r\n");
    
    // send the RSSI command
    uart915_write_cmd("AT+RSSI\r\n");
    
    // acquire the contents of the ring buffer
    while(!ringbuff_is_empty(&uart915_ringbuff))
    {
        ringbuff_get(&uart915_ringbuff, (rspns_buff + (i++)));
    }
    
    // ensure the contents in the response buffer are a string
    rspns_buff[31] = '\0';
    
    // reset array index
    i = 0;
    
    // find first comma in the string
    while(rspns_buff[++i] != ',');
    
    // delimit the string at the first found comma
    rspns_buff[i] = '\0';

    // back up a few characters to get to the start of the number
    while(isdigit(rspns_buff[--i]));
    
    ret_val = (int16_t) (atoi((char*) &rspns_buff[i]));
    
    // convert the number at the current spot in the string to an int
    return ret_val;
}


/* Function Name    : uart915_preconnect
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Sends 10 "AT" and "AT+SEND" commands to he MTXDOT module.
 *  Used during receiver initialization to ensure there is a connection between 
 *  the receiver and transmitter at start up.
 */
void uart915_preconnect(void)
{
    int i = 0;
    
    /* send 10 "AT" and "AT+SEND" commands to validate connection
     * between the receiver and transmitter */
    for(; i < 10; i++)
    {
        uart915_write_cmd("AT\r\n");
        uart915_write_cmd("AT+SEND\r\n");  
    }
}


