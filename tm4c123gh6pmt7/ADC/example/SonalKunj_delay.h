#ifndef _SONALKUNJ_DELAY_H_
#define _SONALKUNJ_DELAY_H_

#include <stdint.h>
#include "TM4C123.h"

/*
* @brief register mapping for RCGCTIMER register
*/
#define RCGCTIMER_Reg (*((volatile uint32_t *)0x400FE604))
#define RCGCWTIMER_Reg (*((volatile uint32_t *)0x400FE65C))
#define SRTIMER_Reg (*((volatile uint32_t *)0x400FE504))	

/*bit declarations*/
#define TIMER0_bit 0
#define TIMER1_bit 1
#define TIMER2_bit 2
#define TIMER3_bit 3
#define TIMER4_bit 4
#define TIMER5_bit 5

#define TAEN_bit 0
#define TBEN_bit 8
#define one_shot_mode_bit 0
#define periodic_mode_bit 1
#define TBTORIS_bit 8
#define TBTOIM_bit 8

#define TIMER_UP_COUNTER_MODE 0x10
#define TIMER_PULSE_TIME_CAPTURE_MODE 0x4
#define TIMER_SELECT_CAPTURE_MODE 0x3
#define TIMER1_CCP0 0x700

/*functions declaration*/
void delayMS(uint32_t); /*gives a blocking delay in miliseconds*/
void delayUS(uint32_t); /*gives a blocking delay in micro seconds*/
void inputCaptureInit(unsigned char pin_no); /* initiates the input capture on timer1A */
void resetTimer1(void);

#endif