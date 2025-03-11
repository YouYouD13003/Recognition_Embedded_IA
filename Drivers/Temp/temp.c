#include "temp.h"
#include <stdio.h>
#include <stdbool.h>
// Utility function for microsecond delay
void delay_us(uint32_t us) {
	uint32_t start_time = __HAL_TIM_GET_COUNTER(&htim2);
	uint32_t target_time = start_time + us;

	while (__HAL_TIM_GET_COUNTER(&htim2) < target_time)
		;
}

// Configure GPIO as Output
void set_gpio_output(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = TMP1826_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(TMP1826_PORT, &GPIO_InitStruct);
}

// Configure GPIO as Input
// Function to configure GPIO as Input
void set_gpio_input(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = TMP1826_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(TMP1826_PORT, &GPIO_InitStruct);
}

void delayus(uint32_t us) {
	volatile uint32_t counter = 8 * us;  // Adjust for your MCU clock speed
	while (counter--)
		;
}

// Initialize TMP1826
void TMP1826_Init(void) {
	set_gpio_output();
	HAL_GPIO_WritePin(TMP1826_PORT, TMP1826_PIN, GPIO_PIN_SET);
	printf("TMP1826 Initialized on PC10\n");
}

// Send a reset signal and check for presence response
uint8_t TMP1826_Reset(void) {
	//printf("TMP1826 Reset Start\n");

	set_gpio_output();
	HAL_GPIO_WritePin(TMP1826_PORT, TMP1826_PIN, GPIO_PIN_RESET);
//	printf("TMP1826 Pulled Low for Reset\n");

	delayus(480);  // Hold LOW for 480µs

	set_gpio_input();
	delayus(70);  // Short delay before checking presence

	uint8_t presence = HAL_GPIO_ReadPin(TMP1826_PORT, TMP1826_PIN);
//	printf("PC10 Read After Presence Pulse Wait: %d\n", presence);

	delayus(410);  // Complete reset window

	if (presence == 0) {
		//	printf("TMP1826 Detected (Presence Pulse Received) ✅\n");
	} else {
		printf("TMP1826 NOT Detected (Timing Issue?) ❌\n");
	}

	return (presence == 0) ? 1 : 0;
}

void TMP1826_WriteBit(uint8_t bit) {
	set_gpio_output();
	HAL_GPIO_WritePin(TMP1826_PORT, TMP1826_PIN, GPIO_PIN_RESET);

	if (bit) {
		delayus(6);  // Write '1' - Short low time
		set_gpio_input();  // Release bus early
		delayus(64);
	} else {
		delayus(60);  // Write '0' - Long low time
		set_gpio_input();
		delayus(10);
	}

	//printf("Write Bit: %d\n", bit);
}

// Read a single bit from the bus
uint8_t TMP1826_ReadBit(void) {
	uint8_t bit;

	set_gpio_output();
	HAL_GPIO_WritePin(TMP1826_PORT, TMP1826_PIN, GPIO_PIN_RESET);
	delay_us(2);  // tRL timing: Start read slot

	set_gpio_input(); // Release the bus
	delay_us(10);  // Allow sensor to drive the bus (tRDV = 15us max)

	bit = HAL_GPIO_ReadPin(TMP1826_PORT, TMP1826_PIN);
	delay_us(50);  // tSLOT timing: Ensure the full bit time is observed

	return bit;
}

// Write a byte (8 bits)
void TMP1826_WriteByte(uint8_t byte) {
	//printf("Writing Byte: 0x%02X\n", byte);

	for (uint8_t i = 0; i < 8; i++) {
		TMP1826_WriteBit(byte & 0x01);
		byte >>= 1;
	}
}

// Read a byte (8 bits)
uint8_t TMP1826_ReadByte(void) {
	uint8_t byte = 0;

	for (uint8_t i = 0; i < 8; i++) {
		byte >>= 1;  // Shift previous bits right
		if (TMP1826_ReadBit())
			byte |= 0x80;  // Set the MSB if the bit read was 1
	}

//	printf("Read Byte: 0x%02X\n", byte);
	return byte;
}

