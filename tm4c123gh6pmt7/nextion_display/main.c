#define ONBOARD_LEDS_H
#define NEXTION_H

#include "configuration.h"

unsigned char settings[3] = {25,50,3};

#define PIOSC 0	/*Precision internal oscillator*/
#define MOSC 1	/*External main oscillator*/
#define clk_portb 1

void clockInit(unsigned char clk_src);

int main(void)
{
	unsigned char response;
	clockInit(MOSC);
	gpioPinInit(GPIO, OUTPUT, blue_led);
	gpioPinInit(GPIO, OUTPUT, green_led);
	gpioPinInit(GPIO, OUTPUT, red_led);
	nextionInit();
	
	while (1)
	{
//		for data transmission in form of text.
//		if (nextionRead_1() == 2)
//		{
//			led(blue_led, ON);
//			nextionSendSensorData(20,50,3);
//			led(red_led, ON);
//		}
//		if (nextionRead_1() == 0)
//		{
//			led(blue_led, OFF);
//		}
		
// for manual
//		response = nextionRead_1();
//		if (response == 6)
//		{
//			led(red_led, ON);
//		}
//		if (response == 7)
//		{
//			led(red_led, OFF);
//		}
//		if (response == 8)
//		{
//			led(blue_led, ON);
//		}
//		if (response == 9)
//		{
//			led(blue_led, OFF);
//		}
//		if (response == 10)
//		{
//			led(green_led, ON);
//		}
//		if (response == 11)
//		{
//			led(green_led, OFF);
//		}
//		if (response == 12)
//		{
//			led(red_led, ON);
//			led(green_led, ON);
//		}
//		if (response == 13)
//		{
//			led(red_led, OFF);
//			led(green_led, OFF);
//		}
	// for settings
	response = nextionRead_1();
	if (response == 4)
	{
		led(red_led, ON);
		while (1)
		{
			response = nextionRead_2();
			if (response == 200)
			{
				saveSettingsFromNextion();
				led(red_led, OFF);
				break;
			}
		}
		
	}
	if (settings[0] == 1)
	{
		led(red_led, ON);
	}
	if (settings[1] == 2)
	{
		led(blue_led, ON);
	}
	if (settings[2] == 30)
	{
		led(green_led, ON);
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
	RCGCGPIO_Reg |= ((1 << clk_portf) | (1 << clk_portb));  // clock for PORTF
	// SYSCTL->RCGC0 |= (1 << clk_portf);	// legacy register not used here.
}

