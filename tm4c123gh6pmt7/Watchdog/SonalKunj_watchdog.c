#include "SonalKunj_watchdog.h"

void initWatchDog1(void)
{
	// provide clk to watchdog timer 1
	SYSCTL->RCGCWD |= WD1_CLK_EN;
	delayMS(100);	// give time to clock to synchronize
	
	while (!(WATCHDOG1->CTL & (1 << 31)));
	WATCHDOG1->LOAD = 80000000;	// wait for 5 sec
	
	while (!(WATCHDOG1->CTL & (1 << 31)));
	// interrupt type standard
	// no reset at first timeout
	WATCHDOG1->CTL |= WD_EN;	// enable the interrupt and timer
	
	while (!(WATCHDOG1->MIS & (1 << 0)));	// poll for interrupt
	WATCHDOG1->ICR = 0x1;	// writing anything will clear the interrupt
	while (!(WATCHDOG1->CTL & (1 << 31)));
	WATCHDOG1->CTL &= 0;	// disable the watchdog timer 1
	SYSCTL->RCGCWD = 0;
	
	// write trigger code here
	// here in this case it is switch ON the red led
	//led(red_led, ON);	// trigger the led
}