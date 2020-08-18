/**********************************************
 * sim_gui.c
 * Function definitions for LCD GUI
 *
 * Author : Khang Vu
 * Capstone Project 2017 - 2018
 **********************************************/

#include "sim_gui.h"
#include "uart_fiber.h"

/************************************************************************/
/*                                Globals                               */
/************************************************************************/
// FatFs work area needed for each volume
FATFS fatFs;
// File object needed for each open file
FIL fil;
//declare rtc instance for calendar
struct rtc_module rtc_instance;
//time instance to get and set time
struct rtc_calendar_time time;

//global values
Ft_Gpu_Hal_Context_t host, *phost;
ft_uint8_t 	tag 	= 0, \
            tempTag	= 0, \
            font 	= 28,\
            alert	= 1, \
            sound	= 0;

//used to put commands to RAM_DL
ft_uint32_t	attnStart=0, 		attnEnd=0,	\
            rssiStart=0,		rssiEnd=0,	\
            histStart=0,		histEnd=0;

//2D array for history
int16_t history[10][10];


/************************************************************************/
/*                                Functions                             */
/************************************************************************/
/* Function Name   	: attnOp
 * Parameters       : rssi_vals* attn_vals
 * Return Values(s) : void
 * Description      : display the current attenuation based on the RSSI value received
 *  display visual alert and play sound if configured
 *  record instances in which the shield failed
 *  write to SD card if one is detected
 *  record attenuation values every 30 minutes regardless of shield status
*/
//attnOp
void attnOp(){
	//declare values for time checking and shield failure triggering
	static rssi_vals attenuation;
	char lastSec, lastMin=1, lastGood = time.second, trigger=0;
	
	do {
		tag = 0;
		//get current time
		rtc_calendar_get_time(&rtc_instance, &time);

		// get attenuation level
		attenuation.rssi27 = 90;
		attenuation.rssi169 =  82;	//10 offset added based on testing
		attenuation.rssi915 = 91;				// approved by Dr. Nguyen
		attenuation.rssi245 =79;


		//display information on the screen
		disStart();
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		Ft_Gpu_CoCmd_Append(phost, attnStart, attnEnd);
		
		Ft_Gpu_CoCmd_Number(phost, 500, 125, 31, OPT_SIGNED|3, ((attenuation.rssi27<0)? 0:attenuation.rssi27));
		Ft_Gpu_CoCmd_Number(phost, 500, 200, 31, OPT_SIGNED|3, ((attenuation.rssi169<0)? 0:attenuation.rssi169));
		Ft_Gpu_CoCmd_Number(phost, 500, 275, 31, OPT_SIGNED|3, ((attenuation.rssi915<0)? 0:attenuation.rssi915));
		Ft_Gpu_CoCmd_Number(phost, 500, 350, 31, OPT_SIGNED|3, ((attenuation.rssi245<0)? 0:attenuation.rssi245));
		
		Ft_Gpu_CoCmd_Text(phost, 250, 125, 31, OPT_SIGNED|3, "27MHz");
		Ft_Gpu_CoCmd_Text(phost, 250, 200, 31, OPT_SIGNED|3, "169MHz");
		Ft_Gpu_CoCmd_Text(phost, 250, 275, 31, OPT_SIGNED|3, "915MHz");
		Ft_Gpu_CoCmd_Text(phost, 250, 350, 31, OPT_SIGNED|3, "2.4GHz");
		
		Ft_Gpu_CoCmd_Text(phost, 650, 125, 31, OPT_SIGNED|3, "dB");
		Ft_Gpu_CoCmd_Text(phost, 650, 200, 31, OPT_SIGNED|3, "dB");
		Ft_Gpu_CoCmd_Text(phost, 650, 275, 31, OPT_SIGNED|3, "dB");
		Ft_Gpu_CoCmd_Text(phost, 650, 350, 31, OPT_SIGNED|3, "dB");
		//draw visual alert if attenuation is below 80 (if configured)
		if (alert == 1){
			drawAlert(40, 125, (attenuation.rssi27<80)? 1:0);
			drawAlert(40, 200, (attenuation.rssi169<80)? 1:0);
			drawAlert(40, 275, (attenuation.rssi915<80)? 1:0);
			drawAlert(40, 350, (attenuation.rssi245<80)? 1:0);
		}
		
		//reset shield failure trigger, this is to avoid false report because of fluctuation
		if (attenuation.rssi169>80 && attenuation.rssi915>80 && attenuation.rssi245>80){
			lastGood = time.second;
			trigger = 0;
		}else if ((time.second-lastGood == 10 ||time.second - lastGood == -50) && trigger == 0)
		//set trigger if shield fail for more than 10 continous seconds
		trigger = 1;
		
		if (trigger == 1){
			//record shield failure instances to history and SD Card (if one is inserted)
			//saveHist(uartib_get_169_rssi(), uartib_get_915_rssi(), uartib_get_245_rssi());
			//play sound when shield fail for more then 10 continous seconds
			if (time.second%5 == 0 && time.second != lastSec && sound==1){
				play();
				lastSec = time.second;
			}
		}

		if (time.minute%30 == 0 && time.minute != lastMin){
			//saveHist(uartib_get_169_rssi(), uartib_get_915_rssi(), uartib_get_245_rssi());
			lastMin = time.minute;
		}

		//draw back button
		Ft_Gpu_Hal_WrCmd32(phost,COLOR_RGB(255,255,255));
		drawBack();
		
		//draw title
		drawTitle("Attenuation");
		
		disEnd();
	} while (tag != back);
}// end attnOp

