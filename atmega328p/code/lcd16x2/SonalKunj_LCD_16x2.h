#ifndef _SONALKUNJ_LCD_16x2_H_
#define _SONALKUNJ_LCD_16x2_H_

#ifdef __AVR_ATmega328P__

#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>

 

void sendCmd(unsigned char, unsigned char);
void sendData(unsigned char, unsigned char);
void initLcd(unsigned char);
void print(unsigned char *message);
void nextLine(void);

#endif

#endif
