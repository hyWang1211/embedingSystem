#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void LED_light();

int main(void)
{
	//open GPIOA's clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//Init GPIO
	GPIO_InitTypeDef* GPIO_InitStruct;
	GPIO_InitStruct->GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct->GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStruct->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, GPIO_InitStruct);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	
	while (1) {
 
		LED_light();
	}
}

void LED_light()
{
	unsigned char i = 0;
	
	for (i = 0; i < 8; i ++) {
		GPIO_Write(GPIOA, ~(0x0001 << i));
		Delay_ms(300);
	}
}