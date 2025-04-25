################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mycode/oled/OLED.c \
../mycode/oled/OLED_Data.c 

OBJS += \
./mycode/oled/OLED.o \
./mycode/oled/OLED_Data.o 

C_DEPS += \
./mycode/oled/OLED.d \
./mycode/oled/OLED_Data.d 


# Each subdirectory must supply rules for building sources it contributes
mycode/oled/%.o mycode/oled/%.su mycode/oled/%.cyclo: ../mycode/oled/%.c mycode/oled/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xintxiao/Desktop/xinjian/car/mycode/include" -I"C:/Users/xintxiao/Desktop/xinjian/car/mycode/oled" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-mycode-2f-oled

clean-mycode-2f-oled:
	-$(RM) ./mycode/oled/OLED.cyclo ./mycode/oled/OLED.d ./mycode/oled/OLED.o ./mycode/oled/OLED.su ./mycode/oled/OLED_Data.cyclo ./mycode/oled/OLED_Data.d ./mycode/oled/OLED_Data.o ./mycode/oled/OLED_Data.su

.PHONY: clean-mycode-2f-oled

