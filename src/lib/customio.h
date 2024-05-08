#pragma once
#include <avr/io.h>

typedef struct {
	int* DDR;
	int* IOR;
	uint8_t SBS;
} IO_t;
