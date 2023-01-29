#include "uart.h"

/* all uart init functions */
void uart_7_Init(void)
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
	UART7->CTL &= ~(1 << UART_EN_bit);
	
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
	UART7->CTL |= (1 << UART_EN_bit);
	
}

void uart_6_Init(void)
{
	/* provide clock to uart 7 */
	RCGCUART_Reg |= (1 << UART_6);
	
	/* clock to port e has been already provided by clockInit */
	
	/* unlock the gpio commit register */
	GPIOD->LOCK = 0x4C4F434B;
	
	/* commit register unmask the required bits to unlock */
	GPIOD->CR |= ((1 << UART_6_RX) | (1 << UART_6_TX));
	
	/* enable the alternate function control on given pins*/
	GPIOD->AFSEL |= ((1 << UART_6_RX) | (1 << UART_6_TX));

	/* selecting uart function for PE0 and PE1*/
	GPIOD->PCTL |= ((1 << 20) | (1 << 16));
	
	/* enable the digital operation on PE0 amd PE1 */
	GPIOD->DEN |= ((1 << UART_6_RX) | (1 << UART_6_TX));
	
	/* select the drive strength 8mA for slew rate control capability */
	GPIOD->DR8R |= ((1 << UART_6_RX) | (1 << UART_6_TX));
	
	/* slew rate control enable for RX and TX*/
	GPIOD->SLR |= ((1 << UART_6_RX) | (1 << UART_6_TX));
	
	/* disable the UART */
	UART6->CTL &= ~(1 << UART_EN_bit);
	
	/* BRD = (16,000,000/(16 x 9600)) = 104.16*/
	/* UARTIBRD = 104 i.e 0x68 */
	/* UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) formulae for fraction register */
	/* UARTFBRD = integer(0.16 x 64 + 0.5) = 10.74 i.e 11 i.e 0xB */
	/* did all calculation manually to avoid cpu load*/
	
	/* integer BRD register */
	UART6->IBRD = 0x68;	/* 16 bits are used out of 32 bits */
	
	/* fraction BRD register */
	UART6->FBRD = 0xB;	/* 6 bits are used out of 32 bits */
	
	/* parity disabled, stick parity disabled, FIFO mode disabled */
	/* only 8 bit data frame is selected with one stop bit */
	UART6->LCRH = 0x00000060;
	
	/* URATCC default */
	//UART7->CC = 0x0;
	
	/* enable the UART7 */
	UART6->CTL |= (1 << UART_EN_bit);
	
}

void uart_5_Init(void)
{
	/* provide clock to uart 7 */
	RCGCUART_Reg |= (1 << UART_5);
	
	/* clock to port e has been already provided by clockInit */
	
	/* unlock the gpio commit register */
	GPIOE->LOCK = 0x4C4F434B;
	
	/* commit register unmask the required bits to unlock */
	GPIOE->CR |= ((1 << UART_5_RX) | (1 << UART_5_TX));
	
	/* enable the alternate function control on given pins*/
	GPIOE->AFSEL |= ((1 << UART_5_RX) | (1 << UART_5_TX));

	/* selecting uart function for PE0 and PE1*/
	GPIOE->PCTL |= ((1 << 20) | (1 << 16));
	
	/* enable the digital operation on PE0 amd PE1 */
	GPIOE->DEN |= ((1 << UART_5_RX) | (1 << UART_5_TX));
	
	/* select the drive strength 8mA for slew rate control capability */
	GPIOE->DR8R |= ((1 << UART_5_RX) | (1 << UART_5_TX));
	
	/* slew rate control enable for RX and TX*/
	GPIOE->SLR |= ((1 << UART_5_RX) | (1 << UART_5_TX));
	
	/* disable the UART */
	UART5->CTL &= ~(1 << UART_EN_bit);
	
	/* BRD = (16,000,000/(16 x 9600)) = 104.16*/
	/* UARTIBRD = 104 i.e 0x68 */
	/* UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) formulae for fraction register */
	/* UARTFBRD = integer(0.16 x 64 + 0.5) = 10.74 i.e 11 i.e 0xB */
	/* did all calculation manually to avoid cpu load*/
	
	/* integer BRD register */
	UART5->IBRD = 0x68;	/* 16 bits are used out of 32 bits */
	
	/* fraction BRD register */
	UART5->FBRD = 0xB;	/* 6 bits are used out of 32 bits */
	
	/* parity disabled, stick parity disabled, FIFO mode disabled */
	/* only 8 bit data frame is selected with one stop bit */
	UART5->LCRH = 0x00000060;
	
	/* URATCC default */
	//UART7->CC = 0x0;
	
	/* enable the UART7 */
	UART5->CTL |= (1 << UART_EN_bit);
	
}

