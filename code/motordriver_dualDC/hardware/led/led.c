/*
* LED.c

*/

#include "led.h"
#include "sys_tim.h"

void LED_Init()
{
	LED_0_OUT();
	LED_0(1);
}



