/*
 * Drivres_AVR.c
 *
 * Created: 3/27/2022 11:04:35 AM
 * Author : Magdy
 */ 

#include "avr/io.h"
#include "HAL/LCD_Driver/lcd.h"
#include "HAL/KEYPAD_Driver/keypad.h"
#include "MCAL/UART/uart.h"


int main(void)
{
	/* Replace with your application code */
	LCD_Init();
	UART_Init();
	
	LCD_WRITE_STRING("UART TEST");
	
	UART_SendString(" HELLO");
	while (1)
	{
		LCD_WRITE_STRING(UART_ReceiveString());
	}
}


