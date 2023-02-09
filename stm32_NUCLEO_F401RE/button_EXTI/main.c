#include <stm32f401xe.h>
#include <stdint.h>
#include "SonalKunj_delay.h"
#include "SonalKunj_onBoards.h"

#define my_delay 1000
#define my_delay_us 1000000

volatile unsigned char state = 0;

void EXTI15_10_IRQHandler(void)
{
	/* check if interrupt has occured or not */
	if (EXTI->PR & (1 << 13))
	{
		state ^= 1;
	}
	/* clear the pending bit */
	EXTI->PR |= (1 << 13);
}

int main(void)
{
	initOnBoardLED();
	initOnBoardButton();
//	while (1)
//	{
//		led(OFF);
//		delayMS(my_delay);
//		led(ON);
//		delayUS(my_delay_us);
//	}
	while (1)
	{
		delayMS(100);
		if(state)
		{
			led(ON);
		}
		else
		{
			led(OFF);
		}
	}
//	while(1)
//	{
//		delayMS(100);
//		if (GPIOC->IDR & (1 << 13))
//		{
//			led(ON);
//		}
//		else
//		{
//			led(OFF);
//		}
//	}
}





