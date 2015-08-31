/**
********************************************************
*
* @file      hal_uart.c
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
#include "stm32f10x_rcc.h"
#include "Hal_Usart/hal_uart.h"

#ifdef __GNUC__
// With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf set to 'Yes') calls __io_putchar()
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/*********************************************************************
  * @brief  UART GPIO configuration
	* @param  None
  * @retval None
	* @date   20141205
***********************************************************************/
void UART_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

#if defined (Open_UART1)
    USART1_GPIO_Cmd(USART1_GPIO_CLK, ENABLE);
    USART1_AFIO_Cmd(USART1_AFIO_CLK, ENABLE);
    USART1_CLK_Cmd(USART1_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = USART1_TxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART1_RxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART1_GPIO_PORT, &GPIO_InitStructure);
#endif

#if defined (Open_UART2)
    USART2_GPIO_Cmd(USART2_GPIO_CLK, ENABLE);
    USART2_CLK_Cmd(USART2_CLK, ENABLE);
    USART2_AFIO_Cmd(USART2_AFIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = USART2_TxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART2_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART2_RxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART2_GPIO_PORT, &GPIO_InitStructure);
#endif
#if defined (Open_UART3)
    USART3_GPIO_Cmd(USART3_GPIO_CLK, ENABLE);
    USART3_CLK_Cmd(USART3_CLK, ENABLE);
    USART3_AFIO_Cmd(USART3_AFIO_CLK, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);

    GPIO_InitStructure.GPIO_Pin = USART3_TxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART3_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART3_RxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART3_GPIO_PORT, &GPIO_InitStructure);
#endif
}
/*********************************************************************
  * @brief  UART configuration
	* @param  None
  * @retval None
	* @date   20141205
***********************************************************************/
void UART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
#if defined (Open_UART1)
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

//	USART_Cmd(USART1, ENABLE);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART1, ENABLE);
    /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
    如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART1, USART_FLAG_TC); /* 清发送完成标志，Transmission Complete flag */
#endif

#if defined (Open_UART2)
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART2, ENABLE);
    /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
    如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART2, USART_FLAG_TC); /* 清发送完成标志，Transmission Complete flag */
#endif

#if defined (Open_UART3)
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3, ENABLE);
		
    /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
    如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART3, USART_FLAG_TC); /* 清发送完成标志，Transmission Complete flag */
#endif

}

/*********************************************************************
  * @brief  Initialize the NCIC
	* @param  None
  * @retval None
	* @date   20141205
***********************************************************************/
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
#if defined (Open_UART1)
    //使能串口中断，并设置优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

#if defined (Open_UART2)
    //使能串口中断，并设置优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

#if defined (Open_UART3)
    //使能串口中断，并设置优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
}

/*********************************************************************
  * @brief  UART2 Send DATA.
	* @param  None
  * @retval None
	* @date   20141205
***********************************************************************/
void UART2_Send_DATA(uint8_t data)
{
    USART_SendData(USART2,data);
    //Loop until the end of transmission
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

/*********************************************************************
  * @brief  UART1 Send DATA.
	* @param  None
  * @retval None
	* @date   20141205
***********************************************************************/
void UART1_Send_DATA(uint8_t data)
{
    USART_SendData(USART1,data);
    //Loop until the end of transmission
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/*********************************************************************
  * @brief  Initializes the UART peripheral.
	* @param  None
  * @retval None
	* @date   20141205
***********************************************************************/
void UARTx_Init(void)
{
    UART_GPIO_Init();
    UART_Config();
    NVIC_Configuration();
}


//不使用半主机模式, 如果没有这段，则需要在target选项中选择使用USE microLIB
// #if 1
// #pragma import(__use_no_semihosting)
// struct __FILE
// {
// 	int handle;
// };
// FILE __stdout;

// _sys_exit(int x)
// {
// 	x = x;
// }
// #endif

PUTCHAR_PROTOTYPE
{
    //Place your implementation of fputc here , e.g. write a character to the USART
    USART_SendData(USART1,(u8)ch);
    //Loop until the end of transmission
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}
