################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AMEFDecoder.cpp \
../src/AMEFEncoder.cpp \
../src/AMEFObject.cpp \
../src/AMEFResources.cpp \
../src/CacheMap.cpp \
../src/Date.cpp \
../src/DateFormat.cpp \
../src/Logger.cpp \
../src/Mutex.cpp \
../src/PropFileReader.cpp \
../src/SSLHandler.cpp \
../src/SelEpolKqEvPrt.cpp \
../src/Server.cpp \
../src/ServiceHandler.cpp \
../src/StringUtil.cpp \
../src/Thread.cpp \
../src/distocache.cpp 

OBJS += \
./AMEFDecoder.o \
./AMEFEncoder.o \
./AMEFObject.o \
./AMEFResources.o \
./CacheMap.o \
./Date.o \
./DateFormat.o \
./Logger.o \
./Mutex.o \
./PropFileReader.o \
./SSLHandler.o \
./SelEpolKqEvPrt.o \
./Server.o \
./ServiceHandler.o \
./StringUtil.o \
./Thread.o \
./distocache.o 

CPP_DEPS += \
./AMEFDecoder.d \
./AMEFEncoder.d \
./AMEFObject.d \
./AMEFResources.d \
./CacheMap.d \
./Date.d \
./DateFormat.d \
./Logger.d \
./Mutex.d \
./PropFileReader.d \
./SSLHandler.d \
./SelEpolKqEvPrt.d \
./Server.d \
./ServiceHandler.d \
./StringUtil.d \
./Thread.d \
./distocache.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ $(PTHREADS) -I../include -I/usr/local/include -O0 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
