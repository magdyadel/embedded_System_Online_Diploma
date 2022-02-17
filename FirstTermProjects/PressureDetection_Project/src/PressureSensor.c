/*
 * PressureSensor.c
 *
 *  Created on: Feb 10, 2022
 *      Author: Magdy Adel
 */
#include "PressureSensor.h"
#include "driver.h"

//variables
static unsigned int PS_pVal;

//STATE Pointer to function
void (*PS_state)();

void PS_init()
{
	//init Pressure Sensor
	PS_state=STATE(PS_reading);
}


STATE_define(PS_reading)
{
	//state Name
	PS_state_id = PS_reading;

	//state Action
	//set Pressure Value
	PS_pVal = getPressureVal();

	PS_state=STATE(PS_waiting);
}

STATE_define(PS_waiting)
{
	//state Name
	PS_state_id = PS_waiting;

	//state Action
	Delay(60);
	//reset timer

	PS_state=STATE(PS_reading);
}
unsigned int SetPressureVal(void)
{
	return PS_pVal;
}

