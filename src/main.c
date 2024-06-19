#include "main.h"
#include "lib/customio.h"

#define F_CPU 16000000ul

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include "lib/sonar.h"


enum modeSelectorModes modeSelector = AGV;


int main(void)
{

    //sonar 1 ---
    //IO_t D43 = {&DDRL, &PORTL, PL6};
    //IO_t D19 = {&DDRD, &PIND, PD2};
    //sonar 2 ----
    //IO_t D45 = {&DDRL, &PORTL, PL4};
    //IO_t D18 = {&DDRD, &PIND, PD3};


    //init_motoren();
    //PORTA |= (1 << PA6) | (1 << PA7);

    //rechter_motor_uit();
    //linker_motor_uit();

//	while(1) {
//		if (modeSelector == AGV) {
//			AGV_Loop();
//		}
//		if (modeSelector == PFM) {
//			PFM_Loop();
//		}
//	}

}


void AGV_Loop() {
    
    rechter_motor_vooruit();
    linker_motor_vooruit();
    _delay_ms(2000);
    if (SonarSensorenDetectie() == 1) {
	rechter_motor_uit();
	linker_motor_uit();
	_delay_ms(2000);
	return;
    }
}

void PFM_Loop() {

}

/*
 */


        //rechter_motor_vooruit();
int SonarSensorenDetectie() {
    return 1;
}

void init_motoren(void) {
    DDRE |= (1<<PE5) | (1<<PE4);
    DDRA |= (1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) | (1 << PA6) | (1 << PA7);
    TCCR3B |= (1<<CS32) | (1<< CS30) | (1<<WGM32); //CLOCK / 64
    TCCR3A |= (1<<WGM30); //8 BIT FAST PWM MODE
    OCR3B = 0;
    OCR3C = 0;
}

void linker_motor_snelheid(int snelheid) {
    OCR3B = snelheid;
    TCCR3A |= (1 << COM3B1);
}

void rechter_motor_snelheid(int snelheid) {
    OCR3C = snelheid;
    TCCR3A |= (1 << COM3C1);
}

void linker_motor_vooruit(void){
    PORTA &= ~(1 << PA0);
    _delay_ms(5);
    PORTA |= (1 << PA1);
}

void linker_motor_achteruit(void){
    PORTA &= ~(1 << PA1);
    _delay_ms(5);
    PORTA |= (1 << PA0);

}

void linker_motor_uit(void){
    PORTA &= ~(1 << PA0);
    PORTA &= ~(1 << PA0);
}

void rechter_motor_achteruit(void){
    PORTA &= ~(1 << PA2);
    _delay_ms(5);
    PORTA |= (1 << PA3);
}

void rechter_motor_vooruit(void){
    PORTA &= ~(1 << PA3);
    _delay_ms(5);
    PORTA |= (1 << PA2);
}

void rechter_motor_uit(void){
    PORTA &= ~(1 << PA2);
    PORTA &= ~(1 << PA3);
}
