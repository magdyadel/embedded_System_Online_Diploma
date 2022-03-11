/*
 * Interrupt.c
 *
 * Created: 3/9/2022 6:57:07 AM
 * Author : Magdy Adel  
 */ 

#include <avr/io.h>
#include "avr/interrupt.h"
#include <util/delay.h>

void EXTI_init(void)
{
	//make INT0 any logical change
	MCUCR |= (0b01<<0);
	//make INT1 rising edge
	MCUCR |= (0b11<<2);
	//make INT2 falling edge
	MCUCR |= (0<<6);
	
	//Enable Interrupt
	GICR |=(1<<5);
	GICR |=(1<<6);
	GICR |=(1<<7);
	
	//set global interrupt enable
	sei();
	
}
int main(void)
{
	EXTI_init();
	
	//make PortD pin 5,6,7 OUTPUT
	DDRD |=(1<<5);
	DDRD |=(1<<6);
	DDRD |=(1<<7);
	
    /* Replace with your application code */
    while (1) 
    {
		//Enable Interrupt
		PORTD |=(0<<5);
		PORTD |=(0<<6);
		PORTD |=(0<<7);
    }
}

ISR(INT0_vect)
{
	PORTD |=(1<<5);
	_delay_ms(500);
	PORTD &= ~(1<<5);
}
ISR(INT1_vect)
{
	PORTD |=(1<<6);
	_delay_ms(500);
	PORTD &= ~(1<<6);
}
ISR(INT2_vect)
{
	PORTD |=(1<<7);
	_delay_ms(500);
	PORTD &= ~(1<<7);
}
