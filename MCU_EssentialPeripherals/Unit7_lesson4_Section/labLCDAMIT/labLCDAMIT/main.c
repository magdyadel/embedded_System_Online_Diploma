/*
 * labLCDAMIT.c
 *
 * Created: 3/31/2022 5:42:52 PM
 * Author : Magdy
 */ 

#include <avr/io.h>
#include "HAL/LCD_Driver/lcd.h"

int main(void)
{
    /* Replace with your application code */
	LCD_Init();
	
	LCD_WRITE_STRING("Learn-In-Depth");	
    while (1) 
    {
    }
}

