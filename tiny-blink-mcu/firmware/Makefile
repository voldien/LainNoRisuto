#!/bin/bash

BASE := $(call my-dir)
RM := rm -f
# Sources
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))
ELFS := $(patsubst %.c,%.elf,$(SRCS))
C_DEPS := $(patsubst %.c,%.d,$(SRCS))
LSS := firmware.lss

FCPU := 9600000
SIZEDUMMY := sizedummy
FLASH_IMAGE := firmware.hex
EEPROM_IMAGE := firmware.eep
LIBS :=
MCU := attiny13a
CFLAGS = -Wall -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -s -DF_CPU=$(FCPU) -mmcu=$(MCU) -O2 -g3
AVRDUDE := avrdude
PROG := usbasp # Default programmer


all: firmware.elf secondary-outputs
	@echo -n ""

%.o : %.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc  $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c $^ -o $@
	@echo 'Finished building: $<'
	@echo ' '

firmware.elf : $(OBJS)
	@echo 'Building target: $@'
	avr-gcc -Wl,-Map,firmware.map -o firmware.elf $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'

firmware.lss: firmware.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S $^  > "$@"
	@echo 'Finished building: $@'
	@echo ' '

# Flash image.
$(FLASH_IMAGE): firmware.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex $^ "$@"
	@echo 'Finished building: $@'
	@echo ' '

# EEPROM
$(EEPROM_IMAGE): firmware.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex $^ "$@"
	@echo 'Finished building: $@'
	@echo ' '


sizedummy: firmware.elf
	-avr-size --format=avr --mcu=$(MCU) $^
	@echo ''

secondary-outputs: $(LSS) $(SIZEDUMMY) $(FLASH_IMAGE) $(EEPROM_IMAGE)


install : firmware.elf
	$(AVRDUDE) -pt13 -c $(PROG) -Uflash:w:$(FLASH_IMAGE):a
	#$(AVRDUDE) -pt13 -c -$(PROG) -U lfuse:w:0xE1:m -U hfuse:w:0xD9:m -U efuse:r:con:r

clean:
	$(RM) $(OBJS) $(LSS) v.elf $(FLASH_IMAGE) $(EEPROM_IMAGE) firmware.map $(C_DEPS) firmware.elf


.PHONY: all clean secondary-outputs sizedummy

