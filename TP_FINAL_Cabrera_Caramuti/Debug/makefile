################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := TP_FINAL_Cabrera_Caramuti
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: TP_FINAL_Cabrera_Caramuti.axf

# Tool invocations
TP_FINAL_Cabrera_Caramuti.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/francabrera/Desktop/Electrónica Digital III/TP_FINAL_LPC1769_CORTEXM3/CMSISv2p00_LPC17xx/Debug" -Xlinker -Map="TP_FINAL_Cabrera_Caramuti.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "TP_FINAL_Cabrera_Caramuti_Debug.ld" -o "TP_FINAL_Cabrera_Caramuti.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) TP_FINAL_Cabrera_Caramuti.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "TP_FINAL_Cabrera_Caramuti.axf"; # arm-none-eabi-objcopy -v -O binary "TP_FINAL_Cabrera_Caramuti.axf" "TP_FINAL_Cabrera_Caramuti.bin" ; # checksum -p LPC1769 -d "TP_FINAL_Cabrera_Caramuti.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
