################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/task/EventTask.cpp \
../src/task/ProcessorAllocater.cpp \
../src/task/ProcessorInfoManager.cpp \
../src/task/ResourceAllocater.cpp 

OBJS += \
./src/task/EventTask.o \
./src/task/ProcessorAllocater.o \
./src/task/ProcessorInfoManager.o \
./src/task/ResourceAllocater.o 

CPP_DEPS += \
./src/task/EventTask.d \
./src/task/ProcessorAllocater.d \
./src/task/ProcessorInfoManager.d \
./src/task/ResourceAllocater.d 


# Each subdirectory must supply rules for building sources it contributes
src/task/%.o: ../src/task/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/AMDAPP/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


