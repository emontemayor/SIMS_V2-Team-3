/**********************************************
 * rssi_mngr.h
 * Header that defines a type for managing RSSI values
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#ifndef RSSI_MNGR_H_
#define RSSI_MNGR_H_

#include <asf.h>
#include <stdint.h>


typedef volatile int16_t rssi_t;

#define RSSI_SIZE sizeof(rssi_t)

// new struct type for managing RSSI values
typedef volatile struct RSSI_VAL_TYPE{
    rssi_t rssi169;
    rssi_t rssi915;
    rssi_t rssi245;
}rssi_vals;

#endif /* RSSI_MNGR_H_ */