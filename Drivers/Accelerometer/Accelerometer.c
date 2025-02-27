#include "Accelerometer.h"

extern I2C_HandleTypeDef hi2c1;
extern const float knowledge[];
static uint16_t neai_buffer_ptr = 0, neai_cnt = 0;
static float neai_buffer[AXIS_NUMBER * DATA_INPUT_USER];
const char *id2class[CLASS_NUMBER + 1] = {
    "unknown",
    "alexander_marche",
    "ayoub_marche",
    "mathias_Marche",
    "jade_marcheCSV"
};

void InitializeISM330DHCX2(void) {
    uint8_t config[2];
    HAL_StatusTypeDef status;

    // Step 1: Enable Register Auto-Increment & Block Data Update (CTRL3_C)
    config[0] = 0x12; // CTRL3_C register
    config[1] = 0x44; // 0b01000100: IF_INC = 1 (Auto-Increment), BDU = 1
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("❌ Error: CTRL3_C setup failed\n");

    HAL_Delay(10);

    // Step 2: Enable Accelerometer - 104Hz ODR, ±2g Full Scale, High-Performance Mode (CTRL1_XL)
    config[0] = 0x10; // CTRL1_XL register
    config[1] = 0x50; // 0b01010000: ODR = 104Hz, ±2g, High-Performance Mode
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("❌ Error: CTRL1_XL setup failed\n");

    HAL_Delay(10);

    // Step 3: Enable Gyroscope - 104Hz ODR, ±1000 dps Full Scale (CTRL2_G)
    config[0] = 0x11; // CTRL2_G register
    config[1] = 0x48; // 0b01001000: ODR = 104Hz, ±1000 dps
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("❌ Error: CTRL2_G setup failed\n");

    HAL_Delay(10);

    // Step 4: Enable High-Performance Mode for Accelerometer (CTRL6_C)
    config[0] = 0x15; // CTRL6_C register
    config[1] = 0x00; // 0b00000000: High-Performance Mode enabled for accelerometer
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("❌ Error: CTRL6_C setup failed\n");

    HAL_Delay(10);

    // Step 5: Enable High-Performance Mode for Gyroscope (CTRL7_G) ✅ FIXED
    config[0] = 0x16; // CTRL7_G register
    config[1] = 0x00; // 0b00000000: High-Performance Mode enabled for gyroscope
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("❌ Error: CTRL7_G setup failed\n");

    HAL_Delay(10);

    // Step 6: Read Back Register Values for Debugging
    uint8_t ctrl1_xl, ctrl2_g, ctrl3_c, ctrl6_c, ctrl7_g;
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &ctrl1_xl, 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &ctrl2_g, 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x12, I2C_MEMADD_SIZE_8BIT, &ctrl3_c, 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x15, I2C_MEMADD_SIZE_8BIT, &ctrl6_c, 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x16, I2C_MEMADD_SIZE_8BIT, &ctrl7_g, 1, 100);

    // Debug Print Statements
    printf(" ISM330DHCX Initialization Complete!\n");
    printf(" CTRL1_XL = 0x%02X (Should be 0x50 - High-Perf Accel)\n", ctrl1_xl);
    printf(" CTRL2_G  = 0x%02X (Should be 0x48 - High-Perf Gyro)\n", ctrl2_g);
    printf(" CTRL3_C  = 0x%02X (Should be 0x44 - Auto-Inc, BDU)\n", ctrl3_c);
    printf(" CTRL6_C  = 0x%02X (Should be 0x00 - High-Perf Accel Confirmed)\n", ctrl6_c);
    printf(" CTRL7_G  = 0x%02X (Should be 0x00 - High-Perf Gyro Confirmed)\n", ctrl7_g);
}


