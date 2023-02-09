#include <stm32f401xe.h>
#include <stdint.h>
#include "SonalKunj_delay.h"
#include "SonalKunj_onBoards.h"

#define my_delay 1000

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
	return 0;
}





