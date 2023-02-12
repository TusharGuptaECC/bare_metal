#include "SonalKunj_usart.h"

void usart_1_Init(void)
{
	/* provide clock to usart1 */
	RCC->APB2ENR |= (1 << USART1_CLK_bit);
	
	/* provide clock to portA  PA9 and PA10 */
	RCC->AHB1ENR |= (1 << 0);// gpioA
	
	/* alternate function at PA9 and PA10 i.e USART */
	GPIOA->MODER |= ((1 << 21) | (1 << 19));
	GPIOA->AFR[1] |= ((1 << 10) | (1 << 9) | (1 << 8) | (1 << 6) | (1 << 5) | (1 << 4));

	USART1->CR1 |= (1 << UE_bit);
	USART1->BRR = 0x683;
	USART1->CR1 |= (1 << TE_bit);
	USART1->CR1 |= (1 << RE_bit);
}

void usart_1_Transmit(unsigned char data)
{
	while (!(USART1->SR & (1 << TXE_bit)));
	USART1->DR = data;
}

unsigned char usart_1_Receive(void)
{
	while (!(USART1->SR & (1 << RXNE_bit)));
	return (unsigned char)USART1->DR;
}

void usart_1_Print(unsigned char *message)
{
  while(*message)
	{
		usart_1_Transmit(*(message++));
	}
}