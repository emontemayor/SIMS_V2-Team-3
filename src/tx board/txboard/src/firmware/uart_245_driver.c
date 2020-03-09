/**********************************************
 * uart_245_driver.c
 * Function definitions for the UART driver for the RC2500HP
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#include "uart_245_driver.h"

/************************************************************************/
/*                                Globals                               */
/************************************************************************/
// UART instance (struct) for interacting with ASF UART functions
static struct usart_module uart245_inst;
// receive buffer
static uint8_t uart245_rx_buff[UART245_RX_BUFF_SIZE];


/************************************************************************/
/*                                Functions                             */
/************************************************************************/
/* Function Name    : uart245_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes the UART SERCOM for communicating with the
 *  RC2500HP.
 */
void uart245_init(void)
{
    struct usart_config config_usart;
    usart_get_config_defaults(&config_usart);
    
    config_usart.baudrate    = UART245_BAUD;
    config_usart.mux_setting = UART245_PINMUX;
    config_usart.pinmux_pad0 = UTX245;
    config_usart.pinmux_pad1 = URX245;
    config_usart.pinmux_pad2 = PINMUX_UNUSED;
    config_usart.pinmux_pad3 = PINMUX_UNUSED;
    config_usart.generator_source = UART245_CLK;
    config_usart.transfer_mode = USART_TRANSFER_ASYNCHRONOUSLY;
    
    while (usart_init(&uart245_inst, UART245, &config_usart) != STATUS_OK);
    
    usart_enable(&uart245_inst);
}


/* Function Name    : uart245_deinit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Deinitializes the UART SERCOM for communicating with the
 *  RC2500HP.
 */
void uart245_deinit(void)
{
    usart_disable(&uart245_inst);
}


/* Function Name    : uart245_wait_prompt
 * Parameters       : void
 * Return Values(s) : status_code_genare_t
 * Description      : Waits for the prompt character from the RC2500HP,
 *  the '>' character. Returns a ASF status code based on the result of UART
 *  functions.
 */
status_code_genare_t uart245_wait_prompt(void)
{
    status_code_genare_t stat_val;
    uint8_t wait_time = 100;
    
    do 
    {
        // set the first value of the buffer to a known value that isn't '>'
        uart245_rx_buff[0] = 0xFF;
        
        // wait for the prompt '>' character
        stat_val = usart_read_buffer_wait(&uart245_inst, uart245_rx_buff, 1);
    
        /* if a character wasn't received before the uart's time out or another
         * error occurred, return that error */
        if((stat_val != STATUS_OK) && (stat_val != STATUS_ERR_TIMEOUT))
            return stat_val;
        
        /* if the received character is not the module's prompt character, 
         * wait some more */
        if(uart245_rx_buff[0] != '>')
            wait_time--;
        else
            return STATUS_OK;
        
        // delay a millisecond
        delay_ms(1);
        
    }while (uart245_rx_buff[0] != '>');
    
    return STATUS_ABORTED;
}


/* Function Name    : uart245_wait_prompt
 * Parameters       : void
 * Return Values(s) : status_code_genare_t
 * Description      : Enters the config mode of the RC2500HP. Refer to pg44 of
 *  the RC2500HP datasheet for enter/exiting configuration mode. Returns a ASF 
 *  status code based on the result of UART functions.
 */
status_code_genare_t uart245_enter_config(void)
{
    status_code_genare_t stat_val;
    
    // pull the CONFIG pin low to begin configuration mode
    port_pin_set_output_level(CONFIG245, false);
    
    // wait for the module to return a prompt '>' character
    stat_val = uart245_wait_prompt();
    
    // set the CONFIG pin back high
    port_pin_set_output_level(CONFIG245, true);
    
    /* if a character wasn't received before the uart's time out or another
     * error occurred, return that error */
    if(stat_val != STATUS_OK)
        return stat_val;
        
    /* if the received character is not the module's prompt character, 
     * return an error */
    if(uart245_rx_buff[0] != '>')
        return STATUS_ABORTED;
        
    // else return the stat_val if everything was OK
    return stat_val;
}


/* Function Name    : uart245_exit_config
 * Parameters       : void
 * Return Values(s) : status_code_genare_t
 * Description      : Exits the config mode of the RC2500HP. Refer to pg44 of
 *  the RC2500HP datasheet for enter/exiting configuration mode. Returns a ASF
 *  status code based on the result of UART functions.
 */
