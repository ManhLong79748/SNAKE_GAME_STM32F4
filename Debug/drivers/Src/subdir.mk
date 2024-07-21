################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/fonts.c \
../drivers/Src/oled.c \
../drivers/Src/stm32f4_gpio.c \
../drivers/Src/stm32f4_i2c.c \
../drivers/Src/stm32f4_rcc.c \
../drivers/Src/systick.c 

OBJS += \
./drivers/Src/fonts.o \
./drivers/Src/oled.o \
./drivers/Src/stm32f4_gpio.o \
./drivers/Src/stm32f4_i2c.o \
./drivers/Src/stm32f4_rcc.o \
./drivers/Src/systick.o 

C_DEPS += \
./drivers/Src/fonts.d \
./drivers/Src/oled.d \
./drivers/Src/stm32f4_gpio.d \
./drivers/Src/stm32f4_i2c.d \
./drivers/Src/stm32f4_rcc.d \
./drivers/Src/systick.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/fonts.o: ../drivers/Src/fonts.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411VETx -DSTM32 -DSTM32F4 -DDEBUG -c -I../Inc -I"D:/KHOA_HOC/MCU/MCU1_DATA/CODE_MCU1/SNAKE_GAME_STM32F4/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/fonts.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/Src/oled.o: ../drivers/Src/oled.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411VETx -DSTM32 -DSTM32F4 -DDEBUG -c -I../Inc -I"D:/KHOA_HOC/MCU/MCU1_DATA/CODE_MCU1/SNAKE_GAME_STM32F4/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/oled.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/Src/stm32f4_gpio.o: ../drivers/Src/stm32f4_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411VETx -DSTM32 -DSTM32F4 -DDEBUG -c -I../Inc -I"D:/KHOA_HOC/MCU/MCU1_DATA/CODE_MCU1/SNAKE_GAME_STM32F4/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/stm32f4_gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/Src/stm32f4_i2c.o: ../drivers/Src/stm32f4_i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411VETx -DSTM32 -DSTM32F4 -DDEBUG -c -I../Inc -I"D:/KHOA_HOC/MCU/MCU1_DATA/CODE_MCU1/SNAKE_GAME_STM32F4/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/stm32f4_i2c.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/Src/stm32f4_rcc.o: ../drivers/Src/stm32f4_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411VETx -DSTM32 -DSTM32F4 -DDEBUG -c -I../Inc -I"D:/KHOA_HOC/MCU/MCU1_DATA/CODE_MCU1/SNAKE_GAME_STM32F4/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/stm32f4_rcc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/Src/systick.o: ../drivers/Src/systick.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F411VETx -DSTM32 -DSTM32F4 -DDEBUG -c -I../Inc -I"D:/KHOA_HOC/MCU/MCU1_DATA/CODE_MCU1/SNAKE_GAME_STM32F4/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/systick.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

