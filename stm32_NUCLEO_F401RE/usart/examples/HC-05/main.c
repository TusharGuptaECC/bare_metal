/*
  Author: Tushar Gupta
Software: Keil uVision
*/

#include <stm32f401xe.h>
#include "SonalKunj_delay.h"
#include "SonalKunj_onBoards.h"
#include "SonalKunj_usart.h"

int main(void)
{
	unsigned char cmd;
	
	initOnBoardLED();
	usart_1_Init();
	usart_1_Print("Hello world\n");
	usart_1_Print("BCR ready to take orders \n");
	while (1)
	{
		cmd = usart_1_Receive();
		if (cmd == 'a')
		{
			led(ON);
		}
		if (cmd == 'b')
		{
			led(OFF);
		}
	}
	return 0;
}

