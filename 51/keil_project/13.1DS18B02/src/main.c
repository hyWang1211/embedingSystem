#include "REG52.H"
#include "DS18B20.h"
#include "LCD1602.h"
#include "delay.h"
#include "key.h"
#include "AT24C02.h"
#include "timer.h"
float T;
char TL = 20, TH = 30;
unsigned char keyNum;
void main()
{
    TL = AT24C02_Read(0);
    TH = AT24C02_Read(1);
    LCD_Init();
    Timer0_init();
    LCD_ShowString(1, 1, "TEMP: ");
    LCD_ShowString(2, 1, "TL:");
    LCD_ShowString(2, 10, "TH:");
    LCD_ShowSignedNum(2, 4, TL, 3);
    LCD_ShowSignedNum(2, 13, TH, 3);
    // temperature_change();
    // Delayxms(1000);
    while(1) {
        keyNum = gey_Num();
        
        temperature_change();
        T = temperature_read();
        if (T < 0) {
            LCD_ShowChar(1, 7, '-');
            T = -T;
        }else {
            LCD_ShowChar(1, 7, '+');
        }

        LCD_ShowNum(1, 8, T, 2);
        LCD_ShowChar(1, 10, '.');
        LCD_ShowNum(1, 11, (unsigned long)(T *10000) % 10000, 4);
        
        if (keyNum) {
            if (keyNum == 1) {
                TL ++;
            }
            
            if (keyNum == 2) {
                TL --;
            }

            
            if (keyNum == 3) {
                TH ++;
            }

            
            if (keyNum == 4) {
                TH --;
            }
            LCD_ShowSignedNum(2, 4, TL, 3);
            AT24C02_Write(0, TL);
            Delayxms(5);
            
            LCD_ShowSignedNum(2, 13, TH, 3);
            AT24C02_Write(1, TH);
            Delayxms(5);
        } 
    }
}

void timer0_Routine() interrupt 1
{
	static unsigned int T_count;
	TL0 = 0x18;
	TH0 = 0xFC;
	T_count ++;
	if (T_count >= 20) {
		T_count = 0;
		get_key_num(); // each 20ms detect one time
	}
}

