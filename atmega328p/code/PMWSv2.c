#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdint.h>
// #include <stdint.h>
// #include <avr/interrupt.h>

// lcd ///////////////////
#define RS_pin 3
#define RW_pin 4
#define E_pin 5
#define LCD_MODE 8
#define NEXT_LINE 0xC0
#define RETURN_HOME 0x02
#define CLEAR_DISPLAY 0x01

// switches ////////////
#define B 'B'
#define C 'C'
#define D 'D'
#define HOME_pin 4
#define UP_pin 3
#define DOWN_pin 5

// io interrupts ///////
#define I_bit 7
#define EXTERNAL_INTERRUPT_EN 1
#define EXTERNAL_INTERRUPT_DIS 0
#define PIN_CHANGE_INTERRUPT_EN 1
#define PIN_CHANGE_INTERRUPT_DIS 0

// PUMP ///////////////////////////
#define PUMP_ON 1
#define PUMP_OFF 0
#define en_pump_pin 1
#define pump_pin 2

#define PUMP_SPEED_PERCENT_0 0
#define PUMP_SPEED_PERCENT_20 20
#define PUMP_SPEED_PERCENT_40 40
#define PUMP_SPEED_PERCENT_60 60
#define PUMP_SPEED_PERCENT_80 80
#define PUMP_SPEED_PERCENT_100 100

// dht11/////////////////////////////
#define dht_pin 0

// system delay/////////////////////
/*
 * This 46 ms is the minimum delay and is calculated by doing rigrous
   practical.
 * This delay is required otherwise system will not update the 
   is_pressed variable after the ISR i.e outside the ISR i.e 
   is_pressed not becomes 0 at once and get ignored so this delay
   is necessary.
  * But for ensuring the proper results wait = 200 ms.
*/
#define wait 300
//#define  '0' 0
//#define 1 '1'
//#define 2 '2'
//#define 3 '3'
//#define 4 '4'
//#define 5 '5'
//#define 6 '6'
//#define 7 '7'
//#define 8 '8'
//#define 9 '9'

// global variables///////////////////////////////////////////
unsigned char *welcome_msg1 = "     PMWSv1     ";
unsigned char *welcome_msg2 = "   powered by      SonalKunj";
unsigned char *home_page_opt1 = "   automatic";
unsigned char *home_page_opt2 = "   manual";
unsigned char *selection_pointer = ">>";
unsigned char *temp = "temp:";
unsigned char *humid = "humid:";
unsigned char *p_speed = "speed";
//unsigned char *display_p_speed = "XXXXX";
unsigned char *manual_msg1 = "U -> ON  :STATUS";
unsigned char *manual_msg2 = "D -> OFF : ";
unsigned char *manual_msg3 = "ON";
unsigned char *manual_msg4 = "OFF";
unsigned char digits[] = "0123456789";
volatile unsigned char is_pressed = 0;
volatile unsigned char is_automatic = 1;
volatile uint32_t ic_data = 0;
volatile int32_t index2 = 0;
volatile uint32_t over_flow = 0;
volatile uint32_t previous_data = 0;
volatile uint32_t over_flow_2 = 0;
volatile  unsigned char dht_data[42];
uint32_t humid_data = 0;
uint32_t temp_data = 0;
uint32_t prev_humid_data = 0;
uint32_t prev_temp_data = 0;
int16_t motor_on_duration = 0;
char pump_speed = 0;
//////////////////////////////////////////////////////////////
// ISRs /////////////////////////////////////////////////////
ISR(PCINT0_vect)
{
  if (readSwitch(B, HOME_pin) == 0)
  {
    is_pressed = 1;
  }
  if (readSwitch(B, UP_pin) == 0)
  {
    is_pressed = 2;
  }
  if (readSwitch(B, DOWN_pin) == 0)
  {
    is_pressed = 3;
  }
}

ISR(TIMER1_CAPT_vect)
{
    //previous_data = ic_data;
    ic_data = ICR1;// + (over_flow * 65536);
	TCNT1 = 0;
    //index2++;
    // PORTC ^= (1 << 0);
	index2++;
}

ISR(TIMER1_OVF_vect)
{
    over_flow++;
}

