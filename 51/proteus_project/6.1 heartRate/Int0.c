#include "Int0.h"
#include <regx52.h>
void Int0_init(void)
{
	IT0 = 1;
	EX0 = 1;
	EA = 1;
	PX0 = 1;
}