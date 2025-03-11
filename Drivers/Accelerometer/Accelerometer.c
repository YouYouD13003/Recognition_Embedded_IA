#include "Accelerometer.h"
#include "string.h"



extern void WriteIMUDataToSD(AccelerometerData *accelData, GyroscopeData *gyroData);



//void InitializeISM330DHCX2(void) {
//    uint8_t config[2];
//    HAL_StatusTypeDef status;
//
//    // Step 1: Enable Register Auto-Increment & Block Data Update (CTRL3_C)
//    config[0] = 0x12; // CTRL3_C register
//    config[1] = 0x44; // 0b01000100: IF_INC = 1 (Auto-Increment), BDU = 1
//    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
//    if (status != HAL_OK) printf(" Error: CTRL3_C setup failed\n");
//
//    HAL_Delay(10);
//
//    // Step 2: Enable Accelerometer - 104Hz ODR, ±2g Full Scale, High-Performance Mode (CTRL1_XL)
//    config[0] = 0x10; // CTRL1_XL register
//    config[1] = 0x50; // 0b01010000: ODR = 104Hz, ±2g, High-Performance Mode
//    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
//    if (status != HAL_OK) printf(" Error: CTRL1_XL setup failed\n");
//
//    HAL_Delay(10);
//
//    // Step 3: Enable Gyroscope - 104Hz ODR, ±1000 dps Full Scale (CTRL2_G)
//    config[0] = 0x11; // CTRL2_G register
//    config[1] = 0x48; // 0b01001000: ODR = 104Hz, ±1000 dps
//    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
//    if (status != HAL_OK) printf(" Error: CTRL2_G setup failed\n");
//
//    HAL_Delay(10);
//
//    // Step 4: Enable High-Performance Mode for Accelerometer (CTRL6_C)
//    config[0] = 0x15; // CTRL6_C register
//    config[1] = 0x00; // 0b00000000: High-Performance Mode enabled for accelerometer
//    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
//    if (status != HAL_OK) printf(" Error: CTRL6_C setup failed\n");
//
//    HAL_Delay(10);
//
//    // Step 5: Enable High-Performance Mode for Gyroscope (CTRL7_G) ✅ FIXED
//    config[0] = 0x16; // CTRL7_G register
//    config[1] = 0x00; // 0b00000000: High-Performance Mode enabled for gyroscope
//    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
//    if (status != HAL_OK) printf(" Error: CTRL7_G setup failed\n");
//
//    HAL_Delay(10);
//
//    // Step 6: Read Back Register Values for Debugging
//    uint8_t ctrl1_xl, ctrl2_g, ctrl3_c, ctrl6_c, ctrl7_g;
//    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &ctrl1_xl, 1, 100);
//    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &ctrl2_g, 1, 100);
//    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x12, I2C_MEMADD_SIZE_8BIT, &ctrl3_c, 1, 100);
//    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x15, I2C_MEMADD_SIZE_8BIT, &ctrl6_c, 1, 100);
//    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x16, I2C_MEMADD_SIZE_8BIT, &ctrl7_g, 1, 100);
//
//    // Debug Print Statements
//    printf(" ISM330DHCX Initialization Complete!\n");
//    printf(" CTRL1_XL = 0x%02X (Should be 0x50 - High-Perf Accel)\n", ctrl1_xl);
//    printf(" CTRL2_G  = 0x%02X (Should be 0x48 - High-Perf Gyro)\n", ctrl2_g);
//    printf(" CTRL3_C  = 0x%02X (Should be 0x44 - Auto-Inc, BDU)\n", ctrl3_c);
//    printf(" CTRL6_C  = 0x%02X (Should be 0x00 - High-Perf Accel Confirmed)\n", ctrl6_c);
//    printf(" CTRL7_G  = 0x%02X (Should be 0x00 - High-Perf Gyro Confirmed)\n", ctrl7_g);
//}


