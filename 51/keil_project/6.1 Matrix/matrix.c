#include "delay.h"
#include "matrix.h"
#include <REGX52.H>

unsigned char getMatrixNum()
{
	
	
	unsigned char getSnum = 0;

	P1 = 0xFF;
		
	//control first col
	P1_3 = 0;
	if (P1_7 == 0) {Delayxms(20); while(P1_7 == 0); Delayxms(20); getSnum = 1;}
	if (P1_6 == 0) {Delayxms(20); while(P1_6 == 0); Delayxms(20); getSnum = 5;}
	if (P1_5 == 0) {Delayxms(20); while(P1_5 == 0); Delayxms(20); getSnum = 9;}
	if (P1_4 == 0) {Delayxms(20); while(P1_4 == 0); Delayxms(20); getSnum = 13;}
	
	//second col
	P1 = 0xFF;
	P1_2 = 0;
	if (P1_7 == 0) {Delayxms(20); while(P1_7 == 0); Delayxms(20); getSnum = 2;}
	if (P1_6 == 0) {Delayxms(20); while(P1_6 == 0); Delayxms(20); getSnum = 6;}
	if (P1_5 == 0) {Delayxms(20); while(P1_5 == 0); Delayxms(20); getSnum = 10;}
	if (P1_4 == 0) {Delayxms(20); while(P1_4 == 0); Delayxms(20); getSnum = 14;}
	
	P1 = 0xFF;
	P1_1 = 0;
	if (P1_7 == 0) {Delayxms(20); while(P1_7 == 0); Delayxms(20); getSnum = 3;}
	if (P1_6 == 0) {Delayxms(20); while(P1_6 == 0); Delayxms(20); getSnum = 7;}
	if (P1_5 == 0) {Delayxms(20); while(P1_5 == 0); Delayxms(20); getSnum = 11;}
	if (P1_4 == 0) {Delayxms(20); while(P1_4 == 0); Delayxms(20); getSnum = 15;}
	
	P1 = 0xFF;
	P1_0 = 0;
	if (P1_7 == 0) {Delayxms(20); while(P1_7 == 0); Delayxms(20); getSnum = 4;}
	if (P1_6 == 0) {Delayxms(20); while(P1_6 == 0); Delayxms(20); getSnum = 8;}
	if (P1_5 == 0) {Delayxms(20); while(P1_5 == 0); Delayxms(20); getSnum = 12;}
	if (P1_4 == 0) {Delayxms(20); while(P1_4 == 0); Delayxms(20); getSnum = 16;}
	
	
	return getSnum;
	
}