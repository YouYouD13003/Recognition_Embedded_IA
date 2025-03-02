################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Accelerometer/Accelerometer.c 

OBJS += \
./Drivers/Accelerometer/Accelerometer.o 

C_DEPS += \
./Drivers/Accelerometer/Accelerometer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Accelerometer/%.o Drivers/Accelerometer/%.su Drivers/Accelerometer/%.cyclo: ../Drivers/Accelerometer/%.c Drivers/Accelerometer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I"D:/STM32/EMBEDDED_AI_M2/Drivers/Accelerometer" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"D:/STM32/EMBEDDED_AI_M2/Drivers/Temp" -I"D:/STM32/EMBEDDED_AI_M2/Drivers" -I"D:/STM32/EMBEDDED_AI_M2/Debug" -I"D:/STM32/EMBEDDED_AI_M2/Core/Src" -I"D:/STM32/EMBEDDED_AI_M2/Drivers/SD_CARD" -I"D:/STM32/EMBEDDED_AI_M2/Core" -I"D:/STM32/EMBEDDED_AI_M2/Drivers/AI" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Accelerometer

clean-Drivers-2f-Accelerometer:
	-$(RM) ./Drivers/Accelerometer/Accelerometer.cyclo ./Drivers/Accelerometer/Accelerometer.d ./Drivers/Accelerometer/Accelerometer.o ./Drivers/Accelerometer/Accelerometer.su

.PHONY: clean-Drivers-2f-Accelerometer

