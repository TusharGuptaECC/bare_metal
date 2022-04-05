// Author: Tushar Gupta
// Branch: ECC 2nd year
// Date: 01/08/2021 - 30/08/2021
// robot.c
// DSC_MBM_study_pod_2.0
// sp0229 project

#include<avr/io.h>
#include<util/delay.h>

#define u 103
#define delay1 500
#define delay2 100

void gpioInit(void);
void usartInit(unsigned int);
void usartTransmit(unsigned char);
unsigned char usartReceive(void);
void moveForward(void);
void moveBackward(void);
void hardLeftTurn(void);
void hardRightTurn(void);
void softLeft(void);
void softRight(void);
void stop(void);

int main()
{
    int i;
    unsigned char cmd=0;
    unsigned char message1[] = "DSC_MBM_STUDY_POD_2.0\r\n";
    unsigned char message2[] = "TEAM_NAME_SP0229\r\n";
    unsigned char message3[] = "DOMAIN ROBOTICS";
    unsigned char message4[] = "ready to take orders\r\n";
    
    // intialization
    gpioInit();
    usartInit(9600);

    for(i=0;message1[i] != '\0'; i++)
    {
        usartTransmit(message1[i]);
    }
    for(i=0;message2[i] != '\0'; i++)
    {
        usartTransmit(message2[i]);
    }
    for(i=0;message3[i] != '\0'; i++)
    {
        usartTransmit(message3[i]);
    }
    for(i=0;message4[i] != '\0'; i++)
    {
        usartTransmit(message4[i]);
    }

    while(1)
    {
        cmd = usartReceive();
        if(cmd == 'a')
        {
            // move forward
            moveForward();
        }

        else if (cmd == 'b')
        {
            // move backward
            moveBackward();
        }

        else if (cmd == 'c')
        {
            // move right
            hardRightTurn();
        }

        else if (cmd == 'd')
        {
            // move left
            hardLeftTurn();
        }

        else if (cmd == 'e')
        {
            //stop
            stop();
        }
        else if (cmd == 'f')
        {
            // soft right
            softRight();
        }
        else if (cmd == 'g')
        {
            // soft left
            softLeft();
        }
        else{}
    }
    return 0;
}

// setting pin in output state
void gpioInit(void)
{
    DDRB |= _BV(DDB0);  // enable left
    DDRB |= _BV(DDB1);  // forward left
    DDRB |= _BV(DDB2);  // backward left
    DDRD |= _BV(DDD7);  // enable right
    DDRD |= _BV(DDD6);  // forward right
    DDRD |= _BV(DDD5);  // backward left
    // setting pins high
    PORTB |= _BV(PORTB0);   // enable left
    PORTD |= _BV(PORTD7);   // enable right
    // setting pins as low
    PORTB &= ~_BV(PORTB1);
    PORTB &= ~_BV(PORTB2);
    PORTD &= ~_BV(PORTD6);
    PORTD &= ~_BV(PORTD5);
}

// asynchronus mode
// 8-bit data
// recieve and transmit
// no interrupts
// 1-stop bit
// no parity
// single speed
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

void moveForward(void)
{
    PORTB |= _BV(PORTB1);
    PORTB &= ~_BV(PORTB2);
    PORTD |= _BV(PORTB6);
    PORTD &= ~_BV(PORTD5);
}

void moveBackward(void)
{
    PORTB &= ~_BV(PORTB1);
    PORTB |= _BV(PORTB2);
    PORTD &= ~_BV(PORTB6);
    PORTD |= _BV(PORTD5);
}

void stop(void)
{
    PORTB &= ~_BV(PORTB1);
    PORTB &= ~_BV(PORTB2);
    PORTD &= ~_BV(PORTD6);
    PORTD &= ~_BV(PORTD5);
}

void hardRightTurn(void)
{
    PORTB |= _BV(PORTB1);
    PORTB &= ~_BV(PORTB2);
    PORTD &= ~_BV(PORTD6);
    PORTD |= _BV(PORTD5);
}

void hardLeftTurn(void)
{
    PORTB &= ~_BV(PORTB1);
    PORTB |= _BV(PORTB2);
    PORTD |= _BV(PORTD6);
    PORTD &= ~_BV(PORTD5);
}

void softRight(void)
{
    PORTB |= _BV(PORTB1);
    PORTB &= ~_BV(PORTB2);
    PORTD &= ~_BV(PORTD6);
    PORTD &= ~_BV(PORTD5);
}

void softLeft(void)
{
    PORTB &= ~_BV(PORTB1);
    PORTB &= ~_BV(PORTB2);
    PORTD |= _BV(PORTD6);
    PORTD &= ~_BV(PORTD5);
}
