#include <REGX52.H>
#include "serial.h"

void main()
{
	serial_init();
	while(1) {
		
	}
}

void UART_Routine() interrupt 4
{
	if (RI == 1) {
		P2 = ~SBUF;
		serial_send(SBUF);
		RI = 0;
	}
}