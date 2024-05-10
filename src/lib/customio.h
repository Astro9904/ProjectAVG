#pragma once
#include <avr/io.h>
#include <stdint.h>

typedef struct {
	volatile uint8_t* DDR;
	volatile uint8_t* IOR;
	uint8_t SBS;
} IO_t;
