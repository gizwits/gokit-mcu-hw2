/**
  ******************************************************************************
  * @file    Hal_led.c
  * @author  jason
	* @Tel     18938045680
	* @QQ      570526723 
  * @version V2.0
  * @date    12/05/2014
  * @brief   1，专业嵌入式智能设备方案定制
						 2，专业开发工具供应商：http://wenjieteam.taobao.com/
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, jason SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2014 jason</center></h2>
  */ 
#include "include.h"


void LED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_LED1_CLK | GPIO_LED2_CLK | GPIO_LED3_CLK | GPIO_LED4_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_LED1_PIN;
	GPIO_Init(GPIO_LED1_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_LED2_PIN;
	GPIO_Init(GPIO_LED2_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_LED3_PIN;
	GPIO_Init(GPIO_LED3_PORT, &GPIO_InitStructure);		
	
	GPIO_InitStructure.GPIO_Pin = GPIO_LED4_PIN;
	GPIO_Init(GPIO_LED4_PORT, &GPIO_InitStructure);		
	
	LED_OFF(LED1);
	LED_OFF(LED2);
	LED_OFF(LED3);
	LED_OFF(LED4);
}

void LED_ON(uint8_t LEDNUM)
{
	switch (LEDNUM)
	{
		case LED1:GPIO_SetBits(GPIO_LED1_PORT,GPIO_LED1_PIN);
			break;
		case LED2:GPIO_SetBits(GPIO_LED2_PORT,GPIO_LED2_PIN);
			break;
		case LED3:GPIO_SetBits(GPIO_LED3_PORT,GPIO_LED3_PIN);
			break;
		case LED4:GPIO_SetBits(GPIO_LED4_PORT,GPIO_LED4_PIN);
			break;
		default:
			break;
	}
}

void LED_OFF(uint8_t LEDNUM)
{
	switch (LEDNUM)
	{
		case LED1:GPIO_ResetBits(GPIO_LED1_PORT,GPIO_LED1_PIN);
			break;
		case LED2:GPIO_ResetBits(GPIO_LED2_PORT,GPIO_LED2_PIN);
			break;
		case LED3:GPIO_ResetBits(GPIO_LED3_PORT,GPIO_LED3_PIN);
			break;
		case LED4:GPIO_ResetBits(GPIO_LED4_PORT,GPIO_LED4_PIN);
			break;
		default:
			break;
	}
}
