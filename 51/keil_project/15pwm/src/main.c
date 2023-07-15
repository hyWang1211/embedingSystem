#include <REG52.H>
#include <timer.h>
// #include "Nixie.h"
#include "LCD1602.h"
#include "Delay.h"
unsigned char Counter, Compare;
unsigned char key, speed;
sbit Motor = P2^0;

void main()
{
    unsigned char i;
    Compare = 0;
    LCD_Init();
    Timer0_init();
    
    while (1) {
        // key = getKeyNum();

        // if (key == 4) {
        //     speed ++;
        //     speed %= 4;

        //     if (speed == 0) Compare = 0;
        //     if (speed == 1) Compare = 25;
        //     if (speed == 2) Compare = 40;
        //     if (speed == 3) Compare = 50;
            
        // }
        // LCD_ShowNum(1, 1, speed, 2);
        // LCD_ShowNum(2, 1, Compare, 3);

        for (i = 0; i < 100; i ++) {
            Compare = i;
            Delay(8);
        }

        for (i = 100; i > 0; i --){
            Compare = i;
            Delay(10);
        }

    }
}


void Timer0_Routine() interrupt 1
{
    TL0 = 0xA4;
	TH0 = 0xFF;
    Counter ++;
    
    if (Counter >= 100) Counter = 0;
    
    if (Counter < Compare) Motor = 1;
    else Motor = 0;
    // Motor = Counter <= Compare ?0: 1;
}

