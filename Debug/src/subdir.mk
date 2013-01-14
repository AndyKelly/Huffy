################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BitString.cpp \
../src/ClientSocket.cpp \
../src/Huffy.cpp \
../src/HuffyBaseType.cpp \
../src/HuffyBool.cpp \
../src/HuffyClient.cpp \
../src/HuffyCompressor.cpp \
../src/HuffyFloat.cpp \
../src/HuffyInt.cpp \
../src/HuffyManager.cpp \
../src/HuffyPacker.cpp \
../src/HuffyPackerUtility.cpp \
../src/HuffySender.cpp \
../src/HuffyServer.cpp \
../src/HuffyTreeManager.cpp \
../src/IDGenerator.cpp \
../src/InputManager.cpp \
../src/OutputManager.cpp \
../src/ServerSocket.cpp \
../src/Socket.cpp 

OBJS += \
./src/BitString.o \
./src/ClientSocket.o \
./src/Huffy.o \
./src/HuffyBaseType.o \
./src/HuffyBool.o \
./src/HuffyClient.o \
./src/HuffyCompressor.o \
./src/HuffyFloat.o \
./src/HuffyInt.o \
./src/HuffyManager.o \
./src/HuffyPacker.o \
./src/HuffyPackerUtility.o \
./src/HuffySender.o \
./src/HuffyServer.o \
./src/HuffyTreeManager.o \
./src/IDGenerator.o \
./src/InputManager.o \
./src/OutputManager.o \
./src/ServerSocket.o \
./src/Socket.o 

CPP_DEPS += \
./src/BitString.d \
./src/ClientSocket.d \
./src/Huffy.d \
./src/HuffyBaseType.d \
./src/HuffyBool.d \
./src/HuffyClient.d \
./src/HuffyCompressor.d \
./src/HuffyFloat.d \
./src/HuffyInt.d \
./src/HuffyManager.d \
./src/HuffyPacker.d \
./src/HuffyPackerUtility.d \
./src/HuffySender.d \
./src/HuffyServer.d \
./src/HuffyTreeManager.d \
./src/IDGenerator.d \
./src/InputManager.d \
./src/OutputManager.d \
./src/ServerSocket.d \
./src/Socket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


