#ifndef		_MOTOR_H_
#define		_MOTOR_H_
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"


#define MOTOR_DEADTM	5
#define	PWM_MOTOR_MIN	5
#define	Period_PWM		1000
/* DIR_Motor1 端口定义 */
sbit DIR_Motor1 = P1^0;
#define	DIR_Motor1_Output()	do{P10_PushPull_Mode;}while(0)
#define DIR_Motor1_ON()   do{DIR_Motor1 = 0;}while(0)
#define DIR_Motor1_OFF()   do{DIR_Motor1 = 1;}while(0)

/* DIR_Motor2 端口定义 */
sbit DIR_Motor2 = P1^4;
#define	DIR_Motor2_Output()	do{P14_PushPull_Mode;}while(0)
#define DIR_Motor2_ON()   do{DIR_Motor2 = 0;}while(0)
#define DIR_Motor2_OFF()   do{DIR_Motor2 = 1;}while(0)


	
/* PWM_Motor1 端口定义 */
sbit PWM_Motor1 = P1^2;
#define	PWM_Motor1_Output()	do{P12_PushPull_Mode;}while(0)
#define PWM_Motor1_ON()   do{PWM_Motor1 = 0;}while(0)
#define PWM_Motor1_OFF()   do{PWM_Motor1 = 1;}while(0)

/* PWM_Motor2 端口定义 */
sbit PWM_Motor2 = P0^1;
#define	PWM_Motor2_Output()	do{P01_PushPull_Mode;}while(0)
#define PWM_Motor2_ON()   do{PWM_Motor2 = 0;}while(0)
#define PWM_Motor2_OFF()   do{PWM_Motor2 = 1;}while(0)

/* IDIR_Motor1 端口定义 */
sbit IDIR_Motor1 = P0^0;
#define	IDIR_Motor1_Output()	do{ P00_PushPull_Mode;}while(0)
#define IDIR_Motor1_OFF()   do{IDIR_Motor1 = 0;}while(0)
#define IDIR_Motor1_ON()   do{IDIR_Motor1 = 1;}while(0)

/* IDIR_Motor2 端口定义 */
sbit IDIR_Motor2 = P1^3;
#define	IDIR_Motor2_Output()	do{ P13_PushPull_Mode;}while(0)
#define IDIR_Motor2_OFF()   do{IDIR_Motor2 = 0;}while(0)
#define IDIR_Motor2_ON()   do{IDIR_Motor2 = 1;}while(0)

/* IPWM_Motor1 端口定义 */
sbit IPWM_Motor1 = P1^1;
#define	IPWM_Motor1_Output()	do{ P11_PushPull_Mode;}while(0)
#define IPWM_Motor1_OFF()   do{IPWM_Motor1 = 0;}while(0)
#define IPWM_Motor1_ON()   do{IPWM_Motor1 = 1;}while(0)

/* IPWM_Motor2 端口定义 */
sbit IPWM_Motor2 = P0^3;
#define	IPWM_Motor2_Output()	do{ P03_PushPull_Mode;}while(0)
#define IPWM_Motor2_OFF()   do{IPWM_Motor2 = 0;}while(0)
#define IPWM_Motor2_ON()   do{IPWM_Motor2 = 1;}while(0)


/* 声明给外部使用的变量 */

/* 声明给外部使用的函数 */
typedef enum	
{
  DIR_back = 0,
  DIR_forward = 1,
  DIR_standby = 2
}MotorDIR;

void setDIR_Motor1(MotorDIR direction);
void setDIR_Motor2(MotorDIR direction);
void Motor_Init(void);

void set_PWM_Motor1(uint16_t speed_motor);
void set_PWM_Motor2(uint16_t speed_motor);
void PWM_DEAD_TIME_VALUE(uint16_t	DeadTimeData);
void set_speed_Motor2(int16_t speed_motor);
void set_speed_Motor1(int16_t speed_motor);
void pwm_Init(void );


extern bit BIT_TMP;
//****SFRS		91H ****
#define set_SFRPAGE  do{BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;SFRS|=(SET_BIT0);EA=BIT_TMP;}while(0)
#define clr_SFRPAGE  do{BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;SFRS&=(~SET_BIT0);EA=BIT_TMP;}while(0)

#endif