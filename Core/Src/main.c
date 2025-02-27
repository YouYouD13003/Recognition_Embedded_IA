/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Accelerometer.h"
#include "NanoEdgeAI.h"
#include "knowledge.h"
#include "temp.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define LIS3DH_I2C_ADDRESS (0x19 << 1) // Shift the 7-bit address left by 1 bit : 0x19 SA0 OUTPUT AT '1'
//#define ISM330DHCX_I2C_ADDRESS (0x6B << 1)  // 0xD6 for Write, 0xD7 for Read
//
//#define MAX_LINES 200  // Limit file to 200 lines
//
//#define WHO_AM_I_REGISTER 0x0F
//#define OUT_X_L_REGISTER (0x28 | 0x80)  // Set MSB to enable auto-increment
//#define START_DELAY 30000
//#define CTRL_REG2 0x21
//#define CTRL_REG5 0x24
//#define CTRL_REG1 0x20
//#define CTRL_REG4 0x23
//#define CTRL_REG3 0x22
//#define OUT_X_L_G 0x22  // First register of gyroscope data
//#define FIFO_CTRL_REG   0x2E
//
//#define OUTX_L_G  0x22
//
//
//

#define READ_DURATION 180000 // 3 minutes = 180000 ms (3 * 60 * 1000)

//
//
//#define OUTX_L_A 28h
//
//#define SAMPLE_WINDOW   256  // Peut être 256, 512 ou 1024
//
////#define SAMPLE_WINDOW 16  // Minimum required for NanoEdge AI
////
//#define BUFFER_SIZE 4096  // Minimum 16, Maximum 4096
//// 50-100 lignes
//// 10-20 ms
//int imuIndex = 0;        // Track current position in buffer
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef hlpuart1;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
//typedef struct
//{
//    int16_t x;
//    int16_t y;
//    int16_t z;
//} AccelerometerData;
//
//
//typedef struct {
//    int16_t x;
//    int16_t y;
//    int16_t z;
//} GyroscopeData;
//
//typedef struct {
//    int16_t ax, ay, az;
//    int16_t gx, gy, gz;
//} IMU_Data;
//
//IMU_Data imuBuffer[BUFFER_SIZE];  // Buffer to store readings
//uint8_t who_am_i = 0;
//FATFS FatFs;   // File system object
//FIL fil;       // File object
//FRESULT res;   // Result code
//UINT bw;       // Bytes written
//UINT br;       // Bytes read
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
int _write(int file, char *ptr, int len);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len) {
	int DataIdx;
	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		//__io_putchar(*ptr++);
		ITM_SendChar(*ptr++);
	}
	return len;
}

float input_user_buffer[DATA_INPUT_USER * AXIS_NUMBER];

