#ifndef __LIGHT_SENSOR_H__
#define __LIGHT_SENSOR_H__
#include "stm32f10x.h"                  // Device header

void Light_Sensor_Init();
uint8_t LightSensor_Get(void);

#endif