//void attnOp(struct shield_data current_fiber1_data, struct shield_data current_fiber2_data){
//	//declare values for time checking and shield failure triggering
//    static rssi_vals attenuation;
//    char lastSec, lastMin=1, lastGood = time.second, trigger=0;
//        
//	do {
//		tag = 0;
//		//get current time
//		rtc_calendar_get_time(&rtc_instance, &time);
//
//		// get attenuation level
//		//attenuation.rssi27 =  current_fiber1_data.rssi_values.MHz27RSSI - current_fiber2_data.rssi_values.MHz27RSSI +90;
//		attenuation.rssi169 = current_fiber1_data.rssi_values.MHz169RSSI - current_fiber2_data.rssi_values.MHz169RSSI + 95;	//10 offset added based on testing 
//		attenuation.rssi915 = current_fiber1_data.rssi_values.MHz915RSSI - current_fiber2_data.rssi_values.MHz915RSSI + 72;				// approved by Dr. Nguyen
//		attenuation.rssi245 = current_fiber1_data.rssi_values.GHz24RSSI - current_fiber2_data.rssi_values.GHz24RSSI + 90;
//		
//		disStart();
//		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
//		Ft_Gpu_CoCmd_Append(phost, attnStart, attnEnd);
//		Ft_Gpu_CoCmd_Number(phost, 500, 125, 31, OPT_SIGNED|3, ((95<0)? 0:95));
//		Ft_Gpu_CoCmd_Number(phost, 500, 255, 31, OPT_SIGNED|3, ((72<0)? 0:72));
//		Ft_Gpu_CoCmd_Number(phost, 500, 385, 31, OPT_SIGNED|3, ((90<0)? 0:90));
//		
//		//display information on the screen
//		//disStart();
//		//tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
//		//Ft_Gpu_CoCmd_Append(phost, attnStart, attnEnd);
//		//Ft_Gpu_CoCmd_Number(phost, 500, 125, 31, OPT_SIGNED|3, ((attenuation.rssi169<0)? 0:attenuation.rssi169));
//		//Ft_Gpu_CoCmd_Number(phost, 500, 255, 31, OPT_SIGNED|3, ((attenuation.rssi915<0)? 0:attenuation.rssi915));
//		//Ft_Gpu_CoCmd_Number(phost, 500, 385, 31, OPT_SIGNED|3, ((attenuation.rssi245<0)? 0:attenuation.rssi245));
//		
//		//draw visual alert if attenuation is below 80 (if configured)
//		//if (alert == 1){
//		//	drawAlert(40, 27, (attenuation.rssi169<80)? 1:0);
//		//	drawAlert(40, 60, (attenuation.rssi915<80)? 1:0);
//		//	drawAlert(40, 93, (attenuation.rssi245<80)? 1:0);
//		//}
//		
//				//draw visual alert if attenuation is below 80 (if configured)
//		if (alert == 1){
//			drawAlert(40, 27, (90<80)? 1:0);
//			drawAlert(40, 60, (90<80)? 1:0);
//			drawAlert(40, 93, (90<80)? 1:0);
//		}
//	
//		
//		//reset shield failure trigger, this is to avoid false report because of fluctuation 
//		if (attenuation.rssi169>80 && attenuation.rssi915>80 && attenuation.rssi245>80){
//			lastGood = time.second;
//			trigger = 0;
//		}else if ((time.second-lastGood == 10 ||time.second - lastGood == -50) && trigger == 0)
//				//set trigger if shield fail for more than 10 continous seconds
//				trigger = 1;
//		
//		if (trigger == 1){
//			//record shield failure instances to history and SD Card (if one is inserted)
//			//saveHist(uartib_get_169_rssi(), uartib_get_915_rssi(), uartib_get_245_rssi());
//			//play sound when shield fail for more then 10 continous seconds
//			if (time.second%5 == 0 && time.second != lastSec && sound==1){
//				play();
//				lastSec = time.second;
//			}
//		}
//
//		if (time.minute%30 == 0 && time.minute != lastMin){
//			//saveHist(uartib_get_169_rssi(), uartib_get_915_rssi(), uartib_get_245_rssi());
//			lastMin = time.minute;
//		}
//
//		//draw back button
//        Ft_Gpu_Hal_WrCmd32(phost,COLOR_RGB(255,255,255));
//        drawBack();
//            
//		//draw title
//		drawTitle("Attenuation");
//            
//		disEnd();
//	} while (tag != back);
//}// end attnOp


/* Function Name    : historyOp
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Display last 10 instances of shield failures
 */
void historyOp(){
	int i, y;
	char buff[128]; 

	do {
		tag = 0;
		y = 125;
		disStart();
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		Ft_Gpu_CoCmd_Append(phost, histStart, histEnd);

		for(i = 0; i < 10; i++){
			// put together the string
			snprintf(buff, 128, "%02d. %02d:%02d:%02d   %02d/%02d/%04d                 %03d                       %03d                      %03d", \
					i+1, history[i][0], history[i][1], history[i][2], history[i][3], history[i][4], \
					history[i][5], history[i][6], history[i][7], history[i][8], history[i][9]);
			//send the string to the GLCD
			Ft_Gpu_CoCmd_Text(phost, 50, y, 28, 0,buff);
			//go to next line on the GLCD
			y = y + 30;
		}
		
		drawBack();
		drawTitle("History");
		disEnd();

		//small delay to avoid continous update on GLCD
		delay_ms(50);
	} while (tag != back);
}//end histOp


