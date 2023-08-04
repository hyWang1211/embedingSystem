#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Timer.h"
uint16_t sensor_count = 0;
uint16_t Timer_Count = 0;
int main()
{	
	OLED_Init();
	Timer2_Init1();
	OLED_ShowString(1, 1, "I Time: ");
	OLED_ShowString(2, 1, "C Time: ");
	while (1) {
		OLED_ShowNum(1, 9, TIM_GetCounter(TIM2), 5);
		
		OLED_ShowNum(2, 9, Timer_Count, 5);
	}
}
