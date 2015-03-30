#include "hal_exti.h"
#include "stm32f10x_exti.h"


void EXTIx_Init(GPIO_TypeDef* GPIOx ,uint16_t GPIO_Pin_x,uint8_t NVIC_IRQChannelPreemptionPriority,uint8_t NVIC_IRQChannelSubPriority)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	uint32_t EXTI_Line_x;
	uint8_t GPIO_PinSource_x;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
		switch (GPIO_Pin_x)
		{
			case GPIO_Pin_0:
						EXTI_Line_x = EXTI_Line0;
						GPIO_PinSource_x = GPIO_PinSource0;
						NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			
				break;
			case GPIO_Pin_1:				
						EXTI_Line_x = EXTI_Line1;
						GPIO_PinSource_x = GPIO_PinSource1;
						NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			
				break;
			case GPIO_Pin_2:
				EXTI_Line_x = EXTI_Line2;
				GPIO_PinSource_x = GPIO_PinSource2;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			
				break;
			case GPIO_Pin_3:
				EXTI_Line_x = EXTI_Line3;
				GPIO_PinSource_x = GPIO_PinSource3;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			
				break;
			case GPIO_Pin_4:
				EXTI_Line_x = EXTI_Line4;
				GPIO_PinSource_x = GPIO_PinSource4;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			
				break;
			case GPIO_Pin_5:
				EXTI_Line_x = EXTI_Line5;
				GPIO_PinSource_x = GPIO_PinSource5;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
				break;
			case GPIO_Pin_6:
				EXTI_Line_x = EXTI_Line6;
				GPIO_PinSource_x = GPIO_PinSource6;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		
				break;
			case GPIO_Pin_7:
				EXTI_Line_x = EXTI_Line7;
				GPIO_PinSource_x = GPIO_PinSource7;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
				break;
			case GPIO_Pin_8:
				EXTI_Line_x = EXTI_Line8;
				GPIO_PinSource_x = GPIO_PinSource8;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
				break;
			case GPIO_Pin_9:
				EXTI_Line_x = EXTI_Line9;
				GPIO_PinSource_x = GPIO_PinSource9;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		
				break;
			case GPIO_Pin_10:
				EXTI_Line_x = EXTI_Line10;
				GPIO_PinSource_x = GPIO_PinSource10;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
				break;
			case GPIO_Pin_11:
				EXTI_Line_x = EXTI_Line11;
				GPIO_PinSource_x = GPIO_PinSource11;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
				break;
			case GPIO_Pin_12:
				EXTI_Line_x = EXTI_Line12;
				GPIO_PinSource_x = GPIO_PinSource12;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
				break;
			case GPIO_Pin_13:
				EXTI_Line_x = EXTI_Line13;
				GPIO_PinSource_x = GPIO_PinSource13;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
				break;
			case GPIO_Pin_14:
				EXTI_Line_x = EXTI_Line14;
				GPIO_PinSource_x = GPIO_PinSource14;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
				break;
			case GPIO_Pin_15:
				EXTI_Line_x = EXTI_Line15;
				GPIO_PinSource_x = GPIO_PinSource15;
				NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
				break;
			
			
			default:
				break;
		}
							
		if (GPIOx == GPIOA)
		{		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);								
			GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource_x);	
			
		}	
		if (GPIOx == GPIOB)
		{		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);								
			GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource_x);	
			
		}	
		if (GPIOx == GPIOC)
		{		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
			GPIO_Init(GPIOC, &GPIO_InitStructure);								
			GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource_x);	
			
		}	
		if (GPIOx == GPIOD)
		{		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//使能PORTA,PORTE时钟
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
			GPIO_Init(GPIOD, &GPIO_InitStructure);								
			GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource_x);	
			
		}			
		if (GPIOx == GPIOE)
		{		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
			GPIO_Init(GPIOE, &GPIO_InitStructure);								
			GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource_x);	
			
		}	
		if (GPIOx == GPIOF)
		{		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//使能PORTA,PORTE时钟
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
			GPIO_Init(GPIOF, &GPIO_InitStructure);								
			GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource_x);	
			
		}	
		if (GPIOx == GPIOG)
		{		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);//使能PORTA,PORTE时钟
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_x;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
			GPIO_Init(GPIOG, &GPIO_InitStructure);		
			EXTI_ClearFlag(EXTI_Line_x); 			
			GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource_x);	
			
		}	
			
			EXTI_InitStructure.EXTI_Line=EXTI_Line_x;	
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;
			EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
			
//			if(GPIO_PinSource_x <5)
				
				
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;	//抢占优先级2， 
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;					//子优先级3
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure); 
	
}


//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
	printf("EXTI_Line0 IRQHandler\r\n");
}
 
//外部中断1服务程序 
void EXTI1_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE1上的中断标志位  
	printf("EXTI_Line1 IRQHandler\r\n");
}

//外部中断2服务程序 
void EXTI2_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE2上的中断标志位  
	printf("EXTI_Line2 IRQHandler\r\n");
}

//外部中断3服务程序 
void EXTI3_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE3上的中断标志位  
	printf("EXTI_Line3 IRQHandler\r\n");
}
 
//外部中断4服务程序 
void EXTI4_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE4上的中断标志位  
	printf("EXTI_Line3 IRQHandler\r\n");
}

//外部中断5_9服务程序 
void EXTI9_5_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE5上的中断标志位 
	EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE6上的中断标志位  
	EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE7上的中断标志位  
	EXTI_ClearITPendingBit(EXTI_Line8); //清除LINE8上的中断标志位  
	EXTI_ClearITPendingBit(EXTI_Line9); //清除LINE9上的中断标志位  	
	printf("EXTI_Line5_9 IRQHandler\r\n");
}

//外部中断10_15 服务程序 
		 
void EXTI15_10_IRQHandler(void)
{
	printf("EXTI_Line10_15 IRQHandler\r\n");
	EXTI_ClearITPendingBit(EXTI_Line10); //清除LINE5上的中断标志位 
	EXTI_ClearITPendingBit(EXTI_Line11); //清除LINE6上的中断标志位  
	EXTI_ClearITPendingBit(EXTI_Line12); //清除LINE7上的中断标志位  
	EXTI_ClearITPendingBit(EXTI_Line13); //清除LINE8上的中断标志位  
	EXTI_ClearITPendingBit(EXTI_Line14); //清除LINE9上的中断标志位  	
	
}