ISR(TIMER2_OVF_vect)
{
    over_flow_2++;
	PORTC ^= (1 << 0);
	if(over_flow_2 > 100000)
	{
		PORTC |= (1 << 0);
	}
}

#define idle_mode 0x00
#define adc_noise_mode 0x02
#define power_down_mode 0x04
#define power_save_mode 0x06
#define standby_mode 0x0C
#define ext_standby_mode 0x0E

void initSleep(unsigned char mode)
{
    SMCR = mode;
    MCUCR = 0x00;   // default settings
    PRR = 0xA7;
}

// This function is device and requirement specific :)
void prepareForSleep(void)
{

}

void goToSleep(void)
{
    SMCR |= (1 << SE);  // SE - sleep enable bit i.e. bit 0
    asm("SLEEP\n\t");
}

int main()
{
  unsigned char enter = 0;
  DDRC |= (1 << 0);
  PORTC &= ~(1 << 0);
  makeSwitch(B, HOME_pin);
  makeSwitch(B, UP_pin);
  makeSwitch(B, DOWN_pin);
  initLcd(LCD_MODE);
  initPump();
  enableIOInterrupt(EXTERNAL_INTERRUPT_DIS,PIN_CHANGE_INTERRUPT_EN);
  //enableIcInterrupt();
  welcomePage1();
  _delay_ms(1000);
  welcomePage2();
  _delay_ms(1000);
  homePage_1();
  // initSleep(power_down_mode);
  // goToSleep();
  while (1)
  {
    
    if (is_pressed == 1)  // home is pressed
    {
      _delay_ms(wait);
      is_pressed = 0;
      if (is_automatic)
      {
        while (1)
        {
            prev_humid_data = humid_data;
            prev_temp_data = temp_data;

            dht11();  // start input cap, input cap intrrupt en, reset timer1, end input cap
            
			humid_data = getHumidityInt();
            temp_data = getTemperatureInt();
            automaticPage(0);
			if ((temp_data - prev_temp_data != 0) && (enter))
            {
				theLogic();
            }
            enter = 1;
            
            _delay_ms(wait);
			// original formula ((motor_on_duration * 1000) / 16))
			if (over_flow_2 > (motor_on_duration * 60))
			{
				_delay_ms(wait);
				powerUpPump(PUMP_OFF);
				automaticPage(1);
				resetTimer2();
				_delay_ms(wait);
				over_flow_2 = 0;
			}
            //sendCmd(8, 0x01); // clear screen
            sendCmd(8, 0x02); // return home
            if (is_pressed == 1)
            {
                _delay_ms(wait);
                is_pressed = 0;
                is_automatic = 1;
                homePage_1();
				powerUpPump(PUMP_OFF);
                break;
            }
        }
      }
      else
      {
        manualPageOff();
        while (1)
        {
          if (is_pressed == 1)
          {
            // debugging code
            /*
              if (is_pressed == 1)
              {
                sendData(8, 0x41);
              }
              problem: some delay required
              solution: defined a wait at line 51
            */
            _delay_ms(wait);
            is_pressed = 0;
            is_automatic = 1;
            homePage_1();
            break;
          }
          
          if (is_pressed == 2)
          {
            _delay_ms(wait);
            is_pressed = 0;
            powerUpPump(PUMP_ON);
            manualPageOn();
          }
          if (is_pressed == 3)
          {
            _delay_ms(wait);
            is_pressed = 0;
            powerUpPump(PUMP_OFF);
            manualPageOff();
          }
        }
      }
    }
    if (is_pressed == 2)  // up is pressed
    {
      _delay_ms(wait);
      is_pressed = 0;
      is_automatic = 1;
      homePage_1();
    }
    if (is_pressed == 3)  // down is pressed
    {
      _delay_ms(wait);
      is_pressed = 0;
      is_automatic = 0;
      homePage_2();
    }
  }
}

// lcd functions ////////////////////////////////////////////////////////////////////////////////////////////
void initLcd(unsigned char bit)
{
  DDRD = 0xFF;
  PORTD = 0xFF;
  DDRC |= 0x38;
  PORTC |= 0x38;
  _delay_ms(20);  // lcd takes approx. 15 ms to startup
  if (bit == 8)
    sendCmd(bit, 0x38); // 8-bit bit mode
  else
    sendCmd(bit, 0x28); // 4-bit bit mode
  sendCmd(bit, 0x06); // entry mode
  sendCmd(bit, 0x01); // clear display
  sendCmd(bit, 0x02); // return home
  sendCmd(bit, 0x0C); // display ON cursor OFF
}

