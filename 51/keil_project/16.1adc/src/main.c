#include <REG52.H>
#include "xtp2046.h"
#include "LCD1602.h"
#include "Delay.h"

#define ADDR_AIN0 0x9C    //x+ 0BC
#define ADDR_AIN1 0xDC    //y+ 
#define ADDR_VBAT 0xAC    //vbat
#define ADDR_AUX  0xEC    //aux

unsigned int ad_value;
void main()
{
    LCD_Init();
    LCD_ShowString(1, 1, "ad_value:");
    while(1) {
        ad_value = xtp2046_adc(ADDR_AIN0);
        LCD_ShowNum(1, 10, ad_value, 3);
        Delay(500);
    }
}

