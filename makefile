PKG=AVG

MCU=atmega2560

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=${MCU} -Wall
PORT=COM4


BUILD_DIR := ./build
OUTPUT_DIR := ./release
SRC_DIRS := ./src


SRCS := $(shell powershell 'Get-ChildItem .\src -Recurse -Include ("*.c", "*.cpp") | Resolve-Path -Relative')


${OUTPUT_DIR}/${PKG}.hex: ${BUILD_DIR}/${PKG}.elf
	${OBJCOPY} -O ihex $< $@

${BUILD_DIR}/${PKG}.elf: ${SRCS}
	${CC} -mmcu=${MCU} -o $@ $^


install: ${OUTPUT_DIR}/${PKG}.hex
	avrdude -v -c arduino -p ${MCU} -P ${PORT} -b 115200 -U flash:w:$<

clean:
	rm -f ${BUILD_DIR}/${PKG}.elf ${OUTPUT_DIR}/${PKG}.hex
