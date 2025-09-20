################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/external_interrupt/subdir.mk
-include MCAL/TWI/subdir.mk
-include MCAL/TIMER_DRIVER/subdir.mk
-include MCAL/EEPROM_DRIVER/subdir.mk
-include MCAL/DIO_driver/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/stepp_motor/subdir.mk
-include HAL/servo_motor/subdir.mk
-include HAL/TCS3200_ColorSensor/subdir.mk
-include HAL/LCD_DRIVER/subdir.mk
-include HAL/KEY_PAD_driver/subdir.mk
-include HAL/DC_motor/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ITI_1M_GRAD_PROJECT_.lss \

FLASH_IMAGE += \
ITI_1M_GRAD_PROJECT_.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: ITI_1M_GRAD_PROJECT_.elf secondary-outputs

# Tool invocations
ITI_1M_GRAD_PROJECT_.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ITI_1M_GRAD_PROJECT_.map -mmcu=atmega32 -o "ITI_1M_GRAD_PROJECT_.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ITI_1M_GRAD_PROJECT_.lss: ITI_1M_GRAD_PROJECT_.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ITI_1M_GRAD_PROJECT_.elf  >"ITI_1M_GRAD_PROJECT_.lss"
	@echo 'Finished building: $@'
	@echo ' '

ITI_1M_GRAD_PROJECT_.hex: ITI_1M_GRAD_PROJECT_.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ITI_1M_GRAD_PROJECT_.elf  "ITI_1M_GRAD_PROJECT_.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ITI_1M_GRAD_PROJECT_.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ITI_1M_GRAD_PROJECT_.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ITI_1M_GRAD_PROJECT_.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