void sendCmd(unsigned char bit, unsigned char cmd)
{

  PORTC &= ~( 1 << RS_pin );
  PORTC &= ~( 1 << RW_pin );

  if(bit == 8)
  {

    PORTD = cmd;

    // sending enable pulse
    PORTC |= ( 1 << E_pin );
    _delay_ms(100);
    PORTC &= ~( 1 << E_pin );
  }
  else
  {
    unsigned char temp;
    // sending upper nibble
    temp = cmd & 0xF0;
    PORTD &= 0x0F;
    PORTD |= temp; 
    // sending enable pulse
    PORTC |= ( 1 << E_pin );
    _delay_ms(100);
    PORTC &= ~( 1 << E_pin );

    //sending lower nibble
    cmd = (cmd << 4) & 0xF0;
    PORTD &= 0x0F;
    PORTD |= cmd; 
    // sending enable pulse
    PORTC |= ( 1 << E_pin );
    _delay_ms(100);
    PORTC &= ~( 1 << E_pin );
  }

}

void sendData(unsigned char bit,unsigned char data)
{
  PORTC |= ( 1 << RS_pin );
  PORTC &= ~( 1 << RW_pin );

  if (bit == 8)
  {
    PORTD = data;
    
    // sending enable pulse
    PORTC |= ( 1 << E_pin );
    _delay_ms(100);
    PORTC &= ~( 1 << E_pin );
  }

  else
  {
    unsigned char temp;
    // sending upper nibble
    temp = data & 0xF0;
    PORTD &= 0x0F;
    PORTD |= temp; 
    // sending enable pulse
    PORTC |= ( 1 << E_pin );
    _delay_ms(100);
    PORTC &= ~( 1 << E_pin );

    //sending lower nibble
    data = (data << 4) & 0xF0;
    PORTD &= 0x0F;
    PORTD |= data; 
    // sending enable pulse
    PORTC |= ( 1 << E_pin );
    _delay_ms(100);
    PORTC &= ~( 1 << E_pin );
  }
}

void displayMsg(unsigned char *msg)
{
  unsigned char index = 0;
  for(index = 0; msg[index] != '\0'; index++)
  {
    if (index == 16)
    {
      sendCmd(LCD_MODE, NEXT_LINE);
    }
    sendData(LCD_MODE, msg[index]);
  }
}

void welcomePage1(void)
{
    sendCmd(LCD_MODE, CLEAR_DISPLAY); // clear display
    sendCmd(LCD_MODE, RETURN_HOME);
    displayMsg(welcome_msg1);
}

void welcomePage2(void)
{
    sendCmd(LCD_MODE, CLEAR_DISPLAY); // clear display
    sendCmd(LCD_MODE, RETURN_HOME);
    displayMsg(welcome_msg2);
}

void homePage_1(void)
{
    sendCmd(LCD_MODE, CLEAR_DISPLAY); // clear display
    sendCmd(LCD_MODE, RETURN_HOME);
    displayMsg(home_page_opt1);
    sendCmd(LCD_MODE, NEXT_LINE);
    displayMsg(home_page_opt2);
    sendCmd(LCD_MODE, RETURN_HOME);
    displayMsg(selection_pointer);
}

void homePage_2(void)
{
    sendCmd(LCD_MODE, CLEAR_DISPLAY); // clear display
    sendCmd(LCD_MODE, RETURN_HOME);
    displayMsg(home_page_opt1);
    sendCmd(LCD_MODE, NEXT_LINE);
    displayMsg(home_page_opt2);
    sendCmd(LCD_MODE, NEXT_LINE);
    displayMsg(selection_pointer);
}

void manualPageOn(void)
{
    sendCmd(LCD_MODE, CLEAR_DISPLAY); // clear display
    sendCmd(LCD_MODE, RETURN_HOME);
    displayMsg(manual_msg1);
    sendCmd(LCD_MODE, NEXT_LINE);
    displayMsg(manual_msg2); 
    displayMsg(manual_msg3);
}

