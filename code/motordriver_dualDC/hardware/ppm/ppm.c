#include "ppm.h"
#include "led.h"



xdata def_ppm ppm_in[PPM_CH_MAX] = {0};



void tim1_Interrupt(void)  interrupt 3
{
    uint8_t i = 0;
//    TH1 += C_TIM1_Reload/256;
//	TL1 += C_TIM1_Reload%256; 
    //cnt_tim1++;
    for(i = 0; i < PPM_CH_MAX; i++)
    {
        if(ppm_in[i].counterLast < 2)
        {
            ppm_in[i].counterLast ++; 
        }
    }
}



void PIO_Interrupt()	 interrupt 7     //ISR for io change interrupt
{
    uint8_t temp_0 = 0;
    uint8_t i = 0;
    uint16_t temp_counterNow = 0;          //
    uint16_t temp_counterResult = 0;          //
    uint8_t temp_H = 0;
    uint8_t temp_L = 0;
    //interrupt flag
    PIF = 0;
    //get timer counterLast
    temp_L = TL1;
    temp_H = TH1;
    
    temp_counterNow = (temp_H << 8) + temp_L;
    
//    LED_R_RUN();
    
    ppm_in[0].io_read = read_ppm_in_0();
    ppm_in[1].io_read = read_ppm_in_1();   
    //check pin 
    
    for(i = 0; i < PPM_CH_MAX; i++)
    {
        if(ppm_in[i].io_read != ppm_in[i].io_before)
        {
            ppm_in[i].io_before = ppm_in[i].io_read;
            
            if(ppm_in[i].io_before == 0)
            {
                //low trig, check high pluse length
                if(ppm_in[i].counterRepeat > 1)
                {
                    //length too long
                    ppm_in[i].errors = 1;
                }
                else
                {
    //              
                    //get result
                    temp_counterResult = temp_counterNow - ppm_in[i].counterLast;
                    if(temp_counterResult > C_PPM_MAX)
                    {
                        //length too long
                        ppm_in[i].errors = 1;
                    }
                    ppm_in[i].result = temp_counterResult;
                    ppm_in[i].F_confirm = 1;
                    
                }
            }
            ppm_in[i].counterRepeat = 0;
            ppm_in[i].counterLast = temp_counterNow;
        }
    }
}

void PIO_config(void )
{
    PICON = 0xFC + port_ppm_in;		//all pin set to edge trig,select port1
    PINEN = (pinNum_ppm_in0 | pinNum_ppm_in1 );//0x20;       		//Enable falling edge interrupt, 0B0010 0000        //P17
    PIPEN = (pinNum_ppm_in0 | pinNum_ppm_in1 );//0x20;       		//Enable raising edge interrupt, 0B0010 0000        //P17
    PIF = 0;                    //clear interrupt flags
    EIE |= (0x01<<1);           //enable pio interrupt
   
    EIP |= (0x01<<1);
    EIPH |= (0x01<<1);          //interrupt level3
}

//65536/16 = 4096us
void tim1_init(void )
{
    //TIMER0_MODE1_ENABLE;
	TMOD&=0x0F;
	TMOD|=0x10;         //mode1: 16bit timer
	set_T1M;			//选择不分频，默认为51默认的12分频
//	TH1 = C_TIM1_Reload/256;
//	TL1 = C_TIM1_Reload%256; 
	set_ET1;
	set_TR1;
}
void ppm_init(void )
{
    tim1_init();
    init_ppm_in_0();
    PIO_config();
}

void ppm_handler(void )
{
    
}

//-------------end-----------------


