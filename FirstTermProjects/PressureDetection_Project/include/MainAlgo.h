/*
 * MainAlgo.h
 *
 *  Created on: Feb 10, 2022
 *      Author: Magdy Adel
 */

#ifndef MainAlgo_H_
#define MainAlgo_H_

#include "state.h"

//Define states

enum{
	MA_highPD,
}MA_state_id;

//declare states functions MA
STATE_define(MA_highPD);


//STATE Pointer to function
extern void (*MA_state)();

#endif /* MainAlgo_H_ */
