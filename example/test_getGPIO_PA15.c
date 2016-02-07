#include <stdio.h>
#include "dlgpio.h"

int main()
{
	dlgpio t = {15, OUT};
	init_gpio(&t);
	int s = getGPIO(&t);
	printf("status : %d\n", s);
	setGPIO(&t, H);
	s = getGPIO(&t);
	printf("status : %d\n", s);
	close_gpio(&t);
	return 0;
}