status_code_genare_t uart245_exit_config(void)
{
    status_code_genare_t stat_val;
    
    // send an 'X' to indicate end of CONFIG mode
    do 
    {
        stat_val = usart_write_wait(&uart245_inst, 'X');
    } while (stat_val == STATUS_BUSY);
    
    /* wait one millisecond so the module can return to IDLE state
     * refer to page 44 of RC2500HP-TM datasheet for timing info */
    delay_ms(1);
    
    return stat_val;
}


/* Function Name    : uart245_config_get_rssi
 * Parameters       : void
 * Return Values(s) : float
 * Description      : Sends an RSSI read config command to
 *  the RC2500HP, reads the output RSSI byte, converts it based on the equation
 *  on pg 51 of the RC2500HP datasheet, and returns the float.
 */
float uart245_config_get_rssi(void)
{
    // unsigned byte to store the RSSI byte received from the module
    uint8_t ret_val = 0;

    // send an 'S' to get the RSSI value, wait until the uart is successful
    while(usart_write_wait(&uart245_inst, 'S') == STATUS_BUSY);
    
    // read one byte RSSI from the RC2500HP
    usart_read_buffer_wait(&uart245_inst, &ret_val, 1);
    
    // wait for the module to return a prompt '>' character
    uart245_wait_prompt();
    
    // convert the RSSI value to a float, see page 51 of the RC2500HP datasheet
    return ((-1.0f) * (((float) ret_val) / 2.00f));
}


/* Function Name    : uart245_config_read_mem
 * Parameters       : mem_addr (address of config memory)
 * Return Values(s) : uint8_t
 * Description      : Reads a byte from the RC2500HP's configuration memory
 *  and returns the byte.
 */
uint8_t uart245_config_read_mem(uint8_t mem_addr)
{
    uint8_t ret_val;
    uint8_t xmit_arr[2];
    
    // format the values to transmit
    xmit_arr[0] = 'Y';
    xmit_arr[1] = mem_addr;

    // send a 'Y' character and the memory address to read from
    usart_write_buffer_wait(&uart245_inst, xmit_arr, 2);
    
    // read the value of the memory address
    usart_read_buffer_wait(&uart245_inst, &ret_val, 1);
    
    // wait for the module to return a prompt '>' character
    uart245_wait_prompt();
    
    return ret_val;
}


/* Function Name    : uart245_config_wrt_mem
 * Parameters       : mem_addr (config address to write to), wrt_byte (byte to
 *                      write)
 * Return Values(s) : void
 * Description      : Writes a byte to the RC2500HP's configuration memory.
 *  Refer to page 52 of the RC2500HP's datasheet.
 */
void uart245_config_wrt_mem(uint8_t mem_addr, uint8_t wrt_byte)
{
    uint8_t xmit_arr[3];
    
    xmit_arr[0] = mem_addr;
    xmit_arr[1] = wrt_byte;
    xmit_arr[2] = 0xFF;
    
    // send an 'M' to initiate memory write, wait until the uart is successful
    while(usart_write_wait(&uart245_inst, 'M') == STATUS_BUSY);
    
    // wait for the module to return a prompt '>' character
    uart245_wait_prompt();
    
    // write the address byte, data byte, and then a 0xFF end the write.
    usart_write_buffer_wait(&uart245_inst, xmit_arr, 3);
    
    // wait for the module to return a prompt '>' character
    uart245_wait_prompt();
}


/* Function Name    : uart245_config_test1
 * Parameters       : void
 * Return Values(s) : void
 * Description      : RC2500HP configuration command to put the module in test
 *  mode 1. This mode continuously transmits a carrier until another
 *  config command is received.
 */
void uart245_config_test1(void)
{
    /* send a '1' to set test mode 1, wait until the uart is successful.
     * Test Mode 1 turns on the TX carrier */
    while(usart_write_wait(&uart245_inst, '1') == STATUS_BUSY);
    
    // wait for the module to return a prompt '>' character
    uart245_wait_prompt();
}


/* Function Name    : uart245_rssi
 * Parameters       : void
 * Return Values(s) : int16_t
 * Description      : Gets an RSSI value from the RC2500HP and returns
 *  it as a 2 byte int.
 */
int16_t uart245_rssi(void)
{
    float float_val = 0;
    int16_t ret_val = 0;
    
    // reset the device to guarantee entry into config mode
    port_pin_set_output_level(RESET245, false);
    delay_ms(10);
    port_pin_set_output_level(RESET245, true);
    delay_ms(4);
    
    // enter the RC2500HP's config mode
    uart245_enter_config();
    
    // get the RSSI
    float_val = uart245_config_get_rssi();
    
    uart245_exit_config();
    
    // cast the float RSSI to a 2 byte int RSSI
    ret_val = (int16_t) float_val;
    
    return ret_val;
}