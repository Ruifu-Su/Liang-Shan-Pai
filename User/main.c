#include "main.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "gd32f4xx.h"
#include "gd32f4xx_misc.h"
#include "stdint.h"
#include "systick.h"
#include <stdio.h>

uint8_t riding_led_status = 1;
uint8_t led_on = 0x01;

void set_led(uint8_t led_on) {
  LED1 = led_on == 0x01;
  LED2 = led_on == 0x02;
  LED3 = led_on == 0x03;
  LED4 = led_on == 0x04;
}

int main(void) {
  /* NVIC 优先级分组 */
  nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);

  systick_config();
  led_gpio_config();
  usart_gpio_config(9600);
  key_gpio_config();
  //   usart_send_string("Hello world\n");
  //   printf("%.4f\n", 3 / 2.0);

  // char customer_number[] = {"1561362A"};
  // printf("The Customer Number of Ruifu Su is %s", customer_number);
  while (1) {
    // key_scan();
    delay_1ms(500);
    if (riding_led_status) {
      set_led(led_on);
      switch (led_on) {
      case 0x01:
        led_on = 0x02;
        break;
      case 0x02:
        led_on = 0x03;
        break;
      case 0x03:
        led_on = 0x04;
        break;
      case 0x04:
        led_on = 0x01;
        break;
      }
    }
  }
}
