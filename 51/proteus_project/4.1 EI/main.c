#include <regx52.h>

sbit led1 = P2^0;
sbit led2 = P2^1;
void int0_init();
void int1_init();
void main()
{
	led1 = 0;
	led2 = 0;
	int0_init();
	int1_init();
	while(1) {
		
	}
}

void int0_init()
{
	IT0 = 1;
	EX0 = 1;
	EA = 1;
}

void int1_init()
{
	IT1 = 1;
	EX1 = 1;
	EA = 1;
}

void int0_routine() interrupt 0
{
	led1 = ~led1;
	
}

void int1_routine() interrupt 2
{
	led2 = ~led2;
}