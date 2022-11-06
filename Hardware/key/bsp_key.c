#include "bsp_key.h"
#include "bsp_led.h"
#include "gd32f4xx.h"
#include "gd32f4xx_exti.h"
#include "gd32f4xx_gpio.h"
#include "gd32f4xx_misc.h"
#include "gd32f4xx_rcu.h"
#include "gd32f4xx_syscfg.h"
#include "stdint.h"
#include "stdio.h"
#include "systick.h"

void key_gpio_config(void) {
  /* 开启时钟 */
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_SYSCFG);
  /* 配置GPIO模式 */
  gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, GPIO_PIN_0);
  /* 设置中断优先级 */
  nvic_irq_enable(EXTI0_IRQn, 3, 3);
  /* 连接中断线 */
  syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN0);
  /* 初始化中断 */
  exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
  /* 使用中断 */
  exti_interrupt_enable(EXTI_0);
  /* 清除中断标志位 */
  exti_interrupt_flag_clear(EXTI_0);
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

extern uint8_t riding_led_status;
void EXTI0_IRQHandler(void) {
  if (exti_interrupt_flag_get(EXTI_0) == SET) {
    if (gpio_input_bit_get(GPIOA, GPIO_PIN_0) == SET) {
      riding_led_status = !riding_led_status;
      if (!riding_led_status) {
        printf("Stop LED\n");
      }
      printf("-------Key pressed------\n");
    } else {
      printf("-------Key released------\n");
    }
    exti_interrupt_flag_clear(EXTI_0);
  }
}
