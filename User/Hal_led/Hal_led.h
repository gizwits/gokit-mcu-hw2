#ifndef _HAL_LED_H
#define _HAL_LED_H

#include <stdio.h>
#include <stm32f10x.h>

#define GPIO_LED1_CLK    RCC_APB2Periph_GPIOB
#define GPIO_LED1_PORT   GPIOB
#define GPIO_LED1_PIN    GPIO_Pin_15

#define GPIO_LED2_CLK    RCC_APB2Periph_GPIOB
#define GPIO_LED2_PORT   GPIOB
#define GPIO_LED2_PIN    GPIO_Pin_14

#define GPIO_LED3_CLK    RCC_APB2Periph_GPIOB
#define GPIO_LED3_PORT   GPIOB
#define GPIO_LED3_PIN    GPIO_Pin_11

#define GPIO_LED4_CLK    RCC_APB2Periph_GPIOB
#define GPIO_LED4_PORT   GPIOB
#define GPIO_LED4_PIN    GPIO_Pin_1



#define LED1             0X01
#define LED2             0X02
#define LED3             0X04
#define LED4             0X08


void LED_GPIO_Init(void);
void LED_ON(uint8_t LEDNUM);
void LED_OFF(uint8_t LEDNUM);

#endif /*_HAL_LED_H*/