/* Function Name    : rssiOp
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Display the RSSI outside and inside the shield
 */
//rssiOp

void rssiOp(){
	do {
	tag = 0;
		disStart();
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		
		//draw table
		Ft_Gpu_CoCmd_Append(phost, rssiStart, rssiEnd);
		
		//display RSSI from the display unit
		Ft_Gpu_CoCmd_Number(phost, 650, 125, 31, OPT_SIGNED|OPT_CENTER|3, 11);
		Ft_Gpu_CoCmd_Number(phost, 650, 200, 31, OPT_SIGNED|OPT_CENTER|3, 10);
		Ft_Gpu_CoCmd_Number(phost, 650, 275, 31, OPT_SIGNED|OPT_CENTER|3, 23);
		Ft_Gpu_CoCmd_Number(phost, 650, 350, 31, OPT_SIGNED|OPT_CENTER|3, 14);

	  	Ft_Gpu_CoCmd_Text(phost, 400, 125, 31, OPT_SIGNED|3, "27MHz");
		Ft_Gpu_CoCmd_Text(phost, 400, 200, 31, OPT_SIGNED|3, "169MHz");
		Ft_Gpu_CoCmd_Text(phost, 400, 275, 31, OPT_SIGNED|3, "915MHz");
		Ft_Gpu_CoCmd_Text(phost, 400, 350, 31, OPT_SIGNED|3, "2.4GHz");
		
		Ft_Gpu_CoCmd_Text(phost, 750, 125, 31, OPT_SIGNED|3, "dB");
		Ft_Gpu_CoCmd_Text(phost, 750, 200, 31, OPT_SIGNED|3, "dB");
		Ft_Gpu_CoCmd_Text(phost, 750, 275, 31, OPT_SIGNED|3, "dB");
		Ft_Gpu_CoCmd_Text(phost, 750, 350, 31, OPT_SIGNED|3, "dB");
		
		drawBack();
		drawTitle("RSSI [interior]");
		disEnd();
	} while (tag != back);
}//end rssiOp


/* Function Name    : settingOp
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Allow user to configure visual and sound alert
 *  set date and time calibrate the screen.
 */
void settingOp(){
	do {
		tag = 0;
		disStart();
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);

		//setup button and assign tag value
		//for visual alert
		Ft_Gpu_CoCmd_Text(phost, (disWid/4), disHei/3-20, 30, OPT_CENTER, "Visual:");
		Ft_Gpu_Hal_WrCmd32(phost,TAG(alertOn));
		Ft_Gpu_CoCmd_Button(phost,disWid/2 - disWid*0.25/2,(disHei*0.24),(disWid*0.12),(disHei*0.112),font, (alert==1)? OPT_FLAT:0,"Yes");
		Ft_Gpu_Hal_WrCmd32(phost,TAG(alertOff));
		Ft_Gpu_CoCmd_Button(phost,disWid/2,(disHei*0.24),(disWid*0.12),(disHei*0.112),font, (alert==0)? OPT_FLAT:0,"No");
		//for sound alert
		Ft_Gpu_CoCmd_Text(phost, (disWid/4), disHei/3+30, 30, OPT_CENTER, "Sound: ");
		Ft_Gpu_Hal_WrCmd32(phost,TAG(soundOn));
		Ft_Gpu_CoCmd_Button(phost,disWid/2 - disWid*0.25/2,(disHei*0.37),(disWid*0.12),(disHei*0.112),font, (sound==1)? OPT_FLAT:0,"Yes");
		Ft_Gpu_Hal_WrCmd32(phost,TAG(soundOff));
		Ft_Gpu_CoCmd_Button(phost,disWid/2,(disHei*0.37),(disWid*0.12),(disHei*0.112),font, (sound==0)? OPT_FLAT:0,"No");
		//option to calibrate the screen
		Ft_Gpu_Hal_WrCmd32(phost,TAG(cal));
		Ft_Gpu_CoCmd_Button(phost,disWid/2 - disWid*0.25/2,(disHei*0.5),(disWid*0.25),(disHei*0.112),font, (tag==cal)? OPT_FLAT:0,"  Calibrate Screen  ");
		//set date
		Ft_Gpu_Hal_WrCmd32(phost,TAG(sDate));
		Ft_Gpu_CoCmd_Button(phost,disWid/2 - disWid*0.25/2,(disHei*0.63),(disWid*0.25),(disHei*0.112),font, (tag==sDate)? OPT_FLAT:0,"  Set Date  ");
		//set time
		Ft_Gpu_Hal_WrCmd32(phost,TAG(sTime));
		Ft_Gpu_CoCmd_Button(phost,disWid/2 - disWid*0.25/2,(disHei*0.76),(disWid*0.25),(disHei*0.112),font, (tag==sTime)? OPT_FLAT:0,"  Set Time  ");
		
		drawBack();
		drawTitle("Settings");
		disEnd();
		
		//check tag value and determine action
		if (tag == cal)			calScreen();	//go to calibrate the screen
		else if (tag == sTime)	setTime();		//set time screen
		else if (tag == sDate)	setDate();		//set date screen
		if (tag == alertOn)		alert = 1;		//set visual alert on
		if (tag == alertOff)	alert = 0;		//set visual alert off
		if (tag == soundOff)	sound = 0;		//set sound alert off
		if (tag == soundOn)		sound = 1;		//set sound alert on
		
		delay_ms(50);
	} while (tag != back);
}//end settOp


/* Function Name    : calScreen
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Calibrate the screen to get more accurate input
 */
