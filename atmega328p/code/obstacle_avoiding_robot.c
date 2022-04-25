/*
* Author: Tushar Gupta
* Project: Obstacle Avoiding Robot (OAR_v1)
* Sensor: HC-SR04 ultrasonic sensor
* Motors: 12 volts BO motors
*/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdint.h>

#define left_forward 3
#define left_backward 4
#define right_forward 3
#define right_backward 4

#define turn_delay 500 
#define turn_delay_left 1000
#define stop_delay 2000

/*
  Connections with Arduino

  enable left -> PD5
  enable right -> PD6

  motor left forward  -> PD3
  motor left backward -> PD4

  motor right forward  -> PB3
  motor right backward -> PB4
*/

/*user defined functions*/
void enInputCapture(void);
long int distanceByUltrasonic(unsigned char);
void denInputCap(void);
void initializeMotors(void);
void motorSpeed(unsigned char);
void moveForward(void);
void movebackward(void);
void softRightTurn(void);
void softLeftTurn(void);
void hardRightTurn(void);
void hardLeftTurn(void);
void dontMove(long int);

int main()
{
  long int result;
  unsigned char turn = 0;
  /*Pin PB0 as input and without pull-ups*/
  DDRB &= ~(1 << 0);
  PORTB &= ~(1 << 0);
  /*power pin for ultrasonic sensor*/
  DDRD |= (1 << 2);
  PORTD |= (1 << 2);

  /*PORTB in 5 as output*/
  DDRB |= (1 << 5);
  initializeMotors();
  motorSpeed(0x33);
  enInputCapture();
  //Serial.begin(57600);
  
  while(1)
  {
    result = distanceByUltrasonic(2);
    while(result > 15)
    {
      PORTB &= ~(1 << 5);
      motorSpeed(0x4C);
      moveForward();
      TCNT1 = 0x00;
      result = distanceByUltrasonic(2);  
      _delay_ms(100);
    }
    PORTB |= (1 << 5);
    dontMove(stop_delay);
    motorSpeed(0x66);
    if (turn == 0)
    {
      hardRightTurn(); // for 500 ms
    }
    else
    {
      hardLeftTurn();  // for 1000 ms
    }
    turn = turn ^ 1;
    dontMove(100);

    // resetting the counter value to 0
    TCNT1 = 0x00;
  }
  return 0;
}

void enInputCapture(void)
{
  TCCR1A = 0x00;
  TIFR1 |= (1 << ICF1);   // clear input capture flag
}

long int distanceByUltrasonic(unsigned char trigger_pin)
{
    long int positive_edge, negative_edge,result;

    TCCR1B = 0x42;  // positive edge trigger and prescaler = 1
    
    // generating a pulse on trigger pin of sensor
    DDRB |= (1 << trigger_pin);
    PORTB |= (1 << trigger_pin);
    _delay_us(10);
    PORTB &= ~(1 << trigger_pin);
    
    while ((TIFR1 & (1 << ICF1)) == 0); // waiting for the positive edge
    positive_edge = ICR1;  // storing ICR1 register value in positive_edge
    TIFR1 |= (1<<ICF1); // clear input capture flag
    
    TCCR1B = 0x02;  // positive edge trigger and prescaler = 1
    while ((TIFR1&(1<<ICF1)) == 0); // waiting for the positive edge
    negative_edge = ICR1;  // storing ICR1 register value in positive_edge
    TIFR1= (1<<ICF1); // clear input capture flag
    
    if (negative_edge > positive_edge)
      result = negative_edge - positive_edge;
    else
      result = positive_edge-negative_edge;
     
    result = (result*170)/20000; // distance in cm
    return result;
}

void denInputCap(void)
{
  TCCR1B = 0x00;
}

/*
* this function initialize motors with 50% efficiency
*/
void initializeMotors(void)
{
  DDRD |= (1 << 6); 
  DDRD |= (1 << 5);
  DDRD |= (1 << 4); 
  DDRD |= (1 << 3);

  DDRB |= (1 << 4); 
  DDRB |= (1 << 3);

  PORTD &= ~(1 << 4);
  PORTD &= ~(1 << 3);

  PORTB &= ~(1 << 4);
  PORTB &= ~(1 << 3);

  /* control registers */
  TCCR0A = 0xA3; // 0xA3 means 60% and 80% and 0xF3 means 60% becomes 40% and 80 becomes 20%
  TCCR0B = 0x05;
  
  /* data registers */
  OCR0A = 0x7F; //60% 153/255 
  OCR0B = 0x7F; //88% 204/255
}

void motorSpeed(unsigned char speed)
{
  OCR0A = speed; //60% 153/255 
  OCR0B = speed; //88% 204/255
}

void moveForward(void)
{
  PORTD &= ~(1 << left_backward);
  PORTD |= (1 << left_forward);

  PORTB &= ~(1 << right_backward);
  PORTB |= (1 << right_forward); 

  //_delay_ms(500);
}

void movebackward(void)
{
  PORTD |= (1 << left_backward);
  PORTD &= ~(1 << left_forward);

  PORTB |= (1 << right_backward);
  PORTB &= ~(1 << right_forward);
}

void dontMove(long int wait)
{
  PORTD &= ~(1 << left_backward);
  PORTD &= ~(1 << left_forward);

  PORTB &= ~(1 << right_backward);
  PORTB &= ~(1 << right_forward);

  _delay_ms(wait);
}

void softLeftTurn(void)
{
  PORTD &= ~(1 << left_backward);
  PORTD &= ~(1 << left_forward);

  PORTB &= ~(1 << right_backward);
  PORTB |= (1 << right_forward);

  _delay_ms(turn_delay); 
}

void softRightTurn(void)
{
  PORTD &= ~(1 << left_backward);
  PORTD |= (1 << left_forward);

  PORTB &= ~(1 << right_backward);
  PORTB &= ~(1 << right_forward);

  _delay_ms(turn_delay); 
}

void hardLeftTurn(void)
{
  PORTD |= (1 << left_backward);
  PORTD &= ~(1 << left_forward);

  PORTB &= ~(1 << right_backward);
  PORTB |= (1 << right_forward);

  _delay_ms(turn_delay_left); 
}

void hardRightTurn(void)
{
  PORTD &= ~(1 << left_backward);
  PORTD |= (1 << left_forward);

  PORTB |= (1 << right_backward);
  PORTB &= ~(1 << right_forward);

  _delay_ms(turn_delay); 
}
