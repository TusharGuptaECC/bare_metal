#ifndef _SONALKUNJ_ONBOARDS_H_
#define _SONALKUNJ_ONBOARDS_H_

#include <stm32f401xe.h>
#include <stdint.h>

#define gpioa 0
#define ON 1
#define OFF 0
#define gpioc 2

void initOnBoardLED(void);
void initOnBoardButton(void);
void led(unsigned char state);

#endif