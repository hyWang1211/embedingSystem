#include "AT24C02.h"
#include "LCD1602.h"
#include <REGX52.H>
#include "delay.h"
#include "timer.h"
void main()
{
	unsigned char Data;
	LCD_Init();
	LCD_ShowString(2, 1, "hello");
	P2 = 0;
	Timer0_init();
	//P2 = 0;
	//AT24C02_Write(0, 66);
	//Delayxms(5);
	//Data = AT24C02_Read(0);
	//if (Data == 66) P2 = 0;
	while (1) {
		
	}
}


void timer0_Routine() interrupt 1
{
	static unsigned int T_count;
	TL0 = 0x18;
	TH0 = 0xFC;
	T_count ++;
	if (T_count >= 1000) {
		T_count = 0;
		P2 = ~P2;
	}
}