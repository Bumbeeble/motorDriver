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
#include "st7032_i2c.h"

bit BIT_TMP;
char char_buf[20] = {0};
//The main C function
void main (void) 
{
	WDT_Clear();
	clr_EA;
	sys_tim_Init();					//系统定时
    UART_Init(C_BaudRate_Set);
	Enable_WDT_Reset_Config();			//配置CONFIG4，打开WDT
	WDT_config(WDTPS_1638ms);			//WDT时间设为1.638s
	//WDT_Stop();
	LED_Init();						//LED
	ADC_Config();
	ADC_Cycle_Start();				//ADC
	Motor_Init();
    ppm_init();
	set_EA;                        //enable interruptsst7032_i2c_config();
    
	printf("\nSystem start...\n");
	printf("I2C LCD Init\n");
    I2C_GPIOInit();
    st7032_i2c_config();
    st7032_i2c_setCursor(1,0);
    st7032_i2c_write_str("Hello world");
	while(1)
	{
		//主循环
		WDT_Clear();
		set_EA; 
		Read_ADC();				//循环采样
		Get_ADCValue();			//数据转换
		systick_Handler();
//		if(pin_ppm_in_0 == 0)
//        {
//            LED0_ON();
//        }
//        else
//        {
//            LED0_OFF();
//        }
		if(sys_tim_Flag_1ms)
		{
			sys_tim_Flag_1ms = 0;
			//简易1ms时间调度
			if(F_Ready_ADCData)
			{
				F_Ready_ADCData = 0;
			}
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
		if(sys_tim_Flag_100ms)
		{
			sys_tim_Flag_100ms = 0;
			//
            
            
            st7032_i2c_setCursor(0,0);
            sprintf(char_buf, "PPM:%04U ",ppm_in[0].result);
            st7032_i2c_write_str(char_buf);
            st7032_i2c_setCursor(1,0);
            sprintf(char_buf, "AIN:%04U ",voltage_Vin);
            st7032_i2c_write_str(char_buf);
		}
		if(sys_tim_Flag_1s)
		{
			sys_tim_Flag_1s = 0;
            ppm_in[0].errors = 0;
            printf("PPM0: %04d\n\r",ppm_in[0].result/16);
            printf("PPM1: %04d\n\r",ppm_in[1].result/16);
			
			printf("voltage_Vin: %04d\n\r", (int16_t)voltage_Vin);
            printf("current_Left: %04d\n\r", (int16_t)current_Left);
            printf("current_Right: %04d\n\r", (int16_t)current_Right);
			LED_0_RUN();
			
		}
	}

}

