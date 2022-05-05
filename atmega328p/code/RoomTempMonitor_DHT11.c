// ROOM Temperature and Humidity Monitor

#include<avr/io.h>
#include<util/delay.h>
#include<math.h>
#include<stdint.h>

// user defined variables

unsigned char data[40];

// user defined functions

void capInit(void);
void dataCapture(void);
void endInputCapture(void);
void lcdInit(void);
unsigned char getHumidityInt(void);
unsigned char getHumidityDec(void);
unsigned char getTemperatureInt(void);
unsigned char getTemperatureDec(void);
void checkSum(unsigned char, unsigned char, unsigned char, unsigned char);
void displayMessage(unsigned char, unsigned char, unsigned char, unsigned char);
void gotoSecondLine(void);
void gotoFirstLine(void);
void clearDisplay(void);
void displayHI(unsigned char);
void displayHD(unsigned char);
void displayTI(unsigned char);
void displayTD(unsigned char);
void displayValue(int);

int main()
{
	unsigned char humidityInt=0,humidityDec=0,tempInt=0,tempDec=0;
	while(1)
	{ 
		DDRB |= _BV(DDB0);	// set PB0 as output
		PORTB |= _BV( PORTB0 );  // set PB0 HIGH
		_delay_ms(3000);
		//------------------------------------------------------------------------------
		// DHT11-------------------------------------------------------------------
		dataCapture();
		endInputCapture();
		//-------------------------------------------------------------------------------
		//LCD------------------------------------------------------------------------
		lcdInit();
		gotoFirstLine();
		humidityInt = getHumidityInt();
		humidityDec = getHumidityDec();
		tempInt = getTemperatureInt();
		tempDec = getTemperatureDec();
		checkSum(humidityInt,humidityDec,tempInt,tempDec);	// error check
		displayMessage(humidityInt,humidityDec,tempInt,tempDec);	// display data on LCD
		PORTD &= ~_BV(PORTD3);	// set PD3 as low
	}
	return 0;
}

// initializes input capture at pin PB0
// prescaler is 1
// no interrupts
void capInit(void)
{
    	
	TCCR1A = 0;
	TIFR1 |= ( 1<<ICF1 );		// clear input capture flag 
	TCCR1B = 0x41;
}

// initializes DHt11
// captures data
void dataCapture(void)
{
	uint16_t previous_state,data1,x;
	unsigned int i=0;
	
	PORTB&= ~_BV(PORTB0);   // set PB0 as LOW
	_delay_ms(25);		// delay 25 miliseconds
          DDRB &= ~_BV(DDB0);	// set PB0 as INPUT
	PORTB |= _BV(PORTB0);	// set PB0 PULL-UP
	_delay_us(30);		// delay 30 microseconds
	PORTB &= ~_BV(PORTB0);	// remove PB0 PULL-UP
	capInit();	// initialize input capture
	
	while ((TIFR1&(1<<ICF1)) == 0);	// waiting for the positive edge 
	TIFR1= (1<<ICF1);	// clear input capture flag 
	while ((TIFR1&(1<<ICF1)) == 0);	// waiting for the positive edge 
	previous_state = ICR1;	// storing ICR1 register value in previous_state
	TIFR1= (1<<ICF1);	// clear input capture flag 
	while(i<=39)
	{
		while ((TIFR1&(1<<ICF1)) == 0);	// waiting for the positive edge 
		data1 = ICR1;	// storing new value of ICR1 in data1
		TIFR1= (1<<ICF1);	// clear input capture flag 
		x = (data1 - previous_state -50);	// storing the pulse width in x
		previous_state = data1;	// updating the previous_state
		if(x>35)	// checking whether the received data is 0 or 1
			data[i] = 1;
		else
			data[i] = 0;
		i++;
	}
}

// disables the input capture
void endInputCapture(void)
{
	TCCR1B = 0x00;
}

// --------------------------------------------------------------------------------------------------------

