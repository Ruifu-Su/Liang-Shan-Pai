#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "bsp_led.h"
#include "stdint.h"

int main(void)
{
		systick_config();
		led_gpio_config();
    while(1) {
			delay_1ms(1000);
			LED2 = 1;
			delay_1ms(1000);
			LED2 = 0;
    }
}
