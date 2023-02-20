#ifndef _SONALKUNJ_NEXTION_H_
#define _SONALKUNJ_NEXTION_H_

#define UART_H
#include "configuration.h"

unsigned char extern settings[3];	/* defined in main.c */

void nextionInit(void);
unsigned char nextionRead(void);
unsigned char nextionRead_1(void);
unsigned char nextionSendSensorData(unsigned char humid,unsigned char temp, float co2);
void saveSettingsFromNextion(void);
unsigned char nextionRead_2(void);

#endif