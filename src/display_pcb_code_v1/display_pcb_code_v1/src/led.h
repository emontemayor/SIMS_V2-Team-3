/**
 * @file
 * @brief Handle the configuration and set/clear of the LEDs.
 *
 * @date 2019
 * @author Steve Karg
 */
#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void led_on(void);
void led_off(void);
void led_rx_on(void);
void led_rx_off(void);
void led_tx_on(void);
void led_tx_off(void);
void led_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
