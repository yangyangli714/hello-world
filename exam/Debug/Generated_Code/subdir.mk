################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AD1.c \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/BLUE.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BitIoLdd3.c \
../Generated_Code/Cpu.c \
../Generated_Code/FC321.c \
../Generated_Code/GREEN.c \
../Generated_Code/Inhr1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c \
../Generated_Code/RED.c \
../Generated_Code/RealTimeLdd1.c \
../Generated_Code/TU1.c \
../Generated_Code/Term1.c 

OBJS += \
./Generated_Code/AD1.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/BLUE.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BitIoLdd3.o \
./Generated_Code/Cpu.o \
./Generated_Code/FC321.o \
./Generated_Code/GREEN.o \
./Generated_Code/Inhr1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o \
./Generated_Code/RED.o \
./Generated_Code/RealTimeLdd1.o \
./Generated_Code/TU1.o \
./Generated_Code/Term1.o 

C_DEPS += \
./Generated_Code/AD1.d \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/BLUE.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BitIoLdd3.d \
./Generated_Code/Cpu.d \
./Generated_Code/FC321.d \
./Generated_Code/GREEN.d \
./Generated_Code/Inhr1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d \
./Generated_Code/RED.d \
./Generated_Code/RealTimeLdd1.d \
./Generated_Code/TU1.d \
./Generated_Code/Term1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/liyan/workspace.kds/exam/Static_Code/System" -I"C:/Users/liyan/workspace.kds/exam/Static_Code/PDD" -I"C:/Users/liyan/workspace.kds/exam/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/liyan/workspace.kds/exam/Sources" -I"C:/Users/liyan/workspace.kds/exam/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


