/*
 * keypad.h
 *
 * Created: 3/24/2022 11:08:30 AM
 *  Author: MAGDY
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 1000000UL

#include "avr/io.h"
#include "util/delay.h"


#define KEYPAD_PORT PORTD
#define DDIR_KEYPAD_PORT DDRD
#define KEYPAD_PIN PIND

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7


void KEYPAD_init();
char KEYPAD_CHAR();



#endif /* KEYPAD_H_ */