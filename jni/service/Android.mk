################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/service/UnixDomainSocketManager.cpp 

OBJS += \
./src/service/UnixDomainSocketManager.o 

CPP_DEPS += \
./src/service/UnixDomainSocketManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/service/%.o: ../src/service/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/AMDAPP/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


