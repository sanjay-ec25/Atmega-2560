
# ==========================================
# AVR BARE METAL MASTER MAKEFILE
# MCU: ATmega2560
# ==========================================

# MCU Configuration
MCU = atmega2560
F_CPU = 16000000UL

# Toolchain
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Upload Configuration
PORT = /dev/ttyACM0
PROGRAMMER = wiring
BAUD = 115200

# Compiler Flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) \
         -Os -Wall -Wextra -std=gnu11

# Get project name from command line
PROJECT = $(firstword $(MAKECMDGOALS))

# Project Directories
SRC_DIR = $(PROJECT)/src
INC_DIR = $(PROJECT)/include
EXAMPLE_DIR = $(PROJECT)/example
BUILD_DIR = $(PROJECT)/build

TARGET = $(PROJECT)

# Find all source files
SRC = $(wildcard $(SRC_DIR)/*.c) $(EXAMPLE_DIR)/main.c

# Generate object file paths
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))


# ==========================================
# DEFAULT TARGET
# ==========================================

.DEFAULT_GOAL := help

.PHONY: help

help:
	@echo "AVR Bare Metal Build System"
	@echo "Usage: make <PROJECT_NAME>"
	@echo "Example: make GPIO"


# ==========================================
# PROJECT VALIDATION
# ==========================================

.PHONY: $(PROJECT)

$(PROJECT):
	@if [ ! -f "$(EXAMPLE_DIR)/main.c" ]; then \
	    echo "Error: $(EXAMPLE_DIR)/main.c not found"; \
	    exit 1; \
	fi
	$(MAKE) PROJECT=$(PROJECT) compile
	$(MAKE) PROJECT=$(PROJECT) upload


# ==========================================
# COMPILE SOURCE FILES
# ==========================================

.PHONY: compile

compile: $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@


# ==========================================
# LINK OBJECT FILES
# ==========================================

$(BUILD_DIR)/$(TARGET).elf: $(OBJ)
	$(CC) -mmcu=$(MCU) $^ -o $@


# ==========================================
# GENERATE HEX FILE
# ==========================================

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@


# ==========================================
# UPLOAD TO ARDUINO MEGA
# ==========================================

.PHONY: upload

upload: $(BUILD_DIR)/$(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) \
	    -P $(PORT) -b $(BAUD) -D \
	    -U flash:w:$<:i


# ==========================================
# CLEAN BUILD FILES
# ==========================================

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)

