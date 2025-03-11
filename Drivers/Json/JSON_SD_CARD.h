/*
 * JSON_SD_CARD.h
 *
 *  Created on: Mar 8, 2025
 *      Author: Ayoub
 */

#ifndef JSON_JSON_SD_CARD_H_
#define JSON_JSON_SD_CARD_H_
#include <stdio.h>    // For printf
#include <stdlib.h>   // For free, malloc, etc.
#include <stddef.h>   // For NULL
#include "cJSON.h"
#include "ff.h"
//#include "SD_CARD.h"
//void WriteConfigToSD(int sampling_frequency, int sensor_enabled);
void WriteConfigToSD(const char* filename, const char* json_string);
#endif /* JSON_JSON_SD_CARD_H_ */
