/*
 * Author: Tushar Gupta
 * Note: This file is developed using Keil uVision5
*/

#include <stm32f401xe.h>
#include <stdint.h>
#include "SonalKunj_delay.h"
#include "SonalKunj_onBoards.h"

#define my_delay 1000
#define my_delay_us 1000000

int main(void)
{
  initOnBoardLED();
  led(ON);
  while (1)
  {
  	led(OFF);
  	delayMS(my_delay);
  	led(ON);
  	delayUS(my_delay_us);
  }
}
