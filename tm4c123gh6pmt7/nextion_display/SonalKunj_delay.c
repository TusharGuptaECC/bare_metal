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