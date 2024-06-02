#include "sonar.h"
#include "customio.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>

void SonarInit(SONAR_t *SonarObject, IO_t *trigpin, IO_t *echopin) {
    SonarObject->echopin = *echopin;
    SonarObject->trigpin = *trigpin;
    cio_pinMode(trigpin, OUTPUT);
    cio_pinMode(echopin, INPUT);
    
    //reset timer control registers.
}

//WARNING this is not an interrupt driven function. The mcu will halt untill the sensor lowers the echopin or untill 20 ms have passed.
//The distance will be stored in sonarObjec->lastResult
void SonarGetDistance(SONAR_t *sonarObjec) {
    cio_digitalWrite(&sonarObjec->trigpin, HIGH);
    _delay_us(10);
    cio_digitalWrite(&sonarObjec->trigpin, LOW);
    //wait till echo pin is high
    while(cio_digitalRead(&sonarObjec->echopin) == LOW);
    
    TCCR1A = 0;
    TCCR1B = 0;
    //enable timer 1 with 8x prescaler.
    TCCR1B |= (_BV(CS11));
    TCNT1 = 0;
    //wait till echo pin is low or 20ms have passed.
    while(cio_digitalRead(&sonarObjec->echopin) == LOW || TCNT1 >= 40000);
    
    //since the clock with 8x prescaler runs at 0.5 microseconds per tick and using the given formula to get the distance in centimers
    //which is distance = microseconds / 58
    //we devide the value in timer register be 116 (58 * 2)
    if (TCNT1 >= 40000) { 
	sonarObjec->lastResult = -1;
    }
    else {
	sonarObjec->lastResult = TCNT1 / 116;
    }
    
    //disable and clear timer after use
    TCCR1B = 0;
    TCNT1 = 0;
    

}
