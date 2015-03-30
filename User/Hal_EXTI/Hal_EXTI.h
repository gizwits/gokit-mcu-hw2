#ifndef _HAL_EXTI_H
#define _HAL_EXTI_H

#include <stdio.h>
#include <stm32f10x.h>
#include <stdio.h>

void EXTIx_Init(GPIO_TypeDef* GPIOx ,uint16_t GPIO_Pin_x,uint8_t NVIC_IRQChannelPreemptionPriority,uint8_t NVIC_IRQChannelSubPriority);


#endif /*_HAL_EXTI_H*/
