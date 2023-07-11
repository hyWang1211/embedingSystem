#include <REG52.H>
#include "delay.h"

sbit DS18B20_DQ = P3^7;

unsigned char DS18B20_Init()
{
    unsigned char data i;
    unsigned char Ack;
    EA = 0;
    
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
    EA = 1;

    return Ack;
}

void DS18B20_Write(unsigned char bbit)
{
    unsigned char data i;
    DS18B20_DQ = 0;
    EA = 0;
    

    /*delay 10us*/
    i = 3;
	while (--i);

    DS18B20_DQ = bbit;

    /*delay 50us*/
    i = 22;
	while (--i);
    DS18B20_DQ = 1;
    EA = 1;
}

unsigned char DS18B20_Read()
{
    unsigned char data i;
    unsigned char rev;
    EA = 0;
    
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
    EA = 1;
    return rev;

}

/**
 * send one byte
*/
void DS18B20_Send(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DS18B20_Write(byte&(0x01<<i));
	}
}

/**
 * receive one byte
 * 
*/
unsigned char DS18B20_recv()
{
	unsigned char i;
	unsigned char Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(DS18B20_Read()){Byte|=(0x01<<i);}
	}
	return Byte;
}

/**
 * temperature change
*/

void temperature_change()
{
    DS18B20_Init();
    DS18B20_Send(0xcc);
    DS18B20_Send(0x44);
}

float temperature_read()
{
    unsigned char LSB, MSB;
    int Temp;
    float T;
    DS18B20_Init();
    DS18B20_Send(0xcc);
    DS18B20_Send(0xBE);
    LSB = DS18B20_recv();
    MSB = DS18B20_recv();
    Temp = (MSB << 8) | LSB;
    T = Temp / 16.0;

    return T;
}