#include "stm32f10x.h"                  // Device header


void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

void LED_State(uint8_t LED_Num, uint8_t LED_Light)
{
	if (LED_Num == 1 && LED_Light == 0) {
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	
	if (LED_Num == 1 && LED_Light == 1) {
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
	
	if (LED_Num == 2 && LED_Light == 0) {
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
	
	if (LED_Num == 2 && LED_Light == 1) {
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
}