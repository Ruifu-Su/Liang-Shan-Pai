#include "main.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "gd32f4xx.h"
#include "stdint.h"
#include "systick.h"
#include <stdio.h>

int main(void) {
  systick_config();
  led_gpio_config();
  usart_gpio_config(9600);

  //   usart_send_string("Hello world\n");
  //   printf("%.4f\n", 3 / 2.0);
  char customer_number[] = {"1561362A"};
  printf("The Customer Number of Ruifu Su is %s", customer_number);
  while (1) {
    delay_1ms(1000);
    LED2 = 0;
  }
}
