#include "uart1.h"


//Ring buf
#define Length_TXBuf	100
static xdata uint8_t buf_TX[Length_TXBuf] = {0};
static uint8_t pos_TX_OUT = 0;
static uint8_t pos_TX_IN = 0;	

static xdata uint8_t cnt_TX = 0;
static bit	Flag_TX_Full = 0;
static bit	Flag_TX_Empty = 1;

/*
* Redefine of printf
*/
void Send_Data_To_UART1 (uint8_t c)
{
	while(Flag_TX_Full);
uart1_Interrupt_OFF();
	buf_TX[pos_TX_IN] = c;
	pos_TX_IN++;					//??????
	if(pos_TX_IN >= Length_TXBuf)
		pos_TX_IN = 0; 

	cnt_TX++;	 					//????

	if(cnt_TX>=Length_TXBuf)
	 	Flag_TX_Full = 1;			//????	  
uart1_Interrupt_ON();
	if(Flag_TX_Empty)
	{
		//set_uart1_TXMode();
		SBUF_1 = (unsigned char)buf_TX[pos_TX_OUT];
		pos_TX_OUT++;
		if(pos_TX_OUT >= Length_TXBuf)
			pos_TX_OUT = 0;

		Flag_TX_Empty = 0;
	}	
}


char putchar (char ch)
{
	Send_Data_To_UART1(ch);
	return(ch);
}

/*
*/
//uart1 interrupt handler
void uart1_Interrupt(void ) interrupt 15
{
	uint16_t buf_length = 0;

	if(TI_1)
	{
		TI_1 = 0;	
		if(cnt_TX > 1)
		{
			SBUF_1 = (unsigned char)buf_TX[pos_TX_OUT];
			pos_TX_OUT++;
			if(pos_TX_OUT >= Length_TXBuf)
				pos_TX_OUT = 0;
			Flag_TX_Full = 0;
			cnt_TX--;
		
		}	
		else
		{
			cnt_TX = 0;
			pos_TX_OUT = 0;
			pos_TX_IN = 0;
			Flag_TX_Empty = 1;
		}
	}
	
	
	if(RI_1)
	{
		RI_1 = 0;
	}
}



void UART_Init(uint32_t baudrate)
{

	
	//baudrate setup
    T3CON &= 0xF8;   //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
    RH3    = HIBYTE(65536 - (1000000/(baudrate)));
    RL3    = LOBYTE(65536 - (1000000/(baudrate)));
    set_TR3;         //Trigger Timer3

    //----------------UART1------------------
	SCON_1 = 0x50;   	//UART1 Mode1,REN_1=1,TI_1=1
	set_SMOD_1;        //UART1 Double Rate Enable
	//UART1 can only chose TIM3 as baud rate
	set_TI_1;
    set_uart1_debug();
}
void set_uart1_debug(void )
{
    //UART1
	UART_TX_R = 1;
//	UART_RX_R = 1;
	P16_PushPull_Mode;		//Tx
//	P02_PushPull_Mode;		//Rx
	//RX on
	//REN_1 = 1;
    //RX off
	REN_1 = 0;
    uart1_Interrupt_ON();
}
#if 0
void set_uart1_Lowpower(void )
{
    //UART1
	UART_TX_R = 0;
	//UART_RX_R = 0;
	P16_OpenDrain_Mode;		//Tx
	P02_OpenDrain_Mode;		//Rx
	//RX on
	REN_1 = 0;		
    uart1_Interrupt_OFF();
}

#endif