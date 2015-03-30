#ifndef __SYSTEM_TIME_H
#define __SYSTEM_TIME_H 	

#include <stm32f10x.h>
#include <system_stm32f10x.h>


void SystemTimeNVICConfig(void);
void SystemTime_Init(uint8_t SYSCLK);



#endif /*__SYSTEM_TIME_H*/



