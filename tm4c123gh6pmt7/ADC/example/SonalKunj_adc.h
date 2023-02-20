#ifndef _SONALKUNJ_ADC_H_
#define _SONALKUNJ_ADC_H_

#include "configuration.h"

#define RCGCADC_Reg (*((volatile uint32_t *)0x400FE638))
	
#define CLOCK_TO_ADC_0 0x00000001
#define CLOCK_TO_GPIO_E 0x00000010 //0b...010000
#define PE_2 (1 << 2)
#define ADC_SS0_EN 0x00000001
#define ADC_SS0_RUN_ALWAYS 0x0000000F
#define ADC_SS0_AIN1 0x11111111
#define ADC_SS0_ASI_E8 0x64444444
#define ADC_SS0_STATUS_INTERRUPT_EN 0x00000001

void adcInitAndReadData(void);

#endif