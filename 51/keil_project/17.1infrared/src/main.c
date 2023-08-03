#include <REG52.H>
#include "infrared.h"
#include "LCD1602.h"
#include "Delay.h"
#include "timer0.h"

unsigned char adr;
unsigned char cmd;
unsigned int time;
sbit p20 = P2^0;
void main()
{
    p20 = 0;
    LCD_Init();
    infrared_init();
    LCD_ShowString(1, 1, "Infradred Test");
    while (1) {
        if (IR_get_data_flag()) {
            adr = IR_get_data_addr();
            cmd = IR_get_data_command();

            LCD_ShowHexNum(2, 1, adr, 4);
            LCD_ShowHexNum(2, 6, cmd, 4);
        }
    }
}
