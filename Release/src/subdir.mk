################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BoardControllerActive.cpp \
../src/BoardControllerContext.cpp \
../src/BoardControllerError.cpp \
../src/BoardControllerIdle.cpp \
../src/BoardControllerShutdown.cpp \
../src/DiscreteManager.cpp \
../src/GlobalTypes.cpp \
../src/OptimizedRefined.cpp \
../src/OptimizedVmeAdapter.cpp \
../src/RWTestVmeAdapter.cpp \
../src/SIMP.cpp \
../src/STIMP.cpp \
../src/SystemBuilder.cpp \
../src/TSAP.cpp \
../src/VMEInterruptHandlerThread.cpp \
../src/main.cpp 

C_SRCS += \
../src/OPB_interface.c 

OBJS += \
./src/BoardControllerActive.o \
./src/BoardControllerContext.o \
./src/BoardControllerError.o \
./src/BoardControllerIdle.o \
./src/BoardControllerShutdown.o \
./src/DiscreteManager.o \
./src/GlobalTypes.o \
./src/OPB_interface.o \
./src/OptimizedRefined.o \
./src/OptimizedVmeAdapter.o \
./src/RWTestVmeAdapter.o \
./src/SIMP.o \
./src/STIMP.o \
./src/SystemBuilder.o \
./src/TSAP.o \
./src/VMEInterruptHandlerThread.o \
./src/main.o 

C_DEPS += \
./src/OPB_interface.d 

CPP_DEPS += \
./src/BoardControllerActive.d \
./src/BoardControllerContext.d \
./src/BoardControllerError.d \
./src/BoardControllerIdle.d \
./src/BoardControllerShutdown.d \
./src/DiscreteManager.d \
./src/GlobalTypes.d \
./src/OptimizedRefined.d \
./src/OptimizedVmeAdapter.d \
./src/RWTestVmeAdapter.d \
./src/SIMP.d \
./src/STIMP.d \
./src/SystemBuilder.d \
./src/TSAP.d \
./src/VMEInterruptHandlerThread.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gianluca/git-workspace/ndimp/include" -I"/home/gianluca/git-workspace/ndimp/include/conf" -I"/home/gianluca/git-workspace/ndimp/include/DataRecorder" -I"/home/gianluca/git-workspace/ndimp/include/Logger" -I"/home/gianluca/git-workspace/ndimp/include/Network" -I"/home/gianluca/git-workspace/ndimp/include/Tests" -I"/home/gianluca/git-workspace/ndimp/include/XsdParser" -I"/home/gianluca/git-workspace/ndimp/Vendors" -I"/home/gianluca/git-workspace/ndimp/Vendors/DesignPattern" -I"/home/gianluca/git-workspace/ndimp/Vendors/EventHandler" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers/32bit" -I"/home/gianluca/git-workspace/ndimp/Vendors/threadObject" -I"/home/gianluca/git-workspace/ndimp/Vendors/Xsd" -I"/home/gianluca/git-workspace/ndimp/XSD" -O3 -Wall -c -fmessage-length=0 -m32 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -static -m32 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


