#include <REGX52.H>
#include "timer.h"

void Timer0_init()
{
	//set model
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	//set low and hight
	TL0 = 64536 % 256;
	TH0 = 64536 / 256;
	
	//set TCON
	TF0 = 0; // prevent interruption at the first time
	TR0 = 1;
	
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}
