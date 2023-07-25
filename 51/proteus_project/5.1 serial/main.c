#include <regx52.h>
#include "serial.h"

unsigned char rev_data = 0, flag = 0;
void main()
{
	timer1_init();
	serial_init();
	while (1) {
		if (flag) {
			send_byte(rev_data);
			flag = 0;
		}
	}
}


void serial_routine() interrupt 4
{
	if (RI) {
		rev_data = SBUF;
		RI = 0;
		flag = 1;
	}
}
