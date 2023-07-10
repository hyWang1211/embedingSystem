#include <REGX52.H>
#include "matrix.h"
#include "LCD1602.h"
#include "delay.h"

unsigned char keyNum;
void main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "Hello");
	while (1) {
		keyNum = getMatrixNum();
		if (keyNum) {
			LCD_ShowNum(2, 1, keyNum, 2);
		}
		
	}
}