void calScreen(){
	disStart();
	Ft_Gpu_CoCmd_Text(phost,disWid/2,disHei/2,30,OPT_CENTER,"Please tap on the dot");

	/* Calibration */
	Ft_Gpu_CoCmd_Calibrate(phost,0);
	disEnd();
	delay_ms(100);
}//end calScreen
	
    
/* Function Name    : setTime
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Set the system time
 */
void setTime(){
	int textBoxWid = disWid*.4, textBoxHei = disHei*.23;
	//checker to avoid multiple input from screen refresh
	char tempTag = 0, timeIn[10] = "0", i = 0, pressed = 0;

	do{
		//create the blinking cursor effect
		rtc_calendar_get_time(&rtc_instance, &time);
		if (time.second%2 == 1)			timeIn[i] = ' ';
		else							timeIn[i] = '_';

		tag = 0;
		disStart();
		// draw text box
		Ft_Gpu_Hal_WrCmd32(phost, BEGIN(RECTS));
		Ft_Gpu_Hal_WrCmd32(phost, LINE_WIDTH(10 * 6));
		Ft_Gpu_Hal_WrCmd32(phost, COLOR_RGB(255,255,255));
		Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F((disWid/2-textBoxWid/2) * 16, textBoxHei * 16) );
		Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(((disWid/2-textBoxWid/2) + textBoxWid) * 16, (textBoxHei + 50) * 16));
		Ft_Gpu_Hal_WrCmd32(phost, END());

		// create label on top of text box
		Ft_Gpu_Hal_WrCmd32(phost, COLOR_RGB(255,255,255));
		Ft_Gpu_CoCmd_Text(phost, disWid/2 - disWid*.2, disHei*.1, 28, 0, "Enter Time");
		Ft_Gpu_CoCmd_Text(phost, disWid/2 - disWid*.2, disHei*.15, 28, 0, "hh:mm:ss    (24h format)");
		//display input in the textbox
		Ft_Gpu_Hal_WrCmd32(phost,COLOR_RGB(0,0,0));
		Ft_Gpu_CoCmd_Text(phost, (disWid/2-textBoxWid/2 + 5), disWid*.15, 30, 0, timeIn);

		// draw keypad
		Ft_Gpu_Hal_WrCmd32(phost,COLOR_RGB(255,255,255));
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		//draw keypad routine
		drawKeypad(pressed);

		drawBack();
		disEnd();
		
		//determine what button was pressed based on tag value 
		if (tag>47 && tag<58)	pressed = tag - 48;
		else					pressed = 0;

		//set checker to avoid multiple input
		if(tag==0)		tempTag = tag;
		//get input in this block
		if (tempTag != tag && tag != 0 && tag!=back){
			tempTag = tag;
			//get time and input checking to make sure time is legitimate
			if(tag> 47 && tag<58){
				if(i==0 && tag>50);								//1st digit in hour
				else if(i==1 && timeIn[0]==50 && tag>51);		//2nd digit in hour
				else if((i==3 || i==6) && tag>53);				//1st digit in minute and second
				else{											//2nd digit in minute and second
					timeIn[i] = tag;
					i++;
				}
			} else if(tag == clr){		//if clr is pressed
				do{						//clear all user input
					timeIn[i] = 0;
					i--;
				}while(i>0);
			} else if(tag==del && i>0){		//if del is pressed
				if(i==3 || i==6){			//clear last user input
					timeIn[i] = 0;
					i--;
				}
				timeIn[i] = 0;
				i--;
			}
			if(tag==ok || i==9){		//if ok is pressed
				timeIn[i] = 0;			// compute time and update to the system
				rtc_calendar_disable(&rtc_instance);
				time.hour = (timeIn[0]%48)*10+(timeIn[1]%48);
				time.minute = (timeIn[3]%48)*10+(timeIn[4]%48);
				time.second = (timeIn[06]%48)*10+(timeIn[7]%48);
				rtc_calendar_set_time(&rtc_instance, &time);
				rtc_calendar_enable(&rtc_instance);
				break;
			}
		}
		//add ':' character to separate hour, minute and second
		if(i==2 || i==5){
			timeIn[i] = ':';
			i++;
		}
	}while(tag != back);
	tag = 0;
}//end setTime


/* Function Name    : setDate
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Set the date for the system
 */
