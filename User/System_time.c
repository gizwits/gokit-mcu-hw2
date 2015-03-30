#include "System_time.h"



static uint8_t  fac_us=0;//us延时倍乘数
static uint16_t fac_ms=0;//ms延时倍乘数

/*******************************************************************************
* Function Name  : SystemTime_Init
* Description    : 系统轮询时间初始化，当使用UCos时做滴答时钟
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SystemTime_Init(uint8_t SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick->CTRL &= ~(1<<0);          //使能Systick定时器
	SysTick->LOAD  = SYSCLK /8;   //系统时钟的1/8;
	SysTick->VAL   = 0x00;   						 //清空计数器
	SysTick->CTRL |= (1<<0);          //使能Systick定时器
	SystemTimeNVICConfig();
}

 void SystemTimeNVICConfig(void)
 {
	NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);	
 }