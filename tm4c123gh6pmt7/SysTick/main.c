#define ONBOARD_LEDS_H
#define DELAY_H
#define SYSTICK_H

#include "configuration.h"


#define PIOSC 0	/*Precision internal oscillator*/
#define MOSC 1	/*External main oscillator*/

//---------------------------------------------------------------

#define SYSCTRL_Reg (*((volatile uint32_t *)0xE0000D10))

volatile unsigned char system_state = 0;



void SysTick_Handler(void)
{
  if (SysTick->CTRL & (1 << 16))
  {
    system_state = 1;
    SysTick->CTRL = 0;  // disable the timer
  }
}

void clockInit(unsigned char clk_src);

int main(void)
{
	// sleep mode code test
	clockInit(MOSC);
	gpioPinInit(GPIO, OUTPUT, green_led);
	gpioPinInit(GPIO, OUTPUT, red_led);
	while (1)
	{
		delayMS(100);
		if (system_state == 0)
		{
			led(red_led, ON);
			SYSCTRL_Reg |= (1 << 2);// when triggered go to deep sleep
	                sysTickInit(SysTick_CLOCK_SRC_PIOSC, SysTick_INTERRUPT_EN, 4);// timeout is 4 sec
	                __ASM("WFI");// go to deep sleep
	                led(red_led, OFF);
		}
		else
		{
			while (1)
			{
				led(green_led, ON);
				delayMS(1000);
				led(green_led, OFF);
				delayMS(1000);
			}
		}
	}
	return 0;
}

void clockInit(unsigned char clk_src)
{
	// RCC default value is 0x078E.3AD1
	uint32_t i;
	if (clk_src == MOSC)
	{
		SYSCTL->RCC = 0x000E3D40;
	}
	if (clk_src == PIOSC)
	{
		SYSCTL->RCC = 0x078E3AD1;
	}
  for (i = 0; i < 10000; i++);
	RCGCGPIO_Reg |= ((1 << clk_portf) | (1 << clk_portb) | CLOCK_TO_GPIO_E);  // clock for PORTF
	// SYSCTL->RCGC0 |= (1 << clk_portf);	// legacy register not used here.
	SystemCoreClockUpdate();
}
