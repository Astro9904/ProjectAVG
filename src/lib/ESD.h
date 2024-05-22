#pragma once
#include "customio.h"
#include <stdint.h>

#ifndef ESD_MAX_displays
#define ESD_MAX_displays 8
#endif

typedef struct {
	IO_t *SDI;
	IO_t *SFTCLK;
	IO_t *LCHCLK;
	uint8_t NoD;
	uint8_t BytesToSend[ESD_MAX_displays];
	uint32_t IntegerToShow;
} ESD_t;

void new_ESD_t(ESD_t *ESD, IO_t *SDI, IO_t *SFTCLK, IO_t *LCHCLK, uint8_t NoD);
