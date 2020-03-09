/*
 * sim_sd_log.c
 *
 * Created: 4/19/2018 6:39:52 PM
 *  Author: Dan
 */ 


#include "sim_sd_log.h"


void sd_log_record(FATFS* fat_fs, SD_LOG* log_ptr)
{
    FIL file_obj;
    UINT bw;
    char str_buff[128];
    uint8_t log_hour = log_ptr->log_time.hour;
    uint8_t log_min = log_ptr->log_time.minute;
    uint8_t log_sec = log_ptr->log_time.second;
    uint8_t log_year = log_ptr->log_time.year;
    uint8_t log_month = log_ptr->log_time.month;
    uint8_t log_day = log_ptr->log_time.day;
    rssi_t attn_169 = log_ptr->attn_vals.rssi169;
    rssi_t attn_915 = log_ptr->attn_vals.rssi915;
    rssi_t attn_245 = log_ptr->attn_vals.rssi245;
    
    uint8_t stat_val = 0;
    
    f_mount(fat_fs, "", 0);		/* Give a work area to the default drive */

    // create file
    if (f_open(&file_obj, "newfile.txt", FA_WRITE | FA_OPEN_APPEND) == FR_OK) 
    {	
        snprintf(str_buff, 128, "%d:%d:%d on %d/%d/%d", log_hour, log_min, log_sec, log_month, log_day, log_year);
        
        stat_val = f_write(&file_obj, "Shield failure detected at ", 27, &bw);	/* Write data to the file */
        
        fat_debug("%d\n", stat_val);
        
        stat_val = f_write(&file_obj, str_buff, strlen(str_buff), &bw);
        
        fat_debug("%d\n", stat_val);
        
        snprintf(str_buff, 128, "\r\n169 MHZ attenuation: %d\r\n915 MHz attenuation: %d\r\n2.45 GHz attenuation: %d\r\n", attn_169, attn_915, attn_245);

        stat_val = f_write(&file_obj, str_buff, strlen(str_buff), &bw);
        
        fat_debug("%d\n", stat_val);
        
        stat_val = f_close(&file_obj);								/* Close the file */
        
        fat_debug("%d\n", stat_val);
    }
    
    f_unmount("");
}