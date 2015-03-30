/**
  ******************************************************************************
  * @file    Hal_hemp_hum.c
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

//Reset DHT11
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 											//SET OUTPUT
  DHT11_DQ_OUT=0; 											//GPIOA.0=0
  Delay_ms(20);    											//Pull down Least 18ms
  DHT11_DQ_OUT=1; 											//GPIOA.0=1 
	Delay_us(30);     										//Pull up 20~40us
}

u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();												//SET INPUT	 
  while (DHT11_DQ_IN&&retry<100)				//DHT11 Pull down 40~80us
	{
		retry++;
		Delay_us(1);
	}	 
	
	if(retry>=100)
		return 1;
	else 
		retry=0;
	
  while (!DHT11_DQ_IN&&retry<100)				//DHT11 Pull up 40~80us
	{
		retry++;
		Delay_us(1);
	}
	
	if(retry>=100)
		return 1;														//chack error	    
	
	return 0;
}

u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)					//wait become Low level
	{
		retry++;
		Delay_us(1);
	}
	
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)				//wait become High level
	{
		retry++;
		Delay_us(1);
	}
	
	Delay_us(40);//wait 40us
	
	if(DHT11_DQ_IN)
		return 1;
	else 
		return 0;		   
}

u8 DHT11_Read_Byte(void)    
{        
  u8 i,dat;
  dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
  }						    
  
	return dat;
}

u8 DHT11_Read_Data(u8 *temperature,u8 *humidity)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humidity=buf[0];
			*temperature=buf[2];
		}
	}
	else 
		return 1;
	
	return 0;	    
}
	 
u8 DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				 
 	GPIO_SetBits(GPIOB,GPIO_Pin_3);		 
			    
	DHT11_Rst();  
	return DHT11_Check();
} 
