#ifndef _HAL_INFRARED_H
#define _HAL_INFRARED_H

#define Infrared_EXTI

#ifdef Gokit
#define Infrared_GPIO_CLK    			 RCC_APB2Periph_GPIOB
#define Infrared_GPIO_PORT         GPIOB
#define Infrared_GPIO_PIN          GPIO_Pin_7
#define Infrared_EXTI_LineX        EXTI_Line7


#endif

#ifdef STUNO
#define Infrared_GPIO_CLK    			 RCC_APB2Periph_GPIOA
#define Infrared_GPIO_PORT         GPIOA
#define Infrared_GPIO_PIN          GPIO_Pin_10
#define Infrared_EXTI_LineX        EXTI_Line10
#endif

#ifdef Xnucleo
#define Infrared_GPIO_CLK    			 RCC_APB2Periph_GPIOA
#define Infrared_GPIO_PORT         GPIOA
#define Infrared_GPIO_PIN          GPIO_Pin_10
#define Infrared_EXTI_LineX        EXTI_Line10
#endif

void IR_Init(void);
void IR_Handle(void);
#endif /*_HAL_INFRARED_H*/


