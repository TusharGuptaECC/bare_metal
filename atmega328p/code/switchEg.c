#include <avr/io.h>
#include <util/delay.h>
#include "atmega328p_switches.h"

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