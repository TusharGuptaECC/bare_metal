#ifndef _ONBOARD_LEDS_
#define _ONBOARD_LEDS_

#include "configuration.h"
#define RCGCGPIO_Reg (*((volatile uint32_t *)0x400FE608))
	
#define clk_portf 5    /* provide clock to portF */
#define red_led 1
#define blue_led 2
#define green_led 3
#define ON 1
#define OFF 0
#define OUTPUT 1
#define INPUT 0
#define GPIO 0

/*function declarations*/

void gpioPortInit(void);
void gpioPinInit(unsigned char, unsigned char, unsigned char);
void led(unsigned char, unsigned char);

#endif