//void ReadIMUData() {
//    AccelerometerData accelData;
//    GyroscopeData gyroData;
//    uint8_t accelDataRaw[6] = {0};
//    uint8_t gyroDataRaw[6] = {0};
//    HAL_StatusTypeDef status;
//
//    // Read Gyroscope Data
//    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x22, I2C_MEMADD_SIZE_8BIT, gyroDataRaw, 6, 100);
//    if (status == HAL_OK) {
//        gyroData.x = (int16_t)((gyroDataRaw[0]) | (gyroDataRaw[1] << 8));  // FIXED
//        gyroData.y = (int16_t)((gyroDataRaw[2]) | (gyroDataRaw[3] << 8));  // FIXED
//        gyroData.z = (int16_t)((gyroDataRaw[4]) | (gyroDataRaw[5] << 8));  // FIXED
//
//        // Convert raw gyroscope data to degrees per second (dps)
//        float gyroX_dps = gyroData.x * 0.035f;
//        float gyroY_dps = gyroData.y * 0.035f;
//        float gyroZ_dps = gyroData.z * 0.035f;
//
//        printf("🔄 Gyro Data (dps) X: %.2f, Y: %.2f, Z: %.2f\n", gyroX_dps, gyroY_dps, gyroZ_dps);
//    } else {
//        printf("❌ Error reading gyroscope data! Status: %d\n", status);
//    }
//
//    // Read Accelerometer Data
//    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x28, I2C_MEMADD_SIZE_8BIT, accelDataRaw, 6, 100);
//    if (status == HAL_OK) {
//        accelData.x = (int16_t)((accelDataRaw[0]) | (accelDataRaw[1] << 8));  // FIXED
//        accelData.y = (int16_t)((accelDataRaw[2]) | (accelDataRaw[3] << 8));  // FIXED
//        accelData.z = (int16_t)((accelDataRaw[4]) | (accelDataRaw[5] << 8));  // FIXED
//
//
//
//        // Convert raw accelerometer data to milli-g (mg)
//        float accelX_mg = accelData.x * 0.061f;
//        float accelY_mg = accelData.y * 0.061f;
//        float accelZ_mg = accelData.z * 0.061f;
//
//        printf("📊 Accel Data (mg) X: %.2f, Y: %.2f, Z: %.2f\n", accelX_mg, accelY_mg, accelZ_mg);
//    } else {
//        printf("❌ Error reading accelerometer data! Status: %d\n", status);
//    }
//
//    // 🔥 Write raw sensor data to SD card (Optional)
//   WriteIMUDataToSD(&accelData, &gyroData);
//
//    // Delay for next reading
//    HAL_Delay(10);
//}



//void ReadIMUData() {
//    AccelerometerData accelData;
//    GyroscopeData gyroData;
//    uint8_t accelDataRaw[6] = {0};
//    uint8_t gyroDataRaw[6] = {0};
//    HAL_StatusTypeDef status;
//
//    // Read Gyroscope Data
//    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x22,
//                               I2C_MEMADD_SIZE_8BIT, gyroDataRaw, 6, 100);
//    if (status == HAL_OK) {
//        int16_t rawGyroX = (int16_t)((gyroDataRaw[1] << 8) | gyroDataRaw[0]);
//        int16_t rawGyroY = (int16_t)((gyroDataRaw[3] << 8) | gyroDataRaw[2]);
//        int16_t rawGyroZ = (int16_t)((gyroDataRaw[5] << 8) | gyroDataRaw[4]);
//
//        // 🔥 Convert to degrees per second (dps)
//        float gyroSensitivity = 35.0f; // Sensitivity for ±1000 dps FS
//        gyroData.x = rawGyroX * gyroSensitivity / 1000.0f; // Convert mdps to dps
//        gyroData.y = rawGyroY * gyroSensitivity / 1000.0f;
//        gyroData.z = rawGyroZ * gyroSensitivity / 1000.0f;
//    } else {
//        printf("❌ Error reading gyroscope data! Status: %d\n", status);
//    }
//
//    // Read Accelerometer Data
//    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x28,
//                               I2C_MEMADD_SIZE_8BIT, accelDataRaw, 6, 100);
//    if (status == HAL_OK) {
//        int16_t rawAccelX = (int16_t)((accelDataRaw[1] << 8) | accelDataRaw[0]);
//        int16_t rawAccelY = (int16_t)((accelDataRaw[3] << 8) | accelDataRaw[2]);
//        int16_t rawAccelZ = (int16_t)((accelDataRaw[5] << 8) | accelDataRaw[4]);
//
//        // 🔥 Convert to g (acceleration)
//        float accelSensitivity = 0.061f; // Sensitivity for ±2g FS
//        accelData.x = rawAccelX * accelSensitivity / 1000.0f; // Convert mg to g
//        accelData.y = rawAccelY * accelSensitivity / 1000.0f;
//        accelData.z = rawAccelZ * accelSensitivity / 1000.0f;
//    } else {
//        printf("❌ Error reading accelerometer data! Status: %d\n", status);
//    }
//
//    // 🔥 Write data to SD card immediately after reading
//    WriteIMUDataToSD(&accelData, &gyroData);
//
//    // Delay for next reading
//    HAL_Delay(10); // Adjust based on your sampling rate
//}









