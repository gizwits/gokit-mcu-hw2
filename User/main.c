/**
  ******************************************************************************
  * @file    mian.c
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

UART_HandleTypeDef         				UART_HandleStruct;
Pro_Wait_AckTypeDef           	  Wait_AckStruct;
Device_WirteTypeDef   					  Device_WirteStruct;    		
Device_ReadTypeDef                Device_ReadStruct; 

Pro_M2W_ReturnInfoTypeDef  				Pro_M2W_ReturnInfoStruct;
Pro_CommonCmdTypeDef      			 	Pro_CommonCmdStruct;
Pro_W2D_WifiStatusTypeDef     	 	Pro_W2D_WifiStatusStruct;     
Pro_CommonCmdTypeDef     	 				Pro_M2WResetCmdStruct;    		
Pro_D2W_ConfigWifiTypeDef       	Pro_D2WConfigCmdStruct;   		
Pro_D2W_ReportDevStatusTypeDef   	Pro_D2W_ReportStatusStruct;
KEY_StatusTypeDef 								KEY_Status;
uint8_t									 					SN;    
uint32_t SystemTimeCount = 0;
uint32_t ReportTimeCount = 0;

uint8_t Set_LedStatus = 0;


void McuStatusInit(void)
{
	printf("UART_HandleStruct Init...\r\n");
	memset(&UART_HandleStruct, 0, sizeof(UART_HandleStruct));
	memset(&Pro_CommonCmdStruct, 0, sizeof(Pro_CommonCmdStruct));
	Pro_CommonCmdStruct.Pro_HeadPart.Head[0] = 0XFF;
	Pro_CommonCmdStruct.Pro_HeadPart.Head[1] = 0XFF;	
	
	printf("Pro_CommonCmdStruct Init...\r\n");
	memset(&Pro_CommonCmdStruct, 0, sizeof(Pro_CommonCmdStruct));
	Pro_CommonCmdStruct.Pro_HeadPart.Head[0] = 0XFF;
	Pro_CommonCmdStruct.Pro_HeadPart.Head[1] = 0XFF;	
	
	
	memset(&Pro_M2W_ReturnInfoStruct, 0, sizeof(Pro_M2W_ReturnInfoStruct));
	Pro_M2W_ReturnInfoStruct.Pro_HeadPart.Head[0] = 0XFF; 
	Pro_M2W_ReturnInfoStruct.Pro_HeadPart.Head[1] = 0XFF;
	Pro_M2W_ReturnInfoStruct.Pro_HeadPart.Len = exchangeBytes(sizeof(Pro_M2W_ReturnInfoStruct) - 4);
	Pro_M2W_ReturnInfoStruct.Pro_HeadPart.Cmd = Pro_D2W__GetDeviceInfo_Ack_Cmd;
	memcpy(Pro_M2W_ReturnInfoStruct.Pro_ver, PRO_VER, strlen(PRO_VER));
	memcpy(Pro_M2W_ReturnInfoStruct.P0_ver, P0_VER, strlen(P0_VER));
	memcpy(Pro_M2W_ReturnInfoStruct.Hard_ver, HARD_VER, strlen(HARD_VER));
	memcpy(Pro_M2W_ReturnInfoStruct.Soft_ver, SOFT_VER, strlen(SOFT_VER));
	memcpy(Pro_M2W_ReturnInfoStruct.Product_Key, PRODUCT_KEY, strlen(PRODUCT_KEY));
	Pro_M2W_ReturnInfoStruct.Binable_Time = exchangeBytes(0);;		
	
	printf("Pro_D2W_ReportStatusStruct Init...\r\n");
	memset(&Pro_D2W_ReportStatusStruct, 0, sizeof(Pro_D2W_ReportStatusStruct));
	Pro_D2W_ReportStatusStruct.Pro_HeadPartP0Cmd.Pro_HeadPart.Head[0] = 0XFF;
	Pro_D2W_ReportStatusStruct.Pro_HeadPartP0Cmd.Pro_HeadPart.Head[1] = 0XFF;            
	Pro_D2W_ReportStatusStruct.Pro_HeadPartP0Cmd.Pro_HeadPart.Len = exchangeBytes(sizeof(Pro_D2W_ReportStatusStruct) - 4);
	Pro_D2W_ReportStatusStruct.Pro_HeadPartP0Cmd.Pro_HeadPart.Cmd = Pro_D2W_P0_Cmd;
	
	printf("Pro_M2WResetCmdStruct Init...\r\n");
	memset(&Pro_M2WResetCmdStruct, 0, sizeof(Pro_M2WResetCmdStruct));
	Pro_M2WResetCmdStruct.Pro_HeadPart.Head[0] = 0XFF;
	Pro_M2WResetCmdStruct.Pro_HeadPart.Head[1] = 0XFF;
	Pro_M2WResetCmdStruct.Pro_HeadPart.Len = exchangeBytes(sizeof(Pro_M2WResetCmdStruct) - 4);
	Pro_M2WResetCmdStruct.Pro_HeadPart.Cmd = Pro_D2W_ResetWifi_Cmd;
	
	printf("Pro_D2WConfigCmdStruct Init...\r\n");
	memset(&Pro_D2WConfigCmdStruct, 0, sizeof(Pro_D2WConfigCmdStruct));
	Pro_D2WConfigCmdStruct.Pro_HeadPart.Head[0] = 0XFF;
	Pro_D2WConfigCmdStruct.Pro_HeadPart.Head[1] = 0XFF;
	Pro_D2WConfigCmdStruct.Pro_HeadPart.Len = exchangeBytes(sizeof(Pro_D2WConfigCmdStruct) - 4);
	Pro_D2WConfigCmdStruct.Pro_HeadPart.Cmd = Pro_D2W_ControlWifi_Config_Cmd;	

	printf("Device_WirteStruct Init...\r\n");
	memset(&Device_WirteStruct, 0, sizeof(Device_WirteStruct));
	Device_WirteStruct.Motor = exchangeBytes(0x05);   //关闭电机
	
	printf("Device_ReadStruct Init...\r\n");
	memset(&Device_ReadStruct, 0, sizeof(Device_ReadStruct));
	
	printf("KEY_Status Init...\r\n");
	memset(&KEY_Status, 0, sizeof(KEY_Status));
	
}
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

void printf_DevStatus(void)
{
	Printf_TimeDisplay();
	
	printf("RGB LED R=%d,G=%d,B=%d; Motor=%d; Humidity=%d,Temperature=%d; Infrared=%d\r\n",
	Pro_D2W_ReportStatusStruct.Device_All.Device_Wirte.LED_R,Pro_D2W_ReportStatusStruct.Device_All.Device_Wirte.LED_G,Pro_D2W_ReportStatusStruct.Device_All.Device_Wirte.LED_B,
	exchangeBytes(Pro_D2W_ReportStatusStruct.Device_All.Device_Wirte.Motor),
	Pro_D2W_ReportStatusStruct.Device_All.Device_Read.Humidity,
	Pro_D2W_ReportStatusStruct.Device_All.Device_Read.Temperature,
	Pro_D2W_ReportStatusStruct.Device_All.Device_Read.Infrared);
	printf("------------------------------ReportDevStatus-------------------------------------\r\n");
}
	

void Hal_Init(void)
{
	RGB_LED_Init();
	printf("RGB LED Init OK\r\n");
	LED_GPIO_Init();
	printf("LED Init OK\r\n");
	TIM3_Int_Init(7199,9);   //1ms SystemTimeCount + 1
	printf("SystemTime Init OK\r\n");
	KEY_GPIO_Init();
	printf("KEY Init OK\r\n");
	Motor_Init();
	printf("Motor Init OK\r\n");
	Delay_Init(72);
	DHT11_Init();
	printf("DHT11 Init OK\r\n");
	IR_Init();
	printf("IR Init OK\r\n");
	OLED_Init();
	OLED_ShowString(40, 0, "GoKit");
	OLED_ShowString(0, 32, "www.gizwits.com");	
	
	
}

void ReportDevStatusHandle(void);

int main(void)
{
	SystemInit();
	UARTx_Init();
	Printf_SystemRccClocks();
	RTC_Init();
	Hal_Init();
	McuStatusInit();
	
	while(1)
	{
		MessageHandle();
		KEY_Handle();		
		IR_Handle();
		DHT11_Read_Data(&Device_ReadStruct.Temperature, &Device_ReadStruct.Humidity);
		ReportDevStatusHandle();
	}
}

void ReportDevStatusHandle(void)
{
	uint8_t Device_Status = 0;
	if(ReportTimeCount >= 3000)
	{
		ReportTimeCount = 0;
		Device_Status = memcmp(&Device_ReadStruct,&Pro_D2W_ReportStatusStruct.Device_All.Device_Read, sizeof(Device_ReadStruct));
		if(Device_Status)
		{
			Pro_D2W_ReportDevStatusHandle();
		}	
	}
}




