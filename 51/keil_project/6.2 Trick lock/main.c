#include <REGX52.H>
#include "matrix.h"
#include "LCD1602.h"
#include "delay.h"

unsigned int keyNum;
unsigned char count;
unsigned int password;
unsigned int truePwd = 1234;
void main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "Hello");
	while (1) {
		keyNum = getMatrixNum();
		
		if (keyNum && keyNum <= 10 && count < 4) {			
			password = password * 10 + keyNum % 10;
			LCD_ShowNum(2, 1, password, 4);
			count ++;
		}
		
		if (keyNum == 11) {
			if (password == truePwd) {
				LCD_ShowString(1, 10, "OK ");
				password = 0;
				count = 0;
				LCD_ShowNum(2, 1, password, 4);
			}else {
				LCD_ShowString(1, 10, "ERR");
				password = 0;
				count = 0;
				LCD_ShowNum(2, 1, password, 4);
			}
		}
		
		if (keyNum == 12) {
			password = 0;
			count = 0;
			LCD_ShowNum(2, 1, password, 4);
		}
	}
}