#include "delay.h"
#include <REGX52.H>
#include "matrix_led.h"

sbit RCK = P3^5;
sbit SCK = P3^6;
sbit SER = P3^4;

#define MATRIX_LED_PORT P0

/**
* @brief select line(or multi-line)
* @param line number
* @retval
*/
unsigned int code img[] = {
	0x00,0x7E,0x10,0x10,0x7E,0x00,0x00,0x3E,0x2A,0x2A,0x3A,0x00,0x00,0x3E,0x2A,0x2A,
	0x3A,0x00,0x00,0x3E,0x02,0x00,0x00,0x3E,0x02,0x00,0x00,0x1C,0x22,0x22,0x1C,0x00,
};


void _74HC595_WriteByte(unsigned int row)
{
	unsigned int i;
	for (i = 0; i < 8; i ++) {
		SER = row & (0x80 >> i);
		SCK = 1;
		SCK = 0; 
	}
	
	RCK = 1;
	RCK = 0;
}

/**
* @brief only single line
* @param one line number(decimal)
* @retval
*/
void code Show_Colum(unsigned int col, unsigned rows)
{
	_74HC595_WriteByte(rows);
	MATRIX_LED_PORT = ~(0x80 >> col);
	Delayxms(1);
	MATRIX_LED_PORT = 0xFF;
}

void show_dynamic_img_init(unsigned int start)
{
	unsigned int i = 0;
	for (i = 0; i < 8; i ++) {
		Show_Colum(i, img[(i + start) % 32]);
	}
}

void Matrix_intit()
{
	RCK = 0;
	SCK = 0;
}