void setDate(){
	int textBoxWid = disWid*.4, textBoxHei = disHei*.23;
	char tempTag = 0, pressed = 0, i = 0, month = 0, dateIn[12] = "0";

	do{
		//setup blinking cursor effect
		rtc_calendar_get_time(&rtc_instance, &time);
		if (time.second%2 == 1)			dateIn[i] = ' ';
		else							dateIn[i] = '_';

		tag = 0;
		disStart();
		// draw text box
		Ft_Gpu_Hal_WrCmd32(phost, BEGIN(RECTS));
		Ft_Gpu_Hal_WrCmd32(phost, LINE_WIDTH(10 * 6));
		Ft_Gpu_Hal_WrCmd32(phost, COLOR_RGB(255,255,255));
		Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F((disWid/2-textBoxWid/2) * 16, textBoxHei * 16) );
		Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(((disWid/2-textBoxWid/2) + textBoxWid) * 16, (textBoxHei + 50) * 16));
		Ft_Gpu_Hal_WrCmd32(phost, END());
		// put the label above textbox
		Ft_Gpu_Hal_WrCmd32(phost, COLOR_RGB(255,255,255));
		Ft_Gpu_CoCmd_Text(phost, disWid/2 - disWid*.2, disHei*.1, 28, 0, "Enter Date");
		Ft_Gpu_CoCmd_Text(phost, disWid/2 - disWid*.2, disHei*.15, 28, 0, "mm/dd/yyyy");
		//put user input into textbox
		Ft_Gpu_Hal_WrCmd32(phost,COLOR_RGB(0,0,0));
		Ft_Gpu_CoCmd_Text(phost, (disWid/2-textBoxWid/2 + 5), disWid*.15, 30, 0, dateIn);

		// draw keypad
		Ft_Gpu_Hal_WrCmd32(phost,COLOR_RGB(255,255,255));
		tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
		drawKeypad(pressed);

		drawBack();
		disEnd();
		
		//check tag and determine what number was pressed
		if (tag>47 && tag<58)	pressed = tag - 48;
		else					pressed = 0;

		if(tag==0)		tempTag = tag;
		//get input in this block and input checking 
		if (tempTag != tag && tag != 0 && tag!=back){
			tempTag = tag;
			//get date
			if(tag> 47 && tag<58){
				if(i==0 && tag>49);					//1st in month
				else if(i==1 && dateIn[0]==49 && tag>50);	//2nd digit in month
				else if(i==3 && (dateIn[0]%48*10 + dateIn[1]%48)==2 && tag>50);		//1st in day
				else if(i==3 && (dateIn[0]%48*10 + dateIn[1]%48)!=2 && tag>51);		//1st in day
				else if(i==4 && !month31((dateIn[0]%48*10 + dateIn[1]%48)) && dateIn[3]==51 && tag>48);		//2nd in day
				else if(i==4 && month31((dateIn[0]%48*10 + dateIn[1]%48)) && dateIn[3]==51 && tag>49);		//2nd in day
				else{
					dateIn[i] = tag;
					i++;
				}
			}else if(tag == clr){			//if clr is pressed
				do{							//clear all user input
					dateIn[i] = 0;
					i--;
				}while(i>0);
			}else if(tag==del && i>0){		//if del is pressed
				if(i==3 || i==6){			//clear last user input
					dateIn[i] = 0;
					i--;
				}
				dateIn[i] = 0;
				i--;
			}
			if(tag==ok || i==11){			//if ok is pressed
				dateIn[i] = 0;				//compute date and update to system
				rtc_calendar_disable(&rtc_instance);
				time.month = (dateIn[0]%48)*10+(dateIn[1]%48);
				time.day = (dateIn[3]%48)*10+(dateIn[4]%48);
				time.year = (dateIn[6]%48)*1000+(dateIn[7]%48)*100+dateIn[8]%48*10+dateIn[9]%48;
				rtc_calendar_set_time(&rtc_instance, &time);
				rtc_calendar_enable(&rtc_instance);
				break;
			}
		}
		//insert '/' to separate date, month and year
		if(i==2 || i==5){
			dateIn[i] = '/';
			i++;
		}
	}while(tag != back);
	tag = 0;
}//end setDate


/* Function Name    : month31
 * Parameters       : char month
 * Return Values(s) : int
 * Description      : Check if the month has 31 days. Return 1 if yes, else
 *  0 if no
 */
int month31(char month){
	if(month==1 || month==3 || month==5 || month==7 || month==8 || \
        month==10 || month==12)
		return 1;
	else
		return 0;
}//end month31


/* Function Name    : printTime
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Get the current time and date, display it on the screen
 */
void printTime(){
	int fstYloc = disHei - 60, sndYloc = disHei - 30;
	char buff[32];
	//get current time and date
	rtc_calendar_get_time(&rtc_instance, &time);
	//put together a string for time and send to display
	snprintf(buff, 32, "%02d:%02d:%02d", time.hour, time.minute, time.second);
	Ft_Gpu_CoCmd_Text(phost, 10, fstYloc, font, 0, buff);
	
	//put together a string for date and send to display
	snprintf(buff, 32, "%02d/%02d/%04d", time.month, time.day, time.year);
	Ft_Gpu_CoCmd_Text(phost, 10, sndYloc, font, 0, buff);
}//end printTime


/* Function Name    : play
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Play 3 consecutive beep at 660Hz when called
 */
void play(){
	//set full volume
	Ft_Gpu_Hal_Wr8(phost,REG_VOL_SOUND,0x255);
	//set one single beet at 660Hz
	Ft_Gpu_Hal_Wr16(phost, REG_SOUND,  (73<< 8) | 0x10);

	//play it 3 times delay 100ms inbetween
	int i;
	for (i=0; i < 3; i++){
		Ft_Gpu_Hal_Wr8(phost, REG_PLAY, 1);
		delay_ms(100);
	}
}//end play


/* Function Name    : shiftHist
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Shift the history in the array down once, so newest 
 *  history is at the beginning of array
 */
void shiftHist(){
	int i, j;
	for(i = 9; i > 0; i--)
		for (j = 0; j < 9; j++)
			history[i][j] = history[i-1][j];
}//end shiftHist


/* Function Name    : saveHist
 * Parameters       : int16_t rssi169, int16_t rssi915, int16_t rssi245
 * Return Values(s) : void
 * Description      : Save the history to the array. Save the history 
 *  to SD Card if one is inserted
 */
void saveHist(int16_t rssi169, int16_t rssi915, int16_t rssi245){
	UINT bw;
	char buff[128];
	//shift history down once
	shiftHist();
	// put the time into the fist array
	history[0][0] = time.hour;
	history[0][1] = time.minute;
	history[0][2] = time.second;
	history[0][3] = time.month;
	history[0][4] = time.day;
	history[0][5] = time.year;
	history[0][6] = rssi169;
	history[0][7] = rssi915;
	history[0][8] = rssi245;
	

}//end saveHist


