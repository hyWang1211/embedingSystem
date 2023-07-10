#include <REGX52.H>

void Delay1ms(unsigned int xms)		//@11.0592MHz
{
	unsigned char data i, j;

	while (xms --) {
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}


void main()
{
	unsigned int tmp = 0x1;
	int count = 0;
	P2 = ~tmp;
	
	while(1) {
		if (P3_1 == 0) {
			Delay1ms(20);
			
			while (P3_1 == 0);
			Delay1ms(20);
			count = (count + 1) % 8;
			P2 = ~(tmp << count);
			
		}
		
		if (P3_0 == 0) {
			Delay1ms(20);
			
			while (P3_0 == 0);
			Delay1ms(20);
			count = (count - 1 + 8) % 8;
			P2 = ~(tmp << count);
			
		}
	}
}