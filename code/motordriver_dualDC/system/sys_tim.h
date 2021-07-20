#ifndef __sys_tim_H__
#define __sys_tim_H__

#include "define.h"
#include "adc.h"

//ϵͳʱ�ӷ�Ƶ��16MHz�ڲ�ʱ�ӣ�0������Ƶ�� 1��2����CKDIV��Ƶ
#define C_ClockDiv_SET		0
#define	C_TIM0_Reload		(65535-16000)		//100us
/*
#if C_ClockDiv_SET
	#define	C_TIM0_Reload		(65535-800/C_ClockDiv_SET)		//100us
#else
	#define	C_TIM0_Reload		(65535-1600)		//100us
#endif
*/

extern xdata uint8_t F_sys_tim_1ms;
extern xdata uint8_t F_sys_tim_250ms;
extern xdata uint8_t F_sys_tim_100ms;
extern xdata uint8_t F_sys_tim_1s;


extern bit F_LED_Blink;
void sys_tim_Init(void );
void systick_Handler(void );
#endif




