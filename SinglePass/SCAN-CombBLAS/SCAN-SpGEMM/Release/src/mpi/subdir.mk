################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mpi/MPIHelper.cpp 

OBJS += \
./src/mpi/MPIHelper.o 

CPP_DEPS += \
./src/mpi/MPIHelper.d 


# Each subdirectory must supply rules for building sources it contributes
src/mpi/%.o: ../src/mpi/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -std=c++1y -I../../CombBLAS -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


