#ifndef __LED_H__
#define __LED_H__

#include "define.h"
#include "debug.h"


sbit	led0 	= P1^5;
#define     led0_config()   do{led0 = 1; P15_PushPull_Mode;}while(0)

#ifndef _DEBUG_LED_
    #define led0_set(x) do{led0 = x;}while(0)
    #define led0_run() do{led0 = !led0;}while(0)
    #define led0_on() do{led0 = 0;}while(0)
    #define led0_off() do{led0 = 1;}while(0)

#else
    
    #define led0_set(x) //do{led0 = x;}while(0)
    #define led0_run() //do{led0 = !led0;}while(0)
    #define led0_on() //led0(0)
    #define led0_off() //led0(1)
#endif

void led_init(void);
#endif

