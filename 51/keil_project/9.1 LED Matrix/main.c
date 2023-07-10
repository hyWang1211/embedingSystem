#include <REGX52.H>
#include "matrix_led.h"
#include "delay.h"
unsigned int start = 0;
void code main()
{
	Matrix_intit();
	
	while (1) {
		show_dynamic_img_init(start);
		
		start = (start + 1) % 32;
	}
}

