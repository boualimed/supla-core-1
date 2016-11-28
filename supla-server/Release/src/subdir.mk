################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/accept_loop.cpp \
../src/cdcommon.cpp \
../src/client.cpp \
../src/clientchannel.cpp \
../src/clientlocation.cpp \
../src/datalogger.cpp \
../src/db.cpp \
../src/device.cpp \
../src/devicechannel.cpp \
../src/ipcctrl.cpp \
../src/serverconnection.cpp \
../src/supla-server.cpp \
../src/user.cpp 

C_SRCS += \
../src/cfg.c \
../src/eh.c \
../src/ini.c \
../src/ipcsocket.c \
../src/lck.c \
../src/log.c \
../src/proto.c \
../src/safearray.c \
../src/srpc.c \
../src/sthread.c \
../src/supla-socket.c \
../src/svrcfg.c \
../src/tools.c 

OBJS += \
./src/accept_loop.o \
./src/cdcommon.o \
./src/cfg.o \
./src/client.o \
./src/clientchannel.o \
./src/clientlocation.o \
./src/datalogger.o \
./src/db.o \
./src/device.o \
./src/devicechannel.o \
./src/eh.o \
./src/ini.o \
./src/ipcctrl.o \
./src/ipcsocket.o \
./src/lck.o \
./src/log.o \
./src/proto.o \
./src/safearray.o \
./src/serverconnection.o \
./src/srpc.o \
./src/sthread.o \
./src/supla-server.o \
./src/supla-socket.o \
./src/svrcfg.o \
./src/tools.o \
./src/user.o 

C_DEPS += \
./src/cfg.d \
./src/eh.d \
./src/ini.d \
./src/ipcsocket.d \
./src/lck.d \
./src/log.d \
./src/proto.d \
./src/safearray.d \
./src/srpc.d \
./src/sthread.d \
./src/supla-socket.d \
./src/svrcfg.d \
./src/tools.d 

CPP_DEPS += \
./src/accept_loop.d \
./src/cdcommon.d \
./src/client.d \
./src/clientchannel.d \
./src/clientlocation.d \
./src/datalogger.d \
./src/db.d \
./src/device.d \
./src/devicechannel.d \
./src/ipcctrl.d \
./src/serverconnection.d \
./src/supla-server.d \
./src/user.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__OPEN_SSL=1 -O3 -Wall $(CPPFLAGS) -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall $(CFLAGS) -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


