//  gnd
//  power - 5V
//  signal ir detected when signal is low



#include<avr/io.h>
#include<util/delay.h>

int main()
{
    DDRD &= ~( 1 << 7 );    // input
    PORTD &= ~( 1 << 7 );   // no pull-up
    
    // by default led is low
    DDRB |= ( 1 << 5 );      
    PORTB &= ~( 1 << 5 );

    while(1)
    {
        while( ( PIND & 0x80 ) == 0 )
        {
            PORTB |= ( 1 << 5 );    // led high if obstacle found
        }
        PORTB &= ~( 1 << 5 );  // led low if no obstacle
    }
    return 0;
}