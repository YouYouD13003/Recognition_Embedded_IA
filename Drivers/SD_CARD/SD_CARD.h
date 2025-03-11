/*
 * SD_CARD.h
 *
 *  Created on: Feb 27, 2025
 *      Author: Ayoub
 */

#ifndef SD_CARD_SD_CARD_H_
#define SD_CARD_SD_CARD_H_

#include "app_fatfs.h"
#include "Accelerometer.h"
#include <string.h>

#define SAMPLE_WINDOW   256
#define BUFFER_SIZE   4096
FATFS FatFs;   // File system object
FIL fil;       // File object
FRESULT res;   // Result code
UINT bw;       // Bytes written
UINT br;       // Bytes read
void buildFullPath(const char *filename, char *fullPath, size_t size);
 char *ReadFileFromSD(const char *filename);
void WriteToSDCard(const char *filename, const char *data);
void WriteIMUDataToSD(AccelerometerData*accelData, GyroscopeData *gyroData);
void WriteToSDCard(const char *filename, const char *data);

#endif /* SD_CARD_SD_CARD_H_ */
