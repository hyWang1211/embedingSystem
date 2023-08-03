#include "stm32f10x.h"                  // Device header
#include "OLED.h"


int main()
{	
	OLED_Init();
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "HelloWorld!");
	OLED_ShowNum(2, 1, 666, 6);
	
	while (1) {
		
	}
}