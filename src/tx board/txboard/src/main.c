/**********************************************
 * main.c
 * Main program for the TX program
 *
 * Author : Dan Filbey and Khang Vu
 * Capstone Project 2017 - 2018
 **********************************************/
#include <txPinDef.h>
#include <asf.h>
#include <spi_169_driver.h>
#include <uart_245_driver.h>
#include <uart_915_driver.h>

/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
void simSysInit(void);
void sys_clk_init(void);
void conf_port_pin(void);
void clk_osc8m_init(void);
void clk_gclk0_init(void);


/************************************************************************/
/*                                      Main                            */
/************************************************************************/
int main (void)
{
    uint8_t tx_preamble[4] = {FIFO_REPEATDATA, 0x38, 8, 0xaa};

    // initialize all the subsystems on the MCU
    simSysInit();
    
    // init registers for 169MHz
  //  spi169_tx_init();

	
    // init registers for 169MHz
    //spi27_tx_init();
	   
    while(1)
    {
        // start a SPI transfer to the FIFO
      //  spi169_start_xfer(AX5043_FIFODATA, WRT);
        
        // write the preamble
      //  spi169_write(tx_preamble, 4);

        // stop the SPI transfer to the FIFO
       // spi169_stop_xfer();
        
		
	
        // send an AT command to the 915 MHz module
        uart915_write_cmd("AT+SEND=test\r\n");
		
		
        /*
        // send the 2.45 GHz test signal (carrier)
        uart245_enter_config();
        uart245_config_test1();
        uart245_exit_config();
		*/
    }
	
}


/************************************************************************/
/*                                Functions                             */
/************************************************************************/
/* Function Name    : simSysInit
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes all relevant subsystems.
 */
void simSysInit(void)
{
	system_init();
	sys_clk_init();
	conf_port_pin();
    spi169_init();
  //  uart245_init();
    uart915_init();
}


/* Function Name    : sys_clk_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes the MCU clocks.
 */
void sys_clk_init(void)
{
	clk_osc8m_init();
	clk_gclk0_init();
    delay_init();
}


/* Function Name    : conf_port_pin
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Configures the GPIO pins.
 */
void conf_port_pin(void)
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	
	/**************config pin for 245*************/
	// cts
	config_port_pin.direction = PORT_PIN_DIR_INPUT;
    config_port_pin.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(CTS245, &config_port_pin);
    
	// rts
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(RTS245, &config_port_pin);
	port_pin_set_output_level(RTS245, true);
    
    // paen
	port_pin_set_config(PAEN245, &config_port_pin);
    port_pin_set_output_level(PAEN245, true);
    
	// config
	port_pin_set_config(CONFIG245, &config_port_pin);
    port_pin_set_output_level(CONFIG245, true);
    
	// reset
	port_pin_set_config(RESET245, &config_port_pin);
    port_pin_set_output_level(RESET245, true);
	
    
	/**************config pin for 915*************/
	// cts
	config_port_pin.direction = PORT_PIN_DIR_INPUT;
    config_port_pin.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(CTS915, &config_port_pin);
    
	// rts
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(RTS915, &config_port_pin);
    port_pin_set_output_level(RTS915, true);
    
	// wake
	// Wake up from low power modes on rising edge
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_DOWN;
	port_pin_set_config(WAKE915, &config_port_pin);
    port_pin_set_output_level(WAKE915, true);
	

	
    
	/**************config pin for 169*************/
	// ss (cs)
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(SS169, &config_port_pin);
    port_pin_set_output_level(SS169, true);
    
	// irq
	config_port_pin.direction = PORT_PIN_DIR_INPUT;
	port_pin_set_config(IRQ169, &config_port_pin);
} // end conf_port_pin(void)


/* Function Name    : clk_osc8m_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Configures the system clock to use the internal
 *  8 MHz oscillator.
 */
void clk_osc8m_init(void)
{
	//create system clock config struct
	struct system_clock_source_osc8m_config osc8_config;

	/*config the 8 MHz oscillator
	divide by 1 = 8 MHz clock
	run on demand
	don't run in standby*/
	osc8_config.prescaler = SYSTEM_OSC8M_DIV_1;
	osc8_config.on_demand = true;
	osc8_config.run_in_standby = false;
	
	//set the 8MHz internal oscillator config
	system_clock_source_osc8m_set_config(&osc8_config);
}


/* Function Name    : clk_gclk0_init
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Initializes Generic Clock0, which is used to supply
 *  internal MCU peripherals with a regulated clock.
 */
void clk_gclk0_init(void)
{
	struct system_gclk_gen_config gclk0_config;
    
    // init MCLK
	system_gclk_init();
	
	// set CPU clock division factor to 1 = 8 MHz CPU
	system_cpu_clock_set_divider(SYSTEM_MAIN_CLOCK_DIV_1);
	
	// use the 8 MHz source
	gclk0_config.source_clock = SYSTEM_CLOCK_SOURCE_OSC8M;
    // don't output it to a pin (requires additional config)
	gclk0_config.output_enable = false;
    // we're not outputting it to a pin, so don't need to set it high when disabled
	gclk0_config.high_when_disabled = false;
    // division factor of 1, we're already at 8 MHz
	gclk0_config.division_factor = 1;
    // don't run in standby
	gclk0_config.run_in_standby = false;
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &gclk0_config);
	
	//enable GCLK0
	system_gclk_gen_enable(GCLK_GENERATOR_0);
}

/* Function Name    : 
 * Parameters       : 
 * Return Values(s) : 
 * Description      : 
 */
