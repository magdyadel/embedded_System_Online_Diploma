/*
 * lcd_keypad_drivers.c
 *
 * Created: 3/24/2022 11:06:21 AM
 * Author : MAGDY
 */ 
#include "avr/io.h"
#include "LCD_Driver/lcd.h"
#include "KEYPAD_Driver/keypad.h"


int main(void)
{
    /* Replace with your application code */
	LCD_Init();
	KEYPAD_init();
	volatile char KEY;
	volatile int count=0;
	
	LCD_WRITE_STRING("welcome");
	
    while (1) 
    {
		_delay_ms(100);
		KEY=KEYPAD_CHAR();
		switch(KEY)
		{
		case'!':LCD_clear_screen();
				break;
				
		case'N':break;
		
		default:
			if(count<16){
				LCD_WRITE_CHAR(KEY);
				count++;
			}
			else
			{
				count=0;
				LCD_clear_screen();
				LCD_WRITE_CHAR(KEY);
			}
			break;
		}
    }
}