//added low pass filter
void InitializeISM330DHCX2(void) {
    uint8_t config[2];
    uint8_t readback;
    HAL_StatusTypeDef status;

    printf("Initializing ISM330DHCX...\n");

    // Step 1: Enable Register Auto-Increment & Block Data Update (CTRL3_C)
    config[0] = 0x12;
    config[1] = 0x44; // IF_INC = 1, BDU = 1
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("Error: CTRL3_C setup failed\n");

    HAL_Delay(10);

    // Read back CTRL3_C to verify
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x12, I2C_MEMADD_SIZE_8BIT, &readback, 1, 100);
    printf("CTRL3_C Readback: 0x%02X (Expected: 0x44)\n", readback);

    // Step 2: Enable Accelerometer - 104Hz ODR, ±2g Full Scale, High-Performance Mode (CTRL1_XL)
    config[0] = 0x10;
    config[1] = 0x50;
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("Error: CTRL1_XL setup failed\n");

    HAL_Delay(10);

    // Read back CTRL1_XL
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &readback, 1, 100);
    printf("CTRL1_XL Readback: 0x%02X (Expected: 0x50)\n", readback);

    // Step 3: Enable Gyroscope - 104Hz ODR, ±1000 dps Full Scale (CTRL2_G)
    config[0] = 0x11;
    config[1] = 0x48;
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("Error: CTRL2_G setup failed\n");

    HAL_Delay(10);

    // Read back CTRL2_G
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &readback, 1, 100);
    printf("CTRL2_G Readback: 0x%02X (Expected: 0x48)\n", readback);

    // Step 4: Enable LPF2 for Accelerometer & Set Cutoff Frequency to ODR/20
    config[0] = 0x17;  // CTRL8_XL register
    config[1] = 0x82;  // LPF2_XL_EN = 1, HPCF_XL = 010 (ODR/20)
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("Error: CTRL8_XL setup failed\n");

    HAL_Delay(10);

    // Read back CTRL8_XL
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x17, I2C_MEMADD_SIZE_8BIT, &readback, 1, 100);
    printf("CTRL8_XL Readback: 0x%02X (Expected: 0x82)\n", readback);

    // Step 5: Enable LPF1 for Gyroscope (CTRL4_C)
    config[0] = 0x13;
    config[1] = 0x02; // LPF1_SEL_G = 1 (Enable LPF1)
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("Error: CTRL4_C setup failed\n");

    HAL_Delay(10);

    // Read back CTRL4_C
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x13, I2C_MEMADD_SIZE_8BIT, &readback, 1, 100);
    printf("CTRL4_C Readback: 0x%02X (Expected: 0x02)\n", readback);

    // Step 6: Set Gyroscope Cutoff Frequency to ODR/10 (CTRL6_C)
    config[0] = 0x15;
    config[1] = 0x02; // FTYPE = 10 (ODR/10)
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) printf("Error: CTRL6_C setup failed\n");

    HAL_Delay(10);

    // Read back CTRL6_C
    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x15, I2C_MEMADD_SIZE_8BIT, &readback, 1, 100);
    printf("CTRL6_C Readback: 0x%02X (Expected: 0x02)\n", readback);

    printf("ISM330DHCX Initialization Complete with LPF Enabled!\n");


}


void SleepISM330DHCX2(void) {
    uint8_t config[2];
    HAL_StatusTypeDef status;

    printf("Deinitializing ISM330DHCX...\n");

    // Disable Accelerometer by setting the ODR bits to 0 (CTRL1_XL)
    config[0] = 0x10; // Address of CTRL1_XL
    config[1] = 0x00; // Set ODR to 0 (power-down)
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) {
        printf("Error: Failed to disable accelerometer (CTRL1_XL)!\n");
    }
    HAL_Delay(10);

    // Disable Gyroscope by setting the ODR bits to 0 (CTRL2_G)
    config[0] = 0x11; // Address of CTRL2_G
    config[1] = 0x00; // Set ODR to 0 (power-down)
    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, 100);
    if (status != HAL_OK) {
        printf("Error: Failed to disable gyroscope (CTRL2_G)!\n");
    }
    HAL_Delay(10);

    // Optionally, you can add other deinitialization steps if needed

    printf("ISM330DHCX Deinitialized successfully.\n");
}

void WakeUpISM330DHCX2(void) {
    uint8_t config;
    HAL_StatusTypeDef status;

    // Re-enable Accelerometer: 104Hz ODR, ±2g, High-performance mode (CTRL1_XL)
    config = 0x50;  // Same value you used in full init
    status = HAL_I2C_Mem_Write(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &config, 1, 100);
    if (status != HAL_OK) {
        printf("Error: Failed to re-enable accelerometer!\n");
    }
    HAL_Delay(10);

    // Re-enable Gyroscope: 104Hz ODR, ±1000 dps (CTRL2_G)
    config = 0x48;  // Same value as in full init
    status = HAL_I2C_Mem_Write(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &config, 1, 100);
    if (status != HAL_OK) {
        printf("Error: Failed to re-enable gyroscope!\n");
    }
    HAL_Delay(10);

    printf("ISM330DHCX wake-up complete by updating ODR registers.\n");
}



