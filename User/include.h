

#ifndef _INCLUDE_H
#define _INCLUDE_H


#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <stm32f10x.h>
#include <time.h>

#include "stm32f10x_tim.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_bkp.h"
#include "delay.h"
#include "sys.h"


#include "./GPIO/sa_gpio.h"
#include "./Hal_Usart/hal_uart.h"
#include "./Protocol/Protocol.h"
#include "./Hal_key/Hal_key.h"
#include "./hal_rgb_led/hal_rgb_led.h"
#include "./Hal_led/Hal_led.h"
#include "./hal_motor/hal_motor.h"
#include "./hal_temp_hum/hal_temp_hum.h"
#include "./hal_infrared/hal_infrared.h"
#include "./Hal_OLED/Hal_OLED.h"
#include "System_time.h"
#include "RTC.h"


#endif /*_INCLUDE_H*/




