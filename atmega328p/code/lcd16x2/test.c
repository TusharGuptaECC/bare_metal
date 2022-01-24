#include<stdio.h>
#include<stdint.h>

void main()
{
	/*unsigned char x = 0x41;
	printf("%c\n",x);
	x = (x << 4) ;
	printf("%c\n",x);*/
		unsigned char cmd, PORTD,PORTB;
		
		unsigned char temp;
		cmd = 0x28;
		PORTD = 0xAA;
		printf("%d",cmd);
		// sending upper nibble
		temp = cmd & 0xF0;
		PORTD &= 0x0F;
		PORTD |= temp; 
		printf("%d\n",PORTD);
		// sending enable pulse
		

		//sending lower nibble
		cmd = 0x28;
		cmd = (cmd << 4) & 0xF0;
		printf("hello :=: %d\n",cmd);
		PORTD &= 0x0F;
		printf("portd %d\n",PORTD);
		PORTD |= cmd; 
		printf("%d",PORTD);
		// sending enable pulse
		
}