#include <dlgpio.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    dlgpio power_led = {POWER_LED, OUT};//GPIO 362 is "Status Led".
	printf("[INIT GPIO]\n");
    init_gpio(&power_led);
    int i;
    for(i = 0; i < 20; i++ )
    {
         setGPIO(&power_led, H);
         printf("1\n");
         sleep(1);
         setGPIO(&power_led, L);
         printf("0\n");
         sleep(1);
    }
	printf("[CLOSE GPIO]\n");
    close_gpio(&power_led);
    return 0;
}
