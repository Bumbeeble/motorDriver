#ifndef		__uart1_H_
#define		__uart1_H_
#include "define.h"

#define C_BaudRate_Set 100000
sbit	UART_TX_R = P1^6;
sbit	UART_RX_R = P0^2;

#define uart1_Interrupt_ON()	do{set_ES_1;}while(0)
#define uart1_Interrupt_OFF()	do{clr_ES_1;}while(0)

void set_uart1_debug(void );

#if 0
void set_uart1_Lowpower(void );
#endif

void UART_Init(uint32_t baudrate);

#endif