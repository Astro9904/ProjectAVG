#pragma once
#include <avr/io.h>
#include <stdint.h>

enum {
	INPUT = 0,
	OUTPUT = 1,
	HIGH = 1,
	LOW = 0
};

//! @param DDR -- Data Direction Register. look at the data sheet of the arduino to see which register. (DDRn).
//! @param IOR -- In Out Register. Look at the data sheet of the arduino to see which register. (PINn of PORTn).
//! @param SBS -- Significant Bit Selector. Select to bit in the byte to change or look at.
//! @param MODE -- Safety variable use cio_pinMode() to set this variable.
typedef struct {
	volatile uint8_t* DDR;
	volatile uint8_t* IOR;
	uint8_t SBS;
	uint8_t MODE;
} IO_t;


int cio_digitalRead(IO_t* pin);
int cio_digitalWrite(IO_t* pin, uint8_t mode);
int cio_pinMode(IO_t* pin, uint8_t mode);
