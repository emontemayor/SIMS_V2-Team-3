/*
 * rssi_mngr.h
 *
 * Created: 4/9/2018 1:30:35 PM
 *  Author: Dan
 */ 


#ifndef RSSI_MNGR_H_
#define RSSI_MNGR_H_

#include <asf.h>
#include <stdint.h>



typedef volatile int16_t rssi_t;

#define RSSI_SIZE sizeof(rssi_t)

typedef volatile struct RSSI_VAL_TYPE{
    rssi_t rssi169;
    rssi_t rssi915;
    rssi_t rssi245;
}rssi_vals;

#endif /* RSSI_MNGR_H_ */