#include <REG52.H>
#include "delay.h"

sbit DS18B20_DQ = P3^7;

unsigned char DS18B20_Init()
{
    unsigned char data i;
    unsigned char Ack;
    DS18B20_DQ = 1;
    DS18B20_DQ = 0;

    //delay 500us
    i = 227;
	while (--i);

    DS18B20_DQ = 1;

    i = 29;
	while (--i);

    Ack = DS18B20_DQ;

    //delay500us
    i = 227;
	while (--i);

    return Ack;
}

void DS18B20_Write(unsigned char bit)
{
    unsigned char data i;
    DS18B20_DQ = 0;

    /*delay 10us*/
    i = 3;
	while (--i);

    DS18B20_DQ = bit;

    /*delay 50us*/
    i = 22;
	while (--i);
    DS18B20_DQ = 1;
}

unsigned char DS18B20_Read()
{
    unsigned char data i;
    unsigned char rev;
    DS18B20_DQ = 0;

    /*delay 5us*/
    i = 2;
	while (--i);

    /*release*/
    DS18B20_DQ = 1;

    /*delay 5us*/
    i = 2;
	while (--i);


    rev = DS18B20_DQ;

    /*delay 50us*/
    i = 22;
	while (--i);

    return rev;
}