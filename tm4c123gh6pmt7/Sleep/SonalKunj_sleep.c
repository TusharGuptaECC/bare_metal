#include "SonalKunj_sleep.h"

void goToSleep(unsigned char wake_up_method, unsigned char sleep_type)
{
	if (sleep_type == 0)
	{
		// normal sleep
		SYSCTRL_Reg &= ~(1 << DEEP_SLEEP_EN_bit);// go to normal sleep
	}
	else
	{
		// deep sleep
		SYSCTRL_Reg |= (1 << DEEP_SLEEP_EN_bit);// go to deep sleep
	}
	
	if (wake_up_method == 0)
	{
		// wake up via sleep on exit
		SYSCTRL_Reg |= (1 << SOE_EN_bit);
		__ASM("WFI");
	}
	else if (wake_up_method == 1)
	{
		// wake up via wait for event
		__ASM("WFE");
	}
	else
	{
		// wake up via wait for interrupt
		__ASM("WFI");
	}
}
