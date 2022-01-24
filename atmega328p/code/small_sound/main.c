// small sound sensor with digital output
#include<avr/io.h>
#include<util/delay.h>

#define delay_1 100
#define delay_2 30

void sendCmd(unsigned char, unsigned char);
void sendData(unsigned char, unsigned char);
void initLcd(unsigned char);

int main()
{
    unsigned char x;
    DDRB |= (1 << 5);
    PORTB &= ~(1 << 5);
    DDRB &= ~(1 << 3);
    PORTB &= ~(1 << 3);
    while(1)
    {
        x = PINB;
        x = x & 0x08;
        while(x != 0)
        {
            PORTB |= (1 << 5);
            //_delay_ms(delay_2);
        }
        PORTB &= ~(1 << 5);
        //_delay_ms(delay_2);
    }
    return 0;
}


void initLcd(unsigned char bit)
{
	_delay_ms(20);	// lcd takes approx. 15 ms to startup
	if (bit == 8)
		sendCmd(bit, 0x38);	// 8-bit bit mode
	else
		sendCmd(bit, 0x28);	// 4-bit bit mode
	sendCmd(bit, 0x06);	// entry mode
	sendCmd(bit, 0x01);	// clear display
	sendCmd(bit, 0x02);	// return home
	sendCmd(bit, 0x0C);	// display ON cursor OFF
}

void sendCmd(unsigned char bit, unsigned char cmd)
{

	PORTB &= ~( 1 << 2 );
	PORTB &= ~( 1 << 1 );

	if(bit == 8)
	{

		PORTD = cmd;

		// sending enable pulse
		PORTB |= ( 1 << 0 );
		_delay_ms(delay_1);
		PORTB &= ~( 1 << 0 );
	}
	else
	{
		unsigned char temp;
		// sending upper nibble
		temp = cmd & 0xF0;
		PORTD &= 0x0F;
		PORTD |= temp; 
		// sending enable pulse
		PORTB |= ( 1 << 0 );
		_delay_ms(delay_1);
		PORTB &= ~( 1 << 0 );

		//sending lower nibble
		cmd = (cmd << 4) & 0xF0;
		PORTD &= 0x0F;
		PORTD |= cmd; 
		// sending enable pulse
		PORTB |= ( 1 << 0 );
		_delay_ms(delay_1);
		PORTB &= ~( 1 << 0 );
	}

}

void sendData(unsigned char bit,unsigned char data)
{
	PORTB |= ( 1 << 2 );
	PORTB &= ~( 1 << 1 );

	if (bit == 8)
	{
		PORTD = data;
		
		// sending enable pulse
		PORTB |= ( 1 << 0 );
		_delay_ms(delay_1);
		PORTB &= ~( 1 << 0 );
	}

	else
	{
		unsigned char temp;
		// sending upper nibble
		temp = data & 0xF0;
		PORTD &= 0x0F;
		PORTD |= temp; 
		// sending enable pulse
		PORTB |= ( 1 << 0 );
		_delay_ms(delay_1);
		PORTB &= ~( 1 << 0 );

		//sending lower nibble
		data = (data << 4) & 0xF0;
		PORTD &= 0x0F;
		PORTD |= data; 
		// sending enable pulse
		PORTB |= ( 1 << 0 );
		_delay_ms(delay_1);
		PORTB &= ~( 1 << 0 );
	}
}