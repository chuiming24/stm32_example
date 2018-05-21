#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"

#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4
#define LED6 5
#define LED7 6
#define LED8 7

void LED_Init(void);
void LED_Control(uint16_t LED,uint8_t LED_Status);


#endif

