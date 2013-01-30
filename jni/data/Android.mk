################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/data/DeviceTable.cpp \
../src/data/ExecData.cpp \
../src/data/FuncData.cpp \
../src/data/KernelCode.cpp \
../src/data/ResourceSizeData.cpp \
../src/data/Signal.cpp \
../src/data/SocketData.cpp \
../src/data/TagData.cpp \
../src/data/WorkItemSizeList.cpp 

OBJS += \
./src/data/DeviceTable.o \
./src/data/ExecData.o \
./src/data/FuncData.o \
./src/data/KernelCode.o \
./src/data/ResourceSizeData.o \
./src/data/Signal.o \
./src/data/SocketData.o \
./src/data/TagData.o \
./src/data/WorkItemSizeList.o 

CPP_DEPS += \
./src/data/DeviceTable.d \
./src/data/ExecData.d \
./src/data/FuncData.d \
./src/data/KernelCode.d \
./src/data/ResourceSizeData.d \
./src/data/Signal.d \
./src/data/SocketData.d \
./src/data/TagData.d \
./src/data/WorkItemSizeList.d 


# Each subdirectory must supply rules for building sources it contributes
src/data/%.o: ../src/data/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/AMDAPP/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


