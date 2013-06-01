################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tests/ACT_DEM.cpp \
../src/Tests/Address_Test.cpp \
../src/Tests/BitHistoryTest.cpp \
../src/Tests/BusyProgramBC.cpp \
../src/Tests/DDLAddressTest.cpp \
../src/Tests/DiscreteIF.cpp \
../src/Tests/Discrete_Input.cpp \
../src/Tests/Discrete_Output.cpp \
../src/Tests/En_IsNoGo..cpp \
../src/Tests/HIACT_LODEM.cpp \
../src/Tests/HS_Interrupt_Pointer_Offset.cpp \
../src/Tests/HS_Selftest.cpp \
../src/Tests/IF_Optimized_Bus_Test.cpp \
../src/Tests/Iniz_Tavola_Descr_SA_01_RX.cpp \
../src/Tests/Iniz_Tavola_Descr_SA_01_TX.cpp \
../src/Tests/Inizializzazione_LS.cpp \
../src/Tests/InterruptLSTest.cpp \
../src/Tests/Loopback_Esterno.cpp \
../src/Tests/Loopback_Esterno_Att_LS.cpp \
../src/Tests/ModNogo.cpp \
../src/Tests/Nmi_3909.cpp \
../src/Tests/Parity_Test.cpp \
../src/Tests/Program_BC.cpp \
../src/Tests/RAM_Test.cpp \
../src/Tests/SIMPLoopbackCHASideB.cpp \
../src/Tests/Selftest.cpp \
../src/Tests/Skeleton.cpp \
../src/Tests/Skeleton_Test.cpp \
../src/Tests/Verifica_Mod_BC.cpp \
../src/Tests/Verifica_Progr_BC.cpp \
../src/Tests/Watch_Dog.cpp \
../src/Tests/Watch_Dog_Test.cpp \
../src/Tests/globals_test_vars.cpp 

OBJS += \
./src/Tests/ACT_DEM.o \
./src/Tests/Address_Test.o \
./src/Tests/BitHistoryTest.o \
./src/Tests/BusyProgramBC.o \
./src/Tests/DDLAddressTest.o \
./src/Tests/DiscreteIF.o \
./src/Tests/Discrete_Input.o \
./src/Tests/Discrete_Output.o \
./src/Tests/En_IsNoGo..o \
./src/Tests/HIACT_LODEM.o \
./src/Tests/HS_Interrupt_Pointer_Offset.o \
./src/Tests/HS_Selftest.o \
./src/Tests/IF_Optimized_Bus_Test.o \
./src/Tests/Iniz_Tavola_Descr_SA_01_RX.o \
./src/Tests/Iniz_Tavola_Descr_SA_01_TX.o \
./src/Tests/Inizializzazione_LS.o \
./src/Tests/InterruptLSTest.o \
./src/Tests/Loopback_Esterno.o \
./src/Tests/Loopback_Esterno_Att_LS.o \
./src/Tests/ModNogo.o \
./src/Tests/Nmi_3909.o \
./src/Tests/Parity_Test.o \
./src/Tests/Program_BC.o \
./src/Tests/RAM_Test.o \
./src/Tests/SIMPLoopbackCHASideB.o \
./src/Tests/Selftest.o \
./src/Tests/Skeleton.o \
./src/Tests/Skeleton_Test.o \
./src/Tests/Verifica_Mod_BC.o \
./src/Tests/Verifica_Progr_BC.o \
./src/Tests/Watch_Dog.o \
./src/Tests/Watch_Dog_Test.o \
./src/Tests/globals_test_vars.o 

CPP_DEPS += \
./src/Tests/ACT_DEM.d \
./src/Tests/Address_Test.d \
./src/Tests/BitHistoryTest.d \
./src/Tests/BusyProgramBC.d \
./src/Tests/DDLAddressTest.d \
./src/Tests/DiscreteIF.d \
./src/Tests/Discrete_Input.d \
./src/Tests/Discrete_Output.d \
./src/Tests/En_IsNoGo..d \
./src/Tests/HIACT_LODEM.d \
./src/Tests/HS_Interrupt_Pointer_Offset.d \
./src/Tests/HS_Selftest.d \
./src/Tests/IF_Optimized_Bus_Test.d \
./src/Tests/Iniz_Tavola_Descr_SA_01_RX.d \
./src/Tests/Iniz_Tavola_Descr_SA_01_TX.d \
./src/Tests/Inizializzazione_LS.d \
./src/Tests/InterruptLSTest.d \
./src/Tests/Loopback_Esterno.d \
./src/Tests/Loopback_Esterno_Att_LS.d \
./src/Tests/ModNogo.d \
./src/Tests/Nmi_3909.d \
./src/Tests/Parity_Test.d \
./src/Tests/Program_BC.d \
./src/Tests/RAM_Test.d \
./src/Tests/SIMPLoopbackCHASideB.d \
./src/Tests/Selftest.d \
./src/Tests/Skeleton.d \
./src/Tests/Skeleton_Test.d \
./src/Tests/Verifica_Mod_BC.d \
./src/Tests/Verifica_Progr_BC.d \
./src/Tests/Watch_Dog.d \
./src/Tests/Watch_Dog_Test.d \
./src/Tests/globals_test_vars.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tests/%.o: ../src/Tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gianluca/git-workspace/ndimp/include" -I"/home/gianluca/git-workspace/ndimp/include/conf" -I"/home/gianluca/git-workspace/ndimp/include/DataRecorder" -I"/home/gianluca/git-workspace/ndimp/include/Logger" -I"/home/gianluca/git-workspace/ndimp/include/Network" -I"/home/gianluca/git-workspace/ndimp/include/Tests" -I"/home/gianluca/git-workspace/ndimp/include/XsdParser" -I"/home/gianluca/git-workspace/ndimp/Vendors" -I"/home/gianluca/git-workspace/ndimp/Vendors/DesignPattern" -I"/home/gianluca/git-workspace/ndimp/Vendors/EventHandler" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers/32bit" -I"/home/gianluca/git-workspace/ndimp/Vendors/threadObject" -I"/home/gianluca/git-workspace/ndimp/Vendors/Xsd" -I"/home/gianluca/git-workspace/ndimp/XSD" -O3 -Wall -c -fmessage-length=0 -m32 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


