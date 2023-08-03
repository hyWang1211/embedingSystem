#include "LED.h"
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"

uint8_t key_num;
uint8_t state1 = 0, state2 = 0;

int main()
{
	LED_Init();
	Key_Init();
	Buzzer_Init();
	Light_Sensor_Init();
	
	while (1) {
		key_num = Key_GetNum();
		
		if ( key_num == 1) {
			state1 = !state1;
			LED_State(1, state1);
		}
		
		if (key_num == 2) {
			state2 = !state2;
			LED_State(2, state2);
		}
		
		if (LightSensor_Get() == 1) {
			Buzzer_On();
		}else {
			Buzzer_Off();
		}
		
	}
}