/****************************************************************************************************************************
													Append Blocks
****************************************************************************************************************************/
/* Function Name    : appAttn
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Put the attenuation background to RAM_DL to reduce MPU workload
 */
void appAttn(void){
	//start sequence for the display
	Ft_Gpu_CoCmd_Dlstart(phost);
	Ft_Gpu_Hal_WrCmd32(phost,CLEAR_COLOR_RGB(0,0,0));	
	Ft_Gpu_Hal_WrCmd32(phost, CLEAR(0,0,0));

	//draw the attenuation backgound
	drawRect(400, 100, 40.68);
	drawRect(400, 230, 915);
	drawRect(400, 360, 2.45);
	//wait for command to empty
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

	//calculate the number of command 
	attnEnd = Ft_Gpu_Hal_Rd16(phost,REG_CMD_DL) - 3*4;
	//coppy the command and put it into RAM_DL
	Ft_Gpu_Hal_WrCmd32(phost,CMD_MEMCPY);
	Ft_Gpu_Hal_WrCmd32(phost,attnStart);
	Ft_Gpu_Hal_WrCmd32(phost,RAM_DL);
	Ft_Gpu_Hal_WrCmd32(phost,attnEnd);
}//end appAttn


/* Function Name    : appRssi
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Put the RSSI background to RAM_DL to reduce MPU workload
 */
void appRssi(){
	//start sequence for the display
	rssiStart = attnStart + attnEnd + 4;
	Ft_Gpu_CoCmd_Dlstart(phost);
	Ft_Gpu_Hal_WrCmd32(phost,CLEAR_COLOR_RGB(0,0,0));
	Ft_Gpu_Hal_WrCmd32(phost, CLEAR(0,0,0));

	//draw the attenuation background
	drawRssi();
	//wait for command to empty
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
	
	//calculate the number of command 
	rssiEnd = Ft_Gpu_Hal_Rd16(phost,REG_CMD_DL) - 3*4;
	//copy the command and put it into RAM_DL
	Ft_Gpu_Hal_WrCmd32(phost,CMD_MEMCPY);
	Ft_Gpu_Hal_WrCmd32(phost,rssiStart);
	Ft_Gpu_Hal_WrCmd32(phost,RAM_DL);
	Ft_Gpu_Hal_WrCmd32(phost,rssiEnd);
}//end appRssi


/* Function Name    : appHist
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Put the history background to RAM_DL to reduce MPU workload
 */
void appHist(){
	//start sequence for the display
	histStart = rssiEnd + rssiStart + 4;Ft_Gpu_CoCmd_Dlstart(phost);
	Ft_Gpu_Hal_WrCmd32(phost,CLEAR_COLOR_RGB(0,0,0));
	Ft_Gpu_Hal_WrCmd32(phost, CLEAR(0,0,0));

	//draw the attenuation background
	drawHist();
	//wait for command to empty
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
	
	//wait for command to empty
	histEnd = Ft_Gpu_Hal_Rd16(phost,REG_CMD_DL) - 3*4;
	//wait for command to empty
	Ft_Gpu_Hal_WrCmd32(phost,CMD_MEMCPY);
	Ft_Gpu_Hal_WrCmd32(phost,histStart);
	Ft_Gpu_Hal_WrCmd32(phost,RAM_DL);
	Ft_Gpu_Hal_WrCmd32(phost,histEnd);
}//end appHist


/****************************************************************************************************************************
													Drawings
****************************************************************************************************************************/
/* Function Name    : drawRect
 * Parameters       : int x, int y, double freq
 * Return Values(s) : void
 * Description      : Draw the background for attenuation screen
 */
void drawRect(int x, int y, double freq){
	// draw rounded rectangles
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(RECTS));
	Ft_Gpu_Hal_WrCmd32(phost, LINE_WIDTH(10 * 16));
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(50));		// transparency apparently
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_RGB(255,255,255));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x * 16, y * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F((x + boxWid) * 16, (y + boxHei) * 16));
	Ft_Gpu_Hal_WrCmd32(phost, END());
	//draw lines
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(LINES));
	Ft_Gpu_Hal_WrCmd32(phost, LINE_WIDTH(2 * 16));
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(100));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F((x + boxWid/4) * 16, (y + 10) * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F((x + boxWid/4) * 16, (y+boxHei - 10) * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, END());
	// put the labels on
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(255));
	if (freq == 2.45){
		Ft_Gpu_CoCmd_Text(phost,x+boxWid/8-1,y+boxHei-30,28,OPT_CENTERX|OPT_CENTERY,"GHz");
		Ft_Gpu_CoCmd_Text(phost,x+boxWid/8-1,y+boxHei-75,30,OPT_CENTERX|OPT_CENTERY,"2.45");
	}else {
		Ft_Gpu_CoCmd_Text(phost,x+boxWid/8-1,y+boxHei-30,28,OPT_CENTERX|OPT_CENTERY,"MHz");
		if (freq == 915)
			Ft_Gpu_CoCmd_Text(phost,x+boxWid/8-1,y+boxHei-75,30,OPT_CENTERX|OPT_CENTERY,"915");
		else	Ft_Gpu_CoCmd_Text(phost,x+boxWid/8-1,y+boxHei-75,30,OPT_CENTERX|OPT_CENTERY,"169");
	}
	Ft_Gpu_CoCmd_Text(phost,x+boxWid-60,y+boxHei/2,31,OPT_CENTERX|OPT_CENTERY," dB ");
}//end drawRect


