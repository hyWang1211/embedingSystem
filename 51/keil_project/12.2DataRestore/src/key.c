#include <REG52.H>
#include "key.h"
#include "delay.h"
sbit Btn1 = P3^1;
sbit Btn2 = P3^0;
sbit Btn3 = P3^2;
sbit Btn4 = P3^3;
unsigned char key_num = 0;

unsigned char gey_Num()
{
	unsigned char temp;
	temp = key_num;
	key_num = 0;
	return temp;
}

unsigned char get_state()
{
	unsigned char keyNum = 0;
	if (Btn1 == 0) {keyNum = 1;}
	if (Btn2 == 0) {keyNum = 2;}
	if (Btn3 == 0) {keyNum = 3;}
	if (Btn4 == 0) {keyNum = 4;}
	
	return keyNum;
}

void get_key_num()
{
	static unsigned char last_state = -1, cur_state = -1;
	last_state = cur_state;
	cur_state = get_state();

	if (last_state == 1 && cur_state == 0)
		key_num = 1;
	if (last_state == 2 && cur_state == 0)
		key_num = 2;
	if (last_state == 3 && cur_state == 0)
		key_num = 3;
	if (last_state == 4 && cur_state == 0)
		key_num = 4;
}