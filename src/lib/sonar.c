/*
 * AVR_HC-SR04_sensor.c
 *
 * Created: 31.12.2020 13:38:11
 * Author : oxford
 */ 

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

#include "sonar.h"

int SonarGetDistance(int* Trig_port, int Trig_Bit, int* Echo_port, int Echo_Bit) {
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1B |= _BV(CS11);
	SonarStartMeasurement(Trig_port, Trig_Bit);
	TCNT1 = 0;
	while(TCNT1 >= 40000 || bit_is_clear(*Echo_port, Echo_Bit));

	if (TCNT1 >= 40000) { return -1; }
	else { return TCNT1 / 116; }
}

void SonarStartMeasurement(int* Trig_port, int Trig_Bit) {
	*Trig_port |= _BV(Trig_Bit);
	_delay_us(10);
	*Trig_port &= ~_BV(Trig_Bit);
}