void uart_4_Init(void)
{
	/* provide clock to uart 7 */
	RCGCUART_Reg |= (1 << UART_4);
	
	/* clock to port e has been already provided by clockInit */
	
	/* unlock the gpio commit register */
	GPIOC->LOCK = 0x4C4F434B;
	
	/* commit register unmask the required bits to unlock */
	GPIOC->CR |= ((1 << UART_4_RX) | (1 << UART_4_TX));
	
	/* enable the alternate function control on given pins*/
	GPIOC->AFSEL |= ((1 << UART_4_RX) | (1 << UART_4_TX));

	/* selecting uart function for PE0 and PE1*/
	GPIOC->PCTL |= ((1 << 20) | (1 << 16));
	
	/* enable the digital operation on PE0 amd PE1 */
	GPIOC->DEN |= ((1 << UART_4_RX) | (1 << UART_4_TX));
	
	/* select the drive strength 8mA for slew rate control capability */
	GPIOC->DR8R |= ((1 << UART_4_RX) | (1 << UART_4_TX));
	
	/* slew rate control enable for RX and TX*/
	GPIOC->SLR |= ((1 << UART_4_RX) | (1 << UART_4_TX));
	
	/* disable the UART */
	UART4->CTL &= ~(1 << UART_EN_bit);
	
	/* BRD = (16,000,000/(16 x 9600)) = 104.16*/
	/* UARTIBRD = 104 i.e 0x68 */
	/* UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) formulae for fraction register */
	/* UARTFBRD = integer(0.16 x 64 + 0.5) = 10.74 i.e 11 i.e 0xB */
	/* did all calculation manually to avoid cpu load*/
	
	/* integer BRD register */
	UART4->IBRD = 0x68;	/* 16 bits are used out of 32 bits */
	
	/* fraction BRD register */
	UART4->FBRD = 0xB;	/* 6 bits are used out of 32 bits */
	
	/* parity disabled, stick parity disabled, FIFO mode disabled */
	/* only 8 bit data frame is selected with one stop bit */
	UART4->LCRH = 0x00000060;
	
	/* URATCC default */
	//UART7->CC = 0x0;
	
	/* enable the UART7 */
	UART4->CTL |= (1 << UART_EN_bit);
	
}

