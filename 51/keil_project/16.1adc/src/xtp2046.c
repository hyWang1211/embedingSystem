#include "xtp2046.h"
#include <REG52.H>
/*define ports*/
sbit DIN = P3^4;
sbit CS = P3^5;
sbit DCLK = P3^6;
sbit DOUT = P3^7;

/**
 * select what to convert, and return its ad value
*/
unsigned int xtp2046_adc(unsigned char command)
{
    /*init*/
    unsigned char i;
    unsigned int AD_Data = 0;
    DCLK = 0;
    CS = 0;
    
    /*write command*/
    for (i = 0; i < 8; i ++) {
        DIN = command & (0x80 >> i);
        DCLK = 1;
        DCLK = 0;
    }

    /*read AD value*/
    for (i = 0; i < 16; i ++) {
        DCLK = 1;
        DCLK = 0;
        
        if (DOUT) {
            AD_Data |= (0x8000 >> i);
        }
    }

    CS = 1;
    return AD_Data >> 8;
}