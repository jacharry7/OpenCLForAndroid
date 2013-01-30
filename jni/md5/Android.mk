################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/md5/md5.c \
../src/md5/md5main.c 

OBJS += \
./src/md5/md5.o \
./src/md5/md5main.o 

C_DEPS += \
./src/md5/md5.d \
./src/md5/md5main.d 


# Each subdirectory must supply rules for building sources it contributes
src/md5/%.o: ../src/md5/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


