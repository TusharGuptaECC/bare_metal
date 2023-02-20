#include "SonalKunj_nextion.h"

void nextionInit(void)
{
	uart_1_Init();
}

unsigned char nextionRead(void)
{
	unsigned char data;
	data = uart_1_Receive();
	if (uart_1_Receive() == 0)
	{
		if (uart_1_Receive() == 0)
		{
			if (uart_1_Receive() == 0)
			{
				/* data has been received properly */
				return data;
			}
			else
			{
				//led(green_led, ON);
			}
		}
		else
		{
			//led(green_led, ON);
		}
	}
	else
	{
		//led(green_led, ON);
	}
	return 200;
}

unsigned char nextionRead_1(void)
{
	unsigned char data;
	uart_1_Receive();
	uart_1_Receive();
	uart_1_Receive();
	uart_1_Receive();
	data = uart_1_Receive();
	if (uart_1_Receive() == 0)
	{
		if (uart_1_Receive() == 0)
		{
			if (uart_1_Receive() == 0)
			{
				/* data has been received properly */
				return data;
			}
			else
			{
				//led(green_led, ON);
			}
		}
		else
		{
			//led(green_led, ON);
		}
	}
	else
	{
		//led(green_led, ON);
	}
	return 200;
}

unsigned char nextionSendSensorData(unsigned char humid,unsigned char temp, float co2)
{
	uart_1_Print("t0.txt=");
	uart_1_Transmit(0x22);
	uart_1_Transmit(humid/10 + '0');
	uart_1_Transmit(humid%10 + '0');
	uart_1_Transmit(0x22);
	uart_1_Transmit(0xFF);
	uart_1_Transmit(0xFF);
	uart_1_Transmit(0xFF);
	
	uart_1_Print("t1.txt=");
	uart_1_Transmit(0x22);
	uart_1_Transmit(temp/10 + '0');
	uart_1_Transmit(temp%10 + '0');
	uart_1_Transmit(0x22);
	uart_1_Transmit(0xFF);
	uart_1_Transmit(0xFF);
	uart_1_Transmit(0xFF);
	
	co2 = co2*10;
	uart_1_Print("t2.txt=");
	uart_1_Transmit(0x22);
	uart_1_Transmit(co2/10 + '0');
	uart_1_Transmit('.');
	uart_1_Transmit((unsigned char)co2%10 + '0');
	uart_1_Transmit(0x22);
	uart_1_Transmit(0xFF);
	uart_1_Transmit(0xFF);
	uart_1_Transmit(0xFF);
}	

/*
	* This function is highly specific to the application.
	* This function must me called after nextionRead_2 only.
*/
void saveSettingsFromNextion(void)
{
	uart_1_Receive();
	uart_1_Receive();
	settings[0] = uart_1_Receive();
	uart_1_Receive();
	uart_1_Receive();
	uart_1_Receive();
	settings[1] = uart_1_Receive();
	uart_1_Receive();
	uart_1_Receive();
	uart_1_Receive();
	settings[2] = uart_1_Receive();
	uart_1_Receive();
	uart_1_Receive();
	uart_1_Receive();
}

/*
	* This function is highly specific to the application.
	* This function must me called only when user taps on settings tab on nextion display.
*/
unsigned char nextionRead_2(void)
{
	/*
	 * Suppose suddenly 17, 00, 00, 00 came on uart as user has pressed back button.
	 * This function assumes that response will be 04, FF, FF, FF 
	 * But when back is pressed instead of later FFs we get 00s so it returns 200 as error code
	 * This 200 indicates that 17 has been arived at the uart.
	*/
	unsigned char data;
	data = uart_1_Receive();
	if (uart_1_Receive() == 0xFF)
	{
		if (uart_1_Receive() == 0xFF)
		{
			if (uart_1_Receive() == 0xFF)
			{
				/* data has been received properly */
				return data;
			}
			else
			{
				//led(green_led, ON);
				/* do nothing */
			}
		}
		else
		{
			//led(green_led, ON);
			/* do nothing */
		}
	}
	else
	{
		//led(green_led, ON);
		/* do nothing */
	}
	/* here retuen of 200 implies new data must be saved */
	return 200;
}
