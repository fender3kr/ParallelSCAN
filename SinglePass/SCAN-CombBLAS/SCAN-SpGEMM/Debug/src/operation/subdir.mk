################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/operation/SCAN.cpp 

OBJS += \
./src/operation/SCAN.o 

CPP_DEPS += \
./src/operation/SCAN.d 


# Each subdirectory must supply rules for building sources it contributes
src/operation/%.o: ../src/operation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -std=c++1y -I../../CombBLAS -O3 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


