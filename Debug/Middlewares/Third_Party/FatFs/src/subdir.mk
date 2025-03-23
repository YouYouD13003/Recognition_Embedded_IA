################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FatFs/src/diskio.c \
../Middlewares/Third_Party/FatFs/src/ff.c \
../Middlewares/Third_Party/FatFs/src/ff_gen_drv.c 

OBJS += \
./Middlewares/Third_Party/FatFs/src/diskio.o \
./Middlewares/Third_Party/FatFs/src/ff.o \
./Middlewares/Third_Party/FatFs/src/ff_gen_drv.o 

C_DEPS += \
./Middlewares/Third_Party/FatFs/src/diskio.d \
./Middlewares/Third_Party/FatFs/src/ff.d \
./Middlewares/Third_Party/FatFs/src/ff_gen_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FatFs/src/%.o Middlewares/Third_Party/FatFs/src/%.su Middlewares/Third_Party/FatFs/src/%.cyclo: ../Middlewares/Third_Party/FatFs/src/%.c Middlewares/Third_Party/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/Accelerometer" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/Temp" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Debug" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Core/Src" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/SD_CARD" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Core" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/AI" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/Json" -I../STM32_WPAN/App -I../Utilities/lpm/tiny_lpm -I../Middlewares/ST/STM32_WPAN -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../Middlewares/ST/STM32_WPAN/utilities -I../Middlewares/ST/STM32_WPAN/ble/core -I../Middlewares/ST/STM32_WPAN/ble/core/auto -I../Middlewares/ST/STM32_WPAN/ble/core/template -I../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../Utilities/sequencer -I../Middlewares/ST/STM32_WPAN/ble -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FatFs-2f-src

clean-Middlewares-2f-Third_Party-2f-FatFs-2f-src:
	-$(RM) ./Middlewares/Third_Party/FatFs/src/diskio.cyclo ./Middlewares/Third_Party/FatFs/src/diskio.d ./Middlewares/Third_Party/FatFs/src/diskio.o ./Middlewares/Third_Party/FatFs/src/diskio.su ./Middlewares/Third_Party/FatFs/src/ff.cyclo ./Middlewares/Third_Party/FatFs/src/ff.d ./Middlewares/Third_Party/FatFs/src/ff.o ./Middlewares/Third_Party/FatFs/src/ff.su ./Middlewares/Third_Party/FatFs/src/ff_gen_drv.cyclo ./Middlewares/Third_Party/FatFs/src/ff_gen_drv.d ./Middlewares/Third_Party/FatFs/src/ff_gen_drv.o ./Middlewares/Third_Party/FatFs/src/ff_gen_drv.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FatFs-2f-src

