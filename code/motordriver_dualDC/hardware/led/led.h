/*
* LEDœ‘ æ
	LED0: PC13
	
*/

#ifndef __LED_H
#define __LED_H


#include "N76E003.h"
#include "Function_define.h"
#include "Common.h"

#include "SFR_Macro.h"
sbit	LED_0 	= P1^5;

#define		LED_0_IN()		do{P15_Input_Mode;}while(0)
#define		LED_0_OUT()		do{P15_PushPull_Mode;}while(0)
#define		LED_0(x)	do{LED_0 = x;}while(0)
#define		LED_0_RUN()	do{LED_0 = !LED_0;}while(0)
#define     LED0_ON()   LED_0(0)
#define     LED0_OFF()   LED_0(1)
void LED_Init(void);
#endif

