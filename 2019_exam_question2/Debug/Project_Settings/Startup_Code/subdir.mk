################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c 

OBJS += \
./Project_Settings/Startup_Code/startup.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:/Desktop/JCU folder/Second Year 2020/Second semester/CC2511/Past exam/2019_exam_question2/Static_Code/PDD" -I"D:/Desktop/JCU folder/Second Year 2020/Second semester/CC2511/Past exam/2019_exam_question2/Static_Code/IO_Map" -I"D:/Desktop/JCU folder/Second Year 2020/Second semester/CC2511/Past exam/2019_exam_question2/Sources" -I"D:/Desktop/JCU folder/Second Year 2020/Second semester/CC2511/Past exam/2019_exam_question2/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


