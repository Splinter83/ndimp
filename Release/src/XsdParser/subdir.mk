################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/XsdParser/CommandFactory.cpp \
../src/XsdParser/CommandResultFactory.cpp \
../src/XsdParser/DiscreteFactory.cpp 

OBJS += \
./src/XsdParser/CommandFactory.o \
./src/XsdParser/CommandResultFactory.o \
./src/XsdParser/DiscreteFactory.o 

CPP_DEPS += \
./src/XsdParser/CommandFactory.d \
./src/XsdParser/CommandResultFactory.d \
./src/XsdParser/DiscreteFactory.d 


# Each subdirectory must supply rules for building sources it contributes
src/XsdParser/%.o: ../src/XsdParser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gianluca/git-workspace/ndimp/include" -I"/home/gianluca/git-workspace/ndimp/include/conf" -I"/home/gianluca/git-workspace/ndimp/include/DataRecorder" -I"/home/gianluca/git-workspace/ndimp/include/Logger" -I"/home/gianluca/git-workspace/ndimp/include/Network" -I"/home/gianluca/git-workspace/ndimp/include/Tests" -I"/home/gianluca/git-workspace/ndimp/include/XsdParser" -I"/home/gianluca/git-workspace/ndimp/Vendors" -I"/home/gianluca/git-workspace/ndimp/Vendors/DesignPattern" -I"/home/gianluca/git-workspace/ndimp/Vendors/EventHandler" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers/32bit" -I"/home/gianluca/git-workspace/ndimp/Vendors/threadObject" -I"/home/gianluca/git-workspace/ndimp/Vendors/Xsd" -I"/home/gianluca/git-workspace/ndimp/XSD" -O3 -Wall -c -fmessage-length=0 -m32 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


