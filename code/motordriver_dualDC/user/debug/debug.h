#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "define.h"
#include "led.h"

//#define _DEBUG_LED_

#ifdef _DEBUG_LED_
    #define	debug_led0 led0
    #define debug_led0_set(x) do{debug_led0 = x;}while(0)
    #define debug_led0_run() do{debug_led0 = !debug_led0;}while(0)
    #define debug_led0_on() do{debug_led0 = 0;}while(0)
    #define debug_led0_off() do{debug_led0 = 1;}while(0)

#else
    
    #define debug_led0_set(x) //do{debug_led0 = x;}while(0)
    #define debug_led0_run() //do{debug_led0 = !debug_led0;}while(0)
    #define debug_led0_on() //debug_led0(0)
    #define debug_led0_off() //debug_led0(1)
#endif
    
#endif


