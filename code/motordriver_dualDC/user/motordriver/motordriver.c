#include "motordriver.h"


void motordriver_init(void )
{
	motor_Init();
    ppm_init();
    
}


void motordriver_handler(void  )
{
    ppm_handler();
    
#if 1
//			set_speed_motor1(voltage_Vin/4);
//			set_speed_motor2(voltage_Vin/4);
    set_speed_motor1(((int16_t)voltage_Vin) - 2048);
    set_speed_motor2(((int16_t)voltage_Vin) - 2048);
#else
        set_speed_motor1(ppm_in[0].result/16-1000);
        set_speed_motor2(ppm_in[0].result/16-1000);
//            if(ppm_in[0].errors)
//            {
//                set_speed_motor1(0);
//                set_speed_motor2(0);
//            }
//            else
//            {
//                
//            }
#endif
}


