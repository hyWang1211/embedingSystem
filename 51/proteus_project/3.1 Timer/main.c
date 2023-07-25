#include <regx52.h>
#include <timer0.h>

unsigned char timer0_count = 0;
sbit wave = P2^0;
void main()
{
	timer0_init();
	
	while(1) {
		
	}
}


void timer0_routine() interrupt 1
{
	TL0 = 0xF0;				//???????
	TH0 = 0xD8;				//???????
	
	timer0_count ++;
	
	if (timer0_count >= 100) {
		wave = ~wave;
		timer0_count = 0;
	}
	
}