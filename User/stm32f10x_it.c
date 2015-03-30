/**
  ******************************************************************************
  * @file    stm32f10x_it.c
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
/* Includes ------------------------------------------------------------------*/
#include <stm32f10x_it.h>
#include "include.h"
#include "stm32f10x_rtc.h"

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

extern UART_HandleTypeDef  							UART_HandleStruct;
extern Device_ReadTypeDef               Device_ReadStruct;
void USART2_IRQHandler(void)
{
	uint8_t 	vlue;
	
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  { 
//		printf("**\r\n");
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		vlue = USART_ReceiveData(USART2);
		if(UART_HandleStruct.Package_Flag ==0)
		{
			
			if(UART_HandleStruct.UART_Flag1 ==0)
			{
				if(vlue == 0xff)
				{   
						UART_HandleStruct.UART_Count = 0;						
						UART_HandleStruct.UART_Buf[UART_HandleStruct.UART_Count]=vlue;
						UART_HandleStruct.UART_Count++;	
						UART_HandleStruct.UART_Flag1 = 1;
				}			
				return ;
			}
			else if(UART_HandleStruct.UART_Flag2 ==0)
			{
					UART_HandleStruct.UART_Buf[UART_HandleStruct.UART_Count]=vlue;
					UART_HandleStruct.UART_Count++;
					if(UART_HandleStruct.UART_Buf[1] == 0xff)
					{
						UART_HandleStruct.UART_Flag2 = 1;	
						
					}					
					else
					{
						UART_HandleStruct.UART_Flag1 = 0;
					}
					return ;
			}
			else
			{
				UART_HandleStruct.UART_Buf[UART_HandleStruct.UART_Count] = vlue;
				if(UART_HandleStruct.UART_Count >=4 && UART_HandleStruct.UART_Buf[UART_HandleStruct.UART_Count] == 0x55 && UART_HandleStruct.UART_Buf[UART_HandleStruct.UART_Count - 1] == 0xFF)
				{}
				else 
				UART_HandleStruct.UART_Count++;
				if(UART_HandleStruct.UART_Count == 0x04)
				{
					UART_HandleStruct.UART_Cmd_len = UART_HandleStruct.UART_Buf[2]*256+  UART_HandleStruct.UART_Buf[3]; 	

				}
				if(UART_HandleStruct.UART_Count ==  (UART_HandleStruct.UART_Cmd_len + 4))
				{
					UART_HandleStruct.Package_Flag = 1;
					UART_HandleStruct.UART_Flag1 = 0;
					UART_HandleStruct.UART_Flag2 = 0;
//					printf("Package_Flag =1 \r\n");
				}	
			}
		}		
  }	
	
}

void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  { 		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		
		USART_SendData(USART1,USART_ReceiveData(USART1));
		//Loop until the end of transmission
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	
	}
}

void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  { 

		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		USART_SendData(USART3,USART_ReceiveData(USART3));
		//Loop until the end of transmission
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);		
	}
}




extern Pro_Wait_AckTypeDef           	  Wait_AckStruct;
extern uint32_t                         SystemTimeCount ;
extern uint8_t 													KeyCountTime;
extern uint32_t ReportTimeCount;
/******************************************************************************/
/*             KEY1 :长按  RESET WIFI, KEY2 :短按  配置WiFi联                 */
/*             定时器3中断服务程序                                            */
/******************************************************************************/
void TIM3_IRQHandler(void)   				
{
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
			SystemTimeCount++;
			Wait_AckStruct.SendTime ++;
			KeyCountTime++;
			ReportTimeCount++;
		}
		

	
}  

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

void RTC_IRQHandler(void)
{
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
	/* Clear the RTC Second interrupt */
	RTC_ClearITPendingBit(RTC_IT_SEC);  
  }
}


#ifdef Infrared_EXTI

#ifdef Gokit
#define  Infrared_EXTI_IRQHandler EXTI9_5_IRQHandler
#endif

#ifdef STUNO
#define  Infrared_EXTI_IRQHandler EXTI15_10_IRQHandler
#endif

#ifdef Xnucleo
#define  Infrared_EXTI_IRQHandler EXTI15_10_IRQHandler
#endif


void Infrared_EXTI_IRQHandler (void)
{
	EXTI->EMR &= (uint32_t)~(1<<1);   									//屏蔽中断事件

	while(EXTI_GetITStatus(Infrared_EXTI_LineX)!= RESET ) 
	{		
		printf("Infrared_EXTI...\r\n");
		if(GPIO_ReadInputDataBit(Infrared_GPIO_PORT, Infrared_GPIO_PIN))
		{
			Device_ReadStruct.Infrared = FALSE;
		}
		else
		{		
			Device_ReadStruct.Infrared = TRUE;
		}	
		Pro_D2W_ReportDevStatusHandle();
		EXTI_ClearITPendingBit(Infrared_EXTI_LineX);
	}	
	
	EXTI->EMR |= (uint32_t)(1<<1);  										//开启中断事件  
}

#endif

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */


void HardFault_Handler(void)
{
  uint32_t r_sp ;

  r_sp = __get_PSP(); //??SP??
//  PERROR(ERROR,Memory Access Error!);
  printf("r_sp = 0x%x",r_sp);
 
  while (1);
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{	
	printf("SysTick_Handler \r\n");
	SysTick->VAL =0X00; 
}






/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
