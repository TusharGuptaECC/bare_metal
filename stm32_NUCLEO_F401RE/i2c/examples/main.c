/*
  Author: Tushar Gupta
Software: Keil uVision5

*/

#include <stm32f401xe.h>
#include "SonalKunj_delay.h"
#include "SonalKunj_onBoards.h"
#include "SonalKunj_usart.h"
#include "SonalKunj_i2c.h"

#define device_address_read 0xD1//0x68
#define device_address_write 0xD0

int main(void)
{
	initOnBoardLED();
	i2cInit();
	usart_1_Init();
	led(ON);
	usart_1_Print("USART 1 is ready !\n");
	while (1)
	{
		i2c_1_MasterTransmit(device_address_write, 0x74);
		usart_1_Transmit((unsigned char)i2c_1_MasterReceive(device_address_read));
		//led(ON);
		delayMS(1000);
	}
	return 0;
}

