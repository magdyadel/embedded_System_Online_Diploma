/*
 * main.c
 *
 *  Created on: Feb 10, 2022
 *      Author: Magdy Adel
 */

#include "AlarmActuatorDriver.h"
#include "AlarmMonitor.h"
#include "MainAlgo.h"
#include "PressureSensor.h"
#include "driver.h"

void setup()
{
	//init BLOCK
	GPIO_INITIALIZATION();

	//init
	PS_init();
	AA_init();
	//Set States pointers for each Block
	MA_state = STATE(MA_highPD);
	AM_state = STATE(AM_alarmOFF);
	AA_state = STATE(AA_waiting);

}

int main(void)
{

	setup();

	while(1)
	{
		//Implement your Design
		PS_state();
		MA_state();
		AM_state();
		AA_state();
	}
}



