################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include drivers/Src/subdir.mk
-include drivers/Inc/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
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

BUILD_ARTIFACT_NAME := SNAKE_GAME_STM32F4
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SNAKE_GAME_STM32F4.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SNAKE_GAME_STM32F4.list \

OBJCOPY_BIN += \
SNAKE_GAME_STM32F4.bin \


# All Target
all: main-build

# Main-build Target
main-build: SNAKE_GAME_STM32F4.elf secondary-outputs

# Tool invocations
SNAKE_GAME_STM32F4.elf: $(OBJS) $(USER_OBJS) D:\KHOA_HOC\MCU\MCU1_DATA\CODE_MCU1\SNAKE_GAME_STM32F4\STM32F411VETX_FLASH.ld
	arm-none-eabi-gcc -o "SNAKE_GAME_STM32F4.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\KHOA_HOC\MCU\MCU1_DATA\CODE_MCU1\SNAKE_GAME_STM32F4\STM32F411VETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SNAKE_GAME_STM32F4.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SNAKE_GAME_STM32F4.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SNAKE_GAME_STM32F4.list"
	@echo 'Finished building: $@'
	@echo ' '

SNAKE_GAME_STM32F4.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "SNAKE_GAME_STM32F4.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
