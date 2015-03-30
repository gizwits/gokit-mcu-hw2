#include "RTC.h"



void Time_Set(u32 t);

/*******************************************************************************
* Function Name  : Time_ConvUnixToCalendar
* Description    : 转换UNIX时间戳为日历时间
* Input          : - t: 当前时间的UNIX时间戳
* Output         : None
* Return         : struct tm
* Attention		 : None
*******************************************************************************/
struct tm Time_ConvUnixToCalendar(time_t t)
{
	struct tm *t_tm;
	t_tm = localtime(&t);
	t_tm->tm_year += 1900;	/* localtime转换结果的tm_year是相对值，需要转成绝对值 */
	return *t_tm;
}

/*******************************************************************************
* Function Name  : Time_ConvCalendarToUnix
* Description    : 写入RTC时钟当前时间
* Input          : - t: struct tm
* Output         : None
* Return         : time_t
* Attention		 : None
*******************************************************************************/
time_t Time_ConvCalendarToUnix(struct tm t)
{
	t.tm_year -= 1900;  /* 外部tm结构体存储的年份为2008格式	*/
						/* 而time.h中定义的年份格式为1900年开始的年份 */
						/* 所以，在日期转换时要考虑到这个因素。*/
	return mktime(&t);
}


/*******************************************************************************
* Function Name  : Time_GetUnixTime
* Description    : 从RTC取当前时间的Unix时间戳值
* Input          : None
* Output         : None
* Return         : time_t
* Attention		 : None
*******************************************************************************/
time_t Time_GetUnixTime(void)
{
	return (time_t)RTC_GetCounter();
}

/*******************************************************************************
* Function Name  : Time_GetCalendarTime
* Description    : 从RTC取当前时间的日历时间（struct tm）
* Input          : None
* Output         : None
* Return         : struct tm
* Attention		 : None
*******************************************************************************/
struct tm Time_GetCalendarTime(void)
{
	time_t t_t;
	struct tm t_tm;

	t_t = (time_t)RTC_GetCounter();
	t_tm = Time_ConvUnixToCalendar(t_t);
	return t_tm;
}

/*******************************************************************************
* Function Name  : Time_SetUnixTime
* Description    : 将给定的Unix时间戳写入RTC
* Input          : - t: time_t 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Time_SetUnixTime(time_t t)
{
	RTC_WaitForLastTask();
	RTC_SetCounter((u32)t);
	RTC_WaitForLastTask();
	return;
}

/*******************************************************************************
* Function Name  : Time_SetCalendarTime
* Description    : 将给定的Calendar格式时间转换成UNIX时间戳写入RTC
* Input          : - t: struct tm
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Time_SetCalendarTime(struct tm t)
{
	Time_SetUnixTime(Time_ConvCalendarToUnix(t));
	return;
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the RTC.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void RTC_Configuration(void)
{
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}

/*******************************************************************************
* Function Name  : Time_Regulate
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Time_Regulate(void)
{
  struct tm time;

  memset(&time, 0 , sizeof(time) );	/* 清空结构体 */
	time.tm_year = 2014;
	time.tm_mon= 12;
	time.tm_mday = 29;
	time.tm_hour = 22;
	time.tm_min = 9;
	time.tm_sec = 0;
  Time_SetCalendarTime(time);  
}

/*******************************************************************************
* Function Name  : RTC_Init
* Description    : RTC Initialization
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None	
*******************************************************************************/
void RTC_Init(void)
{

  if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
  {
    /* Backup data register value is not correct or not yet programmed (when
       the first time the program is executed) */

    printf("RTC not yet configured....\r\n");

    /* RTC Configuration */
    RTC_Configuration();

	Time_Regulate();

	/* Adjust time by values entred by the user on the hyperterminal */

    printf("RTC configured....\r\n");

    BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
  }
  else
  {
    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
      printf("Power On Reset occurred....\r\n");
    }
    /* Check if the Pin Reset flag is set */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
      printf("External Reset occurred....\r\n");
    }

    printf("No need to configure RTC....\r\n");
    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }

   /* NVIC configuration */
   NVIC_Configuration();

#ifdef RTCClockOutput_Enable
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Disable the Tamper Pin */
  BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
                                 functionality must be disabled */

  /* Enable RTC Clock Output on Tamper Pin */
  BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif

   /* Clear reset flags */
  RCC_ClearFlag();
  return;
}

/*******************************************************************************
* Function Name  : Time_Display
* Description    : Printf Time
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Printf_TimeDisplay(void)
{
   struct tm time;
   time = Time_GetCalendarTime();
   printf("Time: %d-%d-%d   %02d:%02d:%02d\r\n", time.tm_year, \
                   time.tm_mon, time.tm_mday,\
                   time.tm_hour, time.tm_min, time.tm_sec);
}
