#ifndef     _DELAY_H_
#define     _DELAY_H_

#include "define.h"

void Delay(uint32_t nCount);
#define	Delay_us(x) Delay(x)
#define osDelay(x) Delay(x)
/**/
#endif


