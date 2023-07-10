#include <INTRINS.h>
#include <REGX52.H>

sbit Buzzer = P2^5;

void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i);
}

void Buzzer_Time(unsigned int xms)
{
	unsigned int i;
	
	for (i = 0; i < xms * 2; i ++) {
		Buzzer = !Buzzer;
		Buzzer_Delay500us();
	}
}