#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0_init();
void Timer0_run(unsigned char flag);
void Timer0_setTime(unsigned char time_value);
unsigned int Timer0_getTime();

#endif