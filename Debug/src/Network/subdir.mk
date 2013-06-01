################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Network/ConcreteTcpSocket.cpp \
../src/Network/ISocketTcp.cpp \
../src/Network/NetAddress.cpp \
../src/Network/TCPClient.cpp \
../src/Network/TCPFactoryMessage.cpp \
../src/Network/TCPServer.cpp \
../src/Network/TcpSocketComponent.cpp \
../src/Network/TcpSocketDecorator.cpp 

OBJS += \
./src/Network/ConcreteTcpSocket.o \
./src/Network/ISocketTcp.o \
./src/Network/NetAddress.o \
./src/Network/TCPClient.o \
./src/Network/TCPFactoryMessage.o \
./src/Network/TCPServer.o \
./src/Network/TcpSocketComponent.o \
./src/Network/TcpSocketDecorator.o 

CPP_DEPS += \
./src/Network/ConcreteTcpSocket.d \
./src/Network/ISocketTcp.d \
./src/Network/NetAddress.d \
./src/Network/TCPClient.d \
./src/Network/TCPFactoryMessage.d \
./src/Network/TCPServer.d \
./src/Network/TcpSocketComponent.d \
./src/Network/TcpSocketDecorator.d 


# Each subdirectory must supply rules for building sources it contributes
src/Network/%.o: ../src/Network/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gianluca/git-workspace/ndimp/include" -I"/home/gianluca/git-workspace/ndimp/include/conf" -I"/home/gianluca/git-workspace/ndimp/include/DataRecorder" -I"/home/gianluca/git-workspace/ndimp/include/Logger" -I"/home/gianluca/git-workspace/ndimp/include/Network" -I"/home/gianluca/git-workspace/ndimp/include/Tests" -I"/home/gianluca/git-workspace/ndimp/include/XsdParser" -I"/home/gianluca/git-workspace/ndimp/Vendors" -I"/home/gianluca/git-workspace/ndimp/Vendors/DesignPattern" -I"/home/gianluca/git-workspace/ndimp/Vendors/EventHandler" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers" -I"/home/gianluca/git-workspace/ndimp/Vendors/LinuxVmeDrivers/32bit" -I"/home/gianluca/git-workspace/ndimp/Vendors/threadObject" -I"/home/gianluca/git-workspace/ndimp/Vendors/Xsd" -I"/home/gianluca/git-workspace/ndimp/XSD" -O0 -Wall -c -fmessage-length=0 -m32 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