//void ReadIMUData() {
//	AccelerometerData accelData;
//	GyroscopeData gyroData;
//	uint8_t accelDataRaw[6] = { 0 };
//	uint8_t gyroDataRaw[6] = { 0 };
//	HAL_StatusTypeDef status;
//
//	// Read Gyroscope Data
//	status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x22,
//			I2C_MEMADD_SIZE_8BIT, gyroDataRaw, 6, 100);
//	if (status == HAL_OK) {
//		gyroData.x = (int16_t) ((gyroDataRaw[1] << 8) | gyroDataRaw[0]);
//		gyroData.y = (int16_t) ((gyroDataRaw[3] << 8) | gyroDataRaw[2]);
//		gyroData.z = (int16_t) ((gyroDataRaw[5] << 8) | gyroDataRaw[4]);
//	} else {
//		printf("❌ Error reading gyroscope data! Status: %d\n", status);
//	}
//
//	// Read Accelerometer Data
//	status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x28,
//			I2C_MEMADD_SIZE_8BIT, accelDataRaw, 6, 100);
//	if (status == HAL_OK) {
//		accelData.x = (int16_t) ((accelDataRaw[1] << 8) | accelDataRaw[0]);
//		accelData.y = (int16_t) ((accelDataRaw[3] << 8) | accelDataRaw[2]);
//		accelData.z = (int16_t) ((accelDataRaw[5] << 8) | accelDataRaw[4]);
//	} else {
//		printf("❌ Error reading accelerometer data! Status: %d\n", status);
//	}
//
//	// 🔥 Write data to SD card immediately after reading
//	WriteIMUDataToSD(&accelData, &gyroData);
//
//	// Delay for next reading
//	HAL_Delay(10); // Adjust based on your sampling rate
//}


