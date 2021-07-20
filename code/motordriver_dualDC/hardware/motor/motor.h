#ifndef		_motor_H_
#define		_motor_H_
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"


#define motor_DEADTM	5
#define	PWM_motor_MIN	5
#define	Period_PWM		1000
/* DIR_motor1 端口定义 */
sbit DIR_motor1 = P1^0;
#define	DIR_motor1_Output()	do{P10_PushPull_Mode;}while(0)
#define DIR_motor1_ON()   do{DIR_motor1 = 0;}while(0)
#define DIR_motor1_OFF()   do{DIR_motor1 = 1;}while(0)

/* DIR_motor2 端口定义 */
sbit DIR_motor2 = P1^4;
#define	DIR_motor2_Output()	do{P14_PushPull_Mode;}while(0)
#define DIR_motor2_ON()   do{DIR_motor2 = 0;}while(0)
#define DIR_motor2_OFF()   do{DIR_motor2 = 1;}while(0)


	
/* PWM_motor1 端口定义 */
sbit PWM_motor1 = P1^2;
#define	PWM_motor1_Output()	do{P12_PushPull_Mode;}while(0)
#define PWM_motor1_ON()   do{PWM_motor1 = 0;}while(0)
#define PWM_motor1_OFF()   do{PWM_motor1 = 1;}while(0)

/* PWM_motor2 端口定义 */
sbit PWM_motor2 = P0^1;
#define	PWM_motor2_Output()	do{P01_PushPull_Mode;}while(0)
#define PWM_motor2_ON()   do{PWM_motor2 = 0;}while(0)
#define PWM_motor2_OFF()   do{PWM_motor2 = 1;}while(0)

/* IDIR_motor1 端口定义 */
sbit IDIR_motor1 = P0^0;
#define	IDIR_motor1_Output()	do{ P00_PushPull_Mode;}while(0)
#define IDIR_motor1_OFF()   do{IDIR_motor1 = 0;}while(0)
#define IDIR_motor1_ON()   do{IDIR_motor1 = 1;}while(0)

/* IDIR_motor2 端口定义 */
sbit IDIR_motor2 = P1^3;
#define	IDIR_motor2_Output()	do{ P13_PushPull_Mode;}while(0)
#define IDIR_motor2_OFF()   do{IDIR_motor2 = 0;}while(0)
#define IDIR_motor2_ON()   do{IDIR_motor2 = 1;}while(0)

/* IPWM_motor1 端口定义 */
sbit IPWM_motor1 = P1^1;
#define	IPWM_motor1_Output()	do{ P11_PushPull_Mode;}while(0)
#define IPWM_motor1_OFF()   do{IPWM_motor1 = 0;}while(0)
#define IPWM_motor1_ON()   do{IPWM_motor1 = 1;}while(0)

/* IPWM_motor2 端口定义 */
sbit IPWM_motor2 = P0^3;
#define	IPWM_motor2_Output()	do{ P03_PushPull_Mode;}while(0)
#define IPWM_motor2_OFF()   do{IPWM_motor2 = 0;}while(0)
#define IPWM_motor2_ON()   do{IPWM_motor2 = 1;}while(0)


typedef enum	
{
  DIR_back = 0,
  DIR_forward = 1,
  DIR_standby = 2
}motorDIR;

void setDIR_motor1(motorDIR direction);
void setDIR_motor2(motorDIR direction);
void motor_Init(void);

void set_PWM_motor1(uint16_t speed_motor);
void set_PWM_motor2(uint16_t speed_motor);
void PWM_DEAD_TIME_VALUE(uint16_t	DeadTimeData);
void set_speed_motor2(int16_t speed_motor);
void set_speed_motor1(int16_t speed_motor);
void pwm_Init(void );


extern bit BIT_TMP;
//****SFRS		91H ****
#define set_SFRPAGE  do{BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;SFRS|=(SET_BIT0);EA=BIT_TMP;}while(0)
#define clr_SFRPAGE  do{BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;SFRS&=(~SET_BIT0);EA=BIT_TMP;}while(0)

#endif