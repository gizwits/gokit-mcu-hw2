#ifndef _HAL_INFRARED_H
#define _HAL_INFRARED_H
#include "stdbool.h"

#define Infrared_GPIO_CLK    	   RCC_APB2Periph_GPIOB
#define Infrared_GPIO_PORT         GPIOB
#define Infrared_GPIO_PIN          GPIO_Pin_7
#define Infrared_EXTI_LineX        EXTI_Line7


void IR_Init(void);
bool IR_Handle(void);

#endif /*_HAL_INFRARED_H*/


