#ifndef _DELAY_H_
#define _DELAY_H_

#include <stdint.h>
#include "TM4C123.h"

/*
* @brief register mapping for RCGCTIMER register
*/
#define RCGCTIMER_Reg (*((volatile uint32_t *)0x400FE604))
#define RCGCWTIMER_Reg (*((volatile uint32_t *)0x400FE65C))

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

/*functions declaration*/
void delayMS(uint16_t); /*gives a blocking delay in miliseconds*/
void delayUS(uint16_t); /*gives a blocking delay in micro seconds*/

#endif