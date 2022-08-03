#define __ATmega2560__
#include "ATmega_i2c.h"
#include <avr/io.h>

void i2cInit(void)
{
	DDRD &= ~((1 << scl_pin) | (1 << sda_pin));
	PORTD |= ((1 << scl_pin) | (1 << sda_pin));

	// SCL frequency = 1MHz
	// default
	TWBR = 0x00;
}

unsigned char i2cMasterMode(unsigned char address)
{
	if ((TWSR == 0x08) || (TWSR == 0x10))
	{
		TWDR = address;
		TWCR &= ~(1 << TWSTA);
		TWCR &= ~(1 << TWSTO);
		TWCR |= (1 << TWINT); 

		// wait till status code generates
		while((TWCR & (1 << TWINT)) == 0);
	}
	else
	{
		return -1;
	}
	return 0;
}

unsigned char i2cBeginTransmission(unsigned char address)
{
	// sending start condition
  	TWCR |= ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN)); 

  	// wait till start has been sent properly
  	while((TWCR & (1 << TWINT)) == 0);

  	
  	return i2cMasterMode(address);
}

void i2cMasterWrite(unsigned char data)
{
	// loading data register
	TWDR = data;

	TWCR &= ~(1 << TWSTA);
	TWCR &= ~(1 << TWSTO);
	TWCR |= (1 << TWINT); 

	// wait till status code generates
	while((TWCR & (1 << TWINT)) == 0);
}

void i2cMasterRepeatStart(unsigned char address)
{
	TWCR |= (1 << TWSTA);
	TWCR &= ~(1 << TWSTO);
	TWCR |= (1 << TWINT); 

	// wait till status code generates
	while((TWCR & (1 << TWINT)) == 0);
	i2cMasterMode(address);
}

void i2cMasterEndTransmission(int really)
{
	if (really)
	 {
	 	TWCR &= ~(1 << TWSTA);
		TWCR |= (1 << TWSTO);
		TWCR |= (1 << TWINT);
	 }

	 else
	 {
	 	TWCR |= (1 << TWSTA);
		TWCR |= (1 << TWSTO);
		TWCR |= (1 << TWINT);
	 } 

	// wait till status code generates
	//while((TWCR & (1 << TWINT)) == 0);
}

signed char i2cRead(int do_ack)
{
	
	signed char data;

	TWCR &= ~(1 << TWSTA);
	TWCR &= ~(1 << TWSTO);
	TWCR |= (1 << TWINT);
	if (do_ack)
	{
		TWCR |= (1 << TWEA);
	}
	else
	{
		TWCR &= ~(1 << TWEA);
	}
	// wait till status code generates
	while((TWCR & (1 << TWINT)) == 0);
	return data;
}

void i2cSlaveTransmit(unsigned char data)
{

}

unsigned char i2cSlaveReceive(void)
{

}