//
//
//
//void UART_HelloWorld(void) {
//    const char *msg = "HelloWorld!\r\n";  // Message to send
//    HAL_UART_Transmit(&hlpuart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
//}
//
//void InitializeISM330DHCX2(void) {
//	uint8_t config[2];
//	HAL_StatusTypeDef status;
//
//	// Step 1: Enable Register Auto-Increment & BDU (CTRL3_C)
//	config[0] = 0x12; // CTRL3_C register
//	config[1] = 0x44; // 0b01000100: IF_INC = 1 (Auto-Increment), BDU = 1
//	status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2,
//			100);
//	if (status != HAL_OK)
//		printf("Error: CTRL3_C setup failed\n");
//
//	HAL_Delay(10);
//
//	// Step 2: Enable Accelerometer (CTRL1_XL) - 104Hz ODR, ±2g Full Scale, High-Performance Mode
//	config[0] = 0x10; // CTRL1_XL register
//	config[1] = 0x50; // 0b01010000: ODR = 104Hz, ±2g, High-Performance Mode
//	status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2,
//			100);
//	if (status != HAL_OK)
//		printf("Error: CTRL1_XL setup failed\n");
//
//	HAL_Delay(10);
//
//	// Step 3: Enable Gyroscope (CTRL2_G) - 104Hz ODR, ±1000 dps Full Scale
//	config[0] = 0x11; // CTRL2_G register
//	config[1] = 0x48; // 0b01001000: ODR = 104Hz, ±1000 dps
//	status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2,
//			100);
//	if (status != HAL_OK)
//		printf("Error: CTRL2_G setup failed\n");
//
//	HAL_Delay(10);
//
//	// Step 4: Enable High-Performance Mode for Accelerometer & Gyroscope (CTRL6_C)
//	config[0] = 0x15; // CTRL6_C register
//	config[1] = 0x00; // 0b00000000: High-Performance Mode enabled
//	status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2,
//			100);
//	if (status != HAL_OK)
//		printf("Error: CTRL6_C setup failed\n");
//
//	HAL_Delay(10);
//
//	// Step 5: Read Back Register Values for Debugging
//	uint8_t ctrl1_xl, ctrl2_g, ctrl3_c, ctrl6_c;
//	HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT,
//			&ctrl1_xl, 1, 100);
//	HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT,
//			&ctrl2_g, 1, 100);
//	HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x12, I2C_MEMADD_SIZE_8BIT,
//			&ctrl3_c, 1, 100);
//	HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x15, I2C_MEMADD_SIZE_8BIT,
//			&ctrl6_c, 1, 100);
//
//	printf("CTRL1_XL = 0x%02X (Should be 0x50)\n", ctrl1_xl);
//	printf("CTRL2_G  = 0x%02X (Should be 0x48)\n", ctrl2_g);
//	printf("CTRL3_C  = 0x%02X (Should be 0x44)\n", ctrl3_c);
//	printf("CTRL6_C  = 0x%02X (Should be 0x00)\n", ctrl6_c);
//
//	printf("ISM330DHCX initialization complete\n");
//}
//
//void InitializeISM330DHCX(void)
//{
//    uint8_t config[2];
//    HAL_StatusTypeDef status;
//
//    // **Enable Register Auto-Increment & BDU (CTRL3_C)**
//    config[0] = 0x12; // CTRL3_C register
//    config[1] = 0x44; // 0b01000100: IF_INC = 1 (Auto-Increment enabled), BDU = 1 (Block Data Update)
//    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, HAL_MAX_DELAY);
//    if (status != HAL_OK) printf("Failed to configure CTRL3_C (Auto-Increment & BDU), Status: %u\n", status);
//
//    // **Configure Gyroscope (CTRL2_G) - 104Hz ODR, ±1000 dps Full Scale**
//    config[0] = 0x11; // CTRL2_G register
//    config[1] = 0x48; // 0b01001000: ODR = 104Hz, FS = ±1000 dps
//    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, HAL_MAX_DELAY);
//    if (status != HAL_OK) printf("Failed to configure CTRL2_G, Status: %u\n", status);
//
//    // **Enable High-Performance Mode (CTRL7_G)**
//    config[0] = 0x16; // CTRL7_G register
//    config[1] = 0x40; // 0b01000000: High-Performance Mode enabled, HPF enabled
//    status = HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_I2C_ADDRESS, config, 2, HAL_MAX_DELAY);
//    if (status != HAL_OK) printf("Failed to configure CTRL7_G, Status: %u\n", status);
//}
//
//
//
//void WriteIMUDataToSD(AccelerometerData *accelData, GyroscopeData *gyroData) {
//    static int sample_count = 0;  // Counter for collected samples
//    static char buffer[50000];    // Increased buffer size
//    static int offset = 0;        // Offset for buffer writing
//
//    // 🔥 Print current IMU data before writing
////    printf("📌 Sample %d -> ax=%d, ay=%d, az=%d, gx=%d, gy=%d, gz=%d\n",
////           sample_count, accelData->x, accelData->y, accelData->z,
////           gyroData->x, gyroData->y, gyroData->z);
//
//    // 🔥 Check if buffer has enough space before writing
//    if (offset + 50 >= sizeof(buffer)) {
//        printf("�?� Buffer overflow prevented! Flushing data early.\n");
//        sample_count = SAMPLE_WINDOW;  // Force writing to SD
//    }
//
//    // 🔥 Append new IMU sample to buffer
//    int bytes_written = snprintf(buffer + offset, sizeof(buffer) - offset, "%d,%d,%d,%d,%d,%d,",
//                                 accelData->x, accelData->y, accelData->z,
//                                 gyroData->x, gyroData->y, gyroData->z);
//    if (bytes_written < 0) {
//        printf("�?� Error formatting IMU data!\n");
//        return;
//    }
//    offset += bytes_written;
//    sample_count++;
//
//    // 🔥 Once we have `SAMPLE_WINDOW` samples, write to SD card
//    if (sample_count >= SAMPLE_WINDOW) {
//        buffer[offset - 1] = '\n';  // Replace last comma with newline
//
//        // 🔥 Print the full formatted buffer before writing
//    //    printf("\n�? Full formatted buffer before writing to SD:\n%s\n", buffer);
//
//        // 🔥 Retry SD Card Mounting up to 3 times
//        int retries = 3;
//        while (retries-- > 0) {
//            if (f_mount(&FatFs, "", 1) == FR_OK) {
//      //          printf("✅ SD card mounted successfully.\n");
//                break;
//            }
//            printf("�?� Retry mounting SD card... (%d attempts left)\n", retries);
//        }
//        if (retries == 0) {
//            printf("�?� Failed to mount SD card! Skipping write.\n");
//            return;
//        }
//
//        // 🔥 Open file and check for errors
//        res = f_open(&fil, "checkin.csv", FA_OPEN_ALWAYS | FA_WRITE);
//        if (res != FR_OK) {
//            printf("�?� Error opening file! FATFS result: %d\n", res);
//            f_mount(0, "", 0);
//            return;
//        }
//
//        // 🔥 Move to end of file
//        f_lseek(&fil, f_size(&fil));
//
//        // 🔥 Write data and check for errors
//        UINT bytesWritten;
//        res = f_write(&fil, buffer, strlen(buffer), &bytesWritten);
//        if (res != FR_OK || bytesWritten == 0) {
//            printf("�?� Error writing to file! FATFS result: %d\n", res);
//        } else {
//         //   printf("✅ Successfully wrote %d bytes to SD card.\n", bytesWritten);
//        }
//
//        // 🔥 Ensure data is written immediately
//        f_sync(&fil);
//        f_close(&fil);
//        f_mount(0, "", 0);
//      //  printf("✅ SD card unmounted.\n");
//
//        // Reset buffer for next batch
//        offset = 0;
//        sample_count = 0;
//    }
//}
//
//
//
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
//        gyroData.x = (int16_t)((gyroDataRaw[1] << 8) | gyroDataRaw[0]);
//        gyroData.y = (int16_t)((gyroDataRaw[3] << 8) | gyroDataRaw[2]);
//        gyroData.z = (int16_t)((gyroDataRaw[5] << 8) | gyroDataRaw[4]);
//    } else {
//        printf("�?� Error reading gyroscope data! Status: %d\n", status);
//    }
//
//    // Read Accelerometer Data
//    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x28, I2C_MEMADD_SIZE_8BIT, accelDataRaw, 6, 100);
//    if (status == HAL_OK) {
//        accelData.x = (int16_t)((accelDataRaw[1] << 8) | accelDataRaw[0]);
//        accelData.y = (int16_t)((accelDataRaw[3] << 8) | accelDataRaw[2]);
//        accelData.z = (int16_t)((accelDataRaw[5] << 8) | accelDataRaw[4]);
//    } else {
//        printf("�?� Error reading accelerometer data! Status: %d\n", status);
//    }
//
//    // 🔥 Write data to SD card immediately after reading
//    WriteIMUDataToSD(&accelData, &gyroData);
//
//    // Delay for next reading
//    HAL_Delay(10); // Adjust based on your sampling rate
//}
//
//
//
//
//




