################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SD_CARD/SD_CARD.c 

OBJS += \
./Drivers/SD_CARD/SD_CARD.o 

C_DEPS += \
./Drivers/SD_CARD/SD_CARD.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SD_CARD/%.o Drivers/SD_CARD/%.su Drivers/SD_CARD/%.cyclo: ../Drivers/SD_CARD/%.c Drivers/SD_CARD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I"D:/STM32/EMBEDDED_AI_M2/Drivers/Accelerometer" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"D:/STM32/EMBEDDED_AI_M2/Drivers/Temp" -I"D:/STM32/EMBEDDED_AI_M2/Drivers" -I"D:/STM32/EMBEDDED_AI_M2/Debug" -I"D:/STM32/EMBEDDED_AI_M2/Core/Src" -I"D:/STM32/EMBEDDED_AI_M2/Drivers/SD_CARD" -I"D:/STM32/EMBEDDED_AI_M2/Core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SD_CARD

clean-Drivers-2f-SD_CARD:
	-$(RM) ./Drivers/SD_CARD/SD_CARD.cyclo ./Drivers/SD_CARD/SD_CARD.d ./Drivers/SD_CARD/SD_CARD.o ./Drivers/SD_CARD/SD_CARD.su

.PHONY: clean-Drivers-2f-SD_CARD

