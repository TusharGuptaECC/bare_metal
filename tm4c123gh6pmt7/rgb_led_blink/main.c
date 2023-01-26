/*
* Author: Tushar Gupta
* Developed using keil uVision5
* This file contains the blinke LED example
*/

#include <stdint.h>
#include "TM4C123.h"
#include "onBoard_LEDs.h"
#include "delay.h"

void clockInit(unsigned char clk_src);

#define PIOSC 0	/*Precision internal oscillator*/
#define MOSC 1	/*External main oscillator*/
#define my_delay 1000	

int main(void)
{
	clockInit(MOSC);
	gpioPinInit(GPIO, OUTPUT, red_led);
	gpioPinInit(GPIO, OUTPUT, blue_led);
	gpioPinInit(GPIO, OUTPUT, green_led);
	while(1)
	{
		/*red*/
		led(red_led, ON);
		led(blue_led, OFF);
		led(green_led, OFF);
		delayMS(my_delay);
		
		/*blue*/
		led(red_led, OFF);
		led(blue_led, ON);
		led(green_led, OFF);
		delayMS(my_delay);
		
		/*green*/
		led(red_led, OFF);
		led(blue_led, OFF);
		led(green_led, ON);
		delayMS(my_delay);
		
		/*cyan*/
		led(red_led, OFF);
		led(blue_led, ON);
		led(green_led, ON);
		delayMS(my_delay);
		
		/*yellow*/
		led(red_led, ON);
		led(blue_led, OFF);
		led(green_led, ON);
		delayMS(my_delay);
		
		/*magenta*/
		led(red_led, ON);
		led(blue_led, ON);
		led(green_led, OFF);
		delayMS(my_delay);
		
		/*white*/
		led(red_led, ON);
		led(blue_led, ON);
		led(green_led, ON);
		delayMS(my_delay);
		
		/*black or no colour*/
		led(red_led, OFF);
		led(blue_led, OFF);
		led(green_led, OFF);
		delayMS(my_delay);
	}
	return 0;
}

void clockInit(unsigned char clk_src)
{
	// RCC default value is 0x078E.3AD1
	if (clk_src == MOSC)
	{
		SYSCTL->RCC = 0x078E3D40;
	}
	if (clk_src == PIOSC)
	{
		SYSCTL->RCC = 0x078E3AD1;
	}
  
	RCGCGPIO_Reg |= (1 << clk_portf);  // clock for PORTF
	// SYSCTL->RCGC0 |= (1 << clk_portf);	// legacy register not used here.
}
