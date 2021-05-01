#!/bin/bash

# Version
MAJOR := 1
MINOR := 0
PATCH := 0
STATE := a
VERSION := $(MAJOR).$(MINOR)$(STATE)$(PATCH)

BASE := $(call my-dir)
RM := rm -f
MKDIR := mkdir -p
CP := cp
# Sources
SRCS = $(wildcard *.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))
LSS := driver.lss
C_DEPS := $(patsubst %.c,%.d,$(SRCS))

SIZEDUMMY := sizedummy
FLASH_IMAGE := driver.hex
EEPROM_IMAGE := driver.eep
LIBS :=
MCU := atmega8
CFLAGS = -Wall -g3 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8 -DF_CPU=8000000UL -DVERSION=\"$(VERSION)\"
AVRDUDE := avrdude
PROG := usbasp # Default programmer

TARGET := christmascard

all: driver.elf secondary-outputs
	@echo -n "Finished building $(TARGET).\n"

%.o : %.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc  $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c $^ -o $@
	@echo 'Finished building: $<'
	@echo ' '

driver.elf : $(OBJS)
	@echo 'Building target: $@'
	avr-gcc -Wl,-Map,driver.map -mmcu=atmega8 -o driver.elf $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'

driver.lss: driver.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S $^  > "$@"
	@echo 'Finished building: $@'
	@echo ' '

# Flash image.
driver.hex: driver.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex $^ "$@"
	@echo 'Finished building: $@'
	@echo ' '

# EEPROM
driver.eep: driver.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex $^ "$@"
	@echo 'Finished building: $@'
	@echo ' '


sizedummy: driver.elf
	-avr-size --format=avr --mcu=$(MCU) $^
	@echo ''

secondary-outputs: $(LSS) $(SIZEDUMMY) $(FLASH_IMAGE) $(EEPROM_IMAGE)


install : driver.elf
	$(AVRDUDE) -p$(MCU) -c $(PROG) -Uflash:w:$(FLASH_IMAGE):a
	$(AVRDUDE) -p$(MCU) -c $(PROG) -U lfuse:w:0xE4:m -U hfuse:w:0xD9:m 

distribution : 
	$(RM) -r $(TARGET)-$(VERSION)
	$(MKDIR) $(TARGET)-$(VERSION)
	$(CP) -r *.c *.h Makefile $(TARGET)-$(VERSION)
	tar cf - $(TARGET)-$(VERSION) | gzip -c > $(TARGET)-$(VERSION).tar.gz
	$(RM) -r $(TARGET)-$(VERSION)

clean:
	$(RM) $(OBJS) $(LSS) driver.elf $(FLASH_IMAGE) $(EEPROM_IMAGE) driver.map $(C_DEPS) ledboard_v1.0.elf


.PHONY: all clean secondary-outputs sizedummy

