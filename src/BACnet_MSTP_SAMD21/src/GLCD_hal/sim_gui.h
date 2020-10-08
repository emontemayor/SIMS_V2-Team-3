/**********************************************
 * sim_gui.h
 * Header for LCD GUI
 *
 * Author : Khang Vu
 * Capstone Project 2017 - 2018
 **********************************************/
#ifndef SIM_GUI_H_
#define SIM_GUI_H_

#include <asf.h>
#include <SIM_PIN_DEF.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sim_system_glcd_software.h>
#include <ff.h>
#include <rssi_mngr.h>
#include <uart_ib.h>
#include <uart_fiber.h>


/************************************************************************/
/*                                Defines                               */
/************************************************************************/
#define SD_SLOT     0
#define DEV_MMC     0

#define disWid			800
#define disHei			480
#define boxWid			300
#define boxHei			100
#define zero			48
#define attn			1
#define hist			2
#define rssi			3
#define sett			4
#define back			6
#define cal				7
#define sDate			8
#define sTime 			5
#define del				9
#define clr				10
#define ok				11
#define alertOn			12
#define alertOff		13
#define soundOn			14
#define soundOff		15


/************************************************************************/
/*                                Prototypes                            */
/************************************************************************/
void mainMenu(void);
void attnOp(struct shield_data *receiver_data);

//void attnOp(struct shield_data, struct shield_data);
void manualOp(void);
void historyOp(void);
void settingOp(void);
void creditOp(void);
void rssiOp(void);
void calScreen(void);
void setTime(void);
void setDate(void);
int month31(char month);
void printTime(void);
void play(void);
void clrHist(void);
void shiftHist(void);
void saveHist(int16_t rssi169, int16_t rssi915, int16_t rssi245);

void appAttn(void);
void appRssi(void);
void appHist(void);

void drawRect(int x, int y, double freq);
void drawTitle(char *title);
void drawBack(void);
void drawKeypad(char pressed);
void drawAlert(int x, int y, char stat);
void drawRssi(void);
void drawHist(void);

void disStart(void);
void disEnd(void);

void configure_ext_ints(void);
void configure_ext_int_callback(void);
void configure_rtc_calendar(void);
void clock_osc32k_init(void);
void clock_gclk2_init(void);


#endif /* SIM_GUI_H_ */