#include <stdint.h>

#ifdef __ATmega2560__

#define scl_pin PD0
#define sda_pin PD1

#endif

#define ACK 1
#define NACK 0
#define generate_stop 1
#define generate_stop_start 0

void i2cInit(void);
unsigned char i2cMasterMode(unsigned char address);
unsigned char i2cBeginTransmission(unsigned char address);
void i2cMasterWrite(unsigned char data);
void i2cMasterRepeatStart(unsigned char address);
void i2cMasterEndTransmission(int really);
signed char i2cRead(int do_ack, int do_ack_1);
void i2cSlaveTransmit(unsigned char data);
unsigned char i2cSlaveReceive(void);
int32_t i2cTakeCareNegative(int32_t number);
signed char i2cRead1(int do_ack);



