################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/sequencer/subdir.mk
-include Utilities/lpm/tiny_lpm/subdir.mk
-include STM32_WPAN/Target/subdir.mk
-include STM32_WPAN/App/subdir.mk
-include Middlewares/Third_Party/FatFs/src/option/subdir.mk
-include Middlewares/Third_Party/FatFs/src/subdir.mk
-include Middlewares/ST/STM32_WPAN/utilities/subdir.mk
-include Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/subdir.mk
-include Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci/subdir.mk
-include Middlewares/ST/STM32_WPAN/ble/svc/Src/subdir.mk
-include Middlewares/ST/STM32_WPAN/ble/core/template/subdir.mk
-include Middlewares/ST/STM32_WPAN/ble/core/auto/subdir.mk
-include FATFS/Target/subdir.mk
-include FATFS/App/subdir.mk
-include Drivers/Temp/subdir.mk
-include Drivers/STM32WBxx_HAL_Driver/Src/subdir.mk
-include Drivers/SD_CARD/subdir.mk
-include Drivers/Json/subdir.mk
-include Drivers/Accelerometer/subdir.mk
-include Drivers/AI/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := EMBEDDED_AI_M2
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
EMBEDDED_AI_M2.elf \

MAP_FILES += \
EMBEDDED_AI_M2.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
EMBEDDED_AI_M2.list \


# All Target
all: main-build

# Main-build Target
main-build: EMBEDDED_AI_M2.elf secondary-outputs

# Tool invocations
EMBEDDED_AI_M2.elf EMBEDDED_AI_M2.map: $(OBJS) $(USER_OBJS) C:\Users\jade.mouillot\STM32CubeIDE\test\Recognition_Embedded_IA-dev_Ayoub_cleaning\ (7).zip_expanded\Recognition_Embedded_IA-dev_Ayoub_cleaning\STM32WB55RGVX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "EMBEDDED_AI_M2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\jade.mouillot\STM32CubeIDE\test\Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded\Recognition_Embedded_IA-dev_Ayoub_cleaning\STM32WB55RGVX_FLASH.ld" --specs=nosys.specs -Wl,-Map="EMBEDDED_AI_M2.map" -Wl,--gc-sections -static -L"C:\Users\jade.mouillot\STM32CubeIDE\test\Recognition_Embedded_IA-dev_Ayoub_cleaning (7).zip_expanded\Recognition_Embedded_IA-dev_Ayoub_cleaning\Core\Src" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

EMBEDDED_AI_M2.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "EMBEDDED_AI_M2.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) EMBEDDED_AI_M2.elf EMBEDDED_AI_M2.list EMBEDDED_AI_M2.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
