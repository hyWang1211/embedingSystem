#include <REGX52.H>
#include <delay.h>
#include <LCD1602.h>
#include <timer.h>

unsigned char Sec, Min, Hour;
void main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "good");
	Timer0_init();
	while(1) {
		if (Sec == 60) {Sec = 0;Min ++;}
		if (Min == 60) {Min = 0;Hour ++;}
		if (Hour == 24) {Hour = 0;}
		LCD_ShowString(1, 1, "H:");
		LCD_ShowNum(1, 3, Hour, 2); 
		LCD_ShowString(1, 5, "M:");
		LCD_ShowNum(1, 7, Min, 2);
		LCD_ShowString(1, 9, "S:");
		LCD_ShowNum(1, 11, Sec, 2);
	}
}


void Timer0_Routine() interrupt 1
{
	static unsigned int T0_count;
	TL0 = 0x18;
	TH0 = 0xFC;
	T0_count ++;
	
	if (T0_count >= 1000) {
		Sec ++;
		T0_count = 0;
	}
}