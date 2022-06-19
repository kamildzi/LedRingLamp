ARDUINO_DIR       = /usr/share/arduino
ARDMK_DIR         = /usr/share/arduino
AVR_TOOLS_DIR     = /usr
AVRDUDE_CONF      = /etc/avrdude.conf
ARDUINO_CORE_PATH = /usr/share/arduino/hardware/archlinux-arduino/avr/cores/arduino
BOARDS_TXT        = /usr/share/arduino/hardware/archlinux-arduino/avr/boards.txt
ARDUINO_VAR_PATH  = /usr/share/arduino/hardware/archlinux-arduino/avr/variants
BOOTLOADER_PARENT = /usr/share/arduino/hardware/archlinux-arduino/avr/bootloaders

MONITOR_PORT = /dev/ttyUSB0
BOARD_TAG    = nano
BOARD_SUB    = atmega328old

PROJECT_ROOT := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
USER_LIB_PATH = $(PROJECT_ROOT)/../../__LIBS__

LOCAL_C_SRCS    = $(shell find . -type f -name '*.c' | tr '\n' ' ')
LOCAL_CPP_SRCS  = $(shell find . -type f -name '*.cpp' | tr '\n' ' ')

include /usr/share/arduino/Arduino.mk
