################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GPIO/Stm32_F103C6_gpio_driver.c 

OBJS += \
./MCAL/GPIO/Stm32_F103C6_gpio_driver.o 

C_DEPS += \
./MCAL/GPIO/Stm32_F103C6_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/GPIO/Stm32_F103C6_gpio_driver.o: ../MCAL/GPIO/Stm32_F103C6_gpio_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Kero/STM32CubeIDE/workspace_1.4.0/Drivers_STM32F103C6/HAL/inc" -I"C:/Users/Kero/STM32CubeIDE/workspace_1.4.0/Drivers_STM32F103C6/MCAL/inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/GPIO/Stm32_F103C6_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

