/*
 *  Author: Tushar Gupta
 *  File: main.c // this is the main file for the project
 *  Developed using Keil uVision5
 */
#include <stdint.h>
#include "TM4C123.h"

#define RCGCGPIO_Reg (*((volatile uint32_t *)0x400FE608))
	
#define clk_portf 5    // provide clock to portF
#define red_led 1
#define blue_led 2
#define green_led 3
#define ON 1
#define OFF 0
#define OUTPUT 1
#define INPUT 0
#define GPIO 0

/*function declarations*/

void clockInit(void);
void gpioPortInit(void);
void gpioPinInit(unsigned char, unsigned char, unsigned char);
void led(unsigned char, unsigned char);

int main(void)
{
	clockInit();
	gpioPinInit(GPIO, OUTPUT, red_led);
	gpioPinInit(GPIO, OUTPUT, blue_led);
	gpioPinInit(GPIO, OUTPUT, green_led);
	led(red_led, ON);
	led(blue_led, ON);
	led(green_led, ON);
	// white colour is displayed
	return 0;
}

void clockInit(void)
{
	// board is set in such a way that we don't have to make any change in system RCC register
	// RCC default value is 0x078E.3AD1
   	RCGCGPIO_Reg |= (1 << clk_portf);  // clock for PORTF
	// SYSCTL->RCGC0 |= (1 << clk_portf);	// legacy register not used here.
}

void gpioPortInit()
{

}

void gpioPinInit(unsigned char function, unsigned char dir, unsigned char pin)
{
    if (function == GPIO)
    {
		GPIOF->AFSEL &= ~(1 << pin);
    }

    GPIOF->DR2R |= ((1 << red_led) | (1 << blue_led) | (1 << green_led));
		
    if (dir)
    {
        GPIOF->DIR |= (1 << pin);
    }
    else
    {
        GPIOF->DIR &= ~(1 << pin);
    }
    GPIOF->DEN |= ((1 << red_led) | (1 << blue_led) | (1 << green_led));
}

void led(unsigned char colour, unsigned char status)
{
    if (status && (colour == red_led))
    {
        GPIOF->DATA |= (1 << red_led);
	}
    else if (status && (colour == blue_led))
    {
        GPIOF->DATA |= (1 << blue_led);
    }
    else if (status && (colour == green_led))
    {
        GPIOF->DATA |= (1 << green_led);
    }
    else
    {
        if (colour == red_led)
        {
            GPIOF->DATA &= ~(1 << red_led);
        }
        if (colour == blue_led)
        {
            GPIOF->DATA &= ~(1 << blue_led);
        }
        if (colour == green_led)
        {
            GPIOF->DATA &= ~(1 << green_led);
        }
    }
}