void manualPageOff(void)
{
    sendCmd(LCD_MODE, CLEAR_DISPLAY); // clear display
    sendCmd(LCD_MODE, RETURN_HOME);
    displayMsg(manual_msg1);
    sendCmd(LCD_MODE, NEXT_LINE);
    displayMsg(manual_msg2); 
    displayMsg(manual_msg4);
}

void automaticPage(unsigned char clear_scr)
{
	if (clear_scr)
	{
		sendData(LCD_MODE, ' ');
		sendData(LCD_MODE, ' ');
		sendData(LCD_MODE, ' ');
		sendData(LCD_MODE, ' ');
		sendData(LCD_MODE, ' ');
		sendData(LCD_MODE, ' ');
		sendData(LCD_MODE, ' ');
		sendCmd(LCD_MODE, 0x02);	// return home
	}
	_delay_ms(100);
	
	displayMsg(temp);
	_delay_ms(100);
	displayTempData(temp_data);
	_delay_ms(100);
	// for(count = 0; count<= 39; count++)
	// {
	// 	dht_data[count] = 0;
	// }
	sendData(LCD_MODE, 0xDF);  // degree symbol
	sendData(LCD_MODE, 'C'); // Celcius symbol
	sendData(LCD_MODE, ' ');  // blank space
	_delay_ms(100);
	displayMsg(p_speed);
	
	sendData(LCD_MODE, ' ');  // blank space
	sendData(LCD_MODE, ' ');  // blank space
	_delay_ms(100);
	
	sendCmd(LCD_MODE, NEXT_LINE);
	_delay_ms(100);
	
	displayMsg(humid);
	_delay_ms(100);
	displayHumidData((humid_data));
	_delay_ms(100);
	
	sendData(LCD_MODE, 0x25); // % symbol
	_delay_ms(100);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Switches functions /////////////////////////////////////////////////////////////////////////////////////
unsigned char makeSwitch(unsigned char pOrt, unsigned char pIn)
{
    if (pOrt == D)
    {
        DDRD &= ~(1 << pIn);
        PORTD |= (1 << pIn);
    }
    else if (pOrt == B)
    {
        DDRB &= ~(1 << pIn);
        PORTB |= (1 << pIn);
    }
    else if (pOrt == C)
    {
        DDRC &= ~(1 << pIn);
        PORTC |= (1 << pIn);
    }
    else
    {
        return -1;
    }
    return 0;
}

unsigned char readSwitch(unsigned char pOrt, unsigned char pIn)
{
    unsigned char reg_read;
    if (pOrt == D)
    {
        reg_read = PIND & (1 << pIn);   
    }
    else if (pOrt == B)
    {
        reg_read = PINB & (1 << pIn);
    }
    else if (pOrt == C)
    {
        reg_read = PINC & (1 << pIn);
    }
    else
    {
        return -1;
    }
    return reg_read;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Interrupts ////////////////////////////////////////////////////////////////////////////////////////
void enableIOInterrupt(unsigned char external_interrupt, unsigned char pin_changed_interrupt)
{
  SREG &= ~(1 << I_bit);  // disable all interrupts do avoid accidents
  if (external_interrupt)
  {
    // no external interrupt
    EICRA = 0x00; // 0b0000,0000 
    EIMSK = 0x00; // 0b0000,0000 unmasking the INT0
    // EIFR flag register
  }
  if (pin_changed_interrupt)
  {
    // yes pin change interrupts
    PCICR = 0x01; // 0b0000,0001 configure pin change at 0th group
    //PCIFR flag register for polling
    PCMSK2 = 0x00; // all are masked
    PCMSK1 = 0x00;  // all are masked
    PCMSK0 = 0x38;  // unmasking of d13, d12, d11
  }
  SREG |= (1 << I_bit);
}

void enableIcInterrupt(void)
{
    SREG &= ~(1 << I_bit);  // disable all interrupts do avoid accidents
    TIMSK1 = 0x21;  // input capture and overflow interrupt enable
    SREG |= (1 << I_bit);
}

void enableTimer2Interrupt(void)
{
    SREG &= ~(1 << I_bit);  // disable all interrupts do avoid accidents
    TIMSK2 = 0x01;  // overflow interrupt enable
    SREG |= (1 << I_bit); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pump Crtl ///////////////////////////////////////////////////////////////////////////////////////////////
void initPump(void)
{
  DDRB |= (1 << en_pump_pin);
  DDRB |= (1 << pump_pin); 
}

void powerUpPump(unsigned char is_enable)
{
  if (is_enable)
  {
    PORTB |= (1 << en_pump_pin);
    PORTB |= (1 << pump_pin);
  }
  else
  {
    PORTB &= ~(1 << en_pump_pin);
    PORTB &= ~(1 << pump_pin);
  }
}

void pwmInit(void)
{
  // inverting 10 bit fast pwm
  TCCR1A = 0x33;  
  TCCR1B = 0x09;  // last three bits are pre-scaler here it is 1.
  TCCR1C = 0x00;  // for non-pwm mode only
  
  // for TCNT1 top is set to 0x03FF in 10-bit fast pwm mode
  //TCNT1H = ; 
  //TCNT1L = ;

  // OCR1A disabled i.e. no pwm on OC1A pin
  //OCR1AH = ;
  //OCR1AL = ;

  // default pwm is 50 %
  OCR1BH = 0x01;  // 0b0000,0000
  OCR1BL = 0x00;  // 0b0000,0000
  
  // no input capture
  // ICR1H = ;
  // ICR1L = ;
  
  // no interrupts
  TIMSK1 = 0x00;
  // TIFR1 = ;
}

void setPumpSpeed(unsigned char pump_speed)
{
  // default pwm is 50 %
  OCR1BH = 0x01;  // 0b0000,0000
  OCR1BL = 0x00;  // 0b0000,0000
  if (pump_speed == 0)
  {
    OCR1BH = 0x00;  // 0b0000,0000
    OCR1BL = 0x00;  // 0b0000,0000
  }
  if (pump_speed == 20)
  {
    OCR1BH = 0x01;  // 0b0000,0000
    OCR1BL = 0x00;  // 0b1100,1101
  }
  if (pump_speed == 40)
  {
    OCR1BH = 0x01;  // 0b0000,0001
    OCR1BL = 0x00;  // 0b1001,1010
  }
  if (pump_speed == 60)
  {
    OCR1BH = 0x01;  // 0b0000,0010
    OCR1BL = 0x00;  // 0b0110,0111
  }
  if (pump_speed == 80)
  {
    OCR1BH = 0x01;  // 0b0000,0011
    OCR1BL = 0x00;  // 0b0011,0100
  }
  if (pump_speed == 100)
  {
    OCR1BH = 0x01;  // 0b0000,0011
    OCR1BL = 0x00;  // 0b1111,1111
  }
}

void resetTimer1(void)
{
  // reset
  TCCR1A = 0x00;  
  TCCR1B = 0x00;  // prescaler starts the timer and stops it
  TCCR1C = 0x00;  // for non-pwm mode only
  TCNT1 = 0;
  // resetting can be done using GTCCR register also
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DHT11 ///////////////////////////////////////////////////////////////////////////////////////////////////
void enInputCap(void)
{
    TCCR1A = 0x00;  // normal mode
    TCCR1B = 0x41;  // trigger at positive edge with prescaler = 1
    TCCR1C = 0x00;  // used in output compare mode
}

unsigned char getHumidityInt(void)
{
    uint32_t humidityInt = 0, count;
    for(count=0;count<=7;count++)
    {
        humidityInt = humidityInt + dht_data[count]*pow(2,7-count);
    }
    return humidityInt;
}

unsigned char getTemperatureInt(void)
{
    uint32_t temperatureInt = 0, count;
    for(count=0;count<=7;count++)
    {
        temperatureInt = temperatureInt + dht_data[count+16]*pow(2,7-count);
    }
    return temperatureInt;
}

void dht11(void)
{
    DDRB |= (1 << dht_pin); // set dht_pin as output
    PORTB &= ~_BV(PORTB0);   // set PB0 as LOW
    _delay_ms(25);    // delay 25 miliseconds
    DDRB &= ~_BV(DDB0); // set PB0 as INPUT
    PORTB |= _BV(PORTB0); // set PB0 PULL-UP
    _delay_us(30);    // delay 30 microseconds
    PORTB &= ~_BV(PORTB0);  // remove PB0 PULL-UP
    enInputCap(); // initialize input capture
    enableIcInterrupt();// enable the interrupt
      while (index2 <= 42)
      {
		
		if (index2 >= 4)
		{
			if ((ic_data - 800) > 800)
			{
				dht_data[index2 - 4] = 1;
			}
			else
			{
				dht_data[index2 - 4] = 0;
			}
		}
      }

    resetTimer1();
    _delay_ms(500);
    over_flow = 0;
	index2 = -1;
}

void displayTempData(uint32_t t)
{
    if (t >= 100)
    {
        sendData(LCD_MODE, digits[1]);
        sendData(LCD_MODE, digits[0]);
        sendData(LCD_MODE, digits[0]); 
    }
    else if(t == 0)
    {
        sendData(LCD_MODE, digits[0]);
        sendData(LCD_MODE, digits[0]);
    }
    else
    {
        sendData(LCD_MODE, digits[t/10]);
        sendData(LCD_MODE, digits[t%10]);
    }
}

void displayHumidData(uint32_t h)
{
    if (h >= 100)
    {
        sendData(LCD_MODE, digits[1]);
        sendData(LCD_MODE, digits[0]);
        sendData(LCD_MODE, digits[0]); 
    }
    else if(h == 0)
    {
        sendData(LCD_MODE, digits[0]);
        sendData(LCD_MODE, digits[0]);
    }
    else
    {
        sendData(LCD_MODE, digits[h/10]);
        sendData(LCD_MODE, digits[h%10]);
    }
}

void initTimer2(void)
{
  TCCR2A = 0x00;
  TCCR2B = 0x07;  // clock pre-scaler = 1024 i.e. 64 us for one step
  //TCCR2C = 0x00;	// this register dosen't exist for timer2
  //ASSR |= (1 << 5);	// AS2 pin for external oscillator at tosc1 pin
  enableTimer2Interrupt();
}

void resetTimer2(void)
{
  TCCR2A = 0x00;
  TCCR2B = 0x00;
  //TCCR2C = 0x00;	// this register dosen't exist for timer2
  TCNT2 = 0;
}

void theLogic(void)
{
	int count = 0, count_inverse = 0;
	// only last temp change will trigger the reaction
	resetTimer2();
	_delay_ms(wait);
	over_flow_2 = 0;
	// actual formula (((temp_data - prev_temp_data) * 60) - ((humid_data / 10) * 10));
	motor_on_duration = (((temp_data - prev_temp_data) * 60) - (humid_data / 5)); 
	pump_speed = ((humid_data / 10) - (temp_data / 10));
	if(motor_on_duration < 0)
	{
		motor_on_duration *= -1;
	}
	if(pump_speed < 0)
	{
		pump_speed *= -1;
	}
	if (pump_speed <= 3)
	{
		pump_speed = 100; // 100%
		count = 4;
	}
	else if (pump_speed <= 5)
	{
		pump_speed = 80; // 80%
		count = 3;
	}
	else if (pump_speed <= 7)
	{
		pump_speed = 60; // 60%
		count = 2;
	}
	else if (pump_speed <= 10)
	{
		pump_speed = 40; // 40%
		count = 1;
	}
	else if (pump_speed > 10)
	{
		pump_speed = 20; // 20%
		count = 0;
	}
	else
	{
		pump_speed = 0; // 0%
		count = -1;
	}
	_delay_ms(100);
	sendData(LCD_MODE, ' ');  // blank space
	count_inverse = count;
	for(; count >= 0; count--)
	{
		sendData(LCD_MODE, 0xFF);
		_delay_ms(100);
	}
	for ( count = 0; count < (4 - count_inverse); count++)
	{
		sendData(LCD_MODE, ' ');	// bar
	}
	
	sendData(LCD_MODE, ' ');  // blank space
	_delay_ms(100);
	pwmInit();
	setPumpSpeed(pump_speed); // 50 percent is default
	powerUpPump(PUMP_ON);
	initTimer2();
}

// void initSleep()
// {
	
// }