float TMP1826_ReadTemperature(void) {
	//   printf("🌡️ Starting TMP1826_ReadTemperature()\n");

	if (!TMP1826_Reset()) {
		printf("❌ TMP1826 not detected!\n");
		return -999.0f;
	}

	TMP1826_WriteByte(0xCC);  // Skip ROM
	TMP1826_WriteByte(0x44);  // Start Temperature Conversion
	//   printf("⏳ TMP1826 Conversion Command Sent\n");

	// ✅ **Improved: Increase polling delay & add timeout mechanism**
	set_gpio_input();
	int timeout = 1000;  // Avoid infinite loop
	while (HAL_GPIO_ReadPin(TMP1826_PORT, TMP1826_PIN) == GPIO_PIN_RESET
			&& timeout > 0) {
		delay_us(200);  // Increased from 100us → 200us
		timeout--;
	}

	if (timeout == 0) {
		printf("❌ TMP1826 Conversion Timeout!\n");
		return -999.0f;
	}

	//  printf("✅ TMP1826 Conversion Complete\n");

	if (!TMP1826_Reset()) {
		printf("❌ TMP1826 not responding after conversion!\n");
		return -999.0f;
	}

	TMP1826_WriteByte(0xCC);
	TMP1826_WriteByte(0xBE);  // Read Scratchpad
	//  printf("📖 TMP1826 Read Scratchpad Command Sent\n");

	// ✅ **Increase delay before reading Scratchpad**
	HAL_Delay(15);  // Increased from 5ms → 15ms

	uint8_t temp_LSB = TMP1826_ReadByte();

	// ✅ **Extra delay before reading MSB**
	HAL_Delay(2);

	uint8_t temp_MSB = TMP1826_ReadByte();

	HAL_Delay(2);
	uint8_t config1 = TMP1826_ReadByte();  // ✅ Read Configuration Register

	// Print Config Register
	//  printf("Config-1 Register: 0x%02X\n", config1);

	// Check if in 16-bit mode or 12-bit mode
	bool is_16bit_mode = (config1 & (1 << 2)) != 0;

	if (is_16bit_mode) {
		//     printf("✅ TMP1826 is in High-Precision Mode (16-bit)\n");
	} else {
		//       printf("✅ TMP1826 is in Legacy Mode (12-bit)\n");
	}

	//   printf("📖 TMP1826 Data Read: LSB = 0x%02X, MSB = 0x%02X\n", temp_LSB, temp_MSB);

	// ✅ **Improve retry mechanism with longer delays**
	int attempt = 0;
	while ((temp_LSB == 0xFF && temp_MSB == 0xFF) && attempt < 3) {
		printf("⚠️ TMP1826 Read Error (0xFFFF), Retrying %d...\n", attempt + 1);
		HAL_Delay(50);  // Increased retry delay from 10ms → 50ms
		temp_LSB = TMP1826_ReadByte();
		temp_MSB = TMP1826_ReadByte();
		attempt++;
	}

	if (temp_LSB == 0xFF && temp_MSB == 0xFF) {
		printf("❌ TMP1826 returned invalid data (0xFFFF) after %d attempts\n",
				attempt);
		return -999.0f;
	}

	int16_t temp_raw = (temp_MSB << 8) | temp_LSB;

	// ✅ **Handle negative temperatures correctly (Two’s Complement)**
	if (temp_raw & 0x8000) {
		temp_raw = -((~temp_raw + 1) & 0xFFFF);
	}

//    float temp_C = temp_raw / 16.0f;
	float temp_C;
	if (is_16bit_mode) {
		temp_C = temp_raw / 128.0f;  // ✅ High-Precision Mode
		//    printf("✅ Using High-Precision Mode (16-bit): %.2f°C\n", temp_C);
	} else {
		temp_C = temp_raw / 16.0f;   // ✅ Legacy Mode (12-bit)
		//  printf("✅ Using Legacy Mode (12-bit): %.2f°C\n", temp_C);
	}
	printf("✅ Temperature Raw: 0x%04X, Converted: %.2f°C\n", temp_raw, temp_C);

	return temp_C;
}

void ManageTempSensor(bool sensor_enabled, uint32_t Delay) {
	if (sensor_enabled) {
		// Wake up: Send a reset and conversion command
		if (!TMP1826_Reset()) {
			printf("TMP1826 not detected!\n");
			return;
		}

		// Wait for conversion (using polling or a delay)

		// Read the temperature
		float temp = TMP1826_ReadTemperature();
		printf("Temperature: %.2f°C\n", temp);

		HAL_Delay(Delay);
	} else {
		// Sensor disabled: Deinitialize or put sensor in high-impedance mode
		set_gpio_input();  // High impedance mode minimizes power consumption
		printf("TMP1826 is in low-power mode.\n");
	}

}
