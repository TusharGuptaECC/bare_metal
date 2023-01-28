#ifndef _UART_H_
#define _UART_H_

#include "configuration.h"

#define RCGCUART_Reg (*((volatile uint32_t *)0x400FE618))
#define UART_7_ECR_Reg (*((volatile uint32_t *)0x40013004))
	
#define UART_7 7
#define UART_7_RX 0
#define UART_7_TX 1
#define UART_7_EN_bit 0
#define UART_7_busy_transmit_bit 3
#define UART_7_RXFF_bit 6

void uartInit(void);
void uart_7_Transmit(unsigned char data);
unsigned char uart_7_Receive(void);
void uart_7_Print(unsigned char *message);

#endif