void uart_3_Init(void)
{
	/* provide clock to uart 7 */
	RCGCUART_Reg |= (1 << UART_3);
	
	/* clock to port e has been already provided by clockInit */
	
	/* unlock the gpio commit register */
	GPIOC->LOCK = 0x4C4F434B;
	
	/* commit register unmask the required bits to unlock */
	GPIOC->CR |= ((1 << UART_3_RX) | (1 << UART_3_TX));
	
	/* enable the alternate function control on given pins*/
	GPIOC->AFSEL |= ((1 << UART_3_RX) | (1 << UART_3_TX));

	/* selecting uart function for PE0 and PE1*/
	GPIOC->PCTL |= ((1 << 28) | (1 << 24));
	
	/* enable the digital operation on PE0 amd PE1 */
	GPIOC->DEN |= ((1 << UART_3_RX) | (1 << UART_3_TX));
	
	/* select the drive strength 8mA for slew rate control capability */
	GPIOC->DR8R |= ((1 << UART_3_RX) | (1 << UART_3_TX));
	
	/* slew rate control enable for RX and TX*/
	GPIOC->SLR |= ((1 << UART_3_RX) | (1 << UART_3_TX));
	
	/* disable the UART */
	UART3->CTL &= ~(1 << UART_EN_bit);
	
	/* BRD = (16,000,000/(16 x 9600)) = 104.16*/
	/* UARTIBRD = 104 i.e 0x68 */
	/* UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) formulae for fraction register */
	/* UARTFBRD = integer(0.16 x 64 + 0.5) = 10.74 i.e 11 i.e 0xB */
	/* did all calculation manually to avoid cpu load*/
	
	/* integer BRD register */
	UART3->IBRD = 0x68;	/* 16 bits are used out of 32 bits */
	
	/* fraction BRD register */
	UART3->FBRD = 0xB;	/* 6 bits are used out of 32 bits */
	
	/* parity disabled, stick parity disabled, FIFO mode disabled */
	/* only 8 bit data frame is selected with one stop bit */
	UART3->LCRH = 0x00000060;
	
	/* URATCC default */
	//UART7->CC = 0x0;
	
	/* enable the UART7 */
	UART3->CTL |= (1 << UART_EN_bit);
	
}

void uart_2_Init(void)
{
	/* provide clock to uart 7 */
	RCGCUART_Reg |= (1 << UART_2);
	
	/* clock to port e has been already provided by clockInit */
	
	/* unlock the gpio commit register */
	GPIOD->LOCK = 0x4C4F434B;
	
	/* commit register unmask the required bits to unlock */
	GPIOD->CR |= ((1 << UART_2_RX) | (1 << UART_2_TX));
	
	/* enable the alternate function control on given pins*/
	GPIOD->AFSEL |= ((1 << UART_2_RX) | (1 << UART_2_TX));

	/* selecting uart function for PE0 and PE1*/
	GPIOD->PCTL |= ((1 << 28) | (1 << 24));
	
	/* enable the digital operation on PE0 amd PE1 */
	GPIOD->DEN |= ((1 << UART_2_RX) | (1 << UART_2_TX));
	
	/* select the drive strength 8mA for slew rate control capability */
	GPIOD->DR8R |= ((1 << UART_2_RX) | (1 << UART_2_TX));
	
	/* slew rate control enable for RX and TX*/
	GPIOD->SLR |= ((1 << UART_2_RX) | (1 << UART_2_TX));
	
	/* disable the UART */
	UART2->CTL &= ~(1 << UART_EN_bit);
	
	/* BRD = (16,000,000/(16 x 9600)) = 104.16*/
	/* UARTIBRD = 104 i.e 0x68 */
	/* UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) formulae for fraction register */
	/* UARTFBRD = integer(0.16 x 64 + 0.5) = 10.74 i.e 11 i.e 0xB */
	/* did all calculation manually to avoid cpu load*/
	
	/* integer BRD register */
	UART2->IBRD = 0x68;	/* 16 bits are used out of 32 bits */
	
	/* fraction BRD register */
	UART2->FBRD = 0xB;	/* 6 bits are used out of 32 bits */
	
	/* parity disabled, stick parity disabled, FIFO mode disabled */
	/* only 8 bit data frame is selected with one stop bit */
	UART2->LCRH = 0x00000060;
	
	/* URATCC default */
	//UART7->CC = 0x0;
	
	/* enable the UART7 */
	UART2->CTL |= (1 << UART_EN_bit);
	
}

