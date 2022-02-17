/*
 * AlarmMonitor.h
 *
 *  Created on: Feb 10, 2022
 *      Author: Magdy Adel
 */

#ifndef AlarmMonitor_H_
#define AlarmMonitor_H_

#include "state.h"

//Define states

enum{
	AM_alarmOFF,
	AM_alarmON,
	AM_waiting,
}AM_state_id;

//declare states functions AM
STATE_define(AM_alarmON);
STATE_define(AM_alarmOFF);
STATE_define(AM_waiting);

//STATE Pointer to function
extern void (*AM_state)();

#endif /* AlarmMonitor_H_ */
