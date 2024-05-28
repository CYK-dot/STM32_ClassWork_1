#ifndef __LED_H
#define __LED_H
#include "stm32f4xx_gpio.h"

void pwm_init(u16 arr,u16 psc);
void LED_Init(void);
void Sych_Init(void);
void delay_ms(u32 x);
void exti_init(void);

#endif

