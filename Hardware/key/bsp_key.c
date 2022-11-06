#include "bsp_key.h"

#include "bsp_led.h"
#include "gd32f4xx.h"
#include "gd32f4xx_gpio.h"
#include "gd32f4xx_rcu.h"
#include "stdint.h"
#include "stdio.h"
#include "systick.h"

void key_gpio_config(void) {
  /* 开启时钟 */
  rcu_periph_clock_enable(RCU_GPIOA);
  /* 配置GPIO模式 */
  gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, GPIO_PIN_0);
}

uint8_t led_status = 0x00;

void key_scan(void) {
  /* 获取按键的电平状态 */
  if (SET == gpio_input_bit_get(GPIOA, GPIO_PIN_0)) {
    delay_1ms(20);
    if (SET == gpio_input_bit_get(GPIOA, GPIO_PIN_0)) {
      /* 执行对应的功能 */
      printf("Key press!\n");
        switch (led_status) {
        case 0x00:
          LED1 = 1;
          led_status = 0x01;
          break;
        case 0x01:
          LED2 = 1;
          led_status = 0x02;
          break;
        case 0x02:
          LED3 = 1;
          led_status = 0x03;
          break;
        case 0x03:
          LED4 = 1;
          led_status = 0x04;
          break;
        case 0x04:
          LED1 = 0;
          LED2 = 0;
          LED3 = 0;
          LED4 = 0;
          led_status = 0x00;
          break;
        }

      /* 检测按键松开 */
      while (gpio_input_bit_get(GPIOA, GPIO_PIN_0) == SET)
        ;
      printf("Key release!\n");
    }
  }
}
