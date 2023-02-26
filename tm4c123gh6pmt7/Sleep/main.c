#define ONBOARD_LEDS_H
#define DELAY_H
#define ONBOARD_SWITCH_H
#define SLEEP_H

#include "configuration.h"

#define PIOSC 0	/*Precision internal oscillator*/
#define MOSC 1	/*External main oscillator*/

volatile unsigned char system_state = 0;

void GPIOF_Handler(void)
{
	if (GPIOF->MIS & (1 << 4))
	{
		system_state = 1;
		GPIOF->ICR |= (1 << 4);
	}
}

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
			goToSleep(SLEEP_WAKEUP_WFI, SLEEP_MODE_DEEP);
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
