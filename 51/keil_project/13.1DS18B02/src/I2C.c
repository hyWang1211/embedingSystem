#include "I2C.h"

#include <REG52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
* @brief start
* @param
* @retval
*/
void I2C_init()
{
	I2C_SCL = 1;
	I2C_SDA = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
}

/**
* @brief stop read or write
* @param
* @retval
*/
void I2C_end()
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}

/**
* @brief send byte
* @param
* @retval
*/
void I2C_SByte(unsigned char Byte)
{
	unsigned char i = 0, base = 0x80;
	for (i = 0; i < 8; i ++) {
		I2C_SDA = Byte & (base >> i);
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}

unsigned char I2C_RByte(void)
{
	unsigned char i = 0, receive = 0, base = 0x80;
	I2C_SDA = 1;
	
	for (i = 0; i < 8; i ++) {
		if (I2C_SDA) {
			receive |= (base >> i);
		}
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
	
	return receive;
}

void I2C_SA(unsigned char sa) {
	I2C_SDA = sa;
	I2C_SCL = 1;
	I2C_SCL = 0;
}

unsigned char I2C_RA() {
	unsigned char ra = 0;
	I2C_SDA = 1;
	ra= I2C_SDA;
	I2C_SCL = 1;
	I2C_SCL = 0;
	return ra;
}