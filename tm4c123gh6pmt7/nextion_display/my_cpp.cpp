#include "my_cpp.h"

unsigned char nextionSendNumber(unsigned char data)
{
	std::string x = String(data);
	uart_1_Print("buttonRead1.val=" + x);
	//uart_1_Transmit(10);
	uart_1_Transmit(0xFF);
	uart_1_Transmit(0xFF);
	uart_1_Transmit(0xFF);
}