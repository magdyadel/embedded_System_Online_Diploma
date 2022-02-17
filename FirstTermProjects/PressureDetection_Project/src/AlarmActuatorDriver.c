/*
 * ALARMACTUATORDRIVER.c
 *
 *  Created on: Feb 10, 2022
 *      Author: Magdy Adel
 */
#include "AlarmActuatorDriver.h"
#include "driver.h"


//variables
int AA_speed=0;

//STATE Pointer to function
void (*AA_state)();

void stopAlarm()
{
	AA_state=STATE(AA_alarmOFF);
}
void startAlarm()
{
	AA_state=STATE(AA_alarmON);
}

// Initialize the alarm actuator
void AA_init()
{
	Set_Alarm_actuator(1);
}

STATE_define(AA_waiting)
{
	//state Name
	AA_state_id = AA_waiting;
}

STATE_define(AA_alarmOFF)
{
	//state Name
	AA_state_id = AA_alarmOFF;

	//state Action.....Set_Alarm_actuator(0)
	Set_Alarm_actuator(1);

	AA_state_id = AA_waiting;
}

STATE_define(AA_alarmON)
{
	//state Name
	AA_state_id = AA_alarmON;

	//state Action.....
	Set_Alarm_actuator(0);

	AA_state_id = AA_waiting;
}
