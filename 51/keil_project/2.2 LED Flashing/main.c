#include <REGX52.H>
#include <INTRINS.H>

void delay(unsigned int xms)
{
	unsigned char i, j;
	while (xms --) {
		i = 2;
		j = 239;
		
		do {
			while (--j);
		}while (i --);
	
	}
}
void main()
{
	while(1) {
		//light
		P2 = 0xFE;
		delay(500);
		//delay 500ms
		
		//unlight
		P2 = 0xFD;
		delay(500);
		
		P2 = 0xFB;
		delay(500);
		
		P2 = 0xF7;
		delay(500);
		
		P2 = 0xEF;
		delay(500);
		
		P2 = 0xDF;
		delay(500);
		
		P2 = 0xBF;
		delay(500);
		
		P2 = 0x7F;
		delay(500);
	}
}