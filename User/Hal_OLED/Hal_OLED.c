/**
  ******************************************************************************
  * @file    Hal_OLED.c
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
#include "Hal_OLED.h"

uint8_t OLED_GRAM[128][8];

/*********************************************************************
  * @brief  Initializes the OLED GPIOx peripheral.
  * @param  None
  * @retval Success : ReceiveData
	*         Failure : 0    
	* @date   20141204
***********************************************************************/
uint8_t SPIx_WriteByte(uint8_t Data)
{
	uint8_t Retry = 0;
	while(SPI_I2S_GetFlagStatus(OLED_SPIx, SPI_I2S_FLAG_TXE) == RESET) 
	{
		if(++ Retry > 200)
			return 0;
	}			  
	SPI_I2S_SendData(OLED_SPIx, Data); 
	Retry=0;

	while(SPI_I2S_GetFlagStatus(OLED_SPIx, SPI_I2S_FLAG_RXNE) == RESET) 
	{
		if(++ Retry > 200)
			return 0;
	}	  						    
	return SPI_I2S_ReceiveData(OLED_SPIx); 
}
/*********************************************************************
  * @brief  Initializes the OLED GPIOx peripheral.
	* @param  uint8_t Data :  Data
	*         uint8_t Cmd  :  Command
  * @retval None   
	* @date   20141204
***********************************************************************/
void OLED_WriteByte(uint8_t Data, uint8_t Cmd)
{
	OLED_CS_RESET();
	if(Cmd)
	{
		OLED_DC_SET();
	}
	else
	{
		OLED_DC_RESET();
	}
		
	SPIx_WriteByte(Data);
	OLED_DC_SET();
	OLED_CS_SET();
}

/*********************************************************************
  * @brief  Initializes the OLED GPIOx peripheral.
  * @param  None
  * @retval None
	* @date   20141204
***********************************************************************/
void OLED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(OLED_SPIx_MISO_CLK | OLED_SPIx_SCK_CLK | OLED_SPIx_MOSI_CLK, ENABLE); 	
 
/**************Enables the High Speed APB2 (CS DC RES) peripheral clock********/	
	RCC_APB2PeriphClockCmd(OLED_CS_CLK | OLED_DC_CLK | OLED_RES_CLK, ENABLE); 
	 
	GPIO_InitStructure.GPIO_Pin = OLED_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_CS_PORT, &GPIO_InitStructure);
	
	OLED_CS_SET();
	GPIO_InitStructure.GPIO_Pin = OLED_DC_PIN;
	GPIO_Init(OLED_DC_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = OLED_RES_PIN;
	GPIO_Init(OLED_RES_PORT, &GPIO_InitStructure);
	
	OLED_DC_RESET();
	OLED_RES_RESET();
}


/*********************************************************************
  * @brief  Initializes the OLED SPI peripheral.
  * @param  None
  * @retval None
	* @date   20141204
***********************************************************************/