//initialize the LCD in 8-bit two line with increment cursor
void lcdInit(void)
{
	DDRB = 0xFF;    // all pins of port B as  OUTPUT
	DDRD |= 0xE0;   // 1110,0000	pin PD7 to PD5 as output
	    
	// lcd 8-bit mode and 2 line mode
	_delay_ms(500);
	PORTD &= ~( ( 1 << 7 ) | ( 1 << 6 ) );	// set pin PD6 and PD7 as LOW
	PORTB = 0x38;	// sending instruction to LCD
	
	// enable pulse
	PORTD |= ( 1 << 5 );	// set pin PD5 as HIGH
	_delay_ms(10);
	PORTD &= ~( 1 << 5 );		// set pin PD5 as LOW

	// display on
	_delay_ms(500);
	PORTB = 0x0E;		// sending instruction to LCD
	
	// enable pulse
	PORTD |= ( 1 << 5 );	// set pin PD5 as HIGH
	_delay_ms(10);
	PORTD &= ~( 1 << 5 );		// set pin PD5 as LOW


	// increment cursor
	_delay_ms(500);
	PORTB = 0x06;		// sending instruction to LCD
	
	// enable pulse
	PORTD |= ( 1 << 5 );	// set pin PD5 as HIGH
	_delay_ms(10);
	PORTD &= ~( 1 << 5 );		// set pin PD5 as LOW
}

// convert sensor's 8-bit binary data into decimal form

unsigned char getHumidityInt(void)
{
        unsigned char humidityInt=0,count;
        for(count=0;count<=7;count++)
        {
            humidityInt = humidityInt + data[count]*pow(2,7-count);
        }
        return humidityInt;
}

unsigned char getHumidityDec(void)
{
        unsigned char humidityDec=0,count;
        for(count=0;count<=7;count++)
        {
            humidityDec = humidityDec + data[count+8]*pow(2,7-count);
        }
        return humidityDec;
}

unsigned char getTemperatureInt(void)
{
        unsigned char temperatureInt=0,count;
        for(count=0;count<=7;count++)
        {
            temperatureInt = temperatureInt + data[count+16]*pow(2,7-count);
        }
        return temperatureInt;
}

unsigned char getTemperatureDec(void)
{
        unsigned char temperatureDec=0,count;
        for(count=0;count<=7;count++)
        {
            temperatureDec = temperatureDec + data[count+24]*pow(2,7-count);
        }
        return temperatureDec;
}

// error check
void checkSum(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    unsigned char sum=0,count;
    for(count=0;count<=7;count++)
    {
        sum = sum + data[count+32]*pow(2,7-count);
    }
    if( ( sum == ( a+b+c+d ) ) || ( sum == ( a+b+c+d-1) ) )
    {
        DDRD |= ( 1 << 3 ); // set pd3 as output
        PORTD |= ( 1 << 3 );    // logic high at pin pd3
    }
}

// displays string on LCD
void displayMessage(unsigned char w, unsigned char x, unsigned char y, unsigned char z)
{
    int i;
    char mess1[] = "HUMID: ";
    char mess2[] = ".";
    char mess3[] = "%RH";
    char mess4[] = "TEMP : ";
    char mess5[] = "`C";
    PORTD &= ~( 1 << 6 );
    PORTD |= ( 1 << 7 );
    for(i=0;mess1[i]!='\0';i++)
    {
        PORTB = mess1[i];
        PORTD |= ( 1 << 5 );
        _delay_ms(10);
        PORTD &= ~( 1 << 5 );
    }
    displayHI(w);
    for(i=0;mess2[i]!='\0';i++)
    {
        PORTB = mess2[i];
        PORTD |= ( 1 << 5 );
        _delay_ms(10);
        PORTD &= ~( 1 << 5 );
    }
    displayHD(x);
    for(i=0;mess3[i]!='\0';i++)
    {
        PORTB = mess3[i];
        PORTD |= ( 1 << 5 );
        _delay_ms(10);
        PORTD &= ~( 1 << 5 );
    }
    
    gotoSecondLine();

    PORTD &= ~( 1 << 6 );
    PORTD |= ( 1 << 7 );
    for(i=0;mess4[i]!='\0';i++)
    {
        PORTB = mess4[i];
        PORTD |= ( 1 << 5 );
        _delay_ms(10);
        PORTD &= ~( 1 << 5 );
    }
    displayTI(y);
    for(i=0;mess2[i]!='\0';i++)
    {
        PORTB = mess2[i];
        PORTD |= ( 1 << 5 );
        _delay_ms(10);
        PORTD &= ~( 1 << 5 );
    }
    displayTD(z);
    for(i=0;mess5[i]!='\0';i++)
    {
        PORTB = mess5[i];
        PORTD |= ( 1 << 5 );
        _delay_ms(10);
        PORTD &= ~( 1 << 5 );
    }

}

