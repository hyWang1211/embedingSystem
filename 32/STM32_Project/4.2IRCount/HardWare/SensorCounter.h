#ifndef __SENSORCOUNTER_H__
#define __SENSORCOUNTER_H__
#include "stm32f10x.h"                  // Device header

void Sensor_Init(void);
uint16_t Get_SensorCount(void);

#endif