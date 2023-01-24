#include <stdint.h>
#include "TM4C123.h"
#include "onBoard_LEDs.h"
#include "delay.h"

#define switch_one 4	/* used in logic */
#define switch_two 0	/* used in logic */
#define sw1 4 /* bits in gpio port f */
#define sw2 0	/* bits in gpio port f */
#define pullup_mode_switch 0
#define pulldown_mode_switch 1
#define rising_edge_mode_switch 2
#define falling_edge_mode_switch 3

void initClock(void);
void onBoardSwitchInit(unsigned char switch_name, unsigned char switch_mode);
unsigned char onBoardSwitchRead(unsigned char switch_name);
volatile unsigned char state = 0; 
void GPIOF_Handler(void)
{
	if (GPIOF->MIS & (1 << 4))
	{
		state ^=1;
	}
	GPIOF->ICR |= (1 << 4);
}

int main(void)
{
	initClock();
	onBoardSwitchInit(switch_one, rising_edge_mode_switch);
	gpioPinInit(GPIO, OUTPUT, green_led);
	gpioPinInit(GPIO, OUTPUT, red_led);
	led(red_led, ON);
	/*uncomment below while loop if using pull-up or pull down mode without interrupts otherwise use the second while loop*/
	/*while (1)
	{
		if (!onBoardSwitchRead(switch_one))
		{
			led(green_led, ON);
		}
		else
		{
			led(green_led, OFF);
		}
	}*/
	while (1)
	{
		if (state)
		{
			led(green_led, ON);
		}
		else
		{
			led(green_led, OFF);
		}
	}
	return 0;
}

void initClock(void)
{
	// board is set in such a way that we don't have to make any change in system RCC register
	// RCC default value is 0x078E.3AD1
   	RCGCGPIO_Reg |= (1 << clk_portf);  // clock for PORTF
	// SYSCTL->RCGC0 |= (1 << clk_portf);	// legacy register not used here.
}

/*
* parameters: first is switch name & second is switch mode
*/
void onBoardSwitchInit(unsigned char switch_name, unsigned char switch_mode)
{
	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->CR |= (1 << 4);
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
		GPIOF->PDR |= (1 << switch_name);
		NVIC_EnableIRQ(GPIOF_IRQn);
		NVIC_SetPriority(GPIOF_IRQn, 0);
	}
}

unsigned char onBoardSwitchRead(unsigned char switch_name)
{
	return (((unsigned char)(GPIOF->DATA)) & (1 << switch_name));
}
