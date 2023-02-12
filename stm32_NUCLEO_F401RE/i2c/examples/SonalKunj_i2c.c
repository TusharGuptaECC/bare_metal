#include "SonalKunj_i2c.h"

void i2cInit(void)
{
	/* provide clock to i2c_1 */
	RCC->APB1ENR |= (1 << 21);
	
	/* disable the i2c1 if enabled */
	I2C1->CR1 &= ~(1 << PE_bit);
	
	/* provide clock to GPIOB */
	RCC->AHB1ENR |= (1 << 1);
	
	/* allow altenate function selection */
	GPIOB->MODER |= ((1 << 19) | (1 << 17));
	
	/* select alternate function of i2c at PB8 and PB9 */
	GPIOB->AFR[1] |= ((1 << 6) | (1 << 2));
	
	/* periphal clock frequency is set to 16MHz */
	I2C1->CR2 |= 16;
	
	/* thigh and tlow is 5000 ns i.e SCL = 100KHz*/
	I2C1->CCR |= 80;
	
	/* scl rise time */
	I2C1->TRISE = 17;
	
	I2C1->CR1 |= (1 << PE_bit);
}

void i2c_1_MasterTransmit(unsigned char add, unsigned char data)
{
	uint32_t status;
//	if (I2C1->SR2 & (1 << 1))
//	{
//		led(OFF);
//		I2C1->CR1 |= (1 << 15);
//		delayUS(100);
//		I2C1->CR1 &= ~(1 << 15); 
//	}
	
	/* generate the start condition */
	I2C1->CR1 |= (1 << I2C_START_bit);
	
	while (!(I2C1->SR1 & (1 << SB_bit)));
	status = I2C1->SR1;
	I2C1->DR = add;
	
	while (!(I2C1->SR1 & (1 << ADDR_bit)));
	status = I2C1->SR1;
	status = I2C1->SR2;

	I2C1->DR = data;
	status = I2C1->SR1;
	status = I2C1->SR2;
	
	while (!(I2C1->SR1 & (1 << TxE_bit)));
}

uint32_t i2c_1_MasterReceive(unsigned char add)
{
	uint32_t result;
	/* generate the start condition */
	I2C1->CR1 |= (1 << I2C_START_bit);
	
	while (!(I2C1->SR1 & (1 << SB_bit)));
	I2C1->DR = add; // read data this time
	
	while (!(I2C1->SR1 & (1 << ADDR_bit)));
	I2C1->CR1 &= ~(1 << 10);
	result = I2C1->SR1;
	result = I2C1->SR2;
	
	result = I2C1->DR;// = 0x75;
	while (!(I2C1->SR1 & (1 << RxNE_bit)));
	I2C1->CR1 |= (1 << 9);
	return result;
}