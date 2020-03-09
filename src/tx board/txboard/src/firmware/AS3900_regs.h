/*
 * AS3900_regs.h
 *
 * Register definitions for the AS3900 27MHz
 * Created: 3/1/2020 4:01:51 PM
 *  Author: Emiliano Montemayor
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

/*Control register*/
#define AS3900_CNTRL	0x00
/*Enable timer register*/
#define AS3900_ENTM		0x01

/*Direct Commands*/
#define CHIP_RESET	0x00
#define IRQ_CLEAR	0X01
#define WAKE_TX		0x04
#define TRANSMIT	0x05
#define SCAN		0x06
#define	PROM_COPY	0x08
#define PROM_FUSE	0x09
#define PROM_LOAD	0x0A
#define MAIN_BANK	0x10
#define SHADOWBANK	0x11
#define POWER_OFF	0x12
#define POWER_ON	0x13
#define WAKE_RX_OFF	0x14
#define WAKE_RX_ON	0x15
#define STREAM_OFF	0x16
#define CLEAR_TIMER0	0x20
#define CLEAR_TIMER1	0x21
#define CLEAR_TIMER2	0x22
#define CLEAR_TIMER3	0x23
#define CLEAR_TIMER4	0x24
#define CLEAR_TIMER5	0x25
#define CLEAR_TIMER6	0x26
#define CLEAR_TIMER7	0x27
#define CLEAR_TIMER_ALL	0x28 

#endif /* INCFILE1_H_ */