/*
 * sim_sd_log.h
 *
 * Created: 4/19/2018 6:39:40 PM
 *  Author: Dan
 */ 


#ifndef SIM_SD_LOG_H_
#define SIM_SD_LOG_H_

#include <asf.h>
#include <string.h>
#include <ff.h>
#include <rssi_mngr.h>
#include <sim_system_glcd_software.h>

typedef struct SD_LOG_TYPE{
    rssi_vals attn_vals;
    struct rtc_calendar_time log_time;
}SD_LOG;


void sd_log_record(FATFS* fat_fs, SD_LOG* log_ptr);



#endif /* SIM_SD_LOG_H_ */