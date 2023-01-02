/*
 *  Author: Tushar Gupta
 *  File: main.c // this is the main file for the project
 */
#include <stdint.h>
/*Register mapping*/

//(*((volatile uint32_t *)0x40000000))

// bus control registers
#define GPIOHBCTL_Base (*((volatile uint32_t *)0x400FE000))
#define GPIOHBCTL_Reg (*((volatile uint32_t *)0x400FE06C))

// clock control registers
#define RCGCGPIO_Base (*((volatile uint32_t *)0x400FE000))
#define RCGCGPIO_Reg (*((volatile uint32_t *)0x400FE608))

// GPIO control registers
#define GPIO_PORT_F_AHB_Base (*((volatile uint32_t *)0x4005D000))
#define GPIO_PORT_F_DATA (*((volatile uint32_t *)0x4005D000))
#define GPIODIR_PORTF (*((volatile uint32_t *)0x4005D400))
#define GPIOAFSEL_PORTF (*((volatile uint32_t *)0x4005D420))
#define GPIODR2R (*((volatile uint32_t *)0x4005D500))
#define GPIODR4R (*((volatile uint32_t *)0x4005D504))
#define GPIODR8R (*((volatile uint32_t *)0x4005D508))
#define GPIODEN (*((volatile uint32_t *)0x4005D51C))

/*Bit mapping*/
#define PORTF_AHB_SEL_bit 5
#define R5 5    // provide clock to portF

/* application specific macros*/
#define red_led 1
#define blue_led 2
#define green_led 3
#define ON 1
#define OFF 0
#define OUTPUT 1
#define INPUT 0
#define GPIO 0

/*function declarations*/
void sysInit(void);
void clockInit(void);
void gpioPortInit(void);
void gpioPinInit(unsigned char, unsigned char, unsigned char);
void led(unsigned char, unsigned char);

int main(void)
{
    sysInit();
    clockInit();
    gpioPinInit(GPIO, OUTPUT, red_led);
    gpioPinInit(GPIO, OUTPUT, blue_led);
    gpioPinInit(GPIO, OUTPUT, green_led);
    led(red_led, ON);
	return 0;
}

void sysInit(void)
{
    GPIOHBCTL_Reg |= (1 << PORTF_AHB_SEL_bit);  // AHB for PORTF
}

void clockInit(void)
{
    RCGCGPIO_Reg |= (1 << R5);  // clock for PORTF
}

void gpioPortInit()
{

}

void gpioPinInit(unsigned char function, unsigned char dir, unsigned char pin)
{
    if (function == GPIO)
    {
        GPIOAFSEL_PORTF &= ~(1 << pin);
    }

    GPIODR2R |= ((1 << red_led) | (1 << blue_led) | (1 << green_led));

    if (dir)
    {
        GPIODIR_PORTF |= (1 << pin);
    }
    else
    {
        GPIODIR_PORTF &= ~(1 << pin);
    }

    GPIODEN |= ((1 << red_led) | (1 << blue_led) | (1 << green_led));
}

void led(unsigned char colour, unsigned char status)
{
    if (status && (colour == red_led))
    {
        GPIO_PORT_F_DATA |= (1 << red_led);
    }
    else if (status && (colour == blue_led))
    {
        GPIO_PORT_F_DATA |= (1 << blue_led);
    }
    else if (status && (colour == green_led))
    {
        GPIO_PORT_F_DATA |= (1 << green_led);
    }
    else
    {
        if (colour == red_led)
        {
            GPIO_PORT_F_DATA &= ~(1 << red_led);
        }
        if (colour == blue_led)
        {
            GPIO_PORT_F_DATA &= ~(1 << blue_led);
        }
        if (colour == green_led)
        {
            GPIO_PORT_F_DATA &= ~(1 << green_led);
        }
    }
}
