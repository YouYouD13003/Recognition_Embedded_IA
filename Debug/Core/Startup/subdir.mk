################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
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
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/Accelerometer" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/FATFS/Target" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/Temp" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Debug" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Core/Inc" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Core/Src" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/SD_CARD" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Core" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/AI" -I"C:/Users/jade.mouillot/STM32CubeIDE/test/Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded/Recognition_Embedded_IA-dev_Ayoub_cleaning/Drivers/Json" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32wb55rgvx.d ./Core/Startup/startup_stm32wb55rgvx.o

.PHONY: clean-Core-2f-Startup

