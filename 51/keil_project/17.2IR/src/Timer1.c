#include <REG52.H>
#include "Timer1.h"

void Timer1_init()
{
    /*TMOD config*/
    TMOD &= 0x0F;
    TMOD |= 0x10;

    /*TCON config*/
    TF1 = 0;
    TR1 = 1;

    /*Time config*/
    TL1 = 0xA4;
    TH1 = 0xFF;

    /*External interrupt config*/
    ET1 = 1;
    PT1 = 0;
    EA = 1;
}
