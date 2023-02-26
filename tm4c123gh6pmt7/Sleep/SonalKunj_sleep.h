#ifndef _SONALKUNJ_SLEEP_H_
#define _SONALKUNJ_SLEEP_H_

#include "configuration.h"

#define SYSCTRL_Reg (*((volatile uint32_t *)0xE0000D10))
#define SLEEP_WAKEUP_WFI 2	// wait for interrupt
#define SLEEP_WAKEUP_WFE 1	// wait for event
#define SLEEP_WAKEUP_SOE 0	// sleep on exit
#define SOE_EN_bit 1
#define DEEP_SLEEP_EN_bit 2
#define SLEEP_MODE_DEEP 1
#define SLEEP_MODE_NORMAL 0

void goToSleep(unsigned char wake_up_method, unsigned char sleep_type);

#endif