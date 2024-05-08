#include "main.h"
#include "lib/customio.h"
#include <avr/io.h>

int main() 
{
	IO_t D13 = {DDRB, PORTB, PB7};
	* D13.DDR |= _BV(D13.SBS);
	* D13.IOR |= _BV(D13.SBS);
	

}