// AI
//void ReadIMUData(AccelerometerData *accelData, GyroscopeData *gyroData) {
//    uint8_t accelDataRaw[6] = {0};
//    uint8_t gyroDataRaw[6] = {0};
//    HAL_StatusTypeDef status;
//
//    //  Read Gyroscope Data
//    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x22,
//                               I2C_MEMADD_SIZE_8BIT, gyroDataRaw, 6, 50);
//    if (status == HAL_OK) {
//        int16_t rawGyroX = (int16_t)((gyroDataRaw[0]) | (gyroDataRaw[1] << 8));
//        int16_t rawGyroY = (int16_t)((gyroDataRaw[2]) | (gyroDataRaw[3] << 8));
//        int16_t rawGyroZ = (int16_t)((gyroDataRaw[4]) | (gyroDataRaw[5] << 8));
//
//        float gyroSensitivity = 0.035f;
//        gyroData->x = rawGyroX * gyroSensitivity;
//        gyroData->y = rawGyroY * gyroSensitivity;
//        gyroData->z = rawGyroZ * gyroSensitivity;
//    } else {
//        printf(" Gyroscope Read Error!\n");
//    }
//
//    //  Read Accelerometer Data
//    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x28,
//                               I2C_MEMADD_SIZE_8BIT, accelDataRaw, 6, 50);
//    if (status == HAL_OK) {
//        int16_t rawAccelX = (int16_t)((accelDataRaw[0]) | (accelDataRaw[1] << 8));
//        int16_t rawAccelY = (int16_t)((accelDataRaw[2]) | (accelDataRaw[3] << 8));
//        int16_t rawAccelZ = (int16_t)((accelDataRaw[4]) | (accelDataRaw[5] << 8));
//
//        float accelSensitivity = 0.000061f;
//        accelData->x = rawAccelX * accelSensitivity;
//        accelData->y = rawAccelY * accelSensitivity;
//        accelData->z = rawAccelZ * accelSensitivity;
//    } else {
//        printf(" Accelerometer Read Error!\n");
//    }
//
//    //  Call AI Model with Converted Data
//    RunNanoEdgeAI(accelData, gyroData);
//}



////// latest

void ReadIMUData(AccelerometerData *accelData, GyroscopeData *gyroData) {
   uint8_t accelDataRaw[6] = {0};
   uint8_t gyroDataRaw[6] = {0};
   HAL_StatusTypeDef status;

   //  Read Gyroscope Data
   status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x22,
                              I2C_MEMADD_SIZE_8BIT, gyroDataRaw, 6, 50);
   if (status == HAL_OK) {
       //  Convert from little-endian format
       int16_t rawGyroX = (int16_t)((gyroDataRaw[0]) | (gyroDataRaw[1] << 8));
       int16_t rawGyroY = (int16_t)((gyroDataRaw[2]) | (gyroDataRaw[3] << 8));
       int16_t rawGyroZ = (int16_t)((gyroDataRaw[4]) | (gyroDataRaw[5] << 8));

       //  Convert to degrees per second (dps)
       float gyroSensitivity = 0.035f; // 35 mdps/LSB = 0.035 dps/LSB
       gyroData->rawX = rawGyroX;
       gyroData->rawY = rawGyroY;
       gyroData->rawZ = rawGyroZ;

       gyroData->x = rawGyroX * gyroSensitivity;
       gyroData->y = rawGyroY * gyroSensitivity;
       gyroData->z = rawGyroZ * gyroSensitivity;

       //  Debug Print - Gyroscope
//       printf("\n Gyroscope Data:");
       printf("\nRAW -> X: %d, Y: %d, Z: %d", rawGyroX, rawGyroY, rawGyroZ);
       printf("\nDPS -> X: %.6f, Y: %.6f, Z: %.6f\n", gyroData->x, gyroData->y, gyroData->z);
   } else {
       printf(" [HIGH PRIORITY] Error reading gyroscope data! Status: %d\n", status);
   }

   //  Read Accelerometer Data
   status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x28,
                              I2C_MEMADD_SIZE_8BIT, accelDataRaw, 6, 50);
   if (status == HAL_OK) {
       //  Convert from little-endian format
       int16_t rawAccelX = (int16_t)((accelDataRaw[0]) | (accelDataRaw[1] << 8));
       int16_t rawAccelY = (int16_t)((accelDataRaw[2]) | (accelDataRaw[3] << 8));
       int16_t rawAccelZ = (int16_t)((accelDataRaw[4]) | (accelDataRaw[5] << 8));

       //  Convert to g (acceleration)
       float accelSensitivity = 0.000061f; // 0.061 mg/LSB = 0.000061 g/LSB
       accelData->rawX = rawAccelX;
       accelData->rawY = rawAccelY;
       accelData->rawZ = rawAccelZ;

       accelData->x = rawAccelX * accelSensitivity;
       accelData->y = rawAccelY * accelSensitivity;
       accelData->z = rawAccelZ * accelSensitivity;

       // 📢 Debug Print - Accelerometer
//       printf("\nAccelerometer Data:");
       printf("\nRAW -> X: %d, Y: %d, Z: %d", rawAccelX, rawAccelY, rawAccelZ);
       printf("\nG  -> X: %.6f, Y: %.6f, Z: %.6f\n", accelData->x, accelData->y, accelData->z);
   } else {
       printf(" Error reading accelerometer data! Status: %d\n", status);
   }


  HAL_Delay(20);
   // ✅ Write converted data to SD
  // WriteIMUDataToSD(accelData, gyroData);
}