void ReadIMUData(AccelerometerData *accelData, GyroscopeData *gyroData) {
    uint8_t accelDataRaw[6] = {0};
    uint8_t gyroDataRaw[6] = {0};
    HAL_StatusTypeDef status;

    // ✅ Read Gyroscope Data
    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x22,
                               I2C_MEMADD_SIZE_8BIT, gyroDataRaw, 6, 100);
    if (status == HAL_OK) {
        int16_t rawGyroX = (int16_t)((gyroDataRaw[1] << 8) | gyroDataRaw[0]);
        int16_t rawGyroY = (int16_t)((gyroDataRaw[3] << 8) | gyroDataRaw[2]);
        int16_t rawGyroZ = (int16_t)((gyroDataRaw[5] << 8) | gyroDataRaw[4]);

        // 🔥 Convert to degrees per second (dps)
        float gyroSensitivity = 35.0f; // Sensitivity for ±1000 dps FS
        gyroData->x = rawGyroX * gyroSensitivity / 1000.0f; // Convert mdps to dps
        gyroData->y = rawGyroY * gyroSensitivity / 1000.0f;
        gyroData->z = rawGyroZ * gyroSensitivity / 1000.0f;
    } else {
        printf("❌ Error reading gyroscope data! Status: %d\n", status);
    }

    // ✅ Read Accelerometer Data
    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x28,
                               I2C_MEMADD_SIZE_8BIT, accelDataRaw, 6, 100);
    if (status == HAL_OK) {
        int16_t rawAccelX = (int16_t)((accelDataRaw[1] << 8) | accelDataRaw[0]);
        int16_t rawAccelY = (int16_t)((accelDataRaw[3] << 8) | accelDataRaw[2]);
        int16_t rawAccelZ = (int16_t)((accelDataRaw[5] << 8) | accelDataRaw[4]);

        // 🔥 Convert to g (acceleration)
        float accelSensitivity = 0.061f; // Sensitivity for ±2g FS
        accelData->x = rawAccelX * accelSensitivity / 1000.0f; // Convert mg to g
        accelData->y = rawAccelY * accelSensitivity / 1000.0f;
        accelData->z = rawAccelZ * accelSensitivity / 1000.0f;
    } else {
        printf("❌ Error reading accelerometer data! Status: %d\n", status);
    }
}







void InitializeAI() {
    enum neai_state ai_status = neai_classification_init(knowledge);

    if (ai_status != NEAI_OK) {
        printf("❌ NanoEdge AI Init Failed! Error: %d\n", ai_status);
        while (1);  // Halt execution
    }
    printf("✅ NanoEdge AI Initialized Successfully!\n");
}



void ClassifyIMUDataAndWriteToSD() {


    uint16_t id_class = 0;
    float output_class_buffer[CLASS_NUMBER];




    // 🔥 Run AI classification
    enum neai_state status = neai_classification(input_user_buffer, output_class_buffer, &id_class);

    if (status == NEAI_OK) {
        float confidence = output_class_buffer[id_class] * 100;  // Convert to percentage
        const char *recognized_person = (id_class < CLASS_NUMBER) ? id2class[id_class] : "unknown";

        // 🔥 Print confidence for all cases
        printf("🔍 AI Classification Result: %s - Confidence: %.2f%%\n", recognized_person, confidence);

        // 🔥 Always log confidence to SD card (if required)
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "%s,%.2f%%\n", recognized_person, confidence);
        WriteToSDCard("recognized.csv", buffer);

        // 🔥 Handle high-confidence cases separately
        if (confidence >= 90.0) {
            printf("✅ High Confidence: %s with %.2f%% confidence\n", recognized_person, confidence);
        } else {
            printf("⚠️ Low confidence (%.2f%%) - Still logging data\n", confidence);
        }
    } else {
        printf("❌ AI Classification Error: %d\n", status);
    }
}


