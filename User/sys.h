#ifndef _SYS_H
#define _SYS_H

#include "gd32f4xx.h"
#include "systick.h"


#define BIT_ADDR(byte_offset,bit_number) (volatile unsigned long*)(0x42000000 +(byte_offset << 5)+(bit_number << 2))   // 位带别名区的地址
	
#define GPIOE_OCTL_OFFSET ((GPIOE + 0x14) - 0x40000000) 	// 偏移量
#define GPIOD_OCTL_OFFSET ((GPIOD + 0x14) - 0x40000000) 	// 偏移量
#define GPIOG_OCTL_OFFSET ((GPIOG + 0x14) - 0x40000000) 	// 偏移量
#define GPIOA_OCTL_OFFSET ((GPIOA + 0x14) - 0x40000000) 	// 偏移量

#define PEout(n)  *(BIT_ADDR(GPIOE_OCTL_OFFSET,n))   		  // PD口输出
#define PDout(n)  *(BIT_ADDR(GPIOD_OCTL_OFFSET,n))   		  // PD口输出
#define PGout(n)  *(BIT_ADDR(GPIOG_OCTL_OFFSET,n))   		  // PD口输出
#define PAout(n)  *(BIT_ADDR(GPIOA_OCTL_OFFSET,n))   		  // PD口输出


#endif  /* SYS_H */
