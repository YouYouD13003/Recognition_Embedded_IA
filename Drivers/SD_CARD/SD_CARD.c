/*
 * SD_CARD.c
 *
 *  Created on: Feb 27, 2025
 *      Author: Ayoub
 */


#include "SD_CARD.h"





//void WriteIMUDataToSD(AccelerometerData *accelData, GyroscopeData *gyroData) {
//    static int sample_count = 0;
//    static char buffer[50000];
//    static int offset = 0;
//
//    // Scale accelerometer data to milli-g (mg)
//    float accelX_mg = accelData->x * 0.061f;
//    float accelY_mg = accelData->y * 0.061f;
//    float accelZ_mg = accelData->z * 0.061f;
//
//    // Scale gyroscope data to degrees per second (dps)
//    float gyroX_dps = gyroData->x * 0.035f;
//    float gyroY_dps = gyroData->y * 0.035f;
//    float gyroZ_dps = gyroData->z * 0.035f;
//
//    // Append scaled IMU data to buffer (accelerometer first, then gyroscope)
//    int bytes_written = snprintf(buffer + offset, sizeof(buffer) - offset, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,",
//                                 accelX_mg, accelY_mg, accelZ_mg,
//                                 gyroX_dps, gyroY_dps, gyroZ_dps);
//    if (bytes_written < 0) {
//        printf("❌ Error formatting IMU data!\n");
//        return;
//    }
//    offset += bytes_written;
//    sample_count++;
//
//    // Check for buffer overflow
//    if (offset + 50 >= sizeof(buffer)) {
//        printf("❌ Buffer overflow prevented! Flushing data early.\n");
//        buffer[offset - 1] = '\n';  // Replace last comma with newline
//        WriteBufferToSD(buffer, offset);
//        offset = 0;
//        sample_count = 0;
//    }
//
//    // Write to SD card if sample window is reached
//    if (sample_count >= SAMPLE_WINDOW) {
//        buffer[offset - 1] = '\n';  // Replace last comma with newline
//        WriteBufferToSD(buffer, offset);
//        offset = 0;
//        sample_count = 0;
//    }
//}



void WriteIMUDataToSD(AccelerometerData *accelData, GyroscopeData *gyroData) {
    static int sample_count = 0;
    static char buffer[50000];
    static int offset = 0;

    // Data is already in g and dps → No need for additional scaling!
    float accelX_g = accelData->x;
    float accelY_g = accelData->y;
    float accelZ_g = accelData->z;

    float gyroX_dps = gyroData->x;
    float gyroY_dps = gyroData->y;
    float gyroZ_dps = gyroData->z;

    // Append IMU data to buffer
    int bytes_written = snprintf(buffer + offset, sizeof(buffer) - offset, "%.4f,%.4f,%.4f,%.2f,%.2f,%.2f,",
                                 accelX_g, accelY_g, accelZ_g,
                                 gyroX_dps, gyroY_dps, gyroZ_dps);
    if (bytes_written < 0) {
        printf("❌ Error formatting IMU data!\n");
        return;
    }
    offset += bytes_written;
    sample_count++;

    // Check for buffer overflow
    if (offset + 50 >= sizeof(buffer)) {
        printf("❌ Buffer overflow prevented! Flushing data early.\n");
        buffer[offset - 1] = '\n';  // Replace last comma with newline
        WriteBufferToSD(buffer, offset);
        offset = 0;
        sample_count = 0;
    }

    // Write to SD card if sample window is reached
    if (sample_count >= SAMPLE_WINDOW) {
        buffer[offset - 1] = '\n';  // Replace last comma with newline
        WriteBufferToSD(buffer, offset);
        offset = 0;
        sample_count = 0;
    }
}





void WriteBufferToSD(char *buffer, int length) {
    // Mount SD card
    if (f_mount(&FatFs, "", 1) != FR_OK) {
        printf("❌ Failed to mount SD card!\n");
        return;
    }

    // Open file in append mode
    if (f_open(&fil, "checkin.csv", FA_OPEN_APPEND | FA_WRITE) != FR_OK) {
        printf("❌ Error opening file!\n");
        f_mount(0, "", 0);
        return;
    }

    // Write data to file
    UINT bytesWritten;
    if (f_write(&fil, buffer, length, &bytesWritten) != FR_OK || bytesWritten != length) {
        printf("❌ Error writing to file!\n");
    } else {
        printf("✅ Successfully wrote %d bytes to SD card.\n", bytesWritten);
    }

    // Close file and unmount SD card
    f_sync(&fil);
    f_close(&fil);
    f_mount(0, "", 0);
}




