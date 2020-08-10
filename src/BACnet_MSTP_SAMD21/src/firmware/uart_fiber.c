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
static struct usart_module uartfiber_inst1; // this is the leftmost fiber module when looking into the fiber holes
static struct usart_module uartfiber_inst2; // this is the rightmost fiber module when looking into the fiber holes

//Since the ASF buffer code seems too unnecessarily complicated we will manage our own data buffers
//This union of data types allows easy access of our struct's data as separate bytes
union fiber_data {
	volatile struct measurement data;
	volatile uint8_t bytes[sizeof(struct measurement)];
};
enum fiber_data_status {data_not_ready, data_ready, data_being_processed};

//Buffer and supporting variables for fiber 1
volatile union fiber_data fiber1_data;
volatile uint8_t fiber1_pointer;
volatile enum fiber_data_status fiber1_data_status;
	
//Buffer and supporting variables for fiber 2
volatile union fiber_data fiber2_data;
volatile uint8_t fiber2_pointer;
volatile enum fiber_data_status fiber2_data_status;

void uartfiber_init(void)
{
	//needs to be done twice, once for each fiber module
    struct usart_config config_usart;
    usart_get_config_defaults(&config_usart);
    
    config_usart.baudrate    = UART_FIBER_BAUD;
    config_usart.mux_setting = UART_FIBER_PINMUX1;
    config_usart.pinmux_pad0 = PINMUX_UNUSED;
    config_usart.pinmux_pad1 = PINMUX_UNUSED;
    config_usart.pinmux_pad2 = PINMUX_UNUSED;
    config_usart.pinmux_pad3 = URX_FIBER1;
    config_usart.generator_source = UART_FIBER_CLK;
    config_usart.transfer_mode = USART_TRANSFER_ASYNCHRONOUSLY;
    
    while (usart_init(&uartfiber_inst1, UART_FIBER1, &config_usart) != STATUS_OK);
    
    //enable the uart
    usart_enable(&uartfiber_inst1);
    
	//again for 2nd fiber module
    usart_get_config_defaults(&config_usart);
    
    config_usart.baudrate    = UART_FIBER_BAUD;
    config_usart.mux_setting = UART_FIBER_PINMUX2;
    config_usart.pinmux_pad0 = URX_FIBER2;
    config_usart.pinmux_pad1 = PINMUX_UNUSED;
    config_usart.pinmux_pad2 = PINMUX_UNUSED;
    config_usart.pinmux_pad3 = PINMUX_UNUSED;
    config_usart.generator_source = UART_FIBER_CLK;
    config_usart.transfer_mode = USART_TRANSFER_ASYNCHRONOUSLY;
    
    while (usart_init(&uartfiber_inst2, UART_FIBER2, &config_usart) != STATUS_OK);
	
    //enable the uart
    usart_enable(&uartfiber_inst2);
	
	//configure callbacks for data buffers
	usart_register_callback(&uartfiber_inst1, &fiber1_callback, USART_CALLBACK_BUFFER_RECEIVED);
	usart_register_callback(&uartfiber_inst2, &fiber2_callback, USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&uartfiber_inst1, USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&uartfiber_inst2, USART_CALLBACK_BUFFER_RECEIVED);
}

void uartfiber_deinit(void)
{
    usart_disable(&uartfiber_inst1);
	usart_disable(&uartfiber_inst2);
}

void fiber1_callback()
{
	uint8_t tempdata = UART_FIBER1->USART.DATA.reg;
	
	if(fiber1_data_status =! data_ready)
	{
		if (tempdata == '$')
		{
			fiber1_pointer = 0;
			fiber1_data_status = data_being_processed;
		}
		else if(tempdata == '\r' && fiber1_data_status == data_being_processed)
		{
			fiber1_data_status = data_ready;
		}
		else
		{
			fiber1_data.bytes[fiber1_pointer++] = tempdata;
		}
	}
}

void fiber2_callback()
{
	uint8_t tempdata = UART_FIBER2->USART.DATA.reg;
	
	if(fiber2_data_status =! data_ready)
	{
		if (tempdata == '$')
		{
			fiber2_pointer = 0;
			fiber2_data_status = data_being_processed;
		}
		else if(tempdata == '\r' && fiber2_data_status == data_being_processed)
		{
			fiber2_data_status = data_ready;
		}
		else
		{
			fiber2_data.bytes[fiber1_pointer++] = tempdata;
		}
	}
}

/*

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


*/