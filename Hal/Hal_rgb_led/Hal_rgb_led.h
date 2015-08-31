#ifndef _HAL_RGB_LED_H
#define _HAL_RGB_LED_H

//#include "include.h"
#include <stdio.h>
#include <stm32f10x.h>
#include <stdio.h>

/*兼容V2.2,RGB开关IO*/
#define GPIO_RGB_CLK    RCC_APB2Periph_GPIOA
#define GPIO_RGB_PORT   GPIOA
#define GPIO_RGB_PIN    GPIO_Pin_0

#define  R_MAX  255
#define  G_MAX  255
#define  B_MAX  255

#define SCL_LOW 	GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define SCL_HIGH 	GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define SDA_LOW		GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define SDA_HIGH	GPIO_SetBits(GPIOB,GPIO_Pin_9)

void RGB_LED_Init(void);
void LED_R_Control(uint8_t R);
void LED_G_Control(uint8_t G);
void LED_B_Control(uint8_t B);
void LED_RGB_Control(uint8_t R,uint8_t B,uint8_t G);
void RGB_KEY_GPIO_Init(void);

#endif /*_HAL_RGB_LED_H*/

