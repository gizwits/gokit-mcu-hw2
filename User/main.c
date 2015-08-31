/**
********************************************************
*
* @file      main.c
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


#include "gokit.h"

/*Global Variable*/
uint32_t ReportTimeCount = 0;
uint8_t gaterSensorFlag = 0;
uint8_t Set_LedStatus = 0;
uint8_t NetConfigureFlag = 0;
uint8_t curTem = 0, curHum = 0;
uint8_t lastTem = 0,lastHum = 0;

extern RingBuffer u_ring_buff;
uint8_t p0Flag = 0;

WirteTypeDef_t	WirteTypeDef;
ReadTypeDef_t	ReadTypeDef;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	uint8_t p0_control_buf[MAX_P0_LEN];
	
	SystemInit();	
	HW_Init();
	Printf_SystemRccClocks();
	SW_Init();		
	while(1)
	{
		KEY_Handle();		
		GizWits_MessageHandle(p0_control_buf, sizeof(WirteTypeDef_t));
		if(p0Flag == 1)
		{
			memcpy((uint8_t *)&WirteTypeDef, p0_control_buf, sizeof(WirteTypeDef_t));
			GizWits_ControlDeviceHandle();
			GizWits_DevStatusUpgrade((uint8_t *)&ReadTypeDef, 10*60*1000, 1);
			p0Flag =0;
		}
        if(gaterSensorFlag != 0)
        {
            GizWits_GatherSensorData(); 
            gaterSensorFlag = 0;
        }
        GizWits_DevStatusUpgrade((uint8_t *)&ReadTypeDef, 10*60*1000, 0);
	}
}
/** @addtogroup GizWits_HW_Init
  * @{
  */
void HW_Init(void)
{
	Delay_Init(72);	
	UARTx_Init();
    RGB_KEY_GPIO_Init();
	RGB_LED_Init();	
	LED_GPIO_Init();	
	KEY_GPIO_Init();
	TIM3_Int_Init(7199,9);   //ms interrupt	
	Motor_Init();	
	DHT11_Init();	
	IR_Init();	
}
/** @addtogroup GizWits_SW_Init
  * @{
  */
void SW_Init()
{
	ReadTypeDef.Alert = 0;
	ReadTypeDef.LED_Cmd = 0;
	ReadTypeDef.LED_R = 0;
	ReadTypeDef.LED_G = 0;  
	ReadTypeDef.LED_B = 0;
	ReadTypeDef.Motor = 5;
	ReadTypeDef.Infrared = 0;
	ReadTypeDef.Temperature = 0;
	ReadTypeDef.Humidity = 0;
	ReadTypeDef.Alert = 0;
	ReadTypeDef.Fault = 0;
	GizWits_init(sizeof(ReadTypeDef_t));
	printf("Gokit Init Ok ...\r\n");
}
/** @addtogroup Printf_SystemRccClocks
  * @{
  */
