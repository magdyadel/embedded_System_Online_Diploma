/*
 * ALARMACTUATORDRIVER.h
 *
 *  Created on: Feb 10, 2022
 *      Author: Magdy Adel
 */

#ifndef ALARMACTUATORDRIVER_H_
#define ALARMACTUATORDRIVER_H_

#include "state.h"

//Define states

enum{
	AA_alarmOFF,
	AA_alarmON,
	AA_waiting,
}AA_state_id;

//declare states functions Alarm Actuator
STATE_define(AA_alarmOFF);
STATE_define(AA_alarmON);
STATE_define(AA_waiting);

void AA_init();

//STATE Pointer to function
extern void (*AA_state)();

#endif /* ALARMACTUATORDRIVER_H_ */