//
//void ReadIMUDataForAI() {
//    AccelerometerData accelData;
//    GyroscopeData gyroData;
//    uint8_t accelDataRaw[6] = {0};
//    uint8_t gyroDataRaw[6] = {0};
//    HAL_StatusTypeDef status;
//
//    // Read Gyroscope Data
//    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x22, I2C_MEMADD_SIZE_8BIT, gyroDataRaw, 6, 100);
//    if (status == HAL_OK) {
//        gyroData.x = (int16_t)((gyroDataRaw[1] << 8) | gyroDataRaw[0]);
//        gyroData.y = (int16_t)((gyroDataRaw[3] << 8) | gyroDataRaw[2]);
//        gyroData.z = (int16_t)((gyroDataRaw[5] << 8) | gyroDataRaw[4]);
//    }
//
//    // Read Accelerometer Data
//    status = HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x28, I2C_MEMADD_SIZE_8BIT, accelDataRaw, 6, 100);
//    if (status == HAL_OK) {
//        accelData.x = (int16_t)((accelDataRaw[1] << 8) | accelDataRaw[0]);
//        accelData.y = (int16_t)((accelDataRaw[3] << 8) | accelDataRaw[2]);
//        accelData.z = (int16_t)((accelDataRaw[5] << 8) | accelDataRaw[4]);
//    }
//
//    // Store in buffer
//    input_user_buffer[sampleIndex * AXIS_NUMBER + 0] = accelData.x;
//    input_user_buffer[sampleIndex * AXIS_NUMBER + 1] = accelData.y;
//    input_user_buffer[sampleIndex * AXIS_NUMBER + 2] = accelData.z;
//    input_user_buffer[sampleIndex * AXIS_NUMBER + 3] = gyroData.x;
//    input_user_buffer[sampleIndex * AXIS_NUMBER + 4] = gyroData.y;
//    input_user_buffer[sampleIndex * AXIS_NUMBER + 5] = gyroData.z;
//
//    sampleIndex++;
//
//    // Check if buffer is full
//    if (sampleIndex >= SAMPLE_WINDOW) {
//        ClassifyIMUDataAndWriteToSD();  // 🔥 Run AI and write results to SD
//        sampleIndex = 0;  // Reset index
//    }
//}
//
//
//
//
//void WriteToSDCard(const char *filename, const char *data) {
//    // 🔥 Step 1: Mount SD Card
//    f_mount(0, "", 0);
//    if (f_mount(&FatFs, "", 1) != FR_OK) {
//        return;  // Mount failed, exit function
//    }
//
//    // 🔥 Step 2: Open CSV file in append mode
//    if (f_open(&fil, filename, FA_OPEN_ALWAYS | FA_WRITE) == FR_OK) {
//        f_lseek(&fil, f_size(&fil));  // Move to end of file
//        UINT bytesWritten;
//        f_write(&fil, data, strlen(data), &bytesWritten);
//        f_close(&fil);
//    }
//
//    // 🔥 Step 3: Unmount SD Card
//    f_mount(0, "", 0);
//}
//
//



