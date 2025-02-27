#include "Accelerometer.h"

extern I2C_HandleTypeDef hi2c1;

// Write a single register using DMA with error checking
HAL_StatusTypeDef LIS3DH_WriteRegister_DMA(uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};

    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit_DMA(&hi2c1, LIS3DH_ADDR << 1, data, 2);
    if (status != HAL_OK) {
        printf("Error: Failed to write register 0x%02X, status: %d\n", reg, status);
    }
    return status;
}

// Read a single register using DMA with error checking
HAL_StatusTypeDef LIS3DH_ReadRegister_DMA(uint8_t reg, uint8_t *value) {
    HAL_StatusTypeDef status;

    // Transmit register address
    status = HAL_I2C_Master_Transmit_DMA(&hi2c1, LIS3DH_ADDR << 1, &reg, 1);
    if (status != HAL_OK) {
        printf("Error: Failed to transmit register address 0x%02X, status: %d\n", reg, status);
        return status;
    }

    // Wait for transmission to complete
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

    // Receive data
    status = HAL_I2C_Master_Receive_DMA(&hi2c1, LIS3DH_ADDR << 1, value, 1);
    if (status != HAL_OK) {
        printf("Error: Failed to read register 0x%02X, status: %d\n", reg, status);
    }
    return status;
}

// Read multiple registers using DMA with error checking
HAL_StatusTypeDef LIS3DH_ReadMultiple_DMA(uint8_t reg, uint8_t *buffer, uint16_t size) {
    HAL_StatusTypeDef status;

    reg |= 0x80; // Set auto-increment for multiple reads

    // Transmit register address
    status = HAL_I2C_Master_Transmit_DMA(&hi2c1, LIS3DH_ADDR << 1, &reg, 1);
    if (status != HAL_OK) {
        printf("Error: Failed to transmit register address 0x%02X, status: %d\n", reg, status);
        return status;
    }

    // Wait for transmission to complete
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

    // Receive data
    status = HAL_I2C_Master_Receive_DMA(&hi2c1, LIS3DH_ADDR << 1, buffer, size);
    if (status != HAL_OK) {
        printf("Error: Failed to read multiple registers starting from 0x%02X, status: %d\n", reg, status);
    }
    return status;
}

// Initialize LIS3DH with error checking
void LIS3DH_Init(void) {
    if (LIS3DH_WriteRegister_DMA(0x20, 0x57) != HAL_OK) {
        printf("Error: Failed to initialize CTRL_REG1 (0x20)\n");
    } else {
        printf("Initialized CTRL_REG1 (0x20) successfully\n");
    }

    if (LIS3DH_WriteRegister_DMA(0x23, 0x08) != HAL_OK) { // Enable high-resolution mode
        printf("Error: Failed to initialize CTRL_REG4 (0x23)\n");
    } else {
        printf("Initialized CTRL_REG4 (0x23) successfully\n");
    }
}

// Read acceleration data with error checking
void LIS3DH_ReadAccel(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t buffer[6];
    if (LIS3DH_ReadMultiple_DMA(0x28, buffer, 6) == HAL_OK) {
        *x = (int16_t)(buffer[1] << 8 | buffer[0]);
        *y = (int16_t)(buffer[3] << 8 | buffer[2]);
        *z = (int16_t)(buffer[5] << 8 | buffer[4]);
        printf("Acceleration data - X: %d, Y: %d, Z: %d\n", *x, *y, *z);
    } else {
        printf("Error: Failed to read acceleration data\n");
    }
}
