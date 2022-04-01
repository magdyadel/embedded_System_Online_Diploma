/*
 * lcd.c
 *
 * Created: 3/24/2022 11:07:49 AM
 *  Author: MAGDY
 */ 

#include "lcd.h"


void LCD_KICK()
{
	LCD_CTRL &= ~(1<<EN_SWITCH) ;
	_delay_ms(50);
	LCD_CTRL |= (1<<EN_SWITCH) ;
}

void LCD_isBUSY(void)
{
	DataDir_LCD_PORT = 0x00 ;
	LCD_CTRL |= (1<<RW_SWITCH);
	LCD_CTRL &= ~(1<<RS_SWITCH);
	LCD_KICK();
	DataDir_LCD_PORT = 0xFF;
	LCD_CTRL &= ~(1<<RW_SWITCH);
}


void LCD_clear_screen()
{
	LCD_WRITE_COMMAND(LCD_CMD_CLEAR_SCREEN);	
}

void LCD_GOTO_XY(unsigned char line , unsigned char position)
{
	if(line==1)
	{
		if(position <16 && position >=0)
		LCD_WRITE_COMMAND(LCD_CMD_BEGIN_AT_FIRST_ROW + position);
	}
	else if (line==2)
	if(position <16 && position >=0)
	LCD_WRITE_COMMAND(LCD_CMD_BEGIN_AT_SECOND_ROW + position);
}


//initialize LCD
void LCD_Init(void)
{
	_delay_ms(20);
	LCD_isBUSY();
	DataDir_LCD_CTRL |= ((1<<EN_SWITCH)|(1<<RW_SWITCH)|(1<<RS_SWITCH)); // Set as output
	LCD_CTRL &= ~((1<<EN_SWITCH)|(1<<RW_SWITCH)|(1<<RS_SWITCH)); // Clear
	DataDir_LCD_PORT = 0xFF; // Set Port as Output
	_delay_ms(15);
	LCD_clear_screen();
	
	#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_CMD_FUNCTION_8BIT_2LINES);
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_WRITE_COMMAND(0x02); // As datasheet
	LCD_WRITE_COMMAND(LCD_CMD_FUNCTION_4BIT_2LINES);
	#endif
	
	LCD_WRITE_COMMAND(LCD_CMD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_CMD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_CMD_DISP_ON_CURSOR_BLINK);
}


void LCD_WRITE_COMMAND(unsigned char command)
{
	#ifdef EIGHT_BIT_MODE
	LCD_isBUSY();
	LCD_PORT = command;
	LCD_CTRL &= ~(1<<RW_SWITCH)|(1<<RS_SWITCH); // Clear
	LCD_KICK();
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_isBUSY();
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
	LCD_KICK();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
	LCD_KICK();
	#endif
}


void LCD_WRITE_CHAR(unsigned char data)
{
	#ifdef EIGHT_BIT_MODE
	LCD_isBUSY();
	LCD_CTRL |= (1<<RS_SWITCH); // Turn RS ON for data mode
	LCD_PORT = (data) ;
	LCD_CTRL |= (1<<RS_SWITCH); // Turn RS ON for data mode
	LCD_CTRL &= ~(1<<RW_SWITCH); // Turn RW OFF for write mode
	LCD_KICK();
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	LCD_CTRL |= (1<<RS_SWITCH); // Turn RS ON for data mode
	LCD_CTRL &= ~(1<<RW_SWITCH); // Turn RW OFF for write mode
	LCD_KICK();
	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
	LCD_CTRL |= (1<<RS_SWITCH); // Turn RS ON for data mode
	LCD_CTRL &= ~(1<<RW_SWITCH); // Turn RW OFF for write mode
	LCD_KICK();
	#endif
}
void LCD_WRITE_STRING(char * str)
{
	int count = 0; // To count how much char on the line (it should be 16 char only)
	
	while (*str)
	{
		count++;
		LCD_WRITE_CHAR(*str++);
		if (count == 16) // Go to the second line
		{
			LCD_GOTO_XY(1,0); // Line 1 position 0
		}
		else if (count == 32 || count == 33) // Clear screen and show again
		{
			LCD_clear_screen();
			LCD_GOTO_XY(0,0); // Line 0 Position 0
			count = 0;
		}
	}

}

