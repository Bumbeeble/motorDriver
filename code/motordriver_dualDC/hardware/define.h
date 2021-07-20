#ifndef	_DEFINR_H_
#define	_DEFINR_H_

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "stdio.h"
#include "stdlib.h"

#define DEBUG_UART1


typedef	uint8_t u8;
typedef	uint16_t u16;
typedef	uint32_t u32;
typedef enum{false = 0, true = !false} bool;
#define FALSE false
#define TRUE true

#define All_interrupt_OFF() do{BIT_TMP=EA;EA=0;}while(0)
#define All_interrupt_ON() do{BIT_TMP=EA;EA=1;}while(0)
#define All_interrupt_Recover() do{EA=BIT_TMP;}while(0)

#define TA_write(reg_addr, reg_data)    do{BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;reg_addr=reg_data;EA=BIT_TMP;}while(0)

//sfr page get must used together; All interrupt will be disabled when switch to sfr page1, and recover when switch to sfr page 0
#define set_SFRPAGE1()  do{BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;SFRS|=SET_BIT0;}while(0)//do{TA_write(SFRS, 0x01);All_interrupt_Recover();}while(0)    //
#define set_SFRPAGE0()  do{EA=0;TA=0xAA;TA=0x55;SFRS&=~SET_BIT0;EA=BIT_TMP;}while(0)//do{All_interrupt_OFF();TA_write(SFRS, 0x00);}while(0)    //

#endif
