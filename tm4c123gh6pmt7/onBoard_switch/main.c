/*
* Author: Tushar Gupta
* Software used: Keil uVision5
* This code configures the on board switches of EX-TM4C123GXL evaluation kit
* Code can configure switches in three modes
* -pull-up without interrupts
* -rising edge with pin change interrupt
* -falling edge with pin change interrupt
* NOTE: pull down mode code is provided but switches are connected to ground so this mode dosen't have any affects.
*/

#include <stdint.h>
#include "TM4C123.h"
#include "onBoard_LEDs.h"
#include "delay.h"
#include "onBoard_switches.h"

void initClock(void);

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
	onBoardSwitchInit(switch_two, pullup_mode_switch);
	gpioPinInit(GPIO, OUTPUT, green_led);
	gpioPinInit(GPIO, OUTPUT, red_led);
	led(red_led, ON);
	/*uncomment below while loop if using pull-up without interrupts otherwise use the second while loop*/
	while (1)
	{
		if (!onBoardSwitchRead(switch_two))
		{
			led(green_led, ON);
		}
		else
		{
			led(green_led, OFF);
		}
	}
	/*uncomment below while loop if using rising or falling edge with interrupts otherwise use the first while loop*/
	/*while (1)
	{
		delayMS(1000);
		if (state)
		{
			led(green_led, ON);
		}
		else
		{
			led(green_led, OFF);
		}
	}*/
	return 0;
}

void initClock(void)
{
	// board is set in such a way that we don't have to make any change in system RCC register
	// RCC default value is 0x078E.3AD1
   	RCGCGPIO_Reg |= (1 << clk_portf);  // clock for PORTF
	// SYSCTL->RCGC0 |= (1 << clk_portf);	// legacy register not used here.
}
