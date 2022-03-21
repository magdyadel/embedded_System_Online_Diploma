/*
 * unit7_lesson1_section.c
 *
 * Author : Magdy
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


#define SETBit(reg, bit)		(reg |= (1<<bit))
#define CLRBit(reg, bit)		(reg &= ~(1<<bit))
#define GETBit(reg, bit)		( ((reg)>>(bit)) &1)
#define TOGGLEBit(reg, bit)		(reg ^= (1<<bit))

// GPIO
#define GPIO_BASE   0x20

//GPIO PORTA registers
#define PORTD   *(volatile unsigned char *)(GPIO_BASE + 0x12) //PORTD data register
#define DDRD    *(volatile unsigned char *)(GPIO_BASE + 0x11) //PORTD data direction register
#define PIND    *(volatile unsigned char *)(GPIO_BASE + 0x10) //PORTD data input register


int main(void)
{
	//PORTD 5,6,7 Output
	DDRD |= (0b111<<5) ;  //set PD 0b111
	
	 uint32_t i;
    while (1) 
    {
		for(i = 5; i <= 7; i++)
		{
			//Turn ON LED Sequentially
			SETBit(PORTD, i);
				
			_delay_ms(1000); //delay
		}
			
		for(i = 7;i >= 5; i--)
		{
			//Turn OFF LED Sequentially
			CLRBit(PORTD, i);
				
			_delay_ms(1000); //delay
		}
    }
}

