#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0_Init(void);
void Timer0_Init_set_counter(unsigned int variable);
unsigned int Timer0_Init_get_counter(void);
void Timer0_control(unsigned char flag);

#endif