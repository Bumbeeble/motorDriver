/*
* motor.c

*/
#include "motor.h"
/*

void PWM_DEAD_TIME_VALUE(UINT16	DeadTimeData)
{
	UINT8 deadtmphigh,deadtmplow;
	deadtmplow = DeadTimeData;
	deadtmphigh = DeadTimeData>>8;
	BIT_TMP = EA;
	if (deadtmphigh==0x01)
	{
		EA = 0;
		TA = 0xAA;
		TA = 0x55;
		PDTEN|=0x10;
	}
	TA = 0xAA;
	TA = 0x55;
	PDTCNT = deadtmplow;
	EA = BIT_TMP;
}
*/

void  setDIR_Motor1(MotorDIR direction)
{
  if(direction == DIR_forward)
  {
	IDIR_Motor1_ON();
	DIR_Motor1_OFF();
  }
  else if(direction == DIR_back)
  {
	DIR_Motor1_ON();
	IDIR_Motor1_OFF();
  }
  else
  {
	DIR_Motor1_OFF();
	IDIR_Motor1_OFF();
  }
  
}

void  setDIR_Motor2(MotorDIR direction)
{
  if(direction == DIR_forward)
  {
	IDIR_Motor2_ON();
	DIR_Motor2_OFF();
  }
  else if(direction == DIR_back)
  {
	DIR_Motor2_ON();
	IDIR_Motor2_OFF();
  }
  else
  {
	DIR_Motor2_OFF();
	IDIR_Motor2_OFF();
  }
  
}
void	set_speed_Motor1(int16_t speed_motor)
{
  if(speed_motor > Period_PWM)
	speed_motor = Period_PWM;
  if(speed_motor < -Period_PWM)
	speed_motor = -Period_PWM;
  
  
  if(speed_motor > PWM_MOTOR_MIN)
  {
	
	setDIR_Motor1(DIR_forward);
	set_PWM_Motor1(speed_motor);
	//TIM1_SetCompare1(speed_motor);
	//PWM_Motor1_ON();
	 // IPWM_Motor1_OFF();
	  
  }
  else if(speed_motor < -PWM_MOTOR_MIN)
  {
	
	setDIR_Motor1(DIR_back);
	//TIM1_SetCompare1(Period_PWM + speed_motor);
	  set_PWM_Motor1(Period_PWM + speed_motor);
	 // PWM_Motor1_OFF();
	 // IPWM_Motor1_ON();
  }
  else
  {
	setDIR_Motor1(DIR_standby);
	  set_PWM_Motor1(0);
	//TIM1_SetCompare1(0);
	//PWM_Motor1_OFF();
	 // IPWM_Motor1_OFF();
  }
}



void set_speed_Motor2(int16_t speed_motor)
{
  if(speed_motor > Period_PWM)
	speed_motor = Period_PWM;
  if(speed_motor < -Period_PWM)
	speed_motor = -Period_PWM;
  
  
  if(speed_motor > PWM_MOTOR_MIN)
  {
	
	setDIR_Motor2(DIR_forward);
	//TIM1_SetCompare1(speed_motor);
	 set_PWM_Motor2(speed_motor);
	//PWM_Motor2_ON();
	//IPWM_Motor2_OFF();
	  
  }
  else if(speed_motor < -PWM_MOTOR_MIN)
  {
	
	setDIR_Motor2(DIR_back);
	//TIM1_SetCompare1(Period_PWM + speed_motor);
	  set_PWM_Motor2(Period_PWM + speed_motor);
	  //PWM_Motor2_OFF();
	  //IPWM_Motor2_ON();
  }
  else
  {
	setDIR_Motor2(DIR_standby);
	  set_PWM_Motor2(0);
	//TIM1_SetCompare1(0);
	//PWM_Motor2_OFF();
	  //IPWM_Motor2_OFF();
  }
}

void set_PWM_Motor1(uint16_t pwm_motor)
{
	PWM0H = pwm_motor/256;
	PWM0L = pwm_motor%256;
	set_LOAD;
}
void set_PWM_Motor2(uint16_t pwm_motor)
{
	set_SFRPAGE;										// PWM4 and PWM5 duty value need set SFPPAGE 1
	PWM4H = pwm_motor/256;
	PWM4L = pwm_motor%256;
	clr_SFRPAGE;
	set_LOAD;
}
void pwm_Init(void )
{
	
	PWMCON0 = 0x00;		//0B0000xxxx
	PWMCON1	= 0x40;		//0B01000000		互补模式
	//PWMCON1	= 0x00;		//0B01000000		独立模式
	CKCON &= (~0x40);	//PWM clock select Fsys
	//period
	PWMPH = Period_PWM/256;	
	PWMPL = Period_PWM%256;
	//Duty
	PWM0H = 0;
	PWM0L = 100;
	set_SFRPAGE;		// PWM4 and PWM5 duty value need set SFPPAGE 1
	PWM4H = 0;
	PWM4L = 200;
	clr_SFRPAGE;
	
	PIOCON0 = 0x33;//0xff;//0x3F;		//IO set up, enable pwm0,pwm1(motor1) and pwm4,pwm5(motor2)
	set_SFRPAGE;
	PIOCON1 = 0x00;			//Page1
	clr_SFRPAGE;
	
	PWM01_DEADTIME_ENABLE;
	PWM45_DEADTIME_ENABLE;
	PWM_DEAD_TIME_VALUE(MOTOR_DEADTM);			//value never over 0x1FF
	PMEN = 0x00;		//掩码控制
	PMD = 0x00;		//掩码状态输出电平设置
	PNP = 0x11;		//0B00100010
	//Please always setting Dead time if needed before PWM run.		
    set_LOAD;
    set_PWMRUN;
}
void Motor_Init(void)
{
	DIR_Motor1_OFF();
	DIR_Motor2_OFF();
	IDIR_Motor1_OFF();
	IDIR_Motor2_OFF();
	
	PWM_Motor1_OFF();
	PWM_Motor2_OFF();
	IPWM_Motor1_OFF();
	IPWM_Motor2_OFF();
	
	DIR_Motor1_Output();
	DIR_Motor2_Output();
	IDIR_Motor1_Output();
	IDIR_Motor2_Output();
	
	PWM_Motor1_Output();
	PWM_Motor2_Output();
	IPWM_Motor1_Output();
	IPWM_Motor2_Output();
	pwm_Init();
	
}	

void PWM_DEAD_TIME_VALUE(uint16_t	DeadTimeData)
{
	uint8_t deadtmphigh,deadtmplow;
	deadtmplow = DeadTimeData;
	deadtmphigh = DeadTimeData>>8;
	BIT_TMP = EA;
	if (deadtmphigh==0x01)
	{
		EA = 0;
		TA = 0xAA;
		TA = 0x55;
		PDTEN|=0x10;
	}
	TA = 0xAA;
	TA = 0x55;
	PDTCNT = deadtmplow;
	EA = BIT_TMP;
}