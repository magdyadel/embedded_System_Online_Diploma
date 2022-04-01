/*
 * uart.h
 *
 * Created: 3/27/2022 4:10:16 PM
 *  Author: MAGDY
 */ 


#ifndef UART_H_
#define UART_H_

#include "../../MemMap.h"
#include "../../Utils.h"
#include "../../StdTypes.h"



/*
* ===================================================================================
* 						APIs Supported by "UART"
* ===================================================================================
*/
void UART_Init(void);
void UART_Send(u8 data);
u8 UART_Receive(void);

void UART_SendNumberU32(u32 num);
u32 UART_ReceiveNumberU32(void);

void UART_SendString(char *data);
char * UART_ReceiveString(void);

#endif /* UART_H_ */