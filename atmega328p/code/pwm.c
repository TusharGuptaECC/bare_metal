/*
*	Author: Tushar Gupta
	Object: pwm and related interrupts
	date  : 03/04/2022
	
*/
#include <avr/io.h>
#include<avr/interrupt.h>

void pwm(void);
void pwmIntEn(unsigned char, unsigned char, unsigned char);
void waitForInt(unsigned char, unsigned char, unsigned char);

/*void pwm_ISR()
{
	count+=1;
}*/


int main()
{ 
   // Write your code here
   // Pins must be in output mode for pwm generation 
   DDRD |= (1 << 6); 
   DDRD |= (1 << 5);
   DDRB |= (1 << 5);
   PORTB &= ~(1 << 5);
   
   pwmIntEn(1,0,0);
   pwm();
   waitForInt(1,0,0);
   
   PORTB |= (1 << 5); 
   
   waitForInt(0,1,0);
   PORTB &= ~(1 << 5);
   //while (1)
      
   return 0;
}
 
void pwm(void)
{
	/* control registers */
	TCCR0A = 0xA3; // 0xA3 means 60% and 80% and 0xF3 means 60% becomes 40% and 80 becomes 20%
	TCCR0B = 0x05;
	
	/* data registers */
	OCR0A = 0x99; //60% 153/255 
	OCR0B = 0xCC; //88% 204/255
}

void pwmIntEn(unsigned char OCnA, unsigned char OCnB, unsigned char over_flow)
{
	if((OCnA == 0) || (OCnB == 0) || (over_flow == 1))
	{
		 sei();
		 TIMSK0 = 0x01;
	}
	else if((OCnA == 0) || (OCnB == 1) || (over_flow == 0))
	{
		 sei();
		TIMSK0 = 0x04;
	}
	else if((OCnA == 0) || (OCnB == 1) || (over_flow == 1))
	{
		sei();
		TIMSK0 = 0x05;
	}
	else if((OCnA == 1) || (OCnB == 0) || (over_flow == 0))
	{
		sei();
		TIMSK0 = 0x02;
	}
	else if((OCnA == 1) || (OCnB == 0) || (over_flow == 1))
	{
		sei();
		TIMSK0 = 0x03;
	}
	else if((OCnA == 1) || (OCnB == 1) || (over_flow == 0))
	{
		sei();
		TIMSK0 = 0x06;
	}
	else if((OCnA == 1) || (OCnB == 1) || (over_flow == 1))
	{
		sei();
		TIMSK0 = 0x07;
	}
	else
	{
		return;
	}
}

void waitForInt(unsigned char OCnA, unsigned char OCnB, unsigned char over_flow)
{
	if( OCnA == 1 )
	{
		while(TIFR0 != 0x02);
	}
	else if( OCnB == 1)
	{
		while(TIFR0 != 0x04);
	}
	else
	{
		while(TIFR0 != 0x01);
	}
	return ;
}
