MCU = atmega2560
F_CPU = 16000000UL
BAUD = 9600UL
all: AVR

AVR: .\bin\debug\inter.elf
	avr-objcopy .\bin\debug\inter.elf -O ihex .\bin\release\TilHulp.hex

.\bin\debug\inter.elf: .\src\main.c .\src\lib\*
	avr-g++.exe .\src\main.c .\src\lib\* -o .\bin\debug\inter.elf -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

