#ifndef _SONALKUNJ_USART_H_
#define _SONALKUNJ_USART_H_

#include <stm32f401xe.h>

#define TXE_bit 7
#define USART1_CLK_bit 4 
#define RXNE_bit 5
#define UE_bit 13
#define TE_bit 3
#define RE_bit 2

void usart_1_Init(void);
void usart_1_Transmit(unsigned char data);
unsigned char usart_1_Receive(void);
void usart_1_Print(unsigned char *message);

#endif