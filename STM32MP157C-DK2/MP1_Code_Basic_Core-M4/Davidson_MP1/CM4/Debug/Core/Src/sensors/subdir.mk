################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/sensors/LIS2DW12_ACC.c \
../Core/Src/sensors/LSM6DSO_ACC-GYRO.c \
../Core/Src/sensors/STTS751_TEMP.c 

OBJS += \
./Core/Src/sensors/LIS2DW12_ACC.o \
./Core/Src/sensors/LSM6DSO_ACC-GYRO.o \
./Core/Src/sensors/STTS751_TEMP.o 

C_DEPS += \
./Core/Src/sensors/LIS2DW12_ACC.d \
./Core/Src/sensors/LSM6DSO_ACC-GYRO.d \
./Core/Src/sensors/STTS751_TEMP.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/sensors/LIS2DW12_ACC.o: ../Core/Src/sensors/LIS2DW12_ACC.c Core/Src/sensors/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32MP157Cxx -c -I../Core/Inc -I../../Drivers/STM32MP1xx_HAL_Driver/Inc -I../../Drivers/STM32MP1xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32MP1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sensors/LIS2DW12_ACC.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sensors/LSM6DSO_ACC-GYRO.o: ../Core/Src/sensors/LSM6DSO_ACC-GYRO.c Core/Src/sensors/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32MP157Cxx -c -I../Core/Inc -I../../Drivers/STM32MP1xx_HAL_Driver/Inc -I../../Drivers/STM32MP1xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32MP1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sensors/LSM6DSO_ACC-GYRO.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sensors/STTS751_TEMP.o: ../Core/Src/sensors/STTS751_TEMP.c Core/Src/sensors/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32MP157Cxx -c -I../Core/Inc -I../../Drivers/STM32MP1xx_HAL_Driver/Inc -I../../Drivers/STM32MP1xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32MP1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sensors/STTS751_TEMP.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

