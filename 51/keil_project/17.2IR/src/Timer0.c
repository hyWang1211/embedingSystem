#include <REG52.H>

void Timer0_init()
{
    TMOD &= 0xF0;
    TMOD |= 0x01;

    TF0 = 0;
    TR0 = 0;
}

void Timer0_run(unsigned char flag)
{
    TR0 = flag;
}

void Timer0_setTime(unsigned char time_value)
{
    TL0 = time_value % 256;
    TH0 = time_value / 256;
}

unsigned int Timer0_getTime()
{
    return (TH0 << 8) | TL0;
}


