#include <regx52.h>
#include "LCD1602.h"

void main()
{
	P2 = 0;
	LCD_Init();
	LCD_ShowNum(1, 1, 12, 3);
	while (1) {};
}