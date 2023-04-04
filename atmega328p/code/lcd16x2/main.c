// Configuring LCD 16x2 into 8-bit mode
/*
	PIN CONNECTIONS ON ARDUINO

	RS - PORT_B_pin_2
	R/W - PORT_B_pin_1
	E - PORT_B_pin_0

	D7 - PORT_D_pin_7
	D6 - PORT_D_pin_6
	D5 - PORT_D_pin_5
	D4 - PORT_D_pin_4
	D3 - PORT_D_pin_3
	D2 - PORT_D_pin_2
	D1 - PORT_D_pin_1
	D0 - PORT_D_pin_0

*/
#include<avr/io.h>
#include<util/delay.h>
#include"SonalKunj_LCD_16x2.h"

int main()
{
	unsigned char message[] = "put any message here";
	unsigned char bit = 8;
	int i;
	DDRB |= 0x07;
	DDRD |= 0xFF;

	initLcd(bit);
	sendData(bit, 0x41);
	for(i=0;message[i] != '\0';i++)
	{
		if(i == 16)
			sendCmd(bit, 0xC0);
		sendData(bit, message[i]);
	}

	/*while(1)
	{

	}*/
	return 0;
}

