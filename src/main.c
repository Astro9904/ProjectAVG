#include "main.h"
#include "lib/customio.h"
#include "lib/ESD.h"

int main() 
{
	IO_t D7 = {&DDRH, &PORTH, PH4};
	IO_t D8 = {&DDRH, &PORTH, PH5};
	IO_t D4 = {&DDRG, &PORTG, PG5};
	cio_pinMode(&D7, OUTPUT);
	cio_digitalWrite(&D7, HIGH);
}
