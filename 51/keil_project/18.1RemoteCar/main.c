#include <REG52.H>
#include "infrared.h"
#include "Delay.h"
#include "timer0.h"

unsigned char adr;
unsigned char cmd;
unsigned char cmdCpy;
unsigned int time;
unsigned char speed = 50;
unsigned char counter = 0;
sbit L1 = P2^0;
sbit L2 = P2^1;
sbit R1 = P2^2;
sbit R2 = P2^3;
void main()
{
    infrared_init();
	Timer1_Init();
	L1 = R1 = L2 = R2 = 0;
	
    while (1) {
        if (IR_get_data_flag()) {
            adr = IR_get_data_addr();
            cmd = IR_get_data_command();
        }
    }
}

void Timer1_Isr(void) interrupt 3
{
	TL1 = 0xA4;				//???????
	TH1 = 0xFF;				//???????
	
	counter ++;
	counter %= 100;
	
	if (cmd == 24) {
		L2 = R2 = 0;
		if (counter <= speed) L1 = R1 = 1;
		else L1 = R1 = 0;
	}else if (cmd == 82) {
		L1 = R1 = 0;
		if (counter <= speed) L2 = R2 = 1;
		else L2 = R2 = 0;
	}else if (cmd == 8) {
		L2 = R2 = 0;
		if (counter <= speed) R1 = 1;
		else R1 = 0;
		if (counter <= speed - 30) L1 = 1;
		else L1 = 0;
	}else if (cmd == 90) {
		L2 = R2 = 0;
		if (counter <= speed) L1 = 1;
		else L1 = 0;
		if (counter <= speed - 30) R1 = 1;
		else R1 = 0;
	}else {
		L1 = R1 = L2 = R2 = 0;
	}
}
