################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
../Vendors/Xsd/Command.cxx \
../Vendors/Xsd/CommandStatus.cxx \
../Vendors/Xsd/Discrete.cxx \
../Vendors/Xsd/Log.cxx 

OBJS += \
./Vendors/Xsd/Command.o \
./Vendors/Xsd/CommandStatus.o \
./Vendors/Xsd/Discrete.o \
./Vendors/Xsd/Log.o 

CXX_DEPS += \
./Vendors/Xsd/Command.d \
./Vendors/Xsd/CommandStatus.d \
./Vendors/Xsd/Discrete.d \
./Vendors/Xsd/Log.d 


# Each subdirectory must supply rules for building sources it contributes
Vendors/Xsd/%.o: ../Vendors/Xsd/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gianluca/git-workspace/ndimp/include" -I"/home/gianluca/git-workspace/ndimp/include/conf" -I"/home/gianluca/git-workspace/ndimp/include/DataRecorder" -I"/home/gianluca/git-workspace/ndimp/include/Logger" -I"/home/gianluca/git-workspace/ndimp/include/Network" -I"/home/gianluca/git-workspace/ndimp/include/Tests" -I"/home/gianluca/git-workspace/ndimp/include/XsdParser" -I"/home/gianluca/git-workspace/ndimp/Vendors" -I"/home/gianluca/git-workspace/ndimp/Vendors/DesignPattern" -I"/home/gianluca/git-workspace/ndimp/Vendors/EventHandler" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers/32bit" -I"/home/gianluca/git-workspace/ndimp/Vendors/threadObject" -I"/home/gianluca/git-workspace/ndimp/Vendors/Xsd" -I"/home/gianluca/git-workspace/ndimp/XSD" -O3 -Wall -c -fmessage-length=0 -m32 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


