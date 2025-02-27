/*
 * temp.c
 *
 *  Created on: Feb 27, 2025
 *      Author: Ayoub
 */

#include "temp.h"



void ONEWIRE_SetOutput(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = ONEWIRE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ONEWIRE_PORT, &GPIO_InitStruct);
}

void ONEWIRE_SetInput(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = ONEWIRE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ONEWIRE_PORT, &GPIO_InitStruct);
}

uint8_t ONEWIRE_Reset(void) {
    ONEWIRE_SetOutput();
    HAL_GPIO_WritePin(ONEWIRE_PORT, ONEWIRE_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);  // 480µs low

    ONEWIRE_SetInput();
    HAL_Delay(1);  // Wait for 60µs

    uint8_t presence = HAL_GPIO_ReadPin(ONEWIRE_PORT, ONEWIRE_PIN);
    HAL_Delay(1);  // Wait for 420µs

    if (presence == 0) {
        printf("TMP1826 detected!\n");
    } else {
        printf("TMP1826 NOT detected!\n");
    }
    return (presence == 0) ? 1 : 0;
}




void ONEWIRE_WriteBit(uint8_t bit) {
    ONEWIRE_SetOutput();
    HAL_GPIO_WritePin(ONEWIRE_PORT, ONEWIRE_PIN, GPIO_PIN_RESET);
    HAL_Delay(0);  // Hold for 1us

    if (bit) ONEWIRE_SetInput();  // Release if writing 1
    HAL_Delay(1);  // Wait for 60us
    ONEWIRE_SetInput();  // Release line
}


uint8_t ONEWIRE_ReadBit(void) {
    uint8_t bit = 0;
    ONEWIRE_SetOutput();
    HAL_GPIO_WritePin(ONEWIRE_PORT, ONEWIRE_PIN, GPIO_PIN_RESET);
    HAL_Delay(0);  // Hold for 1us
    ONEWIRE_SetInput();
    HAL_Delay(0);  // Allow slave to respond

    bit = HAL_GPIO_ReadPin(ONEWIRE_PORT, ONEWIRE_PIN);
    HAL_Delay(1);  // Wait for 60us
    return bit;
}


void ONEWIRE_WriteByte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        ONEWIRE_WriteBit(byte & 0x01);
        byte >>= 1;
    }
}


uint8_t ONEWIRE_ReadByte(void) {
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; i++) {
        byte |= (ONEWIRE_ReadBit() << i);
    }
    return byte;
}

void TMP1826_StartConversion(void) {
    ONEWIRE_Reset();
    ONEWIRE_WriteByte(0xCC);  // Skip ROM
    ONEWIRE_WriteByte(0x44);  // Convert Temperature
}

float TMP1826_ReadTemperature(void) {
    uint16_t raw_temp;
    float temperature;

    ONEWIRE_Reset();
    ONEWIRE_WriteByte(0xCC);  // Skip ROM
    ONEWIRE_WriteByte(0xBE);  // Read Scratchpad

    uint8_t LSB = ONEWIRE_ReadByte();
    uint8_t MSB = ONEWIRE_ReadByte();

    raw_temp = ((uint16_t)MSB << 8) | LSB;

    printf("Raw Temperature Data: 0x%04X\n", raw_temp);

    if (raw_temp == 0xFFFF || raw_temp == 0x0000) {
        printf("ERROR: Invalid temperature reading!\n");
        return -999.99; // Return an error value
    }

    temperature = raw_temp * 0.0078125;  // Convert 16-bit value to Celsius
    return temperature;
}



