#include "SonalKunj_onBoards.h"

void initOnBoardLED(void)
{
	RCC->AHB1ENR |= (1 << gpioa);
	GPIOA->MODER |= (1 << 10);
	/* GPIOA->OTYPER no change as by default it is push pull if = 1 the open drain */
	/* GPIOA->OSPEEDER no change by default low speed */
	/* GPIOA->PUPDR no change as no pull up and pull down */
	/* GPIOA->AFR no change default is system that is gpio */
}

void led(unsigned char state)
{
	if (state)
	{
		GPIOA->ODR |= (1 << 5);
	}
	else
	{
		GPIOA->ODR &= ~(1 << 5);
	}
}

void initOnBoardButton(void)
{
	/* disable the exti15_10 interrupts */
	__NVIC_DisableIRQ(EXTI15_10_IRQn);
	
	/* provide clock to port gpioc */
	RCC->AHB1ENR |= (1 << gpioc);
	/* GPIOC->MODER no change */
	/* GPIOC->OTYPER no change as by default it is push pull if = 1 the open drain */
	/* GPIOC->OSPEEDER no change by default low speed */
	/* pull-up */
	GPIOC->PUPDR |= (1 << 26);
	/* GPIOC->AFR no change default is system that is gpio */
	
	/* configure interrupts */
	/* provide clock to sysconfig controller */
	RCC->APB2ENR |= (1 << 14);

	/* configure interrupt input source for PC13 */
	SYSCFG->EXTICR[3] |= (1 << 5);
	
	/* unmask the line 13 interrupt */
	EXTI->IMR |= (1 <<13);
	
	/* rising edge at exti13 */
	EXTI->RTSR |= (1 << 13);
	
	/* set priority */
	__NVIC_SetPriority(EXTI15_10_IRQn, 0);
	
	/* enable the exti15_10 interrupts*/
	__NVIC_EnableIRQ(EXTI15_10_IRQn);
}
