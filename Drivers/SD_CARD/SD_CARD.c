/*
 * SD_CARD.c
 *
 *  Created on: Feb 27, 2025
 *      Author: Ayoub
 */


#include "SD_CARD.h"

void buildFullPath(const char *filename, char *fullPath, size_t size) {
    snprintf(fullPath, size, "0:%s", filename);
}


char* ReadFileFromSD(const char *filename) {
    FRESULT res;
    char fullPath[64];

    res = f_mount(&FatFs, "0:", 1);
    if (res != FR_OK) {
         printf("Failed to mount SD card in ReadFileFromSD! (Error code: %d)\n", res);
         return NULL;
    }

    buildFullPath(filename, fullPath, sizeof(fullPath));
    res = f_open(&fil, fullPath, FA_READ);
    if (res != FR_OK) {
         printf("Error opening file: %s (Error code: %d)\n", fullPath, res);
         f_mount(0, "0:", 0);
         return NULL;
    }

    DWORD file_size = f_size(&fil);
    char *buffer = malloc(file_size + 1);
    if (!buffer) {
         printf("Memory allocation error in ReadFileFromSD!\n");
         f_close(&fil);
         f_mount(0, "0:", 0);
         return NULL;
    }

    UINT br;
    res = f_read(&fil, buffer, file_size, &br);
    if (res != FR_OK) {
         printf("Error reading file: %s (Error code: %d)\n", fullPath, res);
         free(buffer);
         f_close(&fil);
         f_mount(0, "0:", 0);
         return NULL;
    }
    buffer[file_size] = '\0';

    f_close(&fil);
    f_mount(0, "0:", 0);
    return buffer;
}


void WriteToSDCard(const char *filename, const char *data) {
    FRESULT res;
    char fullPath[64];

    // Mount the SD card using drive "0:"
    res = f_mount(&FatFs, "0:", 1);
    if (res != FR_OK) {
         printf("Failed to mount SD card in WriteToSDCard! (Error code: %d)\n", res);
         return;
    }

    buildFullPath(filename, fullPath, sizeof(fullPath));
    res = f_open(&fil, fullPath, FA_CREATE_ALWAYS | FA_WRITE);
    if (res != FR_OK) {
         if (res == FR_NOT_ENABLED) {
             printf("Error: Disk I/O driver not enabled. (FR_NOT_ENABLED, error code: %d)\n", res);
         } else {
             printf("Error opening file %s for writing! (Error code: %d)\n", fullPath, res);
         }
         f_mount(0, "0:", 0);
         return;
    }

    UINT bw;
    res = f_write(&fil, data, strlen(data), &bw);
    if (res != FR_OK || bw != strlen(data)) {
         printf("Error writing to file %s! (Error code: %d)\n", fullPath, res);
    } else {
         printf("Successfully wrote %d bytes to %s.\n", bw, fullPath);
    }

    f_sync(&fil);
    f_close(&fil);
    f_mount(0, "0:", 0);
}



void WriteBufferToSD(char *buffer, int length) {
    // Mount SD card
    if (f_mount(&FatFs, "", 1) != FR_OK) {
        printf(" Failed to mount SD card!\n");
        return;
    }

    // Open file in append mode
    if (f_open(&fil, "checkin.csv", FA_OPEN_APPEND | FA_WRITE) != FR_OK) {
        printf(" Error opening file!\n");
        f_mount(0, "", 0);
        return;
    }

    // Write data to file
    UINT bytesWritten;
    if (f_write(&fil, buffer, length, &bytesWritten) != FR_OK || bytesWritten != length) {
        printf(" Error writing to file!\n");
    } else {
        printf(" Successfully wrote %d bytes to SD card.\n", bytesWritten);
    }

    // Close file and unmount SD card
    f_sync(&fil);
    f_close(&fil);
    f_mount(0, "", 0);
}





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
        printf(" Error formatting IMU data!\n");
        return;
    }
    offset += bytes_written;
    sample_count++;

    // Check for buffer overflow
    if (offset + 50 >= sizeof(buffer)) {
        printf(" Buffer overflow prevented! Flushing data early.\n");
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





