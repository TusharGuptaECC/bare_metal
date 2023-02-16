#include "SonalKunj_onBoard_LEDs.h"

void gpioPortInit()
{

}

void gpioPinInit(unsigned char function, unsigned char dir, unsigned char pin)
{
    if (function == GPIO)
    {
		GPIOF->AFSEL &= ~(1 << pin);
    }

    GPIOF->DR2R |= ((1 << red_led) | (1 << blue_led) | (1 << green_led));
		
    if (dir)
    {
        GPIOF->DIR |= (1 << pin);
    }
    else
    {
        GPIOF->DIR &= ~(1 << pin);
    }
    GPIOF->DEN |= ((1 << red_led) | (1 << blue_led) | (1 << green_led));
}

void led(unsigned char colour, unsigned char status)
{
    if (status && (colour == red_led))
    {
        GPIOF->DATA |= (1 << red_led);
	}
    else if (status && (colour == blue_led))
    {
        GPIOF->DATA |= (1 << blue_led);
    }
    else if (status && (colour == green_led))
    {
        GPIOF->DATA |= (1 << green_led);
    }
    else
    {
        if (colour == red_led)
        {
            GPIOF->DATA &= ~(1 << red_led);
        }
        if (colour == blue_led)
        {
            GPIOF->DATA &= ~(1 << blue_led);
        }
        if (colour == green_led)
        {
            GPIOF->DATA &= ~(1 << green_led);
        }
    }
}