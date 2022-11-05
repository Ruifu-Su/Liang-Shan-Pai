#ifndef BSP_USART_H
#define BSP_USART_H
#include "stdint.h"

void usart_gpio_config(uint32_t baud_rate);
void usart_send_data(uint8_t data);
void usart_send_string(uint8_t *str);
#endif
