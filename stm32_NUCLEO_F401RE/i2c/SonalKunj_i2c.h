#ifndef _SONALKUNJ_I2C_H_
#define _SONALKUNJ_I2C_H_

#include <stm32f401xe.h>
#include <stdint.h>

#define PE_bit 0
#define I2C_START_bit 8
#define SB_bit 0
#define TxE_bit 7
#define RxNE_bit 6
#define ADDR_bit 1

void i2cInit(void);
void i2c_1_MasterTransmit(unsigned char add, unsigned char data);
uint32_t i2c_1_MasterReceive(unsigned char add);

#endif