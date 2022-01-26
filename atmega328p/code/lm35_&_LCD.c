/*
	Author		:- Tushar Gupta
	Date  		:- 26/01/2022
	Project name:- room temp monitor using lm35 (RTMv_1)
*/

#include<avr/io.h>
#define F_CPU 8000000UL
#include<util/delay.h>
#include<stdint.h>

#define delay_1 100
#define delay_2 30

void sendCmd(unsigned char, unsigned char);
void sendData(unsigned char, unsigned char);
void initLcd(unsigned char);

int main()
{
    unsigned char message[] = "--Temperature-- ";
	unsigned char message2[] = "0123456789";
	unsigned char final_result[5]; 
	
	unsigned char i;
	unsigned char bit_mode = 8;
	
	unsigned char lower_data;
	unsigned char upper_data;
	uint16_t result;
	
	unsigned char r;
	unsigned char sum;

	DDRB |= 0x07;
	DDRD |= 0xFF;

	initLcd(bit_mode);

	ADMUX = 0x45;	//0100,0101
	ADCSRA = 0xC3;	//1101,0011 1100,0011
	ADCSRB = 0x00;	//0000,0000

	for(i = 0; message[i] != '\0';i++)
	{
		sendData(bit_mode, message[i]);
	}

	// send cursor to second line
	sendCmd(bit_mode, 0xC0);
	
	for(i = 0; i <= 4; i++)
	{
		sendData(bit_mode, ' ');
	}
	sendData(bit_mode, '`');
	sendData(bit_mode, 'C');

	while(1)
	{
		// send cursor to second line
		sendCmd(bit_mode, 0xC0);

		//wait until the adc conversion completes
		while((ADCSRA & 0x40) != 0);
		
		// reading lower data register
		lower_data = ADCL;
		
		// reading upper data register
		upper_data = ADCH;
		
		result = (upper_data << 8) | lower_data;
		
		// by observation ADC result must be divided by two
		result = result/2;

		if(result < 0)
		{
			sendData(bit_mode, '-');
			result *= -1; 
		}
		
		i = 0;
		sum = 0;
		while(result != 0)
		{
			r = result%10;
			result = result/10;
			final_result[i] = r;
			i++;
		}
		sum = i;
		for(i=1;i<=sum;i++)
		{
			sendData(bit_mode, message2[final_result[sum-i]]);
		}
		sendData(bit_mode, ' ');

		// restarting ADC
		ADCSRA = 0xC3;
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
	// go to second line 0xC0
	// got to first line 0x80
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

