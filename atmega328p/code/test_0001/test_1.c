#include<avr/io.h>
#include<util/delay.h>

int main()
{
    DDRB |= ( 1 << 5);
    DDRB |= ( 1 << 4);
    
    while(1)
    {
        PORTB |= ( 1 << 5);
        PORTB |= ( 1 << 4);
        _delay_ms(300);
        PORTB &= ~( 1 << 5);
        PORTB &= ~( 1 << 4);
        _delay_ms(300);
    }
    return 0;
}