#include <REG52.H>
#include "Delay.h"
sbit p24 = P2^4;
sbit p23 = P2^3;
sbit p22 = P2^2;

unsigned char Nixie_buf[9] = {0, 10, 10, 10, 10, 10, 10, 10, 10};
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x40};

void show_num(unsigned char location, number)
{
	Nixie_buf[location] = number;
}

void Nixie_Scan(unsigned char Location,Number)
{
	P0=0x00;				//段码�?0，消�?
	switch(Location)		//位码输出
	{
		case 1:p24=1;p23=1;p22=1;break;
		case 2:p24=1;p23=1;p22=0;break;
		case 3:p24=1;p23=0;p22=1;break;
		case 4:p24=1;p23=0;p22=0;break;
		case 5:p24=0;p23=1;p22=1;break;
		case 6:p24=0;p23=1;p22=0;break;
		case 7:p24=0;p23=0;p22=1;break;
		case 8:p24=0;p23=0;p22=0;break;
	}
	P0=NixieTable[Number];	//段码输出
	
}


void Nixie_Loop()
{
	static unsigned char i = 1;
	Nixie_Scan(i, Nixie_buf[i]);

	i ++;
	if (i == 9) i = 1;
}
