#include "serial.h"
#include <REGX52.H>

void serial_init()
{
	//init SCON
	SCON = 0x50; 
	PCON |= 0x80;
	
	//init timer1;
	//init TMOD
	TMOD &= 0x0F;// clear high 4 bits
	TMOD |= 0x20;
	
	//init TCON
	TR1 =1;
	
	//IE init
	ET1 = 0;
	
	//
	TL1 = 0xF3;
	TH1 = 0xF3;
	
	//IE init
	EA = 1;
	ES = 1;
	
}

void serial_send(unsigned char Byte)
{
	SBUF = Byte;
	
	while(TI == 0);
	TI = 0;
}