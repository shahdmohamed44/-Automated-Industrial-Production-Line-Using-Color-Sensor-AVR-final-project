################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ITI_1M_GRAD_PROJECT_/ITI_1M_GRAD_PROJECT_/MCAL/DIO_driver/DIO_program.c 

OBJS += \
./ITI_1M_GRAD_PROJECT_/ITI_1M_GRAD_PROJECT_/MCAL/DIO_driver/DIO_program.o 

C_DEPS += \
./ITI_1M_GRAD_PROJECT_/ITI_1M_GRAD_PROJECT_/MCAL/DIO_driver/DIO_program.d 


# Each subdirectory must supply rules for building sources it contributes
ITI_1M_GRAD_PROJECT_/ITI_1M_GRAD_PROJECT_/MCAL/DIO_driver/%.o: ../ITI_1M_GRAD_PROJECT_/ITI_1M_GRAD_PROJECT_/MCAL/DIO_driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


