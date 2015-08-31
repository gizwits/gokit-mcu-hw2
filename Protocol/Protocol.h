#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdio.h>
#include <stdbool.h>
#include <stm32f10x.h>


#define SoftAp_Mode    0x01
#define AirLink_Mode   0x02

#define MAX_P0_LEN			128 	 		 //p0数据最大长度
#define MAX_PACKAGE_LEN		(MAX_P0_LEN*2) 	 //数据缓冲区最大长度
#define MAX_RINGBUFFER_LEN	MAX_PACKAGE_LEN  //环形缓冲区最大长度
#define Max_UartBuf         MAX_PACKAGE_LEN  //串口数据缓冲区最大长度


#define PROTOCOL_DEBUG //调试通信数据信息宏开关
//#define DEBUG          //系统运行调试信息

#define Send_MaxTime   300
#define Send_MaxNum    2

#define		PRO_VER																"00000004"
#define		P0_VER																"00000004"
#define		HARD_VER															"00000001"
#define		SOFT_VER															"00000001"
#define		PRODUCT_KEY															"6f3074fe43894547a4f1314bd7e3ae0b"

__packed	typedef struct
{
    uint8_t             			Message_Buf[Max_UartBuf]; //串口接收缓冲区
    uint8_t             			Message_Len;	          //接受到的数据长度
} UART_HandleTypeDef;

/*命令码*/
typedef enum
{
    Pro_W2D_GetDeviceInfo_Cmd 					= 0x01,
    Pro_D2W__GetDeviceInfo_Ack_Cmd				= 0x02,

    Pro_W2D_P0_Cmd 								= 0x03,
    Pro_D2W_P0_Ack_Cmd							= 0x04,

    Pro_D2W_P0_Cmd 								= 0x05,
    Pro_W2D_P0_Ack_Cmd							= 0x06,

    Pro_W2D_Heartbeat_Cmd 						= 0x07,
    Pro_D2W_heartbeatAck_Cmd					= 0x08,

    Pro_D2W_ControlWifi_Config_Cmd 				= 0x09,
    Pro_W2D_ControlWifi_Config_Ack_Cmd			= 0x0A,

    Pro_D2W_ResetWifi_Cmd 						= 0x0B,
    Pro_W2D_ResetWifi_Ack_Cmd					= 0x0C,

    Pro_W2D_ReportWifiStatus_Cmd 				= 0x0D,
    Pro_D2W_ReportWifiStatus_Ack_Cmd			= 0x0E,

    Pro_W2D_ReportMCUReset_Cmd 					= 0x0F,
    Pro_D2W_ReportMCUReset_Ack_Cmd				= 0x10,

    Pro_W2D_ErrorPackage_Cmd 					= 0x11,
    Pro_D2W_ErrorPackage_Ack_Cmd				= 0x12,
	
	/*3.10*/
	

} Pro_CmdTypeDef;


typedef enum
{
    SetLED_OnOff    = 0x01,
    SetLED_Color    = 0x02,
    SetLED_R       	= 0x04,
    SetLED_G    	= 0x08,
    SetLED_B  		= 0x10,
    SetMotor		= 0x20,

} Attr_FlagsTypeDef;

typedef enum
{
    LED_OnOff         = 0x00,
    LED_OnOn          = 0x01,
    LED_Costom        = 0x00,
    LED_Yellow    	  = 0x02,
    LED_Purple  	  = 0x04,
    LED_Pink		  = 0x06,

} LED_ColorTypeDef;


/******************************************************
* 重发机制结构体
********************************************************/
__packed	typedef struct
{
    uint32_t        SendTime;//重发的系统时间
    uint8_t			SendNum;//重发次数
    uint8_t			Flag;//1,表示有需要等待的ACK;0,表示无需要等待的ACK
    uint16_t        ResendBufLen;
    uint8_t			Cmd_Buff[Max_UartBuf];//重发数据缓冲区
} Pro_Wait_AckTypeDef;