void ReadIMUData2(AccelerometerData *accelData, GyroscopeData *gyroData,uint32_t Delay) {
   uint8_t accelDataRaw[6] = {0};
   uint8_t gyroDataRaw[6] = {0};
   HAL_StatusTypeDef status;

   //  Read Gyroscope Data
   status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x22,
                              I2C_MEMADD_SIZE_8BIT, gyroDataRaw, 6, 50);
   if (status == HAL_OK) {
       //  Convert from little-endian format
       int16_t rawGyroX = (int16_t)((gyroDataRaw[0]) | (gyroDataRaw[1] << 8));
       int16_t rawGyroY = (int16_t)((gyroDataRaw[2]) | (gyroDataRaw[3] << 8));
       int16_t rawGyroZ = (int16_t)((gyroDataRaw[4]) | (gyroDataRaw[5] << 8));

       //  Convert to degrees per second (dps)
       float gyroSensitivity = 0.035f; // 35 mdps/LSB = 0.035 dps/LSB
       gyroData->rawX = rawGyroX;
       gyroData->rawY = rawGyroY;
       gyroData->rawZ = rawGyroZ;

       gyroData->x = rawGyroX * gyroSensitivity;
       gyroData->y = rawGyroY * gyroSensitivity;
       gyroData->z = rawGyroZ * gyroSensitivity;

       //  Debug Print - Gyroscope
//       printf("\n Gyroscope Data:");
       printf("\nRAW -> X: %d, Y: %d, Z: %d", rawGyroX, rawGyroY, rawGyroZ);
       printf("\nDPS -> X: %.6f, Y: %.6f, Z: %.6f\n", gyroData->x, gyroData->y, gyroData->z);
   } else {
       printf(" [HIGH PRIORITY] Error reading gyroscope data! Status: %d\n", status);
   }

   //  Read Accelerometer Data
   status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x28,
                              I2C_MEMADD_SIZE_8BIT, accelDataRaw, 6, 50);
   if (status == HAL_OK) {
       //  Convert from little-endian format
       int16_t rawAccelX = (int16_t)((accelDataRaw[0]) | (accelDataRaw[1] << 8));
       int16_t rawAccelY = (int16_t)((accelDataRaw[2]) | (accelDataRaw[3] << 8));
       int16_t rawAccelZ = (int16_t)((accelDataRaw[4]) | (accelDataRaw[5] << 8));

       //  Convert to g (acceleration)
       float accelSensitivity = 0.000061f; // 0.061 mg/LSB = 0.000061 g/LSB
       accelData->rawX = rawAccelX;
       accelData->rawY = rawAccelY;
       accelData->rawZ = rawAccelZ;

       accelData->x = rawAccelX * accelSensitivity;
       accelData->y = rawAccelY * accelSensitivity;
       accelData->z = rawAccelZ * accelSensitivity;

       // 📢 Debug Print - Accelerometer
//       printf("\nAccelerometer Data:");
       printf("\nRAW -> X: %d, Y: %d, Z: %d", rawAccelX, rawAccelY, rawAccelZ);
       printf("\nG  -> X: %.6f, Y: %.6f, Z: %.6f\n", accelData->x, accelData->y, accelData->z);
   } else {
       printf(" Error reading accelerometer data! Status: %d\n", status);
   }


   HAL_Delay(Delay);
   // ✅ Write converted data to SD
  // WriteIMUDataToSD(accelData, gyroData);
}








void ManageSensorReading(AccelerometerData *accelData, GyroscopeData *gyroData, uint32_t delay, bool sensor_enabled) {
    if (sensor_enabled) {
        // Initialize sensor if not already done


        	WakeUpISM330DHCX2();
            // Replace with your sensor init function, e.g., Sensor_Init();

            printf("Sensor initialized and ready to go.\n");

        // Read sensor data based on delay
            ReadIMUData2(accelData, gyroData, delay);
    }

    else {
        // When disabled, stop reading and deinitialize sensor if needed

        	SleepISM330DHCX2();
            // Replace with your sensor deinit function, e.g., Sensor_Deinit();

            printf("Sensor deinitialized to save power.\n");

        // Optionally, you can include a small delay or sleep to avoid busy looping.
       //
    }






}



