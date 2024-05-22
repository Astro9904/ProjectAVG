#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include "customio.h"



//errorcodes:
//1 = invalid mode;
int cio_pinMode(IO_t* pin, uint8_t mode) {
    switch (mode) {
	case 0:
	    *pin->DDR &= ~(_BV(pin->SBS));
	    pin->MODE = INPUT;
	    return 0;
	case 1:
	    *pin->DDR |= _BV(pin->SBS);
	    pin->MODE = OUTPUT;
	    return 0;
	default:
	    return 1;
    }
}



//errorcodes:
//1 = invalid mode;
//2 = pin is set as input;
int cio_digitalWrite(IO_t* pin, uint8_t mode) {
    if (pin->MODE == INPUT) { return 2;}
    switch (mode) {
	case 0:
	    *pin->IOR &= ~(_BV(pin->SBS));
	    return 0;
	case 1:
	    *pin->IOR |= _BV(pin->SBS);
	    return 0;
	default:
	    return 1;
    }

}
//errorcode:
//-1 = pin is set as output;
int cio_digitalRead(IO_t* pin) {
    if (pin->MODE == OUTPUT) { return -1;}
    return (*pin->IOR >> pin->SBS) & 1;
}

