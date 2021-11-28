#include"SK_LCD_16x2.h"

void initLcd()
{
	_delay_ms(20);	// lcd takes approx. 15 ms to startup
	sendCmd(0x38);	// 8-bit bit mode
	sendCmd(0x06);	// entry mode
	sendCmd(0x01);	// clear display
	sendCmd(0x02);	// return home
	sendCmd(0x0C);	// display ON cursor OFF
}

void sendCmd(unsigned char cmd)
{

	PORTB &= ~( 1 << 2 );
	PORTB &= ~( 1 << 1 );

	PORTD = cmd;

	// sending enable pulse
	PORTB |= ( 1 << 0 );
	_delay_ms(100);
	PORTB &= ~( 1 << 0 );

}

void sendData(unsigned char data)
{
	PORTB |= ( 1 << 2 );
	PORTB &= ~( 1 << 1 );
	
	PORTD = data;
	
	// sending enable pulse
	PORTB |= ( 1 << 0 );
	_delay_ms(100);
	PORTB &= ~( 1 << 0 );
}