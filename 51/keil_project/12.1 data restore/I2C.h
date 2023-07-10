#ifndef __I2C_H__
#define __I2C_H__

void I2C_init();
void I2C_end();

void I2C_SByte(unsigned char Byte);
unsigned char I2C_RByte(void);

void I2C_SA(unsigned char sa);
unsigned char I2C_RA();

#endif





