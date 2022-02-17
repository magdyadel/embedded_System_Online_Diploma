/*
 * AlarmMonitor.c
 *
 *  Created on: Feb 10, 2022
 *      Author: Magdy Adel
 */
#include "AlarmMonitor.h"
#include "driver.h"
#include "MainAlgo.h"

//variables
int period_alarm = 60;  //20000 == 60sec

//STATE Pointer to function
void (*AM_state)();

void high_pressure_detected()
{
	AM_state=STATE(AM_alarmON);
}

STATE_define(AM_alarmOFF)
{
	//state Name
	AM_state_id = AM_alarmOFF;

	//state Action
	stopAlarm();
	
}


STATE_define(AM_alarmON)
{
	//state Name
	AM_state_id = AM_alarmON;

	//state Action
	startAlarm();
	//set alarm timer = 60sec

	AM_state=STATE(AM_waiting);
}

STATE_define(AM_waiting)
{
	//state Name
	AM_state_id = AM_waiting;

	//state Action
	Delay(period_alarm);

	AM_state=STATE(AM_alarmOFF);
}






