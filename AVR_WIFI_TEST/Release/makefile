################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
AVR_WIFI_TEST.lss \

FLASH_IMAGE += \
AVR_WIFI_TEST.hex \

EEPROM_IMAGE += \
AVR_WIFI_TEST.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: AVR_WIFI_TEST.elf secondary-outputs

# Tool invocations
AVR_WIFI_TEST.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,AVR_WIFI_TEST.map -mmcu=atmega8515 -o "AVR_WIFI_TEST.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

AVR_WIFI_TEST.lss: AVR_WIFI_TEST.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S AVR_WIFI_TEST.elf  >"AVR_WIFI_TEST.lss"
	@echo 'Finished building: $@'
	@echo ' '

AVR_WIFI_TEST.hex: AVR_WIFI_TEST.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex AVR_WIFI_TEST.elf  "AVR_WIFI_TEST.hex"
	@echo 'Finished building: $@'
	@echo ' '

AVR_WIFI_TEST.eep: AVR_WIFI_TEST.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex AVR_WIFI_TEST.elf  "AVR_WIFI_TEST.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: AVR_WIFI_TEST.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t AVR_WIFI_TEST.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) AVR_WIFI_TEST.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
