################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/capsense.c \
../Sources/main.c \
../Sources/new.c \
../Sources/zero.c 

OBJS += \
./Sources/capsense.o \
./Sources/main.o \
./Sources/new.o \
./Sources/zero.o 

C_DEPS += \
./Sources/capsense.d \
./Sources/main.d \
./Sources/new.d \
./Sources/zero.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


