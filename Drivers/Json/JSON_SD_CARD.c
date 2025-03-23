/*
 * JSON_SD_CARD.c
 *
 *  Created on: Mar 8, 2025
 *      Author: Ayoub
 */
#include "JSON_SD_CARD.h"
#include "main.h"
extern void WriteToSDCard(const char *filename, const char *data);
extern char *ReadFileFromSD(const char *filename);
extern void buildFullPath(const char *filename, char *fullPath, size_t size);
extern FATFS FatFs;   // File system object
extern FIL fil;       // File object




//void WriteConfigToSD(int sampling_frequency, int sensor_enabled) {
//    // Create a JSON object
//    cJSON *config = cJSON_CreateObject();
//    cJSON_AddNumberToObject(config, "sampling_frequency", sampling_frequency);
//    cJSON_AddBoolToObject(config, "sensor_enabled", sensor_enabled);
//
//    // Convert JSON object to string
//    char *json_str = cJSON_Print(config);
//    if (json_str == NULL) {
//        printf("Error converting JSON to string!\n");
//        cJSON_Delete(config);
//        return;
//    }
//
//    // Write the JSON string to SD card using our generic function
//    WriteToSDCard("config.json", json_str);
//
//    // Clean up
//    free(json_str);
//    cJSON_Delete(config);
//}



void WriteConfigToSD(const char* filename, const char* json_string) {
    // Parse the JSON string
    cJSON *parsed_json = cJSON_Parse(json_string);
    if (parsed_json == NULL) {
        printf("Error parsing JSON string!\n");
        return;
    }

    // Extract values from the parsed JSON
    cJSON *sampling_freq_item = cJSON_GetObjectItem(parsed_json, "sampling_frequency");
    cJSON *sensor_enabled_item = cJSON_GetObjectItem(parsed_json, "sensor_enabled");

    // Check if the items exist and are of the correct type
    if (!cJSON_IsNumber(sampling_freq_item) || !cJSON_IsBool(sensor_enabled_item)) {
        printf("Invalid JSON format!\n");
        cJSON_Delete(parsed_json);
        return;
    }

    // Declare and initialize variables
    int sampling_frequency = sampling_freq_item->valueint;
    int sensor_enabled = sensor_enabled_item->valueint;

    // JMO
    sampling_frequency = delai;
    sensor_enabled = acq;

    // Clean up parsed JSON object
    cJSON_Delete(parsed_json);

    // Create a new JSON object
    cJSON *config = cJSON_CreateObject();
    cJSON_AddNumberToObject(config, "sampling_frequency", sampling_frequency);
    cJSON_AddBoolToObject(config, "sensor_enabled", sensor_enabled);

    // Convert JSON object to string
    char *json_str = cJSON_Print(config);
    if (json_str == NULL) {
        printf("Error converting JSON to string!\n");
        cJSON_Delete(config);
        return;
    }

    // Write the JSON string to SD card using your generic function
    WriteToSDCard(filename, json_str);

    // Clean up
    free(json_str);
    cJSON_Delete(config);
}


void ReadConfigFromSD(int *sampling_frequency, int *sensor_enabled) {
    FRESULT res;
    char fullPath[64];
    FILINFO fno;

    buildFullPath("config.json", fullPath, sizeof(fullPath));

    // Mount SD card
    res = f_mount(&FatFs, "0:", 1);
    if (res != FR_OK) {
         printf("Failed to mount SD card in ReadConfigFromSD! (Error code: %d)\n", res);
         *sampling_frequency = 500;
         *sensor_enabled = 0;
         return;
    }

    // Check if the file exists
    res = f_stat(fullPath, &fno);
    if (res == FR_NO_FILE) {
         printf("%s not found, creating default configuration.\n", fullPath);
         WriteConfigToSD("config.json", "{\"sampling_frequency\":500,\"sensor_enabled\":false}");
         HAL_Delay(1000);  // Allow time for file creation
         res = f_stat(fullPath, &fno);
         if (res != FR_OK) {
              printf("Failed to create %s! (Error code: %d)\n", fullPath, res);
              *sampling_frequency = 500;
              *sensor_enabled = 0;
              f_mount(0, "0:", 0);
              return;
         }
    } else if (res != FR_OK) {
         printf("Error stating %s! (Error code: %d)\n", fullPath, res);
         *sampling_frequency = 500;
         *sensor_enabled = 0;
         f_mount(0, "0:", 0);
         return;
    }

    char *buffer = ReadFileFromSD("config.json");
    if (buffer == NULL) {
         printf("Failed to read %s!\n", fullPath);
         *sampling_frequency = 500;
         *sensor_enabled = 0;
         return;
    }

    cJSON *config = cJSON_Parse(buffer);
    free(buffer);
    if (config == NULL) {
         printf("Error parsing JSON configuration from %s!\n", fullPath);
         *sampling_frequency = 500;
         *sensor_enabled = 0;
         return;
    }

    cJSON *freq_item = cJSON_GetObjectItem(config, "sampling_frequency");
    if (freq_item && cJSON_IsNumber(freq_item)) {
         *sampling_frequency = (int)freq_item->valuedouble;
    } else {
         *sampling_frequency = 500;
    }

    cJSON *sensor_item = cJSON_GetObjectItem(config, "sensor_enabled");
    if (sensor_item && cJSON_IsBool(sensor_item)) {
         *sensor_enabled = sensor_item->valueint;
    } else {
         *sensor_enabled = 0;
    }
    cJSON_Delete(config);
}








void UpdateConfigOnSD(int sampling_frequency, int sensor_enabled) {
    char *json_str = ReadFileFromSD("config.json");
    cJSON *config = NULL;
    if (json_str != NULL) {
         config = cJSON_Parse(json_str);
         free(json_str);
    }
    if (config == NULL) {
         config = cJSON_CreateObject();
    }
    if (cJSON_GetObjectItem(config, "sampling_frequency") != NULL) {
         cJSON_ReplaceItemInObject(config, "sampling_frequency", cJSON_CreateNumber(sampling_frequency));
    } else {
         cJSON_AddNumberToObject(config, "sampling_frequency", sampling_frequency);
    }
    if (cJSON_GetObjectItem(config, "sensor_enabled") != NULL) {
         cJSON_ReplaceItemInObject(config, "sensor_enabled", cJSON_CreateBool(sensor_enabled));
    } else {
         cJSON_AddBoolToObject(config, "sensor_enabled", sensor_enabled);
    }

    char *new_json_str = cJSON_Print(config);
    if (new_json_str == NULL) {
         printf("Error converting JSON to string in UpdateConfigOnSD!\n");
         cJSON_Delete(config);
         return;
    }
    WriteToSDCard("config.json", new_json_str);
    free(new_json_str);
    cJSON_Delete(config);
}

