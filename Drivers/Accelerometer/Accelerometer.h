/*
 * Accelerometer.h
 *
 *  Created on: Dec 9, 2024
 *      Author: Ayoub
 */

#ifndef ACCELEROMETER_ACCELEROMETER_H_
#define ACCELEROMETER_ACCELEROMETER_H_

#include <stdio.h>
#include <stdlib.h>
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_def.h"
#include "NanoEdgeAI.h"

#include <stdint.h>  // Include this for int16_t


#define AXIS_NUMBER 6       // IMU has 6 axes (Accelerometer + Gyroscope)
#define DATA_INPUT_USER 256 // Adjust based on model settings

extern float input_user_buffer[DATA_INPUT_USER * AXIS_NUMBER];

#define ISM330DHCX_I2C_ADDRESS (0x6B << 1)  // 0xD6 for Write, 0xD7 for Read
#define WHO_AM_I_REGISTER 0x0F
#define OUT_X_L_REGISTER (0x28 | 0x80)  // Set MSB to enable auto-increment
#define START_DELAY 30000
#define CTRL_REG2 0x21
#define CTRL_REG5 0x24
#define CTRL_REG1 0x20
#define CTRL_REG4 0x23
#define CTRL_REG3 0x22
#define OUT_X_L_G 0x22  // First register of gyroscope data
#define FIFO_CTRL_REG   0x2E
#define OUTX_L_G  0x22


typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} AccelerometerData;


typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} GyroscopeData;


void InitializeISM330DHCX2(void);
//void ReadIMUData(void);
void ReadIMUData(AccelerometerData *accelData, GyroscopeData *gyroData);
void ClassifyIMUDataAndWriteToSD(void);


#endif /* ACCELEROMETER_ACCELEROMETER_H_ */
