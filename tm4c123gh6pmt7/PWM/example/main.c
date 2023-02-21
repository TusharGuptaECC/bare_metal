#define ONBOARD_LEDS_H
#define NEXTION_H
#define DELAY_H
#define SWITCH_H
#define ADC_H
#define PWM_H

#include "configuration.h"

unsigned char settings[3] = {16,50,3};

#define PIOSC 0	/*Precision internal oscillator*/
#define MOSC 1	/*External main oscillator*/
#define clk_portb 1
#define dht_pin 2	// portf

//---------------------------------------------------------------


//---------------------------------------------------------------

volatile uint32_t present_time = 0;
volatile uint32_t past_time = 0;
uint32_t dht_data;
volatile int dht_count = 0;
volatile float co2_data = 0;

void TIMER1A_Handler(void)
{
	//led(red_led, ON);
	if (TIMER1->MIS & (1 << 2))
	{
		TIMER1->ICR |= (1 << 2);
		past_time = present_time;
		present_time = ((TIMER1->TAR & 0x0000FFFF));
		dht_count = dht_count + 1;
	}
}

void ADC0SS0_Handler(void)
{
	if (ADC0->ISC & (1 << 0))
	{
		ADC0->ISC |= (1 << 0);
		co2_data = ((8*(ADC0->SSFIFO0 & 0x00000FFF))/10000.00);
	}
}

void clockInit(unsigned char clk_src);
void dhtInit(void);
void dhtReadData(void);

int main(void)
{
	unsigned char response;
	clockInit(MOSC);
	//gpioPinInit(GPIO, OUTPUT, blue_led);
	gpioPinInit(GPIO, OUTPUT, green_led);
	gpioPinInit(GPIO, OUTPUT, red_led);
	nextionInit();
	
	while (1)
	{
//		for data transmission in form of text.
		//delayMS(2000);
		if (nextionRead_1() == 2)
		{
			dhtInit();
		  dhtReadData();
			adcInitAndReadData();
			nextionSendSensorData(((dht_data >> 24) & 0x000000FF), ((dht_data >> 8) & 0x000000FF), co2_data);
			pwm();
			//led(red_led, ON);
		}
		else//if (nextionRead_1() == 0)
		{
			led(green_led, OFF);
		}
		
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
//	response = nextionRead_1();
//	if (response == 4)
//	{
//		led(red_led, ON);
//		while (1)
//		{
//			response = nextionRead_2();
//			if (response == 200)
//			{
//				saveSettingsFromNextion();
//				led(red_led, OFF);
//				break;
//			}
//		}
//		
//	}
//	if (settings[0] == 1)
//	{
//		led(red_led, ON);
//	}
//	if (settings[1] == 2)
//	{
//		led(blue_led, ON);
//	}
//	if (settings[2] == 30)
//	{
//		led(green_led, ON);
//	}
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

void dhtInit(void)
{
	gpioPinInit(GPIO, OUTPUT, dht_pin);
	led(dht_pin, ON);
	delayMS(1000);
	led(dht_pin, OFF);
	delayMS(25);
	led(dht_pin, ON);
	delayUS(5);
	led(dht_pin, OFF);
	gpioPinInit(GPIO, INPUT, dht_pin);
	inputCaptureInit(dht_pin);
}

void dhtReadData(void)
{
	while(dht_count < 31)
	{
		if(dht_count < 3)
		{
			//led(green_led, ON);
			// do nothing
			{}	// avoid compiler optimization
		}
		else if (present_time - past_time > 1600)//past_time - present_time > 1600 ) // 100us
		{
			dht_data |= (1 << (31 - dht_count + 3));
		}
		else
		{
			dht_data &= ~(1 << (31 - dht_count + 3));
		}
		
	}
	while(dht_count < 42)
	{
		{}// do nothing
		
	}
	TIMER1->CTL &= ~(1 << TAEN_bit); // off the timer
	// reset the timer
	resetTimer1();
}


	
	