void OLED_SPI_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	OLED_SPIx_CLK_Cmd(OLED_SPIx_CLK, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = OLED_SPIx_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_SPIx_MOSI_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = OLED_SPIx_MISO_PIN;
	GPIO_Init(OLED_SPIx_MISO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = OLED_SPIx_SCK_PIN;
	GPIO_Init(OLED_SPIx_SCK_PORT, &GPIO_InitStructure);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
	SPI_InitStructure.SPI_CRCPolynomial = 7;	
	SPI_Init(OLED_SPIx, &SPI_InitStructure); 
	
	SPI_Cmd(OLED_SPIx, ENABLE); 
	
}


/*********************************************************************
  * @brief  Initializes the OLED.
  * @param  None
  * @retval None
	* @date   20141204
***********************************************************************/
void OLED_Init(void)
{
	OLED_GPIO_Init();
	OLED_SPI_Init();
	
	OLED_RES_SET();

	OLED_WriteByte(0xAE, OLED_CMD);//--turn off oled panel
	OLED_WriteByte(0x00, OLED_CMD);//---set low column address
	OLED_WriteByte(0x10, OLED_CMD);//---set high column address
	OLED_WriteByte(0x40, OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WriteByte(0x81, OLED_CMD);//--set contrast control register
	OLED_WriteByte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
	OLED_WriteByte(0xA1, OLED_CMD);//--Set SEG/Column Mapping     
	OLED_WriteByte(0xC0, OLED_CMD);//Set COM/Row Scan Direction   
	OLED_WriteByte(0xA6, OLED_CMD);//--set normal display
	OLED_WriteByte(0xA8, OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WriteByte(0x3f, OLED_CMD);//--1/64 duty
	OLED_WriteByte(0xD3, OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WriteByte(0x00, OLED_CMD);//-not offset
	OLED_WriteByte(0xd5, OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WriteByte(0x80, OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WriteByte(0xD9, OLED_CMD);//--set pre-charge period
	OLED_WriteByte(0xF1, OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WriteByte(0xDA, OLED_CMD);//--set com pins hardware configuration
	OLED_WriteByte(0x12, OLED_CMD);
	OLED_WriteByte(0xDB, OLED_CMD);//--set vcomh
	OLED_WriteByte(0x40, OLED_CMD);//Set VCOM Deselect Level
	OLED_WriteByte(0x20, OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WriteByte(0x02, OLED_CMD);//
	OLED_WriteByte(0x8D, OLED_CMD);//--set Charge Pump enable/disable
	OLED_WriteByte(0x14, OLED_CMD);//--set(0x10) disable
	OLED_WriteByte(0xA4, OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WriteByte(0xA6, OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WriteByte(0xAF, OLED_CMD);//--turn on oled panel
	LCD_Clear(0x00);

}



/********************************************************************
  * @brief  Enables the Display         
  * @param  None         
  * @retval  None
	* @date   20141204
********************************************************************/ 
void OLED_DisplayOn(void)
{
	OLED_WriteByte(0X8D, OLED_CMD);  
	OLED_WriteByte(0X14, OLED_CMD);  
	OLED_WriteByte(0XAF, OLED_CMD);  
}

/********************************************************************
  * @brief  Disables the Display        
  * @param  None        
  * @retval  None
	* @date   20141204
********************************************************************/
void OLED_DisplayOff(void)
{
	OLED_WriteByte(0X8D, OLED_CMD);  
	OLED_WriteByte(0X10, OLED_CMD);  
	OLED_WriteByte(0XAE, OLED_CMD);  
}

/*********************************************************************
  * @brief  OLED Refresh Gram
  * @param  None
  * @retval None
	* @date   20141204
***********************************************************************/
void OLED_Refresh_Gram(void)
{
	uint8_t i, n;
	for(i = 0; i < 8; i ++)  
	{  
		OLED_WriteByte(0xb0 + i, OLED_CMD);  
		OLED_WriteByte(0x00, OLED_CMD);      
		OLED_WriteByte(0x10, OLED_CMD);         
		for(n = 0; n < 128; n ++)
		{
			OLED_WriteByte(OLED_GRAM[n][i], OLED_DAT); 
		}
	}   
}

/*********************************************************************
  * @brief  OLED Clear Screen.
  * @param  None
  * @retval None
	* @date   20141204
***********************************************************************/
void LCD_Clear(uint8_t Color)
{
	uint8_t i, n;
	
	for(i = 0; i < 8; i ++)
	{
		for(n = 0; n < 128; n ++)
		{
			OLED_GRAM[n][i] = Color;
		}
	}
	OLED_Refresh_Gram();
}
/*********************************************************************
  * @brief  OLED Draw Point.
  * @param  X:
  *   This parameter can be one of the following values:
  *     @arg X: where x can be 0..127
  * @param  Y: 
  *   This parameter can be one of the following values:
	* @param  uint8_t Fill : 
  *     @arg where Fill can be 0 or 1
  * @retval None
	* @date   20141204
***********************************************************************/
void OLED_DrawPoint(uint8_t Xpos,uint8_t Ypos,uint8_t Fill)
{
	uint8_t Pos, Bx, Temp = 0;
	
	if(Xpos > 127 || Ypos > 63)
		return;
	Pos = 7 - Ypos / 8;
	Bx = Ypos % 8;
	Temp = 1 << (7 - Bx);
	if(Fill)
	{
		OLED_GRAM[Xpos][Pos] |= Temp;
	}
	else 
	{
		OLED_GRAM[Xpos][Pos] &= ~Temp;	 
	}
//	OLED_Refresh_Gram();
}


/**********************************************************************
  * @brief  Displays one character   
  *         
  * @param  X:
  *   This parameter can be one of the following values:
  *     @arg X: where x can be 0..127
  * @param  Y: 
  *   This parameter can be one of the following values:
  *     @arg Y: where y can be 0..63
  * @param  Chr: character ascii code,must be between 0x20 and 0x7e.
  * @param  Size: specifies the size of the font(12 or 16)
  * @param Mode: whether reverses the character
  *   This paramter can be one of following value;
  *   @arg Mode: where Mode can be 0 or 1
  * @retval None
  * @date   20141204
**********************************************************************/

void OLED_ShowChar(uint8_t X, uint8_t Y, uint8_t Chr, uint8_t Size, uint8_t Mode)
{      	
	uint8_t Temp, t, t1;
	uint8_t y0 = Y;
	
	Chr = Chr - ' ';				   
    for(t = 0; t < Size; t ++)
    {   
			if(Size == 12)
			{
				Temp = OLED_Asc2_1206[Chr][t];  
			}
			else 
			{
				Temp = OLED_Asc2_1608[Chr][t];
			}
			for(t1 = 0; t1 < 8; t1 ++)
			{
				if(Temp & 0x80)
					OLED_DrawPoint(X, Y, Mode);
				else 
					OLED_DrawPoint(X, Y, !Mode);
					Temp <<= 1;
					Y ++;
					if((Y - y0) == Size)
					{
						Y = y0;
						X ++;
						break;
					}
			}  	 
    } 
		
}

/**********************************************************************
  * @brief  Displays character string  
  *         
  * @param  X:
  *   This parameter can be one of the following values:
  *     @arg X: where x can be 0..127
  * @param  Y: 
  *   This parameter can be one of the following values:
  *     @arg Y: where y can be 0..63
  * @param  *Str: .character string
  * @retval None
  * @date   20141204
**********************************************************************/
void OLED_ShowString(uint8_t X, uint8_t Y, const uint8_t *Str)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58
	
    while(*Str != '\0')
    {       
        if(X > MAX_CHAR_POSX)
		{
			X = 0;
			Y += 16;
		}
        if(Y > MAX_CHAR_POSY)
		{
			Y = X = 0;
			LCD_Clear(0x00);
		}
        OLED_ShowChar(X, Y, *Str, 16, 1);	 
        X += 8;
        Str ++;
    } 
		OLED_Refresh_Gram();
}
