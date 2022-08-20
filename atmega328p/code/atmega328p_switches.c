#include <avr/io.h>
#include <util/delay.h>
#include "atmega328p_switches.h"

int main()
{
    makeSwitch(B, 4);
    DDRB |= (1 << 5);

    while(1)
    {
        _delay_ms(100);
        if (readSwitch(B, 4) == 0)
        {
            PORTB |= (1 << 5);
        }
        else
        {
            PORTB &= ~(1 << 5);
        }
    }
    return 0;
}