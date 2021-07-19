/*
* uart0.c


*/

#include "uart.h"
#include "sys_tim.h"
#define Length_TXBuf	200
static xdata uint8_t buf_TX[Length_TXBuf] = {0};
static xdata uint8_t pos_TX_OUT = 0;
static xdata uint8_t pos_TX_IN = 0;

static xdata uint8_t cnt_TX = 0;
static bit	Flag_TX_Full = 0;
static bit	Flag_TX_Empty = 1;



char putchar (char ch)
{
#if	Bumbee_DEBUG 
	Send_Data_To_UART0(ch);
#endif
	return(ch);
}
/*
* Redefine of printf
*/
void Send_Data_To_UART0 (uint8_t c)
{
	while(Flag_TX_Full);

	buf_TX[pos_TX_IN] = c;
	pos_TX_IN++;
	if(pos_TX_IN >= Length_TXBuf)
		pos_TX_IN = 0; 
UART0_Interrupt_OFF();
	cnt_TX++;	
UART0_Interrupt_ON();
	if(cnt_TX>=Length_TXBuf)
	 	Flag_TX_Full = 1;	

	if(Flag_TX_Empty)
	{
		SBUF = (unsigned char)buf_TX[pos_TX_OUT];
		pos_TX_OUT++;
		if(pos_TX_OUT >= Length_TXBuf)
			pos_TX_OUT = 0;
		Flag_TX_Empty = 0;
	}
	
}

/*
uart1 
*/
void uart1_interrupt(void ) interrupt 15
{
	if(TI_1)
	{
		TI_1 = 0;
	}
	
	if(RI_1)
	{
		RI_1 = 0;
		
	}
}

/*
*/
//uart0 interrupt handler
void uart0_interrupt(void ) interrupt 4
{
	
	if(TI)
	{
		TI = 0;
		if(Flag_TX_Empty == 0)
		{
			if(cnt_TX > 1)
			{
				cnt_TX--;	 					//????
					//????	
				SBUF = (unsigned char)buf_TX[pos_TX_OUT];
				pos_TX_OUT++;	
				if(pos_TX_OUT >= Length_TXBuf)
					pos_TX_OUT = 0;
				Flag_TX_Full = 0;
			}	
			else
			{
				cnt_TX = 0;
		 		Flag_TX_Empty = 1;
			}

		}
	}
	
	
	if(RI)
	{
		RI = 0;
	}
}



//
void UART_Init(uint32_t baudrate)
{
//--------------IO-------------------
	/**/
	//UART0
	P06_PushPull_Mode;
	//P06_Input_Mode;		//Tx
	P07_Input_Mode;		//Rx
	//UART1
	P02_PushPull_Mode;
	//P02_Input_Mode;		//Tx
	P16_Input_Mode;		//Rx
	
	//baudrate setup
    T3CON &= 0xF8;   //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
#if	C_ClockDiv_SET == 0
		RH3    = HIBYTE(65536 - (1000000/(baudrate)));
		RL3    = LOBYTE(65536 - (1000000/(baudrate)));
#else
		RH3    = HIBYTE(65536 - (1000000/(2*C_ClockDiv_SET*baudrate))-1);
		RL3    = LOBYTE(65536 - (1000000/(2*C_ClockDiv_SET*baudrate))-1);
#endif
    set_TR3;         //Trigger Timer3
//----------------UART0------------------
	SCON = 0x50;     //UART0 Mode1,REN=1,TI=1
    set_SMOD;        //UART0 Double Rate Enable
    set_BRCK;        //UART0 baud rate clock source = Timer3
	//set_TI;					 //For printf function must setting TI = 1
	IP |= 0x10;
	IPH |= 0x10;			//set uart0 interrupt to top level
	
//----------------UART1------------------
	SCON_1 = 0x50;   	//UART1 Mode1,REN_1=1,TI_1=1
	set_SMOD_1;        //UART1 Double Rate Enable
	//UART1 can only chose TIM3 as baud rate
	set_TI_1;
	UART0_Interrupt_ON();
	UART1_Interrupt_ON();
}

/*
void set_UART0_TXMode(void )
{
	//UART0
	P06_PushPull_Mode;		//Tx
	P07_Input_Mode;		//Rx
	
	//RX off
	REN = 0;
	//UART0_Interrupt_OFF();	
}

void set_UART0_RXMode(void )
{

	P06_Input_Mode;		//Tx
	P07_Input_Mode;		//Rx

	//RX on
	REN = 1;
}

void set_UART1_TXMode(void )
{

	//UART1
	P16_PushPull_Mode;		//Tx
	P02_Input_Mode;			//Rx
	
	//RX off
	REN_1 = 0;		
}

void set_UART1_RXMode(void )
{
	//UART1
	P16_Input_Mode;		//Tx
	P02_Input_Mode;		//Rx
	//RX on
	REN_1 = 1;		
}
*/
/*
char putchar (char ch)
{
#if	Bumbee_DEBUG 
	Send_Data_To_UART0(ch);
#endif
	return(ch);
}
*/

