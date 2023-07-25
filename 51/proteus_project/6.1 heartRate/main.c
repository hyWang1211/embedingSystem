#include "LCD1602.h"
#include <regx52.h>
unsigned int heart_time;			/*heartbeat time */
unsigned int heart_time_record;
unsigned int record_time;
unsigned char heart_rate;
void main()
{
	LCD_Init();
	
	LCD_ShowString(1, 1, "HR:");
	LCD_ShowNum(1, 5, heart_rate, 3);
	LCD_ShowString(1, 9, "BMP");
	
	LCD_ShowString(2, 1, "Up:");
	LCD_ShowNum(2, 5, 126, 3);
	
	LCD_ShowString(2, 9, "Low:");
	LCD_ShowNum(2, 14, 12, 2);
	
	while(1) {};
}

void Int0_Routine() interrupt 0
{
	heart_time_record = heart_time;
	heart_time = 0;
}


void Timer0_Routine() interrupt 1
{
	TL0 = 0x66;
	TH0 = 0xFC;
	
	heart_time ++;
	record_time ++;
	
	if (!record_time % 500) {
		record_time = 0;
		heart_rate = 6000 / heart_time_record;
	}
}
