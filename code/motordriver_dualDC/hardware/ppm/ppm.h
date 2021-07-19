#ifndef __PPM_H__
#define __PPM_H__
#include "define.h"


#define C_PPM_MAX       2000L
#define C_TIM1_Reload (65536L-C_PPM_MAX)//33536L
typedef struct {
    //io status
    uint8_t io_read;
    uint8_t io_before;
    //time counter
    uint8_t counterRepeat;
    uint16_t counterLast;
    //output
    uint16_t result;
    //Flag
    uint8_t errors;
    uint8_t F_confirm;
}def_ppm;
#define PPM_CH_MAX      1

//Port
#define port_ppm_in     (0)     //port0

//HALL1
sbit pin_ppm_in0 = P0^5;
#define init_ppm_in_0() do{P05_Quasi_Mode;}while(0)
#define read_ppm_in_0() (pin_ppm_in0)
#define pinNum_ppm_in0 (0x01<<5)

//DEBUG_SCL
sbit pin_ppm_in1 = P0^6;
#define init_ppm_in_1() do{P06_Quasi_Mode;}while(0)
#define read_ppm_in_1() (pin_ppm_in1)
#define pinNum_ppm_in1 (0x01<<6)



extern xdata def_ppm ppm_in[PPM_CH_MAX];
void ppm_init(void );

#endif


