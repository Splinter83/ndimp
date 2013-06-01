################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Vendors/threadObject/BaseRunnableThread.cpp \
../Vendors/threadObject/EventHandler.cpp \
../Vendors/threadObject/Mutex.cpp \
../Vendors/threadObject/MutextCondition.cpp \
../Vendors/threadObject/Thread.cpp 

OBJS += \
./Vendors/threadObject/BaseRunnableThread.o \
./Vendors/threadObject/EventHandler.o \
./Vendors/threadObject/Mutex.o \
./Vendors/threadObject/MutextCondition.o \
./Vendors/threadObject/Thread.o 

CPP_DEPS += \
./Vendors/threadObject/BaseRunnableThread.d \
./Vendors/threadObject/EventHandler.d \
./Vendors/threadObject/Mutex.d \
./Vendors/threadObject/MutextCondition.d \
./Vendors/threadObject/Thread.d 


# Each subdirectory must supply rules for building sources it contributes
Vendors/threadObject/%.o: ../Vendors/threadObject/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gianluca/git-workspace/ndimp/include" -I"/home/gianluca/git-workspace/ndimp/include/conf" -I"/home/gianluca/git-workspace/ndimp/include/DataRecorder" -I"/home/gianluca/git-workspace/ndimp/include/Logger" -I"/home/gianluca/git-workspace/ndimp/include/Network" -I"/home/gianluca/git-workspace/ndimp/include/Tests" -I"/home/gianluca/git-workspace/ndimp/include/XsdParser" -I"/home/gianluca/git-workspace/ndimp/Vendors" -I"/home/gianluca/git-workspace/ndimp/Vendors/DesignPattern" -I"/home/gianluca/git-workspace/ndimp/Vendors/EventHandler" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers/32bit" -I"/home/gianluca/git-workspace/ndimp/Vendors/threadObject" -I"/home/gianluca/git-workspace/ndimp/Vendors/Xsd" -I"/home/gianluca/git-workspace/ndimp/XSD" -O0 -Wall -c -fmessage-length=0 -m32 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


