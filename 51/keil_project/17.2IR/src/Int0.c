#include <REG52.H>

void Int0_init()
{
    IT0 = 1;        /*negative edge trigger*/
    IE0 = 0;
    EX0 = 1;
    EA = 1;
    PX0 = 1;
}