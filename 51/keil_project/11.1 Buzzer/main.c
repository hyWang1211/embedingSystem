#include <REGX52.H>
#include "delay.h"
#include "key.h"
#include "Nixie.h"
#include "Buzzer_Time.h"


void main()
{
	unsigned char keyNum = 0, i = 0;
	Nixie(1, 0);
	while(1) {
		keyNum = getKeyNum();
		if (keyNum) {
			Nixie(1, keyNum);
			Buzzer_Time(100);
		}
		
			
	}
}