#include <delay.h>

void Delay500ms()		//@12.000MHz
{
	unsigned char data i, j, k;

	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
