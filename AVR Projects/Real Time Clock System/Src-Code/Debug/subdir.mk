################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dio.c \
../KPD.c \
../LCD.c \
../Seven_Segment.c \
../Timer.c \
../Timer_1.c \
../main.c 

OBJS += \
./Dio.o \
./KPD.o \
./LCD.o \
./Seven_Segment.o \
./Timer.o \
./Timer_1.o \
./main.o 

C_DEPS += \
./Dio.d \
./KPD.d \
./LCD.d \
./Seven_Segment.d \
./Timer.d \
./Timer_1.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


