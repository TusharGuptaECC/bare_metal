/*
* Author: Tushar Gupta
* Developed using keil uVision5
* This file contains the blinke LED example
*/

#include <stdint.h>
#include "TM4C123.h"
#include "onBoard_LEDs.h"
#include "delay.h"

void clockInit(void);
#define my_delay 10000	/*provides some of 500 ms approx.*/
int main(void)
{
	clockInit();
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
}

void clockInit(void)
{
	// board is set in such a way that we don't have to make any change in system RCC register
	// RCC default value is 0x078E.3AD1
   	RCGCGPIO_Reg |= (1 << clk_portf);  // clock for PORTF
	// SYSCTL->RCGC0 |= (1 << clk_portf);	// legacy register not used here.
}