//

//


//void WaitForStart() {
//    static uint32_t startTime = 0;
//    static uint8_t readyToStart = 0;
//    static uint8_t readingIMU = 0;
//    static int lastPrintedSecond = -1;  // Track last printed second
//
//    if (!readyToStart) {
//        if (startTime == 0) {
//            startTime = HAL_GetTick();  // Capture start time
//            printf("�?� Waiting 30 seconds before starting IMU acquisition...\n");
//        }
//
//        // Calculate elapsed time
//        uint32_t elapsedTime = HAL_GetTick() - startTime;
//        int elapsedSeconds = elapsedTime / 1000;  // Convert to seconds
//
//        // Print countdown every second
//        if (elapsedSeconds != lastPrintedSecond) {
//            printf("�?� Time not elapsed yet: %d / 30 sec\n", elapsedSeconds);
//            lastPrintedSecond = elapsedSeconds;
//        }
//
//        // Check if 30 seconds have passed
//        if (elapsedTime >= START_DELAY) {
//            readyToStart = 1;
//            readingIMU = 1;
//            startTime = HAL_GetTick();  // Reset timer for 3-minute countdown
//            printf("✅ 30 seconds elapsed! Starting 3-minute IMU acquisition...\n");
//        }
//    }
//
//    // If 3-minute window is active, collect data
//    if (readyToStart && readingIMU) {
//        // Collect IMU data
//      //  ClassifyIMUDataAndWriteToSD();
//       // ReadIMUDataForAI();
//    	 ReadIMUData();
//        // Check if 3 minutes have passed
//        if (HAL_GetTick() - startTime >= READ_DURATION) {
//            readingIMU = 0;  // Stop data collection
//            printf("✅ 3-minute IMU acquisition complete. Stopping data collection.\n");
//        }
//    }
//}

