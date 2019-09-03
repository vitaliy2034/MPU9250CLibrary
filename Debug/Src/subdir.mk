################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/mpu9250_RegLvl.c \
../Src/mpu9250_UsrLvl.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/mpu9250_RegLvl.o \
./Src/mpu9250_UsrLvl.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/mpu9250_RegLvl.d \
./Src/mpu9250_UsrLvl.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/main.o: ../Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F030F4Px -c -I../Inc -I"/home/vitlaiy2034/GDrive/STM32_DevicesLibs/MPU9250_class/CMSIS/Inc" -I"/home/vitlaiy2034/GDrive/STM32_DevicesLibs/MPU9250_class/Startup" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/mpu9250_RegLvl.o: ../Src/mpu9250_RegLvl.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F030F4Px -c -I../Inc -I"/home/vitlaiy2034/GDrive/STM32_DevicesLibs/MPU9250_class/CMSIS/Inc" -I"/home/vitlaiy2034/GDrive/STM32_DevicesLibs/MPU9250_class/Startup" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/mpu9250_RegLvl.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/mpu9250_UsrLvl.o: ../Src/mpu9250_UsrLvl.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F030F4Px -c -I../Inc -I"/home/vitlaiy2034/GDrive/STM32_DevicesLibs/MPU9250_class/CMSIS/Inc" -I"/home/vitlaiy2034/GDrive/STM32_DevicesLibs/MPU9250_class/Startup" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/mpu9250_UsrLvl.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F030F4Px -c -I../Inc -I"/home/vitlaiy2034/GDrive/STM32_DevicesLibs/MPU9250_class/CMSIS/Inc" -I"/home/vitlaiy2034/GDrive/STM32_DevicesLibs/MPU9250_class/Startup" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DDEBUG -DSTM32F030F4Px -c -I../Inc -I"/home/vitlaiy2034/GDrive/STM32_DevicesLibs/MPU9250_class/CMSIS/Inc" -I"/home/vitlaiy2034/GDrive/STM32_DevicesLibs/MPU9250_class/Startup" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
