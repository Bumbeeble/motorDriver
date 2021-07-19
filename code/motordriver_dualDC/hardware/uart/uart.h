#ifndef		__UART0_H_
#define		__UART0_H_


#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "stdio.h"
#define Bumbee_DEBUG 1
//-------------------------IO setup-------------------------
sbit	UART_TX_L = P0^6;
sbit	UART_RX_L = P0^7;
sbit	UART_TX_R = P1^6;
sbit	UART_RX_R = P0^2;



//-------------------------var def-------------------------

//-------------------------macro declaration-------------------------
#define UART0_Interrupt_ON()	do{ES = 1;}while(0)
#define UART0_Interrupt_OFF()	do{ES = 0;}while(0)

#define UART0_Receive_ON()		do{REN = 1;}while(0)
#define UART0_Receive_OFF()		do{REN = 0;}while(0)

#define UART1_Interrupt_ON()	do{set_ES_1;}while(0)
#define UART1_Interrupt_OFF()	do{clr_ES_1;}while(0)

#define UART1_Receive_ON()		do{REN_1 = 1;}while(0)
#define UART1_Receive_OFF()		do{REN_1 = 0;}while(0)

//---------------function declaration-------------------------
void UART_Init(uint32_t baudrate);
void  Send_Data_To_UART0(uint8_t c);
uint8_t Receive_Data_From_UART0(void);
void  Send_Data_To_UART1(uint8_t c);
uint8_t Receive_Data_From_UART1(void);
/*
void set_UART0_TXMode(void );
void set_UART0_RXMode(void );

void set_UART1_TXMode(void );
void set_UART1_RXMode(void );
*/

#endif




