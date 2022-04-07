#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdint.h>
void enInputCapture(void);
unsigned char timeByUltrasonic(void);
void denInputCap(void);
void initLcd(unsigned char bit, unsigned char en_pin);
void sendCmd(unsigned char bit, unsigned char cmd, unsigned char en_pin);
void sendData(unsigned char bit,unsigned char data, unsigned char en_pin);
char displayResult(unsigned int result);
char displayResult1(void);

unsigned int result;

int main()
{
	unsigned int positive_edge, negative_edge,result;
	char a;
	DDRB &= ~(1 << 0);
	PORTB &= ~(1 << 0);
	DDRD = 0xFF;
	PORTD = 0xFF;
	DDRB |= ( 1 << 2 );
	DDRB |= ( 1 << 1 );
	DDRB |= (1 << 5);
	PORTB &= ~(1 << 5);
	DDRC |= (1 << 1);
	PORTC |= (1 << 1);
	initLcd(8,3);
	enInputCapture();
	TIFR1 |= ( 1<<ICF1 );		// clear input capture flag
	sendData(8,'S',3);
	while(1)
	{
		TCCR1B = 0x44;	// positive edge trigger and prescaler = 1
		while ((TIFR1&(1<<ICF1)) == 0);	// waiting for the positive edge
		
		positive_edge = TCNT1;	// storing ICR1 register value in positive_edge
		
		PORTB |= (1 << 5); 
		TIFR1= (1<<ICF1);	// clear input capture flag
		TCCR1B = 0x04;	// positive edge trigger and prescaler = 1
		while ((TIFR1&(1<<ICF1)) == 0);	// waiting for the positive edge
		
		negative_edge = TCNT1;	// storing ICR1 register value in positive_edge
		
		PORTB &= ~(1 << 5); 
		TIFR1= (1<<ICF1);	// clear input capture flag
		if (negative_edge > positive_edge)
			result = negative_edge - positive_edge;
		else
			result = positive_edge-negative_edge;
		//result *= 170;
		
		//result = result;
		
		if (result < 11250)
			PORTC &= ~(1 << 1);
		//_delay_ms(100);
		a = displayResult1();
		sendData(8,a,3);
		TCNT1 = 0x00;
	}
	return 0;
}

void enInputCapture(void)
{
	TCCR1A = 0x00;
}

unsigned char timeByUltrasonic(void)
{
	unsigned char positive_edge, negative_edge;
	TCCR1B = 0x41;	// positive edge trigger and prescaler = 1
	while ((TIFR1&(1<<ICF1)) == 0);	// waiting for the positive edge
	positive_edge = ICR1;	// storing ICR1 register value in positive_edge
	TIFR1= (1<<ICF1);	// clear input capture flag 
	TCCR1B = 0x01;	// negative edge trigger and prescaler = 1
	while ((TIFR1&(1<<ICF1)) == 0);	// waiting for the negative edge
	negative_edge = ICR1;	// storing ICR1 register value in negative_edge
	TIFR1= (1<<ICF1);	// clear input capture flag
	return negative_edge - positive_edge;
}

void denInputCap(void)
{
	TCCR1B = 0x00;
}

void initLcd(unsigned char bit, unsigned char en_pin)
{
	_delay_ms(20);	// lcd takes approx. 15 ms to startup
	if (bit == 8)
		sendCmd(bit, 0x38,en_pin);	// 8-bit bit mode
	else
		sendCmd(bit, 0x28,en_pin);	// 4-bit bit mode
	sendCmd(bit, 0x06,en_pin);	// entry mode
	sendCmd(bit, 0x01,en_pin);	// clear display
	sendCmd(bit, 0x02,en_pin);	// return home
	sendCmd(bit, 0x0C,en_pin);	// display ON cursor OFF
}

void sendCmd(unsigned char bit, unsigned char cmd, unsigned char en_pin)
{
	DDRB |= (1 << en_pin);
	PORTB &= ~( 1 << 2 );
	PORTB &= ~( 1 << 1 );

	if(bit == 8)
	{

		PORTD = cmd;

		// sending enable pulse
		PORTB |= ( 1 << en_pin );
		_delay_ms(100);
		PORTB &= ~( 1 << en_pin );
	}
	else
	{
		unsigned char temp;
		// sending upper nibble
		temp = cmd & 0xF0;
		PORTD &= 0x0F;
		PORTD |= temp; 
		// sending enable pulse
		PORTB |= ( 1 << en_pin );
		_delay_ms(100);
		PORTB &= ~( 1 << en_pin );

		//sending lower nibble
		cmd = (cmd << 4) & 0xF0;
		PORTD &= 0x0F;
		PORTD |= cmd; 
		// sending enable pulse
		PORTB |= ( 1 << en_pin );
		_delay_ms(100);
		PORTB &= ~( 1 << en_pin );
	}

}

void sendData(unsigned char bit,unsigned char data, unsigned char en_pin)
{
	DDRB |= (1 << en_pin);
	PORTB |= ( 1 << 2 );
	PORTB &= ~( 1 << 1 );

	if (bit == 8)
	{
		PORTD = data;
		
		// sending enable pulse
		PORTB |= ( 1 << en_pin );
		_delay_ms(100);
		PORTB &= ~( 1 << en_pin );
	}

	else
	{
		unsigned char temp;
		// sending upper nibble
		temp = data & 0xF0;
		PORTD &= 0x0F;
		PORTD |= temp; 
		// sending enable pulse
		PORTB |= ( 1 << en_pin );
		_delay_ms(100);
		PORTB &= ~( 1 << en_pin );

		//sending lower nibble
		data = (data << 4) & 0xF0;
		PORTD &= 0x0F;
		PORTD |= data; 
		// sending enable pulse
		PORTB |= ( 1 << en_pin );
		_delay_ms(100);
		PORTB &= ~( 1 << en_pin );
	}
}

char displayResult(unsigned int result1)
{
	char message[11] = "abcdefghij";//"0123456789";
	unsigned int t = result1;
	t = t + 1;
	int i=0;
	while(result1 != 0)
	{
		//sendData(8,message[i],3);
		if (result1 % 2 == message[i])
		{
			_delay_ms(30);
			sendData(8,message[i],3);
		}
		if (i > 9)
		{
			i = -1;
			result1 = result1 / 2;
		}
		i = i+1;
		_delay_ms(30);
	}
	return message[i];
}

char displayResult1()
{
	char message[11] = "abcdefghij";//"0123456789";
	//unsigned int t = result1;
	//t = t + 1;
	int i=0;
	while(result != 0)
	{
		//sendData(8,message[i],3);
		if (result % 2 == message[i])
		{
			_delay_ms(30);
			sendData(8,message[i],3);
		}
		if (i > 9)
		{
			i = -1;
			result = result / 2;
		}
		i = i+1;
		_delay_ms(30);
	}
	return message[i];
}

/*void displayResult(unsigned char result)
{
	
}*/
