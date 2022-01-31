#include "uart.h"

unsigned char stringBuffer[100]="learn-in-depth : <Magdy Adel> ";
void main(void)
{
	Uart_SendString(stringBuffer); 
} 