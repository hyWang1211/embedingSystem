#include <REG52.H>
#include "IR.h"
#include "LCD1602.h"
#include "DCmotor.h"
#include "Timer1.h"

unsigned char command, addr;

#define IR_0 0x16
#define IR_1 0x0C
#define IR_2 0x18
#define IR_3 0x5E

void main()
{
    LCD_Init();
    IR_init();

    Timer1_init();
    while (1) {
        if (IR_get_data_flag()) {
            command = IR_get_command();
            addr = IR_get_addr();
            LCD_ShowHexNum(2, 1, command, 4);
            LCD_ShowHexNum(2, 6, addr, 4);
            if (command == IR_0) DC_set_speed(0);
            else if(command == IR_1) DC_set_speed(30);
            else if(command == IR_2) DC_set_speed(50);
            else if (command == IR_3) DC_set_speed(80);
        }
    }
}