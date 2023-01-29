#define ONBOARD_LEDS_H
#define UART_H
#include "configuration.h"
	
#define clk_portf 5    /* provide clock to portF */
#define clk_porte 4	 	 /* provide clock to portE */
#define clk_portd 3
#define clk_portb 1
#define PIOSC 0	/*Precision internal oscillator*/
#define MOSC 1	/*External main oscillator*/

void clockInit(unsigned char clk_src);

 int main(void)
{
	unsigned char data = 0;
	clockInit(MOSC);
	uart_1_Init();
	gpioPinInit(GPIO, OUTPUT, red_led);
	gpioPinInit(GPIO, OUTPUT, blue_led);
	gpioPinInit(GPIO, OUTPUT, green_led);
	
	uart_1_Print("Waiting for instructions: \n");
	while(1)
	{
		data = uart_1_Receive();
		if (data == 'a')
		{
			uart_1_Print("RED LED ON \n");
			led(red_led, ON);
		}
		else if (data == 'b')
		{
			uart_1_Print("RED LED OFF \n");
			led(red_led, OFF);
		}
		else if (data == 'c')
		{
			uart_1_Print("GREEN LED ON \n");
			led(green_led, ON);
		}
		else if (data == 'd')
		{
			uart_1_Print("GREEN LED OFF \n");
			led(green_led, OFF);
		}
		else if (data == 'e')
		{
			uart_1_Print("BLUE LED ON \n");
			led(blue_led, ON);
		}
		else if (data == 'f')
		{
			uart_1_Print("BLUE LED OFF \n");
			led(blue_led, OFF);
		}
		else
		{
			// do nothing
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

