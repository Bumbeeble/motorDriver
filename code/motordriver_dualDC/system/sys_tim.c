#include "sys_tim.h"
#include "led.h"
#include "adc.h"
static xdata uint8_t cnt_sys_tim_1ms = 0;
static xdata uint8_t cnt_sys_tim_250ms = 0;
static xdata uint8_t cnt_sys_tim_100ms = 0;
static xdata uint8_t cnt_sys_tim_1s = 0;

xdata uint8_t F_sys_tim_1ms = 0;
xdata uint8_t F_sys_tim_250ms = 0;
xdata uint8_t F_sys_tim_100ms = 0;
xdata uint8_t F_sys_tim_1s = 0;

#define	C_TIM_LED_Blink	250
static xdata uint8_t cnt_LED_Blink = 0;
bit F_LED_Blink = 0;

xdata F_systick = 0;
//time base handler
void systick_Handler()
{
	//---------------1ms----------------------------------------
	if(F_systick == 0)
		return;
	F_systick = 0;
	F_sys_tim_1ms = 1;
	//LED
	cnt_LED_Blink++;
	if(cnt_LED_Blink >= C_TIM_LED_Blink)
	{
		cnt_LED_Blink = 0;
		F_LED_Blink = !F_LED_Blink;
	}
//	F_TIM_LEDRUN = 1;
	F_TIM_ADCValue = 1;
	
	cnt_sys_tim_100ms++;
	if(cnt_sys_tim_100ms >= 100)
	{
		cnt_sys_tim_100ms = 0;
		F_sys_tim_100ms = 1;
	}
	//-------------------------------------------------
	cnt_sys_tim_250ms++;
	if(cnt_sys_tim_250ms>=250)
	{
		cnt_sys_tim_250ms = 0;
		F_sys_tim_250ms = 1;
		//-----------------250ms-------------------------
		cnt_sys_tim_1s++;
		if(cnt_sys_tim_1s >= 4)
		{
			cnt_sys_tim_1s = 0;
			F_sys_tim_1s = 1;
		}

	}
}
#define c_cnt_systick_Set 10
xdata uint8_t cnt_systick = 0;

/**
  * @brief  This function handles sys_tim Handler.
  * @param  None
  * @retval None
	* 100us 
  */
void sys_tim_Interrupt(void)  interrupt 1  //interrupt address is 0x000B
{
	//Read_Encoder();
	TH0 += C_TIM0_Reload/256;
  TL0 += C_TIM0_Reload%256;
	cnt_systick++;
	F_systick = 1;
	if(cnt_systick >= c_cnt_systick_Set)
	{
		//1ms
		cnt_systick = 0;
		
	}
	
}


void sys_tim_Init(void)
{
	//system clock division
	CKDIV = 0;//C_ClockDiv_SET;				//系统时钟16M，1/4分频，4MHz主频
	
	
	//TIMER0_MODE1_ENABLE;
	TMOD&=0xF0;
	TMOD|=0x01;
	set_T0M;					//选择不分频，默认为51默认的12分频
	TH0 = C_TIM0_Reload/256;
	TL0 = C_TIM0_Reload%256; 
	set_ET0;
	set_TR0;
}


