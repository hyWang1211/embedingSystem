#include "SensorCounter.h"
#include "stm32f10x.h"                  // Device header
extern uint16_t sensor_count;

void Sensor_Init()
{
	//enable GPIO and AFIO's clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//Init GPIO
	GPIO_InitTypeDef GPIO_Init_Struct;
	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_Init_Struct);
	
	//Init AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	//Init EXTI
	EXTI_InitTypeDef EXIT_InitStruct;
	EXIT_InitStruct.EXTI_Line = EXTI_Line14;
	EXIT_InitStruct.EXTI_LineCmd = ENABLE;
	EXIT_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXIT_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&EXIT_InitStruct);
	
	//Init NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI15_10_IRQHandler(void)
{
	//judge source
	if (EXTI_GetITStatus(EXTI_Line14) == SET) {
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0){
			sensor_count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
