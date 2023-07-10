#include <REGX52.H>
#include "key.h"
#include "delay.h"
unsigned char getKeyNum()
{
	unsigned char keyNum = 0;
	if (P3_1 == 0) {Delayxms(20); while (P3_1 == 0); Delayxms(20); keyNum = 1;}
	if (P3_0 == 0) {Delayxms(20); while (P3_0 == 0); Delayxms(20); keyNum = 2;}
	if (P3_2 == 0) {Delayxms(20); while (P3_2 == 0); Delayxms(20); keyNum = 3;}
	if (P3_3 == 0) {Delayxms(20); while (P3_3 == 0); Delayxms(20); keyNum = 4;}
	
	return keyNum;
}