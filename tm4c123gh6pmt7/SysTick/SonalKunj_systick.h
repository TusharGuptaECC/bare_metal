#ifndef _SONALKUNJ_SYSTICK_H_
#define _SONALKUNJ_SYSTICK_H_

#include "configuration.h"

#define SysTick_CURRENT_Reg (*((volatile uint32_t *)0xE0000018))
#define SysTick_CLOCK_SRC_PIOSC 1
#define SysTick_CLOCK_SRC_MAIN 0
#define SysTick_INTERRUPT_EN 1
#define SysTick_INTERRUPT_DEN 0

void sysTickInit(unsigned char clock_source, unsigned char is_interrupt_en, uint32_t time_out);

#endif