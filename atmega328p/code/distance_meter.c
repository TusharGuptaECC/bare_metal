/*
* Author: Tushar Gupta
* Project: Distance meter 
* Sensor: HC-SR04 ultrasonic sensor
*/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdint.h>

#define lcd_mode 8

/*user defined functions*/
void enInputCapture(void);
unsigned char timeByUltrasonic(void);
void denInputCap(void);
void initLcd(unsigned char bit, unsigned char en_pin);
void sendCmd(unsigned char bit, unsigned char cmd, unsigned char en_pin);
void sendData(unsigned char bit,unsigned char data, unsigned char en_pin);
void displayResult(unsigned int result);
void displayMsg(unsigned char*);
void sendString(void);

/*user defined global variables*/
unsigned char message[] = "Initializing the distance meter";
unsigned char message1[] = "<<<Distance>>>";
unsigned char message2[] = " cm";

int main()
{
  long int positive_edge, negative_edge,result;
  int i;

  /*Pin PB0 as input and without pull-ups*/
  DDRB &= ~(1 << 0);
  PORTB &= ~(1 << 0);

  /*Configuring PORTD as Output and all HIGH*/
  DDRD = 0xFF;

  /*PB 1,2,4, and 5 as output*/
  DDRB |= ( 1 << 2 );
  DDRB |= ( 1 << 1 );
  DDRB |= (1 << 4);
  DDRB |= (1 << 5);
  
  initLcd(lcd_mode,3); // initializing the lcd
  displayMsg(message);
  sendCmd(8, 0x01,3);  // clear display
  displayMsg(message1);
  sendCmd(lcd_mode, 0xC0,3); // send cursor in next line
  enInputCapture();
  TIFR1 |= (1 << ICF1);   // clear input capture flag
  
  while(1)
  {
    TCCR1B = 0x41;  // positive edge trigger and prescaler = 1
    
    // generating a pulse on trigger pin of sensor
    PORTB |= (1 << 4);
    _delay_us(10);
    PORTB &= ~(1 << 4);
    
    while ((TIFR1 & (1 << ICF1)) == 0); // waiting for the positive edge
    positive_edge = ICR1;  // storing ICR1 register value in positive_edge
    TIFR1 |= (1<<ICF1); // clear input capture flag
    
    TCCR1B = 0x01;  // positive edge trigger and prescaler = 1
    while ((TIFR1&(1<<ICF1)) == 0); // waiting for the positive edge
    negative_edge = ICR1;  // storing ICR1 register value in positive_edge
    TIFR1= (1<<ICF1); // clear input capture flag
    
    if (negative_edge > positive_edge)
      result = negative_edge - positive_edge;
    else
      result = positive_edge-negative_edge;
     
    result = (result*170)/160000; // distance in cm

    
    // if distance is less than 5 cm then onboard LED glows
    (result < 5 )? (PORTB |= (1 << 5)) : (PORTB &= ~(1 << 5));
    sendCmd(lcd_mode, 0xC0,3); // send cursor in next line
    displayResult(result);
    displayMsg(message2);
    
    // resetting the counter value to 0
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
  TCCR1B = 0x41;  // positive edge trigger and prescaler = 1
  while ((TIFR1&(1<<ICF1)) == 0); // waiting for the positive edge
  positive_edge = ICR1; // storing ICR1 register value in positive_edge
  TIFR1= (1<<ICF1); // clear input capture flag 
  TCCR1B = 0x01;  // negative edge trigger and prescaler = 1
  while ((TIFR1&(1<<ICF1)) == 0); // waiting for the negative edge
  negative_edge = ICR1; // storing ICR1 register value in negative_edge
  TIFR1= (1<<ICF1); // clear input capture flag
  return negative_edge - positive_edge;
}

void denInputCap(void)
{
  TCCR1B = 0x00;
}

void initLcd(unsigned char bit, unsigned char en_pin)
{
  _delay_ms(20);  // lcd takes approx. 15 ms to startup
  if (bit == 8)
    sendCmd(bit, 0x38,en_pin);  // 8-bit bit mode
  else
    sendCmd(bit, 0x28,en_pin);  // 4-bit bit mode
  sendCmd(bit, 0x06,en_pin);  // entry mode
  sendCmd(bit, 0x01,en_pin);  // clear display
  sendCmd(bit, 0x02,en_pin);  // return home
  sendCmd(bit, 0x0C,en_pin);  // display ON cursor OFF
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

void displayResult(unsigned int result)
{
  unsigned char distance[] = {'0','0','0'},i=0; // range of distance meter is 3 cm to 400 cm so only three digits will be present
  unsigned int temp = result;
  while(result / 10 != 0)
  {
    distance[2-i] = (result % 10) + '0';
    result /= 10;
    i++;
  }
  if (temp / 100 != 0)
  {
    i++;  
  }
  distance[2-i] = (result % 10) + '0';
  for(i = 0; i < 3; i++)
  {
    sendData(8,distance[i],3);  
  }
}

void displayMsg(unsigned char* message)
{
  unsigned char i;
  for(i=0;message[i] != '\0';i++)
  {
    if(i == 16)
      sendCmd(lcd_mode, 0xC0,3);
    sendData(lcd_mode, message[i],3);
  }
}

