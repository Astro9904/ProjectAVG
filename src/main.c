#include "main.h"
#include "lib/customio.h"

#define F_CPU 16000000ul

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include "lib/usart.h"


#define BUFF_SIZE   25


int main(void)
{
	//uart_set_FrameFormat(USART_8BIT_DATA|USART_1STOP_BIT|USART_NO_PARITY|USART_ASYNC_MODE); // default settings
	uart_init(BAUD_CALC(115200)); // 8n1 transmission is set as default
	
	stdout = &uart0_io; // attach uart stream to stdout & stdin
	stdin = &uart0_io; // uart0_in and uart0_out are only available if NO_USART_RX or NO_USART_TX is defined
	
	sei(); // enable interrupts, library wouldn't work without this
		
	uart_puts("hello from usart 0\r\n"); // write const string to usart buffer // C++ restriction, in C its the same as uart_putstr()
	
	printf("hello from printf\n");

	char buffer[BUFF_SIZE];
	uart_gets(buffer, BUFF_SIZE); // read at most 24 bytes from buffer (CR,LF will not be cut)
	
	int a;
	
	uart_puts("gimmie a number: ");
	a = uart_getint();
	
	uart_puts("numba a: ");
	uart_putint(a);
	uart_puts("\r\n");
	a = uart_getint();
}
