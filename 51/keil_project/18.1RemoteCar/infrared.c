#include "infrared.h"
#include <REG52.H>
#include "int0.h"
#include "timer0.h"

unsigned char IR_state;                 /*last IR_state*/
unsigned int IR_time;                   /*duration of negative edge*/
unsigned char IR_data[4];               /*store the final data*/
unsigned char IR_pdata;                 /*point to each bit of data, from 0 to 31*/
unsigned char IR_data_flag;             /*complete data or not*/
unsigned char IR_repeat_flag;           /*repeat state*/
unsigned char IR_addr, IR_command;      /*data format*/

void infrared_init()
{
    Int0_init();
    Timer0_Init();
}

unsigned char IR_get_data_flag()
{
    unsigned char temp = IR_data_flag;
    IR_data_flag = 0;
    return temp;
}

unsigned char IR_get_repeat_flag()
{
    unsigned char temp = IR_repeat_flag;
    IR_repeat_flag = 0;
    return temp;
}

unsigned char IR_get_data_addr()
{
    return IR_addr;
}

unsigned char IR_get_data_command()
{
    return IR_command;
}

 
void int0_routine() interrupt 0
{
    if (IR_state == 0) {
        // P2 = 0;
        Timer0_Init_set_counter(0);     /*clear time*/
        Timer0_control(1);              /*start counting*/
        IR_state = 1;                      /**over spare time*/
    }else if (IR_state == 1) {
        // P2 =0;
        IR_time = Timer0_Init_get_counter();   /*The duration of IR_state 1*/
        Timer0_Init_set_counter(0);

        if (IR_time > 12442 - 500 && IR_time < 12442 + 500) {         /*demonstrate last IR_state 1 is start IR_state*/
            // P2 = 0;
            IR_state = 2;                  /*update next IR_state*/
            
        }else if (IR_time > 10368 - 500 && IR_time < 10368 + 500) {   /*demonstrate last IR_state 1 is repeat IR_state*/
            // P2 = 0;
            IR_repeat_flag = 1;
            IR_state = 0;                  /*enter spare time*/
        }else {
            // P2 = 0;
            IR_state = 1;
        }

    }else if (IR_state == 2) {             /*data transmission IR_state*/
        // P2 = 0;
        IR_time = Timer0_Init_get_counter();
        Timer0_Init_set_counter(0);

        if (IR_time > 1032-500 && IR_time < 1032 + 500) {       /*data 0*/
            // P2 = 0;
            /*store data 0 to IR_data*/
            // IR_state = 2;

            /**
             * IR_pdata / 8: Which byte is locked
             * IR_pdata % 8): Which bit is locked in above byte
             * X&= ~(0x01) means set the first bit of X to zero
            */
            IR_data[IR_pdata / 8] &= ~(0x01 << (IR_pdata % 8));
            IR_pdata ++;
        }else if (IR_time > 2074 - 500 && IR_time < 2074 + 500) {   /*data 1*/
            // IR_state = 2;

            IR_data[IR_pdata / 8] |= (0x01 << (IR_pdata % 8));
            IR_pdata++;
        }else {
            IR_pdata = 0;
            IR_state = 1;
        }

        if (IR_pdata >= 32) {
            // P2 = 0;  
            // IR_state = 0;
            IR_pdata = 0;
            if (IR_data[0] == ~IR_data[1] && IR_data[2] == ~IR_data[3]) {
                IR_addr = IR_data[0];
                IR_command = IR_data[2];
                IR_data_flag = 1;
            }

            Timer0_control(0);
            IR_state = 0;
        }
    }
}