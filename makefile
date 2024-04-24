PKG=AVG

BUILD_DIR := ./build
OUTPUT_DIR := ./release
SRC_DIRS := ./src


MCU=atmega2560

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=${MCU} -Wall
PORT=COM4


SRCS := $(shell powershell 'Get-ChildItem D:\001-programming\009-ProjectAVG\ProjectAVG\src -Recurse -Include ("*.c", "*.cpp") | Resolve-Path -Relative')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)


BIN=${PKG}


${OUTPUT_DIR}/${PKG}.hex: ${BUILD_DIR}/${PKG}.elf
	${OBJCOPY} -O ihex $< $@

${BUILD_DIR}/${PKG}.elf: ${SRCS}
	${CC} -mmcu=${MCU} -o $@ $^


install: ${OUTPUT_DIR}/${PKG}.hex
	avrdude -v -c arduino -p ${MCU} -P ${PORT} -b 115200 -U flash:w:$<

clean:
	rm -f ${BIN}.elf ${BIN}.hex ${OBJS}

-include $(DEPS)