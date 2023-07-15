#include <REG52.H>

void Timer0_Init(void)		//100΢��@11.0592MHz
{
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ

	TF0 = 0;				//���TF0��־
	TR0 = 0;				//��ʱ��0��ʼ��ʱ
}

/**
 * ���ö�ʱʱ��
*/
void Timer0_Init_set_counter(unsigned int variable)
{
    TL0 = variable % 256;				//���ö�ʱ��ʼֵ
	TH0 = variable / 256;	            //���ö�ʱ��ʼֵ
}

unsigned int Timer0_Init_get_counter(void)
{
    return (TH0 << 8) | TL0;
}


void Timer0_control(unsigned char flag)
{
    TR0 = flag;
}


