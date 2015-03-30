#ifndef _RTC_H
#define _RTC_H


#include "include.h"



/* Private function prototypes -----------------------------------------------*/
void RTC_Init(void);
void Time_Display(void);
void Time_Regulate(void);
struct tm Time_GetCalendarTime(void);
void Printf_TimeDisplay(void);

#endif /*_RTC_H*/