/* Function Name    : drawTitle
 * Parameters       : char *title 
 * Return Values(s) : void
 * Description      : Draw the title to each screen based on title received
 */
void drawTitle(char *title){
	Ft_Gpu_Hal_WrCmd32(phost, SCISSOR_XY(disWid/3,0));
	Ft_Gpu_Hal_WrCmd32(phost, SCISSOR_SIZE((disWid*3/2), 50));
	Ft_Gpu_CoCmd_Gradient(phost, disWid/3*2,0, 0x8B90FF, disWid/3*2, 50,0x2933FF);
//	Ft_Gpu_CoCmd_Gradient(phost, disWid/3,0, 0x2933FF, disWid, 50,0x8B90FF);
	Ft_Gpu_CoCmd_Text(phost, (disWid/3*2), 30, 30, OPT_CENTER, title);
	Ft_Gpu_Hal_WrCmd32(phost, CLEAR(0,1,1));
}//end drawTitle


/* Function Name    : drawBack
 * Parameters       : void
 * Return Values(s) : void
 * Description      : Draw back button when called
 */
void drawBack(){
	//assign tag value and draw button
	Ft_Gpu_Hal_WrCmd32(phost,TAG(back));
	Ft_Gpu_CoCmd_Button(phost,0, 0,(disWid*0.125),(disHei*0.112),font, (tag==back)? OPT_FLAT:0,"  Back  ");
}//end drawBack


/* Function Name    : drawKeypad
 * Parameters       : char pressed
 * Return Values(s) : void
 * Description      : Draw keypad and put effect on a key (if pressed)
 */
void drawKeypad(char pressed){
	//draw number from 1 to 9 
	Ft_Gpu_CoCmd_Keys(phost, disWid/2 - disWid*.2, disHei*.4, disWid*.3, 60, 29, pressed+48, "123");
	Ft_Gpu_CoCmd_Keys(phost, disWid/2 - disWid*.2, disHei*.54, disWid*.3, 60, 29, pressed+48, "456");
	Ft_Gpu_CoCmd_Keys(phost, disWid/2 - disWid*.2, disHei*.68, disWid*.3, 60, 29, pressed+48, "789");
	
	//draw '0' button
	Ft_Gpu_Hal_WrCmd32(phost,TAG(zero));
	Ft_Gpu_CoCmd_Button(phost, disWid/2 - disWid*.2, disHei*.82, disWid*.1455, 60, 29, (tag == zero)?  OPT_FLAT:0, "0");
	//draw delete button
	Ft_Gpu_Hal_WrCmd32(phost,TAG(del));
	Ft_Gpu_CoCmd_Button(phost, disWid/2 - disWid*.045, disHei*.82, disWid*.1455, 60, 29, (tag == del)?  OPT_FLAT:0, "<-");
	//draw clear button
	Ft_Gpu_Hal_WrCmd32(phost,TAG(clr));
	Ft_Gpu_CoCmd_Button(phost, disWid/2 + disWid*.105, disHei*.4, disWid*.1, disHei*.265, 29, (tag == clr)?  OPT_FLAT:0, "CLR");
	//draw ok button
	Ft_Gpu_Hal_WrCmd32(phost,TAG(ok));
	Ft_Gpu_CoCmd_Button(phost, disWid/2 + disWid*.105, disHei*.68, disWid*.1, disHei*.265, 29, (tag == ok)?  OPT_FLAT:0, "OK");
}//end drawKeypad


/* Function Name       : drawAlert
	* Parameters       : int x, int y, char stat
	* Return Values(s) : void
	* Description      : Draw alert, green if good attenuation, red otherwise
	*/
void drawAlert(int x, int y, char stat){
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(RECTS));
	Ft_Gpu_Hal_WrCmd32(phost, LINE_WIDTH(7 * 16));
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(255));
	if (stat == 0)			Ft_Gpu_Hal_WrCmd32(phost, COLOR_RGB(0, 255, 85));
	else					Ft_Gpu_Hal_WrCmd32(phost, COLOR_RGB(204, 51, 0));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x * 16, y * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F((x + 25) * 16, (y + 20) * 16));
	Ft_Gpu_Hal_WrCmd32(phost, END());
}//end drawAlert


/* Function Name    : drawRssi
 * Parameters       : void
 * Return Values(s) : void
 * Description      : draw rssi background
 */
void drawRssi(){
	//draw lines in table style
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(LINES));
	Ft_Gpu_Hal_WrCmd32(phost, LINE_WIDTH(2 * 16));
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(150));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(50 * 16, 150 * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(750 * 16, 150 * 16) );
		
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(50 * 16, 250 * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(750 * 16, 250 * 16) );
		
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(50 * 16, 350 * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(750 * 16, 350 * 16) );
		
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(525 * 16, 75 * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(525 * 16, 425 * 16) );
		
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(275 * 16, 75 * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(275 * 16, 425 * 16) );
	Ft_Gpu_Hal_WrCmd32(phost, END());
	
	//put label into the "table"
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(255));
	Ft_Gpu_CoCmd_Text(phost, 150, 100, 30, OPT_CENTER,"Unit");
	Ft_Gpu_CoCmd_Text(phost, 150, 200, 30, OPT_CENTER,"169 MHz");
	Ft_Gpu_CoCmd_Text(phost, 150, 300, 30, OPT_CENTER,"915 MHz");
	Ft_Gpu_CoCmd_Text(phost, 150, 400, 30, OPT_CENTER,"2.45 GHz");
	Ft_Gpu_CoCmd_Text(phost, 400, 100, 30, OPT_CENTER,"Display");
	Ft_Gpu_CoCmd_Text(phost, 650, 100, 30, OPT_CENTER," Receiver ");
}//end drawRssi


