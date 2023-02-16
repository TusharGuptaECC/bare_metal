#ifndef _SONALKUNJ_UART_H_
#define _SONALKUNJ_UART_H_

#include "configuration.h"

#define RCGCUART_Reg (*((volatile uint32_t *)0x400FE618))
#define UART_7_ECR_Reg (*((volatile uint32_t *)0x40013004))
	
#define UART_7 7
#define UART_6 6
#define UART_5 5
#define UART_4 4
#define UART_3 3
#define UART_2 2
#define UART_1 1
#define UART_0 0

#define UART_7_RX 0
#define UART_7_TX 1

#define UART_6_RX 4
#define UART_6_TX 5

#define UART_5_RX 4
#define UART_5_TX 5

#define UART_4_RX 4
#define UART_4_TX 5

#define UART_3_RX 6
#define UART_3_TX 7

#define UART_2_RX 6
#define UART_2_TX 7

#define UART_1_RX 0
#define UART_1_TX 1

#define UART_0_RX 0
#define UART_0_TX 1

#define UART_EN_bit 0
#define UART_busy_transmit_bit 3
#define UART_RXFF_bit 6

void uart_7_Init(void);
void uart_6_Init(void);
void uart_5_Init(void);
void uart_4_Init(void);
void uart_3_Init(void);
void uart_2_Init(void);
void uart_1_Init(void);
void uart_0_Init(void);

void uart_7_Transmit(unsigned char data);
void uart_6_Transmit(unsigned char data);
void uart_5_Transmit(unsigned char data);
void uart_4_Transmit(unsigned char data);
void uart_3_Transmit(unsigned char data);
void uart_2_Transmit(unsigned char data);
void uart_1_Transmit(unsigned char data);
void uart_0_Transmit(unsigned char data);

void uart_7_Print(unsigned char *message);
void uart_6_Print(unsigned char *message);
void uart_5_Print(unsigned char *message);
void uart_4_Print(unsigned char *message);
void uart_3_Print(unsigned char *message);
void uart_2_Print(unsigned char *message);
void uart_1_Print(unsigned char *message);
void uart_0_Print(unsigned char *message);

unsigned char uart_7_Receive(void);
unsigned char uart_6_Receive(void);
unsigned char uart_5_Receive(void);
unsigned char uart_4_Receive(void);
unsigned char uart_3_Receive(void);
unsigned char uart_2_Receive(void);
unsigned char uart_1_Receive(void);
unsigned char uart_0_Receive(void);


#endif