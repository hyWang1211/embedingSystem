#ifndef _DS18B20_H__
#define _DS18B20_H__

unsigned char DS18B20_Init();
void DS18B20_Write();
void DS18B20_Send(unsigned char byte);
unsigned char DS18B20_recv();
void temperature_change();
float temperature_read();
#endif
