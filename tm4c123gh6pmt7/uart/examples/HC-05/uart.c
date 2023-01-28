#include "uart.h"

void uartInit(void)
{
	/* provide clock to uart 7 */
	RCGCUART_Reg |= (1 << UART_7);
	
	/* clock to port e has been already provided by clockInit */
	
	/* unlock the gpio commit register */
	GPIOE->LOCK = 0x4C4F434B;
	
	/* commit register unmask the required bits to unlock */
	GPIOE->CR |= ((1 << UART_7_RX) | (1 << UART_7_TX));
	
	/* enable the alternate function control on given pins*/
	GPIOE->AFSEL |= ((1 << UART_7_RX) | (1 << UART_7_TX));

	/* selecting uart function for PE0 and PE1*/
	GPIOE->PCTL |= ((1 << 4) | (1 << 0));
	
	/* enable the digital operation on PE0 amd PE1 */
	GPIOE->DEN |= ((1 << UART_7_RX) | (1 << UART_7_TX));
	
	/* select the drive strength 8mA for slew rate control capability */
	GPIOE->DR8R |= ((1 << UART_7_RX) | (1 << UART_7_TX));
	
	/* slew rate control enable for RX and TX*/
	GPIOE->SLR |= ((1 << UART_7_RX) | (1 << UART_7_TX));
	
	/* disable the UART */
	UART7->CTL &= ~(1 << UART_7_EN_bit);
	
	/* BRD = (16,000,000/(16 x 9600)) = 104.16*/
	/* UARTIBRD = 104 i.e 0x68 */
	/* UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) formulae for fraction register */
	/* UARTFBRD = integer(0.16 x 64 + 0.5) = 10.74 i.e 11 i.e 0xB */
	/* did all calculation manually to avoid cpu load*/
	
	/* integer BRD register */
	UART7->IBRD = 0x68;	/* 16 bits are used out of 32 bits */
	
	/* fraction BRD register */
	UART7->FBRD = 0xB;	/* 6 bits are used out of 32 bits */
	
	/* parity disabled, stick parity disabled, FIFO mode disabled */
	/* only 8 bit data frame is selected with one stop bit */
	UART7->LCRH = 0x00000060;
	
	/* URATCC default */
	//UART7->CC = 0x0;
	
	/* enable the UART7 */
	UART7->CTL |= (1 << UART_7_EN_bit);
	
}

void uart_7_Transmit(unsigned char data)
{
	while(UART7->FR & (1 << UART_7_busy_transmit_bit));
	UART7->DR = data;				
}

unsigned char uart_7_Receive(void)
{
	while (!(UART7->FR & (1 << UART_7_RXFF_bit)));
	return (unsigned char)UART7->DR;
}

void uart_7_Print(unsigned char *message)
{
  while(*message)
	{
		uart_7_Transmit(*(message++));
	}
}
