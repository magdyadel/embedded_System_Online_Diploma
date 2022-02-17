/*
 * MainAlgo.c
 *
 *  Created on: Feb 10, 2022
 *      Author: Magdy Adel
 */
#include "MainAlgo.h"

//variables
static unsigned int MA_pVal ;
static unsigned int MA_threshold=20;

//STATE Pointer to function
void (*MA_state)();

STATE_define(MA_highPD)
{
	//state Name
	MA_state_id = MA_highPD;
	
	MA_pVal = SetPressureVal();
	if(MA_pVal > MA_threshold)
	{
		high_pressure_detected();
	}
	
}

