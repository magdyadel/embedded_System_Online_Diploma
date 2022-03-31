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
	_delay_ms(30);
	LCD_CTRL |= (1<<EN_SWITCH) ;
}

void LCD_isBUSY(void)
{
	DataDir_LCD_PORT &= ~(0xFF<<DATA_SHIFT) ;		//Input Mode
	LCD_CTRL |= (1<<RW_SWITCH) ;	//Read mode -- ON
	LCD_CTRL &= ~(1<<RS_SWITCH) ;	//Read mode -- OFF
	LCD_KICK();
	DataDir_LCD_PORT = 0xFF;
	LCD_CTRL &= ~(1<<RW_SWITCH) ;
}


void LCD_clear_screen()
{
	LCD_WRITE_COMMAND(LCD_CMD_CLEAR_SCREEN);	
}

void LCD_GOTO_XY(unsigned char line , unsigned char position)
{
	if (line == 1 && position>=0 )
	{
		LCD_WRITE_COMMAND(LCD_CMD_BEGIN_AT_FIRST_ROW + position);
	}else if(line == 2 && position>=0 )
	{
		LCD_WRITE_COMMAND(LCD_CMD_BEGIN_AT_SECOND_ROW + position);
	}
}


//initialize LCD
void LCD_Init(void)
{
	_delay_ms(20);
	LCD_isBUSY();
	DataDir_LCD_CTRL |= ((1<<EN_SWITCH) | (1<<RW_SWITCH)| (1<<RS_SWITCH)) ;
	LCD_CTRL &= ~((1<<EN_SWITCH) | (1<<RW_SWITCH)| (1<<RS_SWITCH)) ;
	DataDir_LCD_PORT = 0xFF ;
	_delay_ms(15);
	LCD_clear_screen();
	
	#ifdef EIGHT_BIT_MODE
		LCD_WRITE_COMMAND(LCD_CMD_FUNCTION_8BIT_2LINES);
	#endif
	
	#ifdef FOUR_BIT_MODE
		LCD_WRITE_COMMAND(0x02);
		LCD_WRITE_COMMAND(LCD_CMD_FUNCTION_4BIT_2LINES);
	#endif
	
	
	LCD_WRITE_COMMAND(LCD_CMD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_CMD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_CMD_DISP_ON_CURSOR_BLINK);
}


void LCD_WRITE_COMMAND(unsigned char command)
{
	LCD_isBUSY();
	
	#ifdef EIGHT_BIT_MODE
		LCD_PORT = command ;
		LCD_CTRL &= ~ ((1<<RW_SWITCH) | (1<<RS_SWITCH)) ;
		_delay_ms(1);
		LCD_KICK();
	#endif
}

void LCD_WRITE_CHAR(unsigned char data)
{
	LCD_isBUSY();
	
	#ifdef EIGHT_BIT_MODE
		LCD_PORT = data ;
		LCD_CTRL &= ~ (1<<RW_SWITCH) ; // Turn RW OFF for write mode
		LCD_CTRL |=  (1<<RS_SWITCH) ; // Turn RS ON for data mode
		LCD_KICK();
	#endif
	
}
void LCD_WRITE_STRING(char * str)
{
	int count =0;
	while(*str)
	{
		count++;
		LCD_WRITE_CHAR(*str++);
		if (count==16)
		{
			LCD_GOTO_XY(2, 0);
		}else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1, 0);
			count = 0;
		}
				
	}
}

