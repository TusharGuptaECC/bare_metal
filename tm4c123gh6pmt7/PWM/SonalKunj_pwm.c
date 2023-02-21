#include "SonalKunj_pwm.h"

// This function assumes that pwm clock is 250,000 Hz
// This function takes time period in ms
// This function takes duty-cycle in percentage i.e. valid range is 0 to 100
void pwmBegin(unsigned char time_period, unsigned char duty_cycle)
{
	// clock to pwm1 module
	SYSCTL->RCGCPWM |= PWM_1_CLOCK_EN;
	
	// clock to port f pin1 in case if not provided earlier
	SYSCTL->RCGCGPIO |= (1 << 5);

	// disable the pwm block
	PWM1->_2_CTL &= ~(1 << 0);
	
	// unlock the pf1 pin
	GPIOF->LOCK = 0x4C4F434B;
	
	// commit changes at pf1 pin
	GPIOF->CR |= (1 << 1);//PF1
	
	// enable alternate function at pf1 pin
	GPIOF->AFSEL |= (1 << 1);
	
	// select pwm as alternate function
	GPIOF->PCTL |= 0x50;
	
	// PREDIVISIOR IN RCC IS DEFAULT TO /64
	// enable pwm divisor
	SYSCTL->RCC |= (1 << 20);
	
	// select the counting direction
	PWM1->_2_CTL |= (1 << 1);//UP COUNT
	
	// when counter reaches 0 drive the pin HIGH and when comparator match occurs drive the pin LOW
	PWM1->_2_GENB |= ((1 << 9) | (1 << 1) | (1 << 0));
	
	// maximum period possible
	PWM1->_2_LOAD |= ((250000*time_period)/1000);// for 20 ms time period //0xFFFF;
	
	// 50% pwm
	PWM1->_2_CMPB |= ((duty_cycle*PWM1->_2_LOAD)/100);//0x8000;//0x1000;//0X8000;
	
	// enable the pwm block
	PWM1->_2_CTL |= (1 << 0);
	
	// enable the pwm channel 5
	PWM1->ENABLE |= (1 << 5);
}

void pwmStop(void)
{
	PWM1->_2_CTL &= ~(1 << 0);
	
	// enable the pwm channel 5
	PWM1->ENABLE &= ~(1 << 5);
}