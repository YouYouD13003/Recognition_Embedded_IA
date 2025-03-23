################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/Accelerometer" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/Temp" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Debug" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Core/Src" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/SD_CARD" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Core" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/AI" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/Json" -I../STM32_WPAN/App -I../Utilities/lpm/tiny_lpm -I../Middlewares/ST/STM32_WPAN -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../Middlewares/ST/STM32_WPAN/utilities -I../Middlewares/ST/STM32_WPAN/ble/core -I../Middlewares/ST/STM32_WPAN/ble/core/auto -I../Middlewares/ST/STM32_WPAN/ble/core/template -I../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../Utilities/sequencer -I../Middlewares/ST/STM32_WPAN/ble -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SD_CARD

clean-Drivers-2f-SD_CARD:
	-$(RM) ./Drivers/SD_CARD/SD_CARD.cyclo ./Drivers/SD_CARD/SD_CARD.d ./Drivers/SD_CARD/SD_CARD.o ./Drivers/SD_CARD/SD_CARD.su

.PHONY: clean-Drivers-2f-SD_CARD

