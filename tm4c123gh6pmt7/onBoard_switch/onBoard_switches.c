#include "onBoard_switches.h"

/*
* parameters: first is switch name & second is switch mode
*/
void onBoardSwitchInit(unsigned char switch_name, unsigned char switch_mode)
{
	GPIOF->LOCK = 0x4C4F434B; /* unlocking is necessary for commiting changes in GPIOPUR & GPIOPDR registers */
	GPIOF->CR |= (1 << switch_name);/* commit register unmask the required bits to unlock */
	GPIOF->DIR &= ~(1 << switch_name);	/* set as input */
	GPIOF->AFSEL &= ~(1 << switch_name); /* set as GPIO */
	GPIOF->DEN |= (1 << switch_name); /* enable the digital operation */
	if (switch_mode == 0)
	{
		GPIOF->PUR |= (1 << switch_name);
	}
	else if (switch_mode == 1)
	{
		GPIOF->PDR |= (1 << switch_name);
	}
	else if (switch_mode == 2)
	{
		NVIC_DisableIRQ(GPIOF_IRQn);
		GPIOF->IM &= ~(1 << switch_name);
		// not required as default is edge triggered GPIOF->IS &= ~(1 << switch_name);
		// GPIOF->IBE not required as don't want both edge triggering
		GPIOF->IEV |= (1 << switch_name);// rising edge
		GPIOF->IM |= (1 << switch_name);
		GPIOF->PUR |= (1 << switch_name);
		NVIC_EnableIRQ(GPIOF_IRQn);
		NVIC_SetPriority(GPIOF_IRQn, 0);
		
	}
	else
	{
		NVIC_DisableIRQ(GPIOF_IRQn);
		GPIOF->IM &= ~(1 << switch_name);
		// not required as default is edge triggered GPIOF->IS &= ~(1 << switch_name);
		// GPIOF->IBE not required as don't want both edge triggering
		GPIOF->IEV &= ~(1 << switch_name);// falling edge
		GPIOF->IM |= (1 << switch_name);
		GPIOF->PUR |= (1 << switch_name);/* pullup only as onboard switch when pressed connect pin with gnd */
		NVIC_EnableIRQ(GPIOF_IRQn);
		NVIC_SetPriority(GPIOF_IRQn, 0);
	}
	GPIOF->LOCK = 0x00000000;
}

unsigned char onBoardSwitchRead(unsigned char switch_name)
{
	return (((unsigned char)(GPIOF->DATA)) & (1 << switch_name));
}