/**
********************************************************
*
* @file      Hal_motor.c
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
#include "Hal_motor/Hal_motor.h"

/*
 * 函数名：TIM3_GPIO_Config
 * 描述  ：配置TIM3复用输出PWM时用到的I/O
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM3_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE); 
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	
  /*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/*
 * 函数名：TIM3_Mode_Config
 * 描述  ：配置TIM3输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM3_Mode_Config(void)
{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM信号电平跳变值 */
	u16 CCR1_Val = 500;        
	u16 CCR2_Val = 500;


/* -----------------------------------------------------------------------
    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM3CLK = 72 MHz, Prescaler = 0x0, TIM3 counter clock = 72 MHz
    TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
    TIM3 Frequency = 72 KHz.
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */

//  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  //使能通道2
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //使能定时器3	
}

void Motor_Init(void)
{
	TIM3_GPIO_Config();
	TIM3_Mode_Config();
	
}


void Motor_Control(u8 m1,u8 m2)
{
	u16 temp = (MOTOR_ARR+1) / MOTOR_MAX;
	
	TIM_SetCompare1(TIM3,m1*temp);	//m1
	TIM_SetCompare2(TIM3,m2*temp);	//m4
	
}
void Motor_status(MOTOR_T status)
{		
	if(status == 5)
	{
		Motor_Control(0,0);
	}
	else if (status > 5)
	{
		Motor_Control(status*10,0);
	}
	else if (status < 5)
	{
		Motor_Control(0,(10-status)*10);
	}

}


