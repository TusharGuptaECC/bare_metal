#include "SonalKunj_delay.h"
/*
 * @param unsigned char wait
 * @brief provides a blocking delay for "wait" miliseconds
*/

void delayMS(uint32_t wait1)
{
	wait1 = wait1 * 16;
	while (wait1 != 0)
	{
		/*provide clock to 16/32 bit timers*/
		RCGCTIMER_Reg |= (1 << TIMER0_bit);
		
		/*provide clock to 32/64 bit timers*/
		/*uncomment the following line to provide clock to 32/64 bit timers in case of large delays*/
		/*RCGCWTIMER_Reg |= (1 << TIMER0_bit);*/
		
		/*disable the gptm block 0 timer B*/
		TIMER0->CTL &= ~(1 << TBEN_bit);
		
		/*For a 16/32-bit timer, this value selects the 16-bit timer configuration*/
		TIMER0->CFG = 0x00000004;
		
		/*one short mode*/
		TIMER0->TBMR |= (1 << one_shot_mode_bit);
		
		/*sets the upper bound for the timeout event*/
		TIMER0->TBILR = 0x00000400;	/*64 micro second time out*/
		
		/*enable the gptm block 0 timer B*/
		TIMER0->CTL |= (1 << TBEN_bit);
		
		/*polling for timeout*/
		while (!(TIMER0->RIS & (1 << TBTORIS_bit)));
		
		/*resetting the flag*/
		TIMER0->ICR |= (1 << TBTORIS_bit);
		
		wait1 -= 1;
	}
}

/*
 * @param unsigned char wait
 * @brief provides a blocking delay for "wait" microseconds
*/
void delayUS(uint32_t wait1)
{
	while (wait1 != 0)
	{
		/*provide clock to 16/32 bit timers*/
		RCGCTIMER_Reg |= (1 << TIMER0_bit);
		
		/*provide clock to 32/64 bit timers*/
		/*uncomment the following line to provide clock to 32/64 bit timers in case of large delays*/
		/*RCGCWTIMER_Reg |= (1 << TIMER0_bit);*/
		
		/*disable the gptm block 0 timer B*/
		TIMER0->CTL &= ~(1 << TBEN_bit);
		
		/*For a 16/32-bit timer, this value selects the 16-bit timer configuration*/
		TIMER0->CFG = 0x00000004;
		
		/*one short mode*/
		TIMER0->TBMR |= (1 << one_shot_mode_bit);
		
		/*sets the upper bound for the timeout event*/
		TIMER0->TBILR = 0x00000010;	/*1 micro second time out*/
		
		/*enable the gptm block 0 timer B*/
		TIMER0->CTL |= (1 << TBEN_bit);
		
		/*polling for timeout*/
		while (!(TIMER0->RIS & (1 << TBTORIS_bit)));
		
		/*resetting the flag*/
		TIMER0->ICR |= (1 << TBTORIS_bit);
		
		wait1 -= 1;
	}
}

void inputCaptureInit(unsigned char pin)
{
	// asuming clock has been provided to gpio pin
	
	// provide clock to timer1
	RCGCTIMER_Reg |= (1 << TIMER1_bit);
	
	// unlock the pf2 bit
	GPIOF->LOCK = 0x4C4F434B;
	
	// commit pf2 changes
	GPIOF->CR |= (1 << pin);
	
	// enable digital function
	GPIOF->DEN |= (1 << pin);
	
	// selected pin as input
	GPIOF->DIR &= ~(1 << pin);
	
	// enable alternate function at selected pin
	GPIOF->AFSEL |= (1 << pin);
	
	// select the alternate function at given pin
	GPIOF->PCTL |= TIMER1_CCP0;//((1 << 10) | (1 << 9) | (1 << 8));
	
	// disable the timer1A
	TIMER1->CTL &= ~(1 << 0);
	
	// configure the use of timer
	TIMER1->CFG = 0x00000004;
	
	// configure the running mode of the timer
	TIMER1->TAMR |= TIMER_SELECT_CAPTURE_MODE | TIMER_PULSE_TIME_CAPTURE_MODE | TIMER_UP_COUNTER_MODE;//((1 << 4) | (1 << 2) | (1 << 1) | (1 << 0));

	// type of capture event defaul set to rising edges
	//TIMER1->CTL |= bits 3 and 2
	
	// prescaler no use in 32 bit mode of 16/32 bit timer
	
	// load the upper bound to inerval load register tequirement is 65536 i.e default so no change
	TIMER1->TAILR = 0x0000FFFF;	

	// enable the interrupt
	TIMER1->ICR |= (1 << 2);
	TIMER1->IMR |= (1 << 2);
	NVIC_SetPriority(TIMER1A_IRQn, 1);
	NVIC_EnableIRQ(TIMER1A_IRQn);
	
	// on the timer A
	TIMER1->CTL |= (1 << 0);
}

void resetTimer1(void)
{
	TIMER1->CTL &= ~(1 << TAEN_bit); // off the timer
	// reset the timer
	SRTIMER_Reg |= (1 << TIMER1_bit);
	delayMS(100);
	SRTIMER_Reg &= ~(1 << TIMER1_bit);
	// put some delay as timer takes time to set again
	delayMS(100);
}