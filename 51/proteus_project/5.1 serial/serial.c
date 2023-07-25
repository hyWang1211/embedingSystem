#include <regx52.h>

void serial_init()
{
	SCON = 0x50;
	PCON = 0x80;
	
	//IE
	EA = 1;
	ES = 1;
}

void timer1_init()
{
	//TCON
	TF1 = 0;
	TR1 = 1;
	
	//IE
	ET1 = 0;
	EA = 1;
	
	//TMOD
	TMOD &= 0x0F;
	TMOD |= 0x20;
	
	//
	TH1 = TL1 = 0xFA;
}

void send_byte(unsigned char Byte)
{
	SBUF = Byte;
	
	while(TI == 0);
	TI = 0;
}