#include "SonalKunj_delay.h"

void delayMS(uint32_t wait)
{
	/*clock to timer 2 */
	RCC->APB1ENR |= (1 << tim2_bit);
	
	/* Timer2 is in upcounting mode */
	TIM2->CR1 &= ~(1 << CEN_bit);	/* disable timer 2 */
	
	while(wait > 0)
	{
		TIM2->CR1 |= (1 << OPM_bit);
		TIM2->CNT = 0;
		TIM2->ARR = 0x3E80;
		TIM2->CR1 |= (1 << CEN_bit);	/* enable timer 2 */
		while (!(TIM2->SR & (1 << UIF_bit)));
		TIM2->SR &= ~(1 << UIF_bit);
		wait--;
	}
}

void delayUS(uint32_t wait)
{
	/*clock to timer 2 */
	RCC->APB1ENR |= (1 << tim2_bit);
	
	/* Timer2 is in upcounting mode */
	TIM2->CR1 &= ~(1 << CEN_bit);	/* disable timer 2 */
	
	while(wait > 0)
	{
		TIM2->CR1 |= (1 << OPM_bit);
		TIM2->CNT = 0;
		TIM2->ARR = 0x10;
		TIM2->CR1 |= (1 << CEN_bit);	/* enable timer 2 */
		while (!(TIM2->SR & (1 << UIF_bit)));
		TIM2->SR &= ~(1 << UIF_bit);
		wait--;
	}
}