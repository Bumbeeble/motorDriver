//-------------chip----------------------
#include "define.h"
//-------------system----------------------
#include "sys_tim.h"
#include "wdt.h"
//-------------hardware----------------------
#include "uart1.h"

#include "motordriver.h"

#include "display.h"

bit BIT_TMP;
char char_buf[20] = {0};
//The main C function
void main (void) 
{
	WDT_Clear();
    All_interrupt_OFF();
    
	sys_tim_Init();					//系统定时
    UART_Init(C_BaudRate_Set);
	Enable_WDT_Reset_Config();			//配置CONFIG4，打开WDT
	WDT_config(WDTPS_1638ms);			//WDT时间设为1.638s
	//WDT_Stop();
	led_init();						//LED
	ADC_Config();
    display_init();
    motordriver_init();
	All_interrupt_ON();
    
	printf("\nSystem start...\n");
	while(1)
	{
		//主循环
		WDT_Clear();
		Read_ADC();
		Get_ADCValue();
		systick_Handler();
		if(F_sys_tim_1ms)
		{
			F_sys_tim_1ms = 0;
            adc_handler();
            display_handler();
            motordriver_handler();
			
		}
		if(F_sys_tim_100ms)
		{
			F_sys_tim_100ms = 0;
            
		}
		if(F_sys_tim_1s)
		{
			F_sys_tim_1s = 0;
            ppm_in[0].errors = 0;
            printf("PPM0: %04d\n\r",ppm_in[0].result/16);
            printf("PPM1: %04d\n\r",ppm_in[1].result/16);
			
			printf("voltage_Vin: %04d\n\r", (int16_t)voltage_Vin);
            printf("current_Left: %04d\n\r", (int16_t)current_Left);
            printf("current_Right: %04d\n\r", (int16_t)current_Right);
			led0_run();
			
		}
	}

}

