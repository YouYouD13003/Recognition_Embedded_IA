/*
 * temp.h
 *
 *  Created on: Feb 27, 2025
 *      Author: Ayoub
 */

#ifndef TEMP_TEMP_H_
#define TEMP_TEMP_H_

#include <stdio.h>
#include <stdlib.h>
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_def.h"

#define ONEWIRE_PIN temp_io_Pin
#define ONEWIRE_PORT temp_io_GPIO_Port

// GPIO Pin and Port Configuration
#define TMP1826_PORT GPIOC  // GPIO Port should be GPIOC
#define TMP1826_PIN GPIO_PIN_10  // Pin should be GPIO_PIN_10

// 1-Wire Timing Definitions (Standard Speed)
// Adjusted delays based on TMP1826 datasheet
#define TMP1826_STARTUP_DELAY  300  // µs (max 300 µs)
#define TMP1826_CONV_DELAY     3500 // µs (3.5 ms for standard mode)
#define TMP1826_CONV_DELAY_HP  6500 // µs (6.5 ms for high-precision mode)
#define TMP1826_RESET_DELAY    500  // µs (standard mode)
#define TMP1826_RESET_DELAY_OD 60   // µs (overdrive mode)

// 1-Wire write and read timing
#define TMP1826_WR0_DELAY  90   // µs (write '0' in standard mode)
#define TMP1826_WR1_DELAY  10   // µs (write '1' in standard mode)
#define TMP1826_RD_DELAY   3    // µs (read pulse in standard mode)
#define TMP1826_MS_WINDOW  35   // µs (sampling window in standard mode)
extern TIM_HandleTypeDef htim2;
// Function Prototypes
void TMP1826_Init(void);
uint8_t TMP1826_Reset(void);
void TMP1826_WriteBit(uint8_t bit);
uint8_t TMP1826_ReadBit(void);
void TMP1826_WriteByte(uint8_t byte);
uint8_t TMP1826_ReadByte(void);
float TMP1826_ReadTemperature(void);

#endif /* TEMP_TEMP_H_ */
