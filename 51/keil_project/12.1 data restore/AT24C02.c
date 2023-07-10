#include "I2C.h"
#include "AT24C02.h"
#include <REGX52.H>

void AT24C02_Write(unsigned char addr, Data)
{
	unsigned char Ack = -1;
	I2C_init();
	I2C_SByte(0xA0);
	I2C_RA();
	I2C_SByte(addr);
	I2C_RA();
	I2C_SByte(Data);
	I2C_RA();
	I2C_end();
}


unsigned char AT24C02_Read(unsigned char addr)
{
	unsigned char Data;
	I2C_init();
	I2C_SByte(0xA0);
	I2C_RA();
	I2C_SByte(addr);
	I2C_RA();
	
	I2C_init();
	I2C_SByte(0xA0 | 0x01);
	I2C_RA();
	Data = I2C_RByte();
	
	I2C_SA(1);
	I2C_end();
	return Data;
}