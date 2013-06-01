################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataRecorder/ConsoleDevice.cpp \
../src/DataRecorder/DataRecLogger.cpp \
../src/DataRecorder/DataRecorder.cpp \
../src/DataRecorder/FilestreamDevice.cpp \
../src/DataRecorder/IDataRecorder.cpp \
../src/DataRecorder/IRecordable.cpp \
../src/DataRecorder/IRecordingDevice.cpp \
../src/DataRecorder/RecordableItem.cpp \
../src/DataRecorder/XmlLogDevice.cpp 

OBJS += \
./src/DataRecorder/ConsoleDevice.o \
./src/DataRecorder/DataRecLogger.o \
./src/DataRecorder/DataRecorder.o \
./src/DataRecorder/FilestreamDevice.o \
./src/DataRecorder/IDataRecorder.o \
./src/DataRecorder/IRecordable.o \
./src/DataRecorder/IRecordingDevice.o \
./src/DataRecorder/RecordableItem.o \
./src/DataRecorder/XmlLogDevice.o 

CPP_DEPS += \
./src/DataRecorder/ConsoleDevice.d \
./src/DataRecorder/DataRecLogger.d \
./src/DataRecorder/DataRecorder.d \
./src/DataRecorder/FilestreamDevice.d \
./src/DataRecorder/IDataRecorder.d \
./src/DataRecorder/IRecordable.d \
./src/DataRecorder/IRecordingDevice.d \
./src/DataRecorder/RecordableItem.d \
./src/DataRecorder/XmlLogDevice.d 


# Each subdirectory must supply rules for building sources it contributes
src/DataRecorder/%.o: ../src/DataRecorder/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gianluca/git-workspace/ndimp/include" -I"/home/gianluca/git-workspace/ndimp/include/conf" -I"/home/gianluca/git-workspace/ndimp/include/DataRecorder" -I"/home/gianluca/git-workspace/ndimp/include/Logger" -I"/home/gianluca/git-workspace/ndimp/include/Network" -I"/home/gianluca/git-workspace/ndimp/include/Tests" -I"/home/gianluca/git-workspace/ndimp/include/XsdParser" -I"/home/gianluca/git-workspace/ndimp/Vendors" -I"/home/gianluca/git-workspace/ndimp/Vendors/DesignPattern" -I"/home/gianluca/git-workspace/ndimp/Vendors/EventHandler" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers/32bit" -I"/home/gianluca/git-workspace/ndimp/Vendors/threadObject" -I"/home/gianluca/git-workspace/ndimp/Vendors/Xsd" -I"/home/gianluca/git-workspace/ndimp/XSD" -O3 -Wall -c -fmessage-length=0 -m32 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


