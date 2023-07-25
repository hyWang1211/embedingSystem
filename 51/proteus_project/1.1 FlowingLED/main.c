#include <regx52.h>
#include <delay.h>

void flowing_led();
int main()
{
	P2 = 1;
	
	while (1) {
		flowing_led();
	}
	
}


void flowing_led()
{
	unsigned char i = 0;
	unsigned char temp= 0x01;
	for (i = 0; i < 8; i ++) {
		P2 = ~(temp << i);
		Delay500ms();
	}
}



