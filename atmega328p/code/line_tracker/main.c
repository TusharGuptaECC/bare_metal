// ky -033

// Vcc
// signal
// gnd

#include<avr/io.h>
//#include<util/delay.h>

int main()
{
	DDRB |= ( 1 << 5 );
	PORTB &= ~( 1 << 5 );
	
	DDRD &= ~( 1 << 7 );
	PORTD &= ~( 1 << 7 );
	
	while(1)
	{
		while( ( PIND & 0x80 ) == 0 )
		{
			PORTB |= ( 1 << 5 );
		}
		PORTB &= ~( 1 << 5 );	
	}
	return 0;
}