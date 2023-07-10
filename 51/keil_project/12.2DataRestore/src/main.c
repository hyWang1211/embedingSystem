#include "AT24C02.h"
#include "LCD1602.h"
#include <REG52.H>
#include "delay.h"
#include "timer.h"
#include "key.h"
#include "Nixie.h"

unsigned char Min, Sec, MiniSec, runFlag;

void main()
{
	unsigned char num;
	unsigned char temp = 0;
	LCD_Init();
	LCD_ShowString(2, 1, "hello");
	Timer0_init();
	//P2 = 0;
	//AT24C02_Write(0, 66);
	//Delayxms(5);
	//Data = AT24C02_Read(0);
	//if (Data == 66) P2 = 0;

	while (1) {
		num = gey_Num();

		if (num == 1) {
			runFlag = !runFlag;
		}

		if (num == 2) {
			Min = 0;
			Sec = 0;
			MiniSec = 0;
		}

		//write
		if (num == 3) {
			AT24C02_Write(0, Min);
			Delayxms(5);
			AT24C02_Write(1, Sec);
			Delayxms(5);
			AT24C02_Write(2, MiniSec);
			Delayxms(5);
		}

		//read
		if (num == 4) {
			Min = AT24C02_Read(0);
			Sec = AT24C02_Read(1);
			MiniSec = AT24C02_Read(2);
		}
		

		show_num(1, Min / 10);
		show_num(2, Min % 10);
		show_num(3, 11);
		show_num(4, Sec / 10);
		show_num(5, Sec % 10);
		show_num(6, 11);
		show_num(7, MiniSec / 10);
		show_num(8, MiniSec % 10);
	}
}

void Sec_Loop()
{
	if (runFlag) {
		MiniSec ++;

		if (MiniSec >= 100) {
			Sec ++;
			MiniSec = 0;

			if (Sec >= 60) {
				Min ++;
				Sec = 0;

				if (Min >= 60) {
					Min = 0;
				}	
			}
		}
	}
}

void timer0_Routine() interrupt 1
{
	static unsigned int T_count, T_count2, T_count3;
	TL0 = 0x18;
	TH0 = 0xFC;
	T_count ++;
	T_count2 ++;
	T_count3 ++;
	if (T_count >= 20) {
		T_count = 0;
		get_key_num(); // each 20ms detect one time
	}

	if (T_count2 >= 2) {
		T_count2 = 0;
		Nixie_Loop();
	}

	if (T_count3 >= 10) {
		T_count3 = 0;
		Sec_Loop();
	}

}