#include "SonalKunj_adc.h"

void adcInitAndReadData(void)
{
	// module initialization
	SYSCTL->RCC &= ~((1 << 13));	// turn on the PLL
	SystemCoreClockUpdate();	// update the system clock
	delayMS(100);
	
	// provide clock to ADC0
	RCGCADC_Reg |= CLOCK_TO_ADC_0;
	
	// wait till periphal is ready for access
	while (!(SYSCTL->PRADC & (1 << 0)));
	
	// provide clock to pe2
	//RCGCGPIO_Reg |= CLOCK_TO_GPIO_E;

	// unlock the given pin
	GPIOE->LOCK = 0x4C4F434B;
	
	// allow commit the changes
	GPIOE->CR |= (1 << 2);//PE_2;
	
	// alternate function at pe2 
	GPIOE->AFSEL |= (1 << 2);
	
	// disable the digital function
	GPIOE->DEN &= ~(1 << 2);// default
	
	// select the analog function
	GPIOE->AMSEL |= (1 << 2);//PE_2;
	
	
	// sequencer configuration
	NVIC_DisableIRQ(ADC0SS0_IRQn);
	
	// disable the sequencer
	ADC0->ACTSS &= ~(1 << 0);
	
	// default mode trigger by the processor
	//ADC0->EMUX |= ADC_SS0_RUN_ALWAYS;
	
	// select the channel 1 for sequencer 0
	ADC0->SSMUX0 |= ADC_SS0_AIN1;
	
	// interrupt at all 8 completion and end of line at 8th conversion
	ADC0->SSCTL0 |= ADC_SS0_ASI_E8;
	
	// interrupt at ss0 conversion complete
	ADC0->IM |= ADC_SS0_STATUS_INTERRUPT_EN;
	
	// set the interrupt priority
	NVIC_SetPriority(ADC0SS0_IRQn, 3);
	
	// enable the interrupt handler
	NVIC_EnableIRQ(ADC0SS0_IRQn);
	
	// enable the sequencer
	ADC0->ACTSS |= (1 << 0);//ADC_SS0_EN;
	
	// trigger  the conversion
	ADC0->PSSI |= (1 << 0);
	
	// wait for first interrupt
	while (!(ADC0->RIS & (1 << 0)));
	
	// restore the clock to MOSC
	SYSCTL->RCC |= (1 << 13);
	SystemCoreClockUpdate();
	delayMS(100); 
}