void Printf_SystemRccClocks(void)
{
	uint8_t SYSCLKSource;

	RCC_ClocksTypeDef  SystemRCC_Clocks;
	printf("System start...\r\n");
	SYSCLKSource = RCC_GetSYSCLKSource();
	if(SYSCLKSource==0x04)
		printf("SYSCLKSource is HSE\r\n");
	else if(SYSCLKSource==0x00)
		printf("SYSCLKSource is HSI\r\n");
	else if(SYSCLKSource==0x08)
		printf("SYSCLKSource is PL!\r\n");
	
	RCC_GetClocksFreq(&SystemRCC_Clocks);
	printf("SYS clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.SYSCLK_Frequency/1000000);
	printf("HCLK clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.HCLK_Frequency/1000000);
	printf("PCLK1 clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.PCLK1_Frequency/1000000);
	printf("PCLK2_clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.PCLK2_Frequency/1000000);	
	printf("SADCCLK_Frequencyclock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.ADCCLK_Frequency/1000000);

}

/*******************************************************************************
* Function Name  : GizWits_ControlDeviceHandle
* Description    : Analy P0 Package
* Input          : None
* Output         : None
* Return         : Bit , Attr_Flags
* Attention		 : 
*******************************************************************************/
void GizWits_ControlDeviceHandle()
{
	if( (WirteTypeDef.Attr_Flags & (1<<0)) == (1<<0))
	{
		if(Set_LedStatus != 1)
		{
			if(WirteTypeDef.LED_Cmd == LED_OnOff)
			{
				LED_RGB_Control(0,0,0);
				ReadTypeDef.LED_Cmd = LED_OnOff;
				printf("SetLED_Off \r\n");
			}
			if(WirteTypeDef.LED_Cmd == LED_OnOn)
			{
				ReadTypeDef.LED_Cmd = LED_OnOn;
				LED_RGB_Control(254,0,0);
				printf("SetLED_On \r\n");
			}
		}
		
	}
	if( (WirteTypeDef.Attr_Flags & (1<<1)) == (1<<1))
	{
		if(WirteTypeDef.LED_Cmd == LED_Costom)
			{
				ReadTypeDef.LED_Cmd = LED_Costom;
				ReadTypeDef.LED_R = 0;
				ReadTypeDef.LED_G = 0;
				ReadTypeDef.LED_B = 0;
				Set_LedStatus = 0;
				LED_RGB_Control(0, 0, 0);
				printf("SetLED LED_Costom \r\n");
			}
			if(WirteTypeDef.LED_Cmd == LED_Yellow)
			{
				Set_LedStatus = 1;
				ReadTypeDef.LED_Cmd = LED_Yellow;
				ReadTypeDef.LED_R = 254;
				ReadTypeDef.LED_G = 254;
				ReadTypeDef.LED_B = 0;
				
				LED_RGB_Control(254, 254, 0);
				printf("SetLED LED_Yellow \r\n");
			}
					
			if(WirteTypeDef.LED_Cmd == LED_Purple)
			{
				ReadTypeDef.LED_Cmd = LED_Purple;
				ReadTypeDef.LED_R = 254;
				ReadTypeDef.LED_G = 0;
				ReadTypeDef.LED_B = 70;
				Set_LedStatus = 1;
				LED_RGB_Control(254, 0, 70);	
				printf("SetLED LED_Purple \r\n");
			}
			if(WirteTypeDef.LED_Cmd == LED_Pink)
			{
				ReadTypeDef.LED_Cmd = LED_Pink;
				ReadTypeDef.LED_R = 238;
				ReadTypeDef.LED_G = 30;
				ReadTypeDef.LED_B = 30;
				Set_LedStatus = 1;
				LED_RGB_Control(238 ,30 ,30);
				printf("SetLED LED_Pink \r\n");
			}
	}
	if( (WirteTypeDef.Attr_Flags & (1<<2)) == (1<<2))
	{
		if(Set_LedStatus != 1)
		{
			ReadTypeDef.LED_R = WirteTypeDef.LED_R;
			printf("W2D Control LED_R = %d \r\n",WirteTypeDef.LED_R);
			LED_RGB_Control(ReadTypeDef.LED_R,ReadTypeDef.LED_G,ReadTypeDef.LED_B);
		}
		
	}
	if( (WirteTypeDef.Attr_Flags & (1<<3)) == (1<<3))
	{
		if(Set_LedStatus != 1)
		{
			ReadTypeDef.LED_G = WirteTypeDef.LED_G;
			printf("W2D Control LED_G = %d \r\n",WirteTypeDef.LED_G);
			LED_RGB_Control(ReadTypeDef.LED_R,ReadTypeDef.LED_G,ReadTypeDef.LED_B);
		}
		
	}
	if( (WirteTypeDef.Attr_Flags & (1<<4)) == (1<<4))
	{
		if(Set_LedStatus != 1)
		{
			ReadTypeDef.LED_B = WirteTypeDef.LED_B;
			printf("W2D Control LED_B = %d \r\n",WirteTypeDef.LED_B);
			LED_RGB_Control(ReadTypeDef.LED_R,ReadTypeDef.LED_G,ReadTypeDef.LED_B);
		}
		
	}
	if( (WirteTypeDef.Attr_Flags & (1<<5)) == (1<<5))
	{
		ReadTypeDef.Motor = WirteTypeDef.Motor;
#ifdef MOTOR_16
		printf("W2D Control Motor = %d \r\n",exchangeBytes(WirteTypeDef.Motor));
		Motor_status(exchangeBytes(WirteTypeDef.Motor));
#else
		printf("W2D Control Motor = %d \r\n",WirteTypeDef.Motor);
		Motor_status(WirteTypeDef.Motor);
#endif
	}
}
/*******************************************************************************
* Function Name  : GizWits_GatherSensorData();
* Description    : Gather Sensor Data
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GizWits_GatherSensorData(void)
{
	ReadTypeDef.Infrared = IR_Handle();
	DHT11_Read_Data(&curTem, &curHum);
	ReadTypeDef.Temperature = (curTem + lastTem) /2;
	ReadTypeDef.Humidity = (curHum + lastHum)/2;

	ReadTypeDef.Temperature = ReadTypeDef.Temperature + 13;//Temperature Data Correction
	lastTem = curTem;
	lastHum = curHum;
}
/*******************************************************************************
* Function Name  : KEY_Handle
* Description    : Key processing function
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void KEY_Handle(void)
{
	uint8_t Key_return =0;	
	Key_return = ReadKeyValue();	
	if(Key_return & KEY_UP)
	{
		if(Key_return & PRESS_KEY1)
		{
#ifdef PROTOCOL_DEBUG
  				printf("KEY1 PRESS\r\n");
#endif		
		}
		if(Key_return & PRESS_KEY2)
		{
#ifdef PROTOCOL_DEBUG
			printf("KEY2 PRESS ,Soft AP mode\r\n");
#endif	
			//Soft AP mode, RGB red
			LED_RGB_Control(255, 0, 0);
			GizWits_D2WConfigCmd(SoftAp_Mode);
			NetConfigureFlag = 1;
		}				
	}

	if(Key_return & KEY_LONG)
	{
		if(Key_return & PRESS_KEY1)
		{
#ifdef PROTOCOL_DEBUG
				printf("KEY1 PRESS LONG ,Wifi Reset\r\n");
#endif			
			GizWits_D2WResetCmd();
		}
		if(Key_return & PRESS_KEY2)
		{
			//AirLink mode, RGB Green
#ifdef PROTOCOL_DEBUG
				printf("KEY2 PRESS LONG ,AirLink mode\r\n");
#endif	
			LED_RGB_Control(0, 128, 0);
			GizWits_D2WConfigCmd(AirLink_Mode);
			NetConfigureFlag = 1;
		}
	}
}
/*******************************************************************************
* Function Name  : GizWits_WiFiStatueHandle
* Description    : Callback function , Judge Wifi statue
* Input          : None
* Output         : None
* Return         : Bit , Attr_Flags
* Attention		 : 
*******************************************************************************/
void GizWits_WiFiStatueHandle(uint16_t wifiStatue) 
{	
	if(((wifiStatue & Wifi_ConnClouds) == Wifi_ConnClouds) && (NetConfigureFlag == 1))
	{
		printf("W2M->Wifi_ConnClouds\r\n");
		NetConfigureFlag = 0;
		LED_RGB_Control(0,0,0);
	}
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
