//-------------chip----------------------
#include "define.h"
//-------------system----------------------
#include "sys_tim.h"
#include "wdt.h"
//-------------hardware----------------------
#include "led.h"
#include "adc.h"
//-------------UART---------------------
//#include "uart.h"
#include "motor.h"
#include "ppm.h"

#include "uart1.h"
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
	Motor_Init();
    ppm_init();
	All_interrupt_ON();
    
	printf("\nSystem start...\n");
	while(1)
	{
		//主循环
		WDT_Clear();
		Read_ADC();				//循环采样
		Get_ADCValue();			//数据转换
		systick_Handler();
		if(F_sys_tim_1ms)
		{
			F_sys_tim_1ms = 0;
            display_handler();
            ppm_handler();
            
			//简易1ms时间调度
            adc_handler();
#if 1
//			set_speed_Motor1(voltage_Vin/4);
//			set_speed_Motor2(voltage_Vin/4);
			set_speed_Motor1(((int16_t)voltage_Vin) - 2048);
			set_speed_Motor2(((int16_t)voltage_Vin) - 2048);
#else
                set_speed_Motor1(ppm_in[0].result/16-1000);
                set_speed_Motor2(ppm_in[0].result/16-1000);
//            if(ppm_in[0].errors)
//            {
//                set_speed_Motor1(0);
//                set_speed_Motor2(0);
//            }
//            else
//            {
//                
//            }
#endif
			
		}
		if(F_sys_tim_100ms)
		{
			F_sys_tim_100ms = 0;
			//
            
            
            st7032_i2c_setCursor(0,0);
            sprintf(char_buf, "PPM:%04U ",ppm_in[0].result);
            st7032_i2c_write_str(char_buf);
            st7032_i2c_setCursor(1,0);
            sprintf(char_buf, "AIN:%04U ",voltage_Vin);
            st7032_i2c_write_str(char_buf);
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

