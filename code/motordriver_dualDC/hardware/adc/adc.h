#ifndef _ADC_H_
#define _ADC_H_
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "stdlib.h"

#define		NUM_ADChannel	3

#define MAX_ADCCycle    10				//��һ�����10�β���

#define	SET_ADC_OFFSET_MAX	30
#define	SET_ADC_OFFSET_MIN	2
#define VOL_VREF	3300		//reference voltage, 
#define VALUE_VREF	4096
#define channel_LeftCur		ADC_Channel_5
#define channel_RightCur	ADC_Channel_1
#define channel_VinVol		ADC_Channel_0


sbit pin_adc_VinVol = P1^7;
#define init_pin_adc_VinVol() do{P17_Input_Mode;}while(0)

sbit pin_adc_LeftCur = P0^4;
#define init_pin_adc_LeftCur() do{P04_Input_Mode;}while(0)

sbit pin_adc_RightCur = P3^0;
#define init_pin_adc_RightCur() do{P30_Input_Mode;}while(0)

enum {
 LeftCur = 0,
 RightCur	,
 VinVol	
};
typedef	enum
{
	ADC_Channel_0 = 0,
	ADC_Channel_1 = 1,
	ADC_Channel_2 = 2,
	ADC_Channel_3 = 3,
	ADC_Channel_4 = 4,
	ADC_Channel_5 = 5,
	ADC_Channel_6 = 6,
	ADC_Channel_7 = 7,
	ADC_Channel_8 = 8
}	type_adc_channel;

struct ADC_Type
{
	type_adc_channel  channel;			//ͨ���趨
	uint16_t Data;			//����ֵ
	uint16_t offset;
};
extern xdata  struct ADC_Type ADC_Data[NUM_ADChannel];
extern xdata  uint8_t F_ADC_Over ;
extern uint16_t err_cnt;
extern xdata uint8_t BandgapHigh,BandgapLow,BandgapMark;
extern bit	F_TIM_ADCValue;
extern xdata uint16_t Bandgap_Value, Bandgap_Voltage;
extern bit	F_Ready_ADCData;
extern xdata  uint16_t current_Left;
extern xdata  uint16_t current_Right;
extern xdata  uint16_t voltage_Vin;

void ADC_Config(void);
void Read_ADC(void );
void Get_ADCValue(void );
void ADC_Cycle_Start(void );
void READ_BANDGAP();



#endif

