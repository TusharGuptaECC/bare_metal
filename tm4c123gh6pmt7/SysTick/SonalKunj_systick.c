#include "SonalKunj_systick.h"

// 1.048 sec 16 MHz
// 4.194 sec on PIOSC
void sysTickInit(unsigned char clock_source, unsigned char is_interrupt_en, uint32_t time_out)
{
	SysTick->CTRL &= ~(1 << 0); 
	NVIC_DisableIRQ(SysTick_IRQn);
	if (clock_source)
	{
		// PIOSC is selected
		SysTick->LOAD = (time_out*4000000); 
		SysTick_CURRENT_Reg = 1;
		SysTick->CTRL &= ~(1 << 2);
	}
	else
	{
		// system clock is selected
		// assume system clock is set at 16MHz
		SysTick->LOAD = (time_out*16000000); 
		SysTick_CURRENT_Reg = 1;
		SysTick->CTRL |= (1 << 2);
	}
	if (is_interrupt_en)
	{
		SysTick->CTRL |= (1 << 1);
		NVIC_EnableIRQ(SysTick_IRQn);
	}
	else
	{
		SysTick->CTRL &= ~(1 << 1);
	}
	SysTick->CTRL |= (1 << 0);
}