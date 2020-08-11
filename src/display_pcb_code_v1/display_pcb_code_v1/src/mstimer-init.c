/**
 * @file
 * @author Steve Karg
 * @date 2015
 * @brief Millisecond timer library header file.
 *
 * @section DESCRIPTION
 *
 * The mstimer library provides functions for setting, resetting and
 * restarting timers, and for checking if a timer has expired. An
 * application must "manually" check if its timers have expired; this
 * is not done automatically.
 *
 * A timer is declared as a \c struct \c mstimer and all access to the
 * timer is made by a pointer to the declared timer.
 *
 * Adapted from the Contiki operating system stimer module.
 * Original Authors: Adam Dunkels <adam@sics.se>, Nicolas Tsiftes <nvt@sics.se>
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "asf.h"
#include "bacnet/basic/sys/mstimer.h"

/* counter for the timer */
static volatile uint32_t Millisecond_Counter;


/**
 * Handles the interrupt from the timer
 */
void SysTick_Handler(void)
{
    /* increment the tick count */
    Millisecond_Counter++;
}

 /**
 * @brief Function retrieves the system time, in milliseconds.
 * The system time is the time elapsed since OS was started.
 * @return milliseconds since OS was started
 */
unsigned long mstimer_now(void)
{
    return Millisecond_Counter;
}

/**
 * @brief Initialization for timer
 */
void mstimer_init(void)
{
    /* Setup SysTick Timer for 1ms interrupts  */
    if (SysTick_Config(SystemCoreClock / 1000)) {
        /* Capture error */
        while (1)
            ;
    }
    NVIC_EnableIRQ(SysTick_IRQn);
}
