#include <REGX52.H>
#include "Delay.h"
#include "Nixie.h"


void main()
{
	while (1){
		Nixie(1, 0);
		//Delay1ms(50);
		Nixie(2, 1);
		//Delay1ms(50);
		Nixie(3, 2);
		//Delay1ms(50);
	}
}