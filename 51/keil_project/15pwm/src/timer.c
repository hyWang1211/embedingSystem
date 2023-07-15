#include <REG52.H>
#include "timer.h"

void Timer0_init()
{
	//set model
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	//set low and hight
	TL0 = 0xA4;
	TH0 = 0xFF;
	
	//set TCON
	TF0 = 0; // prevent interruption at the first time
	TR0 = 1;
	
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}