void ReadIMUDataForAI() {
    static int sample_index = 0; // Tracks how many samples are stored

    AccelerometerData accelData;
    GyroscopeData gyroData;
    uint8_t accelDataRaw[6] = {0};
    uint8_t gyroDataRaw[6] = {0};
    HAL_StatusTypeDef status;

    // Read Gyroscope Data
    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x22,
                              I2C_MEMADD_SIZE_8BIT, gyroDataRaw, 6, 100);
    if (status == HAL_OK) {
        gyroData.x = (int16_t)((gyroDataRaw[1] << 8) | gyroDataRaw[0]);
        gyroData.y = (int16_t)((gyroDataRaw[3] << 8) | gyroDataRaw[2]);
        gyroData.z = (int16_t)((gyroDataRaw[5] << 8) | gyroDataRaw[4]);
    } else {
        printf("❌ Error reading gyroscope data! Status: %d\n", status);
        return;
    }

    // Read Accelerometer Data
    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x28,
                              I2C_MEMADD_SIZE_8BIT, accelDataRaw, 6, 100);
    if (status == HAL_OK) {
        accelData.x = (int16_t)((accelDataRaw[1] << 8) | accelDataRaw[0]);
        accelData.y = (int16_t)((accelDataRaw[3] << 8) | accelDataRaw[2]);
        accelData.z = (int16_t)((accelDataRaw[5] << 8) | accelDataRaw[4]);
    } else {
        printf("❌ Error reading accelerometer data! Status: %d\n", status);
        return;
    }

    // 🔥 Store data into AI buffer
    input_user_buffer[sample_index * AXIS_NUMBER + 0] = accelData.x;
    input_user_buffer[sample_index * AXIS_NUMBER + 1] = accelData.y;
    input_user_buffer[sample_index * AXIS_NUMBER + 2] = accelData.z;
    input_user_buffer[sample_index * AXIS_NUMBER + 3] = gyroData.x;
    input_user_buffer[sample_index * AXIS_NUMBER + 4] = gyroData.y;
    input_user_buffer[sample_index * AXIS_NUMBER + 5] = gyroData.z;

    // 🔍 Debugging: Print stored values
    printf(" Sample %d stored in AI buffer:\n", sample_index);
    printf("Accel  X: %d, Y: %d, Z: %d\n", accelData.x, accelData.y, accelData.z);
    printf("Gyro   X: %d, Y: %d, Z: %d\n", gyroData.x, gyroData.y, gyroData.z);

    sample_index++;

    // 🔥 When enough samples are collected, classify and reset buffer
    if (sample_index >= DATA_INPUT_USER) {
        printf("✅ Collected %d samples. Running AI classification...\n", DATA_INPUT_USER);

        // Print first few values in buffer before classification
        printf("🔎 First 6 AI input values: ");
        for (int i = 0; i < 6; i++) {
            printf("%.2f ", input_user_buffer[i]);
        }
        printf("\n");

        ClassifyIMUDataAndWriteToSD(); // Call AI classification
        sample_index = 0; // Reset index for next batch
    }

    // Delay based on sampling rate
    HAL_Delay(10);
}









void ProcessIMUData() {
    AccelerometerData accelData;
    GyroscopeData gyroData;
    uint8_t reg;

    while (1) {
        // ✅ Check if new data is ready
        HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x1E, I2C_MEMADD_SIZE_8BIT, &reg, 1, 100);

        if (reg & 0x03) {  // Bit 0 = Accel new data, Bit 1 = Gyro new data
            ReadIMUData(&accelData, &gyroData); // Read latest IMU data

            // ✅ Store values in the classification buffer
            neai_buffer[(AXIS_NUMBER * neai_buffer_ptr)] = accelData.x;
            neai_buffer[(AXIS_NUMBER * neai_buffer_ptr) + 1] = accelData.y;
            neai_buffer[(AXIS_NUMBER * neai_buffer_ptr) + 2] = accelData.z;
            neai_buffer[(AXIS_NUMBER * neai_buffer_ptr) + 3] = gyroData.x;
            neai_buffer[(AXIS_NUMBER * neai_buffer_ptr) + 4] = gyroData.y;
            neai_buffer[(AXIS_NUMBER * neai_buffer_ptr) + 5] = gyroData.z;

            neai_buffer_ptr++;
        }

        // ✅ Proceed to classification after filling the buffer
        if (neai_buffer_ptr >= DATA_INPUT_USER) {
            uint8_t id_class;
            float output_class_buffer[CLASS_NUMBER];

            // 🚀 Run classification
            if (neai_classification(neai_buffer, output_class_buffer, &id_class) == NEAI_OK) {
                printf("🔥 Classified as: %s\n", id2class[id_class]);
            } else {
                printf("❌ Classification error!\n");
            }

            // ✅ Reset buffer for the next batch
            neai_buffer_ptr = 0;
            memset(neai_buffer, 0, AXIS_NUMBER * DATA_INPUT_USER * sizeof(float));
        }
    }
}


