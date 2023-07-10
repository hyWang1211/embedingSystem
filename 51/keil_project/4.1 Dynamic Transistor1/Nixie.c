#include <REGX52.H>
#include "Delay.h"

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
		case 1:P2_4 = 0; P2_3 = 0; P2_2 = 0;break;
		case 2:P2_4 = 0; P2_3 = 0; P2_2 = 1;break;
		case 3:P2_4 = 0; P2_3 = 1; P2_2 = 0;break;
		case 4:P2_4 = 0; P2_3 = 1; P2_2 = 1;break;
		case 5:P2_4 = 1; P2_3 = 0; P2_2 = 0;break;
		case 6:P2_4 = 1; P2_3 = 0; P2_2 = 1;break;
		case 7:P2_4 = 1; P2_3 = 1; P2_2 = 0;break;
		case 8:P2_4 = 1; P2_3 = 1; P2_2 = 1;break;
	}
	
	P0 = NixieTable[number];
	Delay(1);
	P0 = 0x00;
}