/******************************************************
* 协议标准头
********************************************************/
__packed	typedef struct
{
    uint8_t							Head[2];
    uint16_t						Len;
    uint8_t							Cmd;
    uint8_t							SN;
    uint8_t							Flags[2];

} Pro_HeadPartTypeDef;

/******************************************************
* 4.1  WiFi模组请求设备信息
********************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef  					Pro_HeadPart;
    uint8_t									Pro_ver[8];
    uint8_t									P0_ver[8];
    uint8_t									Hard_ver[8];
    uint8_t									Soft_ver[8];
    uint8_t									Product_Key[32];
    uint16_t								Binable_Time;
    uint8_t									Sum;

} Pro_M2W_ReturnInfoTypeDef;

/*****************************************************
* 协议通用数据帧(4.2、4.4、4.6、4.9、4.10)
******************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef    	Pro_HeadPart;
    uint8_t					Sum;
} Pro_CommonCmdTypeDef;


/******************************************************
* 4.3 设备MCU通知WiFi模组进入配置模式
********************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef  		Pro_HeadPart;
    uint8_t                 	Config_Method;
    uint8_t						Sum;
} Pro_D2W_ConfigWifiTypeDef;


/*****************************************************
* WiFi模组工作状态
******************************************************/
#define 		Wifi_SoftAPMode       			(uint8_t)(1<<0)    //SoftAP
#define 		Wifi_StationMode      	    	(uint8_t)(1<<1)    //Station
#define 		Wifi_ConfigMode       		  	(uint8_t)(1<<2)    //
#define 		Wifi_BindingMode     			(uint8_t)(1<<3)    //
#define     	Wifi_ConnRouter             	(uint8_t)(1<<4)    //
#define     	Wifi_ConnClouds             	(uint8_t)(1<<5)    //
/*****************************************************
* 4.5 WiFi模组向MCU通知WiFi模组工作状态的变化
******************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef    	Pro_HeadPart;
    uint16_t                Wifi_Status;
    uint8_t					Sum;
} Pro_W2D_WifiStatusTypeDef;

/*****************************************************
* 非法报文类型
******************************************************/
typedef enum
{
    Error_AckSum = 0x01,      //校验错误
    Error_Cmd 	 = 0x02,	  //命令码错误
    Error_Other  = 0x03,      //其他
} Error_PacketsTypeDef;


/*****************************************************
* 4.7 非法消息通知
******************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef  		Pro_HeadPart;
    Error_PacketsTypeDef		Error_Packets;
    uint8_t						Sum;
} Pro_ErrorCmdTypeDef;


/*****************************************************
* P0 command 命令码
******************************************************/
typedef enum
{
    P0_W2D_Control_Devce_Action 		= 0x01,
    P0_W2D_ReadDevStatus_Action 		= 0x02,
    P0_D2W_ReadDevStatus_Action_ACK 	= 0x03,
    P0_D2W_ReportDevStatus_Action   	= 0X04,

} P0_ActionTypeDef;


/******************************************************
* P0报文标准头
********************************************************/
__packed	typedef struct
{
    Pro_HeadPartTypeDef  		Pro_HeadPart;
    P0_ActionTypeDef        	Action;
} Pro_HeadPartP0CmdTypeDef;

short	exchangeBytes(short	value);
uint8_t CheckSum( uint8_t *buf, int packLen );
void GizWits_init(uint8_t P0_Len);
void GizWits_D2WResetCmd(void);
void GizWits_D2WConfigCmd(uint8_t WiFi_Mode);
void GizWits_DevStatusUpgrade(uint8_t *P0_Buff, uint32_t Time, uint8_t flag);
void GizWits_WiFiStatueHandle(uint16_t wifiStatue);
u8 GizWits_MessageHandle(u8 * Message_Buf, u8 Length_buf);

#endif /*_PROTOCOL_H*/
