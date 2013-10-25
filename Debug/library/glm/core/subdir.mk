################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../library/glm/core/dummy.cpp 

OBJS += \
./library/glm/core/dummy.o 

CPP_DEPS += \
./library/glm/core/dummy.d 


# Each subdirectory must supply rules for building sources it contributes
library/glm/core/%.o: ../library/glm/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


