#include <REGX52.H>
#include "DS1302.h"
#include "LCD1602.h"
#include "key.h"
#include "timer.h"
//four independent button to control time
//assume there are two MODE for time show
//one mode is show time, another is adjust time

//there we use button k1 to choose two mode, press button means adjust
unsigned char MODE = 0, keyNum = 0, TimeSetSelect = 0, TimeFlashFlag = 0;
unsigned char Month_days[] = {
	31,
	28,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31
};

void Time_Show()
{
	show_time();
	LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);
}

unsigned char Is_Leap_Year(unsigned char year)
{
	return year % 4 == 0;
}

void Time_Set()
{
	
	if (keyNum == 2) {
		//select what to adjust(1-6)
		TimeSetSelect = (TimeSetSelect + 1) % 6;
		LCD_ShowNum(2, 10, TimeSetSelect, 2); 
		
	}else if (keyNum == 3) {
		//current to increase
		DS1302_Time[TimeSetSelect] ++;
		if (Is_Leap_Year(DS1302_Time[0]))
			Month_days[1] = 29;
		else
			Month_days[1] = 28;
		
		
		if (DS1302_Time[5] >= 60) {DS1302_Time[5] = 0;}
		if (DS1302_Time[4] >= 60) {DS1302_Time[4] = 0;}
		if (DS1302_Time[3] >= 24) {DS1302_Time[3] = 0;}
		if (DS1302_Time[0] > 99) {DS1302_Time[0] = 0;}
		if (DS1302_Time[1] > 12) {DS1302_Time[1] = 1;}
		if (DS1302_Time[2] > Month_days[DS1302_Time[1] - 1]) {
			DS1302_Time[2] = 1;
		}
		
	}else if (keyNum == 4) {
		DS1302_Time[TimeSetSelect] --;
		if (Is_Leap_Year(DS1302_Time[0]))
			Month_days[1] = 29;
		else
			Month_days[1] = 28;
		
		
		if (DS1302_Time[5] < 0 ) {DS1302_Time[5] = 59;}
		if (DS1302_Time[4] < 0 ) {DS1302_Time[4] = 59;}
		if (DS1302_Time[3] < 0 ) {DS1302_Time[3] = 23;}
		
		if (DS1302_Time[0] < 0) {DS1302_Time[0] = 99;}
		if (DS1302_Time[1] <= 0 ) {DS1302_Time[1] = 12;}
		
		if (DS1302_Time[2] <= Month_days[DS1302_Time[1] - 1]) {
			//riqihefa
			if (DS1302_Time[2] <= 0) {
				DS1302_Time[2] = Month_days[DS1302_Time[1] - 1];
			}
		}else {
			DS1302_Time[2] = Month_days[DS1302_Time[1] - 1];
		}
		
		
	}
	
	if (TimeSetSelect == 0 && TimeFlashFlag == 1) {
		LCD_ShowString(1, 1, "  ");
	}else {
		LCD_ShowNum(1,1,DS1302_Time[0],2);
	}
	
	if (TimeSetSelect == 1 && TimeFlashFlag == 1) {
		LCD_ShowString(1, 4, "  ");
	}else {
		LCD_ShowNum(1,4,DS1302_Time[1],2);
	}
	
	if (TimeSetSelect == 2 && TimeFlashFlag == 1) {
		LCD_ShowString(1, 7, "  ");
	}else {
		LCD_ShowNum(1,7,DS1302_Time[2],2);
	}
	
	if (TimeSetSelect == 3 && TimeFlashFlag == 1) {
		LCD_ShowString(2, 1, "  ");
	}else {
		LCD_ShowNum(2,1,DS1302_Time[3],2);
	}
	
	if (TimeSetSelect == 4 && TimeFlashFlag == 1) {
		LCD_ShowString(2, 4, "  ");
	}else {
		LCD_ShowNum(2,4,DS1302_Time[4],2);
	}
	
	if (TimeSetSelect == 5 && TimeFlashFlag == 1) {
		LCD_ShowString(2, 7, "  ");
	}else {
		LCD_ShowNum(2,7,DS1302_Time[5],2);
	}
	
	/*LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);*/
}




void main()
{
	DS1302_init();
	LCD_Init();
	Timer0_init();
	set_time();
	while (1) {
		
		// which 
		keyNum = getKeyNum();
		
		if (keyNum == 1) {
			MODE = !MODE;
			if (MODE == 0) set_time();
		}
		
		LCD_ShowNum(1, 10, MODE, 1);
		if (MODE == 0) {
			LCD_ShowNum(1, 13, MODE, 1);
			Time_Show();
		}else {
			Time_Set();
		}
	}
}

//interrupt1 to control falsh
void Timer0_Routine() interrupt 1
{
	static unsigned int T0_count;
	
	TL0 = 0x18;
	TH0 = 0xFC;
	
	T0_count ++;
	
	if (T0_count >= 500) {
		T0_count = 0;
		TimeFlashFlag = !TimeFlashFlag;
	}
}