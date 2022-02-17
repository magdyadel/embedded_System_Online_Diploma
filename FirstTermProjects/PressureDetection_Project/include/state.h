/*
 * state.h
 *
 *  Created on: Feb 10, 2022
 *      Author: Magdy Adel
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"
//Automatic STATE Function generated
#define STATE_define(_statFUN_) void ST_##_statFUN_()
#define STATE(_statFUN_) ST_##_statFUN_

//States Connection
unsigned int SetPressureVal(void);
void high_pressure_detected();
void startAlarm(void);
void stopAlarm(void);


#endif /* STATE_H_ */
