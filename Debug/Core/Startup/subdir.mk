################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32wb55rgvx.s 

OBJS += \
./Core/Startup/startup_stm32wb55rgvx.o 

S_DEPS += \
./Core/Startup/startup_stm32wb55rgvx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/STM32/EMBEDDED_AI_M2/Drivers/Accelerometer" -I"D:/STM32/EMBEDDED_AI_M2/FATFS/Target" -I"D:/STM32/EMBEDDED_AI_M2/Drivers/Temp" -I"D:/STM32/EMBEDDED_AI_M2/Drivers" -I"D:/STM32/EMBEDDED_AI_M2/Debug" -I"D:/STM32/EMBEDDED_AI_M2/Core/Inc" -I"D:/STM32/EMBEDDED_AI_M2/Core/Src" -I"D:/STM32/EMBEDDED_AI_M2/Drivers/SD_CARD" -I"D:/STM32/EMBEDDED_AI_M2/Core" -I"D:/STM32/EMBEDDED_AI_M2/Drivers/AI" -I"D:/STM32/EMBEDDED_AI_M2/Drivers/Json" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32wb55rgvx.d ./Core/Startup/startup_stm32wb55rgvx.o

.PHONY: clean-Core-2f-Startup

