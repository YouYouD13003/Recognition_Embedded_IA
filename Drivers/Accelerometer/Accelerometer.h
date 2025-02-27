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

#define LIS3DH_ADDR 0x19 // I2C address of the sensor

HAL_StatusTypeDef LIS3DH_WriteRegister_DMA(uint8_t reg, uint8_t value);

HAL_StatusTypeDef LIS3DH_ReadRegister_DMA(uint8_t reg, uint8_t *value);

HAL_StatusTypeDef LIS3DH_ReadMultiple_DMA(uint8_t reg, uint8_t *buffer,
		uint16_t size);

void LIS3DH_Init(void);

void LIS3DH_ReadAccel(int16_t *x, int16_t *y, int16_t *z);

#endif /* ACCELEROMETER_ACCELEROMETER_H_ */
