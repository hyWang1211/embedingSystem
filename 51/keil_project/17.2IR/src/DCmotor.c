#include <REG52.H>

sbit DC_Motor = P1^0;
unsigned char speed;
unsigned char T1_count;


void DC_set_speed(unsigned char spd)
{
    speed = spd;
}

void Timer1_routine() interrupt 3
{
    TL1 = 0xA4;
    TH1 = 0xFF;
    T1_count ++;

    T1_count %= 100;
    if (speed > T1_count) DC_Motor = 1;
    else DC_Motor = 0;
}

