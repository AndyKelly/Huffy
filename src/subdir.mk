################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Huffy.cpp \
../src/HuffyBaseType.cpp \
../src/HuffyBool.cpp \
../src/HuffyCompressor.cpp \
../src/HuffyFloat.cpp \
../src/HuffyInt.cpp \
../src/HuffyManager.cpp \
../src/HuffySender.cpp \
../src/IDGenerator.cpp \
../src/InputManager.cpp \
../src/OutputManager.cpp 

OBJS += \
./src/Huffy.o \
./src/HuffyBaseType.o \
./src/HuffyBool.o \
./src/HuffyCompressor.o \
./src/HuffyFloat.o \
./src/HuffyInt.o \
./src/HuffyManager.o \
./src/HuffySender.o \
./src/IDGenerator.o \
./src/InputManager.o \
./src/OutputManager.o 

CPP_DEPS += \
./src/Huffy.d \
./src/HuffyBaseType.d \
./src/HuffyBool.d \
./src/HuffyCompressor.d \
./src/HuffyFloat.d \
./src/HuffyInt.d \
./src/HuffyManager.d \
./src/HuffySender.d \
./src/IDGenerator.d \
./src/InputManager.d \
./src/OutputManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


