#include <REGX52.H>
#include "timer.h"
#include "key.h"
#include <INTRINS.H>

unsigned int T_count;
unsigned char key = 0;
unsigned char LEDMOD = 0;

void main()
{
	P2 = 0xFE; // D1 light
	Timer0_init();
	while (1) {
		key = getKeyNum(); // 1 left, 0 right
		if (key) {
			LEDMOD = key % 2;
		}
	}
}

void Timer0_Routine() interrupt 1
{
	TL0 = 64536 % 256;
	TH0 = 64536 / 256;
	T_count++;
	
	if (T_count >= 1000) {
		if (LEDMOD == 0) {
			P2 = _crol_(P2, 1);
		}else {
			P2 = _cror_(P2, 1);
		}
		T_count = 0;
	}
	
}