// clear LCD 
void clearDisplay(void)
{
    _delay_ms(10);
    PORTD &= ~( 1 << 6 );
    PORTD &= ~( 1 << 7 );
    PORTB = 0x01;
    PORTD |= ( 1 << 5 );
    _delay_ms(10);
    PORTD &= ~( 1 << 5 );
}

// force cursor to go on second line of LCD
void gotoSecondLine(void)
{
    _delay_ms(10);
    PORTD &= ~( 1 << 6 );
    PORTD &= ~( 1 << 7 );
    PORTB = 0xC0;
    PORTD |= ( 1 << 5 );
    _delay_ms(10);
    PORTD &= ~( 1 << 5 );
}

// force cursor to go on first line of LCD
void gotoFirstLine(void)
{
    _delay_ms(10);
    PORTD &= ~( 1 << 6 );
    PORTD &= ~( 1 << 7 );
    PORTB = 0x80;
    PORTD |= ( 1 << 5 );
    _delay_ms(10);
    PORTD &= ~( 1 << 5 );
}

// display humidity's integral part
void displayHI(unsigned char w)
{
    int r,q;
    if(w>=100)
    {
        displayValue(1);
        displayValue(0);
        displayValue(0);     
    }
	else if(w==0)
	{
		q = 0;
		r = 0;
displayValue(q);
displayValue(r);
	}
    else
    {
        q = w/10;
        r = w%10;
        displayValue(q);
        displayValue(r);
    }
}

// display humidity's integral part
void displayHD(unsigned char x)
{
    int q,r;
    if(x>99)
    {
        x = x/10;
        q = x/10;
        r = x%10;
        displayValue(q);
        displayValue(r);
    }
	else if(x==0)
	{
		q = 0;
		r = 0;
displayValue(q);
displayValue(r);
	}
    else
    {
        q = x/10;
        r = x%10;
        displayValue(q);
        displayValue(r);
    }
}

// display humidity's integral part
void displayTI(unsigned char x)
{
    int q,r;
    if(x>99)
    {
        q = x/100;
        displayValue(q);
        x = x%100;
        q = x/10;
        r = x%10;
        displayValue(q);
        displayValue(r);
    }
	else if(x==0)
	{
		q = 0;
		r = 0;
displayValue(q);
displayValue(r);
	}
    else
    {
        q = x/10;
        r = x%10;
        displayValue(q);
        displayValue(r);
    }
}

// display humidity's integral part
void displayTD(unsigned char x)
{
    int q,r;
    if(x>99)
    {
        x = x/10;
        q = x/10;
        r = x%10;
        displayValue(q);
        displayValue(r);
    }
	else if(x==0)
	{
		q = 0;
		r = 0;
displayValue(q);
displayValue(r);
	}
    else
    {
        q = x/10;
        r = x%10;
        displayValue(q);
        displayValue(r);
    }
}

// display integers on the LCD
void displayValue(int x)
{
    if(x==0)
    {
        PORTB = 0x30;
    }
    if(x==1)
    {
        PORTB = 0x31;
    }
    if(x==2)
    {
        PORTB = 0x32;
    }
    if(x==3)
    {
        PORTB = 0x33;
    }
    if(x==4)
    {
        PORTB = 0x34;
    }
    if(x==5)
    {
        PORTB = 0x35;
    }
    if(x==6)
    {
        PORTB = 0x36;
    }
    if(x==7)
    {
        PORTB = 0x37;
    }
    if(x==8)
    {
        PORTB = 0x38;
    }
    if(x==9)
    {
        PORTB = 0x39;
    }
     PORTD |= ( 1 << 5 );
    _delay_ms(10);
    PORTD &= ~( 1 << 5 );
}

