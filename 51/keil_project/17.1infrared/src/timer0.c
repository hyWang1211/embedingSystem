#include <REG52.H>

void Timer0_Init(void)		//100微秒@11.0592MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式

	TF0 = 0;				//清除TF0标志
	TR0 = 0;				//定时器0开始计时
}

/**
 * 设置定时时长
*/
void Timer0_Init_set_counter(unsigned int variable)
{
    TL0 = variable % 256;				//设置定时初始值
	TH0 = variable / 256;	            //设置定时初始值
}

unsigned int Timer0_Init_get_counter(void)
{
    return (TH0 << 8) | TL0;
}


void Timer0_control(unsigned char flag)
{
    TR0 = flag;
}


