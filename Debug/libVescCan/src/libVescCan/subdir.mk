################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libVescCan/src/libVescCan/VESC_Convert.c \
../libVescCan/src/libVescCan/VESC_Endian.c 

OBJS += \
./libVescCan/src/libVescCan/VESC_Convert.o \
./libVescCan/src/libVescCan/VESC_Endian.o 

C_DEPS += \
./libVescCan/src/libVescCan/VESC_Convert.d \
./libVescCan/src/libVescCan/VESC_Endian.d 


# Each subdirectory must supply rules for building sources it contributes
libVescCan/src/libVescCan/%.o libVescCan/src/libVescCan/%.su libVescCan/src/libVescCan/%.cyclo: ../libVescCan/src/libVescCan/%.c libVescCan/src/libVescCan/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../libVescCan/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-libVescCan-2f-src-2f-libVescCan

clean-libVescCan-2f-src-2f-libVescCan:
	-$(RM) ./libVescCan/src/libVescCan/VESC_Convert.cyclo ./libVescCan/src/libVescCan/VESC_Convert.d ./libVescCan/src/libVescCan/VESC_Convert.o ./libVescCan/src/libVescCan/VESC_Convert.su ./libVescCan/src/libVescCan/VESC_Endian.cyclo ./libVescCan/src/libVescCan/VESC_Endian.d ./libVescCan/src/libVescCan/VESC_Endian.o ./libVescCan/src/libVescCan/VESC_Endian.su

.PHONY: clean-libVescCan-2f-src-2f-libVescCan

