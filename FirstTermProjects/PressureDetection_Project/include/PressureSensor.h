/*
 * PressureSensor.h
 *
 *  Created on: Feb 10, 2022
 *      Author: Magdy Adel
 */

#ifndef PressureSensor_H_
#define PressureSensor_H_

#include "state.h"

//Define states

enum{
	PS_reading,
	PS_waiting,
}PS_state_id;

//declare states functions PS
STATE_define(PS_reading);
STATE_define(PS_waiting);

void PS_init();

//STATE Pointer to function
extern void (*PS_state)();

#endif /* PressureSensor_H_ */