/* Function Name       : drawHist
 * Parameters       : void
 * Return Values(s) : void
 * Description      : draw history background
 */
void drawHist(){
	//put label to the background
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(255));
	Ft_Gpu_CoCmd_Text(phost, 100, 110, 28, OPT_CENTER," Date and Time ");
	Ft_Gpu_CoCmd_Text(phost, 100, 400, 28, OPT_CENTER," 169 MHz ");
	Ft_Gpu_CoCmd_Text(phost, 100, 550, 28, OPT_CENTER," 915 MHz ");
	Ft_Gpu_CoCmd_Text(phost, 100, 700, 28, OPT_CENTER," 2.45 GHz ");
}//end drawHist


/****************************************************************************************************************************
													Display Start / End
****************************************************************************************************************************/
/* Function Name    : disStart
 * Parameters       : void
 * Return Values(s) : void
 * Description      : display start sequence
 */
void disStart(){
	Ft_Gpu_CoCmd_Dlstart(phost);
    //change this for initial bg
	Ft_Gpu_Hal_WrCmd32(phost,CLEAR_COLOR_RGB(0,0,0));
	Ft_Gpu_Hal_WrCmd32(phost, CLEAR(1,1,1));
}//end disStart


/* Function Name    : disEnd
 * Parameters       : void
 * Return Values(s) : void
 * Description      : display end sequence
 */
void disEnd(){
	Ft_Gpu_Hal_WrCmd32(phost,DISPLAY());
	Ft_Gpu_CoCmd_Swap(phost);
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
}//end disEnd


/* Function Name    : configure_ext_ints
	* Parameters       : void
	* Return Values(s) : void
	* Description      : config external interrupt
	*/
void configure_ext_ints(void){
	// struct for external interrupt config
	struct extint_chan_conf ext_int_config;
	    
	// configure the external interrupt
	ext_int_config.gpio_pin            = LCD_INT;
	ext_int_config.gpio_pin_mux        = LCD_INT_PINMUX;
	ext_int_config.gpio_pin_pull       = LCD_INT_PULL;
	ext_int_config.wake_if_sleeping    = true;
	ext_int_config.filter_input_signal = false;
	ext_int_config.detection_criteria  = LCD_INT_DETECT;

	extint_chan_set_config(LCD_INT_LINE, &ext_int_config);
}//end configure_ext_ints

/* Function Name    : configure_ext_int_callback
	* Parameters       : void
	* Return Values(s) : void
	* Description      : config external interrupt callback
	*/
void configure_ext_int_callback(void){
	// register callback for the LCD's interrupt
	extint_register_callback(lcd_interrupt_callback, LCD_INT_LINE, \
	    LCD_INT_DETECT);
}//end configure_ext_int_callback
	
/* Function Name    : configure_rtc_calendar
	* Parameters       : void
	* Return Values(s) : void
	* Description      : config the rtc and set time to 00:00:00 01/01/2000
	*/
void configure_rtc_calendar(void){
	//initial time
	time.year   = 2017;
	time.month  = 12;
	time.day    = 31;
	time.hour   = 23;
	time.minute = 59;
	time.second = 55;
		
	/* Initialize RTC in calendar mode. */
	struct rtc_calendar_config config_rtc_calendar;
	rtc_calendar_get_config_defaults(&config_rtc_calendar);
	config_rtc_calendar.clock_24h     = true;
	rtc_calendar_init(&rtc_instance, RTC, &config_rtc_calendar);
		
	rtc_calendar_set_time(&rtc_instance, &time);
	rtc_calendar_enable(&rtc_instance);
	// adjust the frequency (the clock is slow atm)
	rtc_calendar_frequency_correction(&rtc_instance, 127);
}//end configure_rtc_calendar

/* Function Name    : clock_osc32k_init
	* Parameters       : void
	* Return Values(s) : void
	* Description      : config internal oscillator 32 kHz
	*/
void clock_osc32k_init(void){
	struct system_clock_source_osc32k_config osc32_config;
	system_clock_source_osc32k_get_config_defaults(&osc32_config);
		
	osc32_config.enable_1khz_output		= true;
	osc32_config.enable_32khz_output	= true;
	osc32_config.on_demand				= true;
	osc32_config.run_in_standby			= false;
	osc32_config.startup_time			= SYSTEM_OSC32K_STARTUP_130;
	osc32_config.write_once				= false;
	
	system_clock_source_osc32k_set_config(&osc32_config);
}//end clock_osc32k_init

/* Function Name    : clock_gclk2_init
	* Parameters       : void
	* Return Values(s) : void
	* Description      : turn on glck using internal 32 kHz oscillator
	*/
void clock_gclk2_init(void){
	struct system_gclk_gen_config gclk2_config;
		
	system_gclk_init();
		
	gclk2_config.source_clock			= SYSTEM_CLOCK_SOURCE_OSC32K;
	gclk2_config.output_enable			= false;
	gclk2_config.high_when_disabled		= false;
	gclk2_config.division_factor		= 32;
	gclk2_config.run_in_standby			= false;
		
	system_gclk_gen_set_config(GCLK_GENERATOR_2, &gclk2_config);
	system_gclk_gen_enable(GCLK_GENERATOR_2);
}//end clock_gclk2_init
/****************************************************************************************************************************
													Nothing beyond this point
****************************************************************************************************************************/