#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "SensorCounter.h"
#include "Encoder.h"
uint16_t sensor_count = 0;

uint16_t Get_SensorCount(void);

int main()
{	
	OLED_Init();
	OLED_ShowString(1, 1, "Counter: ");
	Sensor_Init();
	Encoder_Init();
	while (1) {
		OLED_ShowNum(1, 9, Get_SensorCount(), 5);
	}
}


uint16_t Get_SensorCount(void)
{
	return sensor_count;
}