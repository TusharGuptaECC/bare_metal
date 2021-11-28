#include<stdio.h>
#include<stdint.h>

void main()
{
	unsigned char x = 0x41;
	printf("%c\n",x);
	x = (x << 4) ;
	printf("%c\n",x);
}