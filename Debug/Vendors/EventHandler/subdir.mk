################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Vendors/EventHandler/ActiveObject.cpp \
../Vendors/EventHandler/CircularBuffer.cpp \
../Vendors/EventHandler/Endianess.cpp \
../Vendors/EventHandler/IActiveObjectCommand.cpp \
../Vendors/EventHandler/IOutputDataStream.cpp 

OBJS += \
./Vendors/EventHandler/ActiveObject.o \
./Vendors/EventHandler/CircularBuffer.o \
./Vendors/EventHandler/Endianess.o \
./Vendors/EventHandler/IActiveObjectCommand.o \
./Vendors/EventHandler/IOutputDataStream.o 

CPP_DEPS += \
./Vendors/EventHandler/ActiveObject.d \
./Vendors/EventHandler/CircularBuffer.d \
./Vendors/EventHandler/Endianess.d \
./Vendors/EventHandler/IActiveObjectCommand.d \
./Vendors/EventHandler/IOutputDataStream.d 


# Each subdirectory must supply rules for building sources it contributes
Vendors/EventHandler/%.o: ../Vendors/EventHandler/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gianluca/git-workspace/ndimp/include" -I"/home/gianluca/git-workspace/ndimp/include/conf" -I"/home/gianluca/git-workspace/ndimp/include/DataRecorder" -I"/home/gianluca/git-workspace/ndimp/include/Logger" -I"/home/gianluca/git-workspace/ndimp/include/Network" -I"/home/gianluca/git-workspace/ndimp/include/Tests" -I"/home/gianluca/git-workspace/ndimp/include/XsdParser" -I"/home/gianluca/git-workspace/ndimp/Vendors" -I"/home/gianluca/git-workspace/ndimp/Vendors/DesignPattern" -I"/home/gianluca/git-workspace/ndimp/Vendors/EventHandler" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers/32bit" -I"/home/gianluca/git-workspace/ndimp/Vendors/threadObject" -I"/home/gianluca/git-workspace/ndimp/Vendors/Xsd" -I"/home/gianluca/git-workspace/ndimp/XSD" -O0 -Wall -c -fmessage-length=0 -m32 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


