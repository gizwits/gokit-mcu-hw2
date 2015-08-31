/**
********************************************************
*
* @file      stm32f10x_it.c
* @author    Gizwtis
* @version   V2.3
* @date      2015-07-06
*
* @brief     机智云 只为智能硬件而生
*            Gizwits Smart Cloud  for Smart Products
*            链接|增值|开放|中立|安全|自有|自由|生态
*            www.gizwits.com
*
*********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_gpio.h"
#include "ringbuffer.h"
#include "Protocol.h"
#include "Hal_infrared/Hal_infrared.h"
#include "Hal_key/Hal_key.h"

extern uint8_t							  gaterSensorFlag ;
extern Pro_Wait_AckTypeDef           	  Wait_AckStruct;
extern uint32_t                           SystemTimeCount ;
extern uint8_t 							  KeyCountTime;
extern RingBuffer 						  u_ring_buff;

uint8_t last_data = 0;
uint16_t gaterTime = 0;

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
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
__asm void wait()
{
	BX lr 
}
void HardFault_Handler(void)
{
	wait();
// 	uint32_t r_sp ;

//   r_sp = __get_PSP(); //??SP??
// 	
//   /* Go to infinite loop when Hard Fault exception occurs */
//   while (1)
//   {
//   }
	
	
// 	  uint32_t r_sp ;

//   r_sp = __get_PSP(); //??SP??
//  PERROR(ERROR,Memory Access Error!);
// 	Panic(r_sp);
//   printf("r_sp = 0x%x",r_sp);
//  
//   while (1);
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
  * @brief  This function handles PendSV_Handler exception.
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
	SysTick->VAL =0X00; 
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

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

/**
  * USART2_IRQHandler
  */
void USART2_IRQHandler(void)
{
	uint8_t value = 0;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		value = USART_ReceiveData(USART2);
		if(rb_can_write(&u_ring_buff) > 0)
		{
			rb_write(&u_ring_buff, &value, 1);
		}
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


/**
  * TIM3_IRQHandler
  */
void TIM3_IRQHandler(void)   				
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );
        SystemTimeCount++;
        gaterTime++;
        KeyCountTime++;
        if (gaterTime >= 1000) 
        {
            gaterTime = 0;
            gaterSensorFlag = 1;
        }
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



#define  Infrared_EXTI_IRQHandler EXTI9_5_IRQHandler
void Infrared_EXTI_IRQHandler (void)
{
	EXTI->EMR &= (uint32_t)~(1<<1);   									//??????

	while(EXTI_GetITStatus(Infrared_EXTI_LineX)!= RESET ) 
	{		
		printf("Infrared_EXTI...\r\n");
		if(GPIO_ReadInputDataBit(Infrared_GPIO_PORT, Infrared_GPIO_PIN))
		{
			//Device_ReadStruct.Infrared = FALSE;
		}
		else
		{		
			//Device_ReadStruct.Infrared = TRUE;
		}	
//		Pro_D2W_ReportDevStatusHandle();
		EXTI_ClearITPendingBit(Infrared_EXTI_LineX);
	}	
	
	EXTI->EMR |= (uint32_t)(1<<1);  										//??????  
}
/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
