/*
 * Author: Tushar Gupta
*/

#include <avr/io.h>
#include <util/delay.h>

#define u 103
#define msg_size 20
unsigned char msg[msg_size];

void usartInit(unsigned int);
void usartTransmit(unsigned char);
unsigned char usartReceive(void);

int main()
{
  unsigned char *message = "SonalKunj";
  usartInit(9600);
  while(1)
  {
    usartTransmit('a');
    usartTransmit('\n');
    //usartReceive();
    usartReceiveString();
    usartTransmitString(msg);
    usartTransmit('\n');
    usartTransmit('b');
    usartTransmit('\n');
  }
  return 0;
}

void usartInit(unsigned int baud_rate)
{
    unsigned char ubrr_value;
    UCSR0A = 0x20;  // 0b0010,0000
    UCSR0B = 0x18;  // 0b0001,1000
    UCSR0C = 0x06;  // 0b0000,0110
    
    ubrr_value = u;//FOSC/(16*(baud_rate - 1));
    UBRR0H = ubrr_value >> 8;
    UBRR0L = ubrr_value;
}

// transmit data
void usartTransmit(unsigned char data)
{
/* Wait for empty transmit buffer */
while (!(UCSR0A & (1<<UDRE0)))
;
/* Put data into buffer, sends the data */
UDR0 = data;
}

// receives data
unsigned char usartReceive(void)
{
/* Wait for data to be received */
while (!(UCSR0A & (1<<RXC0)))
;
/* Get and return received data from buffer */
return UDR0;
}

void usartTransmitString(unsigned char *message)
{
  unsigned char index = 0;
  while(message[index] != '\0')
  {
    usartTransmit(message[index]);
    index++;
  }
}

void usartReceiveString(void)
{
  //static unsigned char msg[20];
  unsigned char index = 0;
  while(1)
  {
    if ((index > msg_size ))
    {
      break;
    }
    msg[index] = usartReceive();
    index++;
  }
}
