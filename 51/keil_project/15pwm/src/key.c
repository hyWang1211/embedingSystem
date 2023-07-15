#include <REG52.H>
#include "key.h"
#include "Delay.h"

sbit p30 = P3^0;
sbit p31 = P3^1;
sbit p32 = P3^2;
sbit p33 = P3^3;
unsigned char getKeyNum()
{
	unsigned char keyNum = 0;
	if (p31 == 0) {Delay(20); while (p31 == 0); Delay(20); keyNum = 1;}
	if (p30 == 0) {Delay(20); while (p30 == 0); Delay(20); keyNum = 2;}
	if (p32 == 0) {Delay(20); while (p32 == 0); Delay(20); keyNum = 3;}
	if (p33 == 0) {Delay(20); while (p33 == 0); Delay(20); keyNum = 4;}
	
	return keyNum;
}