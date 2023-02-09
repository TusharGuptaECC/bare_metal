#ifndef _SONALKUNJ_DELAY_H_
#define _SONALKUNJ_DELAY_H_

#include <stm32f401xe.h>
#include <stdint.h>

#define CEN_bit 0	/* timer enable or disable */
#define OPM_bit 3 /* single shot mode */
#define UIF_bit 0 /* update event bit */
#define tim2_bit 0 /* timer2 bit */

void delayMS(uint32_t wait);
void delayUS(uint32_t wait);

#endif