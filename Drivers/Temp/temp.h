/*
 * temp.h
 *
 *  Created on: Feb 27, 2025
 *      Author: Ayoub
 */

#ifndef TEMP_TEMP_H_
#define TEMP_TEMP_H_
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_def.h"

#define ONEWIRE_PIN temp_io_Pin
#define ONEWIRE_PORT temp_io_GPIO_Port


void ONEWIRE_SetOutput(void);
void ONEWIRE_SetInput(void);
uint8_t ONEWIRE_Reset(void);
void ONEWIRE_WriteBit(uint8_t bit);
uint8_t ONEWIRE_ReadBit(void);
void ONEWIRE_WriteByte(uint8_t byte);
uint8_t ONEWIRE_ReadByte(void);
void TMP1826_StartConversion(void);
float TMP1826_ReadTemperature(void);

#endif /* TEMP_TEMP_H_ */
