#include <regx52.h>

void disw_control_led();
void logicstate_control_led();

sbit led = P1^0;
sbit logic = P1^6;
void main()
{
	while(1) {
		disw_control_led();
		logicstate_control_led();
	}
		
}

void disw_control_led()
{
	P2 = P3;
}

void logicstate_control_led()
{
	unsigned char temp = logic;
	led = temp;
}