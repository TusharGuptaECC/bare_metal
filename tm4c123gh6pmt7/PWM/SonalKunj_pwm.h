#ifndef _SONALKUNJ_PWM_H_
#define _SONALKUNJ_PWM_H_

#include "configuration.h"

#define PWM_1_CLOCK_EN 0x2

void pwmBegin(unsigned char time_period, unsigned char duty_cycle);
void pwmStop(void);

#endif