void uart_1_Init(void)
{
	/* provide clock to uart 7 */
	RCGCUART_Reg |= (1 << UART_1);
	
	/* clock to port e has been already provided by clockInit */
	
	/* unlock the gpio commit register */
	GPIOB->LOCK = 0x4C4F434B;
	
	/* commit register unmask the required bits to unlock */
	GPIOB->CR |= ((1 << UART_1_RX) | (1 << UART_1_TX));
	
	/* enable the alternate function control on given pins*/
	GPIOB->AFSEL |= ((1 << UART_1_RX) | (1 << UART_1_TX));

	/* selecting uart function for PE0 and PE1*/
	GPIOB->PCTL |= ((1 << 4) | (1 << 0));
	
	/* enable the digital operation on PE0 amd PE1 */
	GPIOB->DEN |= ((1 << UART_1_RX) | (1 << UART_1_TX));
	
	/* select the drive strength 8mA for slew rate control capability */
	GPIOB->DR8R |= ((1 << UART_1_RX) | (1 << UART_1_TX));
	
	/* slew rate control enable for RX and TX*/
	GPIOB->SLR |= ((1 << UART_1_RX) | (1 << UART_1_TX));
	
	/* disable the UART */
	UART1->CTL &= ~(1 << UART_EN_bit);
	
	/* BRD = (16,000,000/(16 x 9600)) = 104.16*/
	/* UARTIBRD = 104 i.e 0x68 */
	/* UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) formulae for fraction register */
	/* UARTFBRD = integer(0.16 x 64 + 0.5) = 10.74 i.e 11 i.e 0xB */
	/* did all calculation manually to avoid cpu load*/
	
	/* integer BRD register */
	UART1->IBRD = 0x68;	/* 16 bits are used out of 32 bits */
	
	/* fraction BRD register */
	UART1->FBRD = 0xB;	/* 6 bits are used out of 32 bits */
	
	/* parity disabled, stick parity disabled, FIFO mode disabled */
	/* only 8 bit data frame is selected with one stop bit */
	UART1->LCRH = 0x00000060;
	
	/* URATCC default */
	//UART7->CC = 0x0;
	
	/* enable the UART7 */
	UART1->CTL |= (1 << UART_EN_bit);
	
}

void uart_0_Init(void)
{
	/* provide clock to uart 7 */
	RCGCUART_Reg |= (1 << UART_0);
	
	/* clock to port e has been already provided by clockInit */
	
	/* unlock the gpio commit register */
	GPIOA->LOCK = 0x4C4F434B;
	
	/* commit register unmask the required bits to unlock */
	GPIOA->CR |= ((1 << UART_0_RX) | (1 << UART_0_TX));
	
	/* enable the alternate function control on given pins*/
	GPIOA->AFSEL |= ((1 << UART_0_RX) | (1 << UART_0_TX));

	/* selecting uart function for PE0 and PE1*/
	GPIOA->PCTL |= ((1 << 4) | (1 << 0));
	
	/* enable the digital operation on PE0 amd PE1 */
	GPIOA->DEN |= ((1 << UART_0_RX) | (1 << UART_0_TX));
	
	/* select the drive strength 8mA for slew rate control capability */
	GPIOA->DR8R |= ((1 << UART_0_RX) | (1 << UART_0_TX));
	
	/* slew rate control enable for RX and TX*/
	GPIOA->SLR |= ((1 << UART_0_RX) | (1 << UART_0_TX));
	
	/* disable the UART */
	UART0->CTL &= ~(1 << UART_EN_bit);
	
	/* BRD = (16,000,000/(16 x 9600)) = 104.16*/
	/* UARTIBRD = 104 i.e 0x68 */
	/* UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) formulae for fraction register */
	/* UARTFBRD = integer(0.16 x 64 + 0.5) = 10.74 i.e 11 i.e 0xB */
	/* did all calculation manually to avoid cpu load*/
	
	/* integer BRD register */
	UART0->IBRD = 0x68;	/* 16 bits are used out of 32 bits */
	
	/* fraction BRD register */
	UART0->FBRD = 0xB;	/* 6 bits are used out of 32 bits */
	
	/* parity disabled, stick parity disabled, FIFO mode disabled */
	/* only 8 bit data frame is selected with one stop bit */
	UART0->LCRH = 0x00000060;
	
	/* URATCC default */
	//UART7->CC = 0x0;
	
	/* enable the UART7 */
	UART0->CTL |= (1 << UART_EN_bit);
	
}

