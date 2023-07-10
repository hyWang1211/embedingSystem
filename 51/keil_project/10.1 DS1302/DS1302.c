#include "DS1302.h"
#include <REGX52.H>
#include "LCD1602.h"
sbit DS1302_CE = P3^5;
sbit DS1302_IO = P3^4;
sbit DS1302_SCLK = P3^6;

//read or write addr
#define DS1302_SEC 0x80			//second
#define DS1302_MIN 0x82			//minute
#define DS1302_HOUR 0x84		//houre
#define DS1302_DATE 0x86		//datatime
#define DS1302_MONTH 0x88		//month
#define DS1302_DAY 0x8A			//day
#define DS1302_YEAR 0x8C		//year
#define DS1302_WP 0x8E			//open write?

unsigned char DS1302_Addrr[] = {
	DS1302_YEAR,
	DS1302_MONTH,
	DS1302_DATE,
	DS1302_HOUR,
	DS1302_MIN,
	DS1302_SEC,
	DS1302_DAY,
};

//current time
char DS1302_Time[] = {
	23,
	12,
	31,
	10,
	38,
	23,
	3
};

void DS1302_init()
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

void DS1302_Write(unsigned char Command, Data)
{
	unsigned char i;
	DS1302_CE = 1;
	for (i = 0; i < 8; i ++) {
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		//LCD_ShowNum(1, 8 - i, DS1302_IO, 1);
	}
	
	for (i = 0; i < 8; i ++) {
		
		DS1302_IO = Data & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;	
		//LCD_ShowNum(1, 8 - i, DS1302_IO, 1);
	}
	DS1302_CE = 0;
}

unsigned char DS1302_Read(unsigned char Command)
{
	unsigned char i;
	unsigned char clk_data = 0x00;
	unsigned char temp;
	Command |= 0x01;
	DS1302_CE = 1;
	
	for (i = 0; i < 8; i ++) {
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		//LCD_ShowNum(1, 8 - i, DS1302_IO, 1);
	}
	
	for (i = 0; i < 8; i ++ ){
		temp = DS1302_IO;
		clk_data  = (temp << 7) | (clk_data >> 1);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	DS1302_CE = 0;
	DS1302_IO = 0;
	return clk_data;
}


unsigned char dec2bcd(unsigned char dec)
{
	return dec / 10 * 16 + dec % 10;
}

unsigned char bcd2dec(unsigned char bcd)
{
	return bcd / 16 * 10 + bcd % 16;
}


/**
* @brief set current time
* @param
* @retval
*/
void set_time()
{
	unsigned char i;
	DS1302_Write(DS1302_WP, 0x00); //allow write
	
	for ( i = 0; i < 7; i ++) {
		DS1302_Write(DS1302_Addrr[i], dec2bcd(DS1302_Time[i]));
	}
	
	DS1302_Write(DS1302_WP, 0x80); //forbid write
}

void show_time()
{
	unsigned char i;
	for ( i = 0; i < 7; i ++) {
		DS1302_Time[i] = bcd2dec(DS1302_Read(DS1302_Addrr[i]));
	}
}

