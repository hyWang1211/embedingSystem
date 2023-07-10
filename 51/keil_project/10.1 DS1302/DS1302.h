#ifndef __DS1302_H__
#define __DS1302_H__

void DS1302_init();
void DS1302_Write(unsigned int Command, Data);
unsigned char DS1302_Read(unsigned char Command);
extern char DS1302_Time[];
void set_time();
void show_time();
#endif