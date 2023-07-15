#include <REG52.H>
#include "Delay.h"
sbit p24 = P2^4;
sbit p23 = P2^3;
sbit p22 = P2^2;

void Nixie(unsigned char Location, number)
{
	unsigned char NixieTable[]={
	0x3F,  //"0"
    0x06,  //"1"
    0x5B,  //"2"
    0x4F,  //"3"
    0x66,  //"4"
    0x6D,  //"5"
    0x7D,  //"6"
    0x07,  //"7"
    0x7F,  //"8"
    0x6F,  //"9"
    0x77,  //"A"
    0x7C,  //"B"
    0x39,  //"C"
    0x5E,  //"D"
    0x79,  //"E"
    0x71,  //"F"
    0x76,  //"H"
    0x38,  //"L"
    0x37,  //"n"
    0x3E,  //"u"
    0x73,  //"P"
    0x5C,  //"o"
    0x40,  //"-"
    0x00  //??
	};

	switch(Location) {
		case 1:p24 = 0; p23 = 0; p22 = 0;break;
		case 2:p24 = 0; p23 = 0; p22 = 1;break;
		case 3:p24 = 0; p23 = 1; p22 = 0;break;
		case 4:p24 = 0; p23 = 1; p22 = 1;break;
		case 5:p24 = 1; p23 = 0; p22 = 0;break;
		case 6:p24 = 1; p23 = 0; p22 = 1;break;
		case 7:p24 = 1; p23 = 1; p22 = 0;break;
		case 8:p24 = 1; p23 = 1; p22 = 1;break;
	}
	
	P0 = NixieTable[number];
	Delay(1);
	P0 = 0x00;
}