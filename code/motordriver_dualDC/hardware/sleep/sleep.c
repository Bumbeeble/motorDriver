#include "sleep.h"
#include "output.h"
#include "adc.h"
#include "bat.h"
//#include "init.h"
uint8_t Decnt_SleepDelay = 0;
#define C_SleepDelay_Set	5*4


void sleep_Handler(void )
{
	if(	((F_Input_Status || F_CTRL_Boost) == 0 ) && F_Leftoutput_Stable && F_Rightoutput_Stable )
	{
		if(Decnt_SleepDelay == 0)
		{
			//Ë¯Ãß×´Ì¬È·ÈÏ
			
			
			Decnt_SleepDelay = C_SleepDelay_Set;
		}
	}
	else
	{
		Decnt_SleepDelay = C_SleepDelay_Set;
	}
	
}