################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AMEFDecoder.cpp \
../src/AMEFEncoder.cpp \
../src/AMEFObject.cpp \
../src/AMEFResources.cpp \
../src/BinaryData.cpp \
../src/Client.cpp \
../src/ClientInterface.cpp \
../src/Constants.cpp \
../src/Date.cpp \
../src/DateFormat.cpp \
../src/DistoCacheClientUtils.cpp \
../src/DistoCacheConnectionFactory.cpp \
../src/Logger.cpp \
../src/Mutex.cpp \
../src/PropFileReader.cpp \
../src/SSLClient.cpp \
../src/Serialize.cpp \
../src/StringUtil.cpp

OBJS += \
./AMEFDecoder.o \
./AMEFEncoder.o \
./AMEFObject.o \
./AMEFResources.o \
./BinaryData.o \
./Client.o \
./ClientInterface.o \
./Constants.o \
./Date.o \
./DateFormat.o \
./DistoCacheClientUtils.o \
./DistoCacheConnectionFactory.o \
./Logger.o \
./Mutex.o \
./PropFileReader.o \
./SSLClient.o \
./Serialize.o \
./StringUtil.o

CPP_DEPS += \
./AMEFDecoder.d \
./AMEFEncoder.d \
./AMEFObject.d \
./AMEFResources.d \
./BinaryData.d \
./Client.d \
./ClientInterface.d \
./Constants.d \
./Date.d \
./DateFormat.d \
./DistoCacheClientUtils.d \
./DistoCacheConnectionFactory.d \
./Logger.d \
./Mutex.d \
./PropFileReader.d \
./SSLClient.d \
./Serialize.d \
./StringUtil.d


# Each subdirectory must supply rules for building sources it contributes
%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ $(PTHREADS) -I../include -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