/* all transmit functions */
void uart_7_Transmit(unsigned char data)
{
	while(UART7->FR & (1 << UART_busy_transmit_bit));
	UART7->DR = data;				
}

void uart_6_Transmit(unsigned char data)
{
	while(UART6->FR & (1 << UART_busy_transmit_bit));
	UART6->DR = data;				
}

void uart_5_Transmit(unsigned char data)
{
	while(UART5->FR & (1 << UART_busy_transmit_bit));
	UART5->DR = data;				
}

void uart_4_Transmit(unsigned char data)
{
	while(UART4->FR & (1 << UART_busy_transmit_bit));
	UART4->DR = data;				
}

void uart_3_Transmit(unsigned char data)
{
	while(UART3->FR & (1 << UART_busy_transmit_bit));
	UART3->DR = data;				
}

void uart_2_Transmit(unsigned char data)
{
	while(UART2->FR & (1 << UART_busy_transmit_bit));
	UART2->DR = data;				
}

void uart_1_Transmit(unsigned char data)
{
	while(UART1->FR & (1 << UART_busy_transmit_bit));
	UART1->DR = data;				
}

void uart_0_Transmit(unsigned char data)
{
	while(UART0->FR & (1 << UART_busy_transmit_bit));
	UART0->DR = data;				
}

/* all uart print functions */
void uart_7_Print(unsigned char *message)
{
  while(*message)
	{
		uart_7_Transmit(*(message++));
	}
}

void uart_6_Print(unsigned char *message)
{
  while(*message)
	{
		uart_6_Transmit(*(message++));
	}
}

void uart_5_Print(unsigned char *message)
{
  while(*message)
	{
		uart_5_Transmit(*(message++));
	}
}

void uart_4_Print(unsigned char *message)
{
  while(*message)
	{
		uart_4_Transmit(*(message++));
	}
}

void uart_3_Print(unsigned char *message)
{
  while(*message)
	{
		uart_3_Transmit(*(message++));
	}
}

void uart_2_Print(unsigned char *message)
{
  while(*message)
	{
		uart_2_Transmit(*(message++));
	}
}

void uart_1_Print(unsigned char *message)
{
  while(*message)
	{
		uart_1_Transmit(*(message++));
	}
}

void uart_0_Print(unsigned char *message)
{
  while(*message)
	{
		uart_0_Transmit(*(message++));
	}
}

/* all receive functions */
unsigned char uart_7_Receive(void)
{
	while (!(UART7->FR & (1 << UART_RXFF_bit)));
	return (unsigned char)UART7->DR;
}

unsigned char uart_6_Receive(void)
{
	while (!(UART6->FR & (1 << UART_RXFF_bit)));
	return (unsigned char)UART6->DR;
}

unsigned char uart_5_Receive(void)
{
	while (!(UART5->FR & (1 << UART_RXFF_bit)));
	return (unsigned char)UART5->DR;
}

unsigned char uart_4_Receive(void)
{
	while (!(UART4->FR & (1 << UART_RXFF_bit)));
	return (unsigned char)UART4->DR;
}

unsigned char uart_3_Receive(void)
{
	while (!(UART3->FR & (1 << UART_RXFF_bit)));
	return (unsigned char)UART3->DR;
}

unsigned char uart_2_Receive(void)
{
	while (!(UART2->FR & (1 << UART_RXFF_bit)));
	return (unsigned char)UART2->DR;
}

unsigned char uart_1_Receive(void)
{
	while (!(UART1->FR & (1 << UART_RXFF_bit)));
	return (unsigned char)UART1->DR;
}

unsigned char uart_0_Receive(void)
{
	while (!(UART0->FR & (1 << UART_RXFF_bit)));
	return (unsigned char)UART0->DR;
}


