#ifndef __DELAY_H
#define __DELAY_H 	

#include <stm32f10x.h>

void Delay_Init(uint8_t SYSCLK);
void Delay_ms(uint16_t nms);
void Delay_us(uint32_t nus);


#endif 