//


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

	HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_LPUART1_UART_Init();
  MX_SPI1_Init();
  if (MX_FATFS_Init() != APP_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN 2 */

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
//
//  HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c1, LIS3DH_I2C_ADDRESS, 3, 100);
//
//    if (status == HAL_OK)
//    {
//        // Device is ready
//        printf("LIS3DH is ready for communication.\n");
//    }
//    else
//    {
//        // Device not ready or communication failed
//        printf("LIS3DH is not ready. HAL_StatusTypeDef: %d\n", status);
//    }




  HAL_StatusTypeDef  status = HAL_I2C_IsDeviceReady(&hi2c1, ISM330DHCX_I2C_ADDRESS, 3, 100);

	    if (status == HAL_OK)
	    {
	        // Device is ready
	        printf("Gyro is ready for communication.\n");
	    }
	    else
	    {
	        // Device not ready or communication failed
	        printf("Gyro is not ready. HAL_StatusTypeDef: %d\n", status);
	    }
//
//
//
//
//
    InitializeISM330DHCX2();
//    AccelerometerData data;
//    GyroscopeData data_g;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

//
//    HAL_I2C_Mem_Read(&hi2c1, LIS3DH_I2C_ADDRESS, 0x0F, I2C_MEMADD_SIZE_8BIT, &who_am_i, 1, 100);
//    HAL_Delay(500);
//    printf(" LIS3DH WHO_AM_I: 0x%02X\n", who_am_i); // should get  0x33
//
//    HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_I2C_ADDRESS, 0x0F, I2C_MEMADD_SIZE_8BIT, &who_am_i, 1, 100);
//    HAL_Delay(500);
//    printf("ISM330DHCX WHO_AM_I: 0x%02X\n", who_am_i); // should get  0x6B

  //  InitializeAI();
    AccelerometerData accel;
    GyroscopeData gyro;
  while (1)
  {
    /* USER CODE END WHILE */



    /* USER CODE BEGIN 3 */


	// ReadIMUData(&data,&data_g);
	  ReadIMUData(&accel,&gyro);
	// HAL_Delay(500);
	//  WriteIMUDataToSD();





//	   TMP1826_StartConversion();
//	        HAL_Delay(750);  // Wait for conversion
//	        float temp = TMP1826_ReadTemperature();
//	        printf("Temperature: %.2f°C\n", temp);
//	        HAL_Delay(1000);
	//  ReadIMUData();




	// WaitForStart();
	// ClassifyIMUDataAndWriteToSD();

	 // HAL_Delay(10);

	  //  ReadIMUDataForAI();


	  //    imuIndex = 0;  // Reset buffer index



	  //ReadAccelerometerData(&data);
	// ReadGyroscopeData(&data_g);
	 // HAL_Delay(500);
//	  Test_I2C_Communication();

//	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, SET);
//
//	  HAL_Delay(500);
//
//
//	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11, RESET);
//
//	  HAL_Delay(500);

//	  // Read a single register using DMA
//	  if (LIS3DH_ReadRegister_DMA(0x28, buffer) == HAL_OK) {
//	      printf("Single register read from OUT_X_L (0x28) successful: Data = 0x%02X\n", buffer[0]);
//	  } else {
//	      printf("Single register read from OUT_X_L (0x28) failed!\n");
//	  }
//
//	  // Read multiple registers using DMA  // print  words ..
//	  if (LIS3DH_ReadMultiple_DMA(0x28, buffer, 6) == HAL_OK) {
//	      printf("Multiple register read starting from OUT_X_L (0x28) successful:\n");
//	      printf("X_L: 0x%02X, X_H: 0x%02X, Y_L: 0x%02X, Y_H: 0x%02X, Z_L: 0x%02X, Z_H: 0x%02X\n",
//	             buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
//	  } else {
//	      printf("Multiple register read starting from OUT_X_L (0x28) failed!\n");
//	  }
//
//
//	   LIS3DH_ReadAccel(&x,&y,&z);// print real data

	//  UART_HelloWorld();

	  //HAL_Delay(100);


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_10;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4|RCC_CLOCKTYPE_HCLK2
                              |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSI;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN Smps */

  /* USER CODE END Smps */
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00B07CB4;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SD_CS_Pin|SA0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(temp_io_GPIO_Port, temp_io_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SD_CS_Pin SA0_Pin */
  GPIO_InitStruct.Pin = SD_CS_Pin|SA0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : temp_io_Pin */
  GPIO_InitStruct.Pin = temp_io_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(temp_io_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        // Transmission complete
        printf("I2C Transmit Complete\n");
    }
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        // Reception complete
        printf("I2C Receive Complete\n");
    }
}





/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
