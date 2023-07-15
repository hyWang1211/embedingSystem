#include "IR.h"
#include "Timer0.h"
#include "Int0.h"
#include <REG52.H>

unsigned char IR_state;
unsigned int IR_time;
unsigned char IR_repeat;
unsigned char IR_data[4];
unsigned char IR_pdata;
unsigned char IR_data_flag;
unsigned char IR_command, IR_addr;



void IR_init()
{
    Timer0_init();
    Int0_init();
}

unsigned char IR_get_data_flag()
{
    unsigned char temp = IR_data_flag;
    IR_data_flag = 0;
    return temp;
}

unsigned char IR_get_repeat_flag()
{
    unsigned char temp = IR_repeat;
    IR_repeat = 0;
    return temp;
}

unsigned char IR_get_command()
{
    return IR_command;
}

unsigned char IR_get_addr()
{
    return IR_addr;
}

void IR_routine() interrupt 0
{
    if (IR_state == 0) {
        Timer0_setTime(0);
        Timer0_run(1);
        IR_state = 1;
    }else if (IR_state == 1) {
        IR_time = Timer0_getTime();
        Timer0_setTime(0);
        
        if (IR_time > 12442 - 500 && IR_time < 12442 + 500) {
            
            IR_state = 2;
        }else if (IR_time > 10368 - 500 && IR_time < 10368 + 500) {
            IR_repeat = 1;
            IR_state = 0;
        }else {
            //IR_state = 1;
        }
    }else if (IR_state == 2) {
        // P2 = 0;
        IR_time = Timer0_getTime();
        Timer0_setTime(0);

        if (IR_time > 1032 - 500 && IR_time < 1032 + 500) {
            IR_data[IR_pdata / 8] &= ~(0x01 << (IR_pdata % 8));
            IR_pdata ++;
        }else if (IR_time > 2074 - 500 && IR_time < 2074 + 500) {
            IR_data[IR_pdata / 8] |= (0x01 << (IR_pdata % 8));
            IR_pdata ++;
        }else {
            IR_state = 1;
            IR_pdata = 0;
        }

        

        if (IR_pdata >= 32 && IR_data[0] == ~IR_data[1] && IR_data[2] == ~IR_data[3]) {
            // P2 = 0;
            Timer0_run(0);
            IR_state = 0;
            IR_data_flag = 1;
            IR_pdata = 0;
            IR_addr = IR_data[0];
            IR_command = IR_data[2];
        }

    }
}


