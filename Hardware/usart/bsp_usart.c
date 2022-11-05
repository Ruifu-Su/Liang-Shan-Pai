#include "bsp_usart.h"
#include "gd32f4xx.h"
#include "gd32f4xx_gpio.h"
#include "gd32f4xx_rcu.h"
#include "gd32f4xx_usart.h"
#include "stdio.h"
#include "systick.h"

void usart_gpio_config(uint32_t baud_rate) {
  /* 开启时钟 */
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_USART0);
  /* 配置GPIO复用功能 */
  gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9);
  gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_10);
  /* 配置GPIO模式 */
  gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
  gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
  /* 配置GPIO输出 */
  gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
  gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
  /* 配置串口参数 */
  usart_deinit(USART0);
  usart_baudrate_set(USART0, baud_rate);
  usart_parity_config(USART0, USART_PM_NONE);
  usart_word_length_set(USART0, USART_WL_8BIT);
  usart_stop_bit_set(USART0, USART_STB_1BIT);
  /* 打开串口 */
  usart_enable(USART0);
  usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
  usart_receive_config(USART0, USART_RECEIVE_ENABLE);
}

void usart_send_data(uint8_t data) {
  usart_data_transmit(USART0, (uint8_t)data);
  while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
    ;
}

void usart_send_string(uint8_t *str) {
  if (!str) {
    return;
  }
  while (*str) {
    usart_send_data(*str++);
  }
}

int fputc(int ch, FILE *f) {
  usart_send_data(ch);
  return ch;
}
