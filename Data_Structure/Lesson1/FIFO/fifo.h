/*
 * fifo.h
 *
 *  Created on: Feb 7, 2022
 *      Author: Magdy
 */

#ifndef FIFO_H_
#define FIFO_H_


#include <stdio.h>
#include <stdint.h>

/* User Configuration */
//Select element type (uint8_t, uint16_t, uint32_t,.... )
#define element_type uint8_t

//create buffer
#define width1 5
element_type uart_buff[width1];

//FIFO Data Types

typedef struct{
	unsigned int len;
	unsigned int count;
	element_type* base;
	element_type* head;
	element_type* tail;
}FIFO_Buff_t;

typedef enum{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_NULL
}FIFO_status;


//FIFO APIs
FIFO_status FIFO_init(FIFO_Buff_t * fifo , element_type * buf, uint32_t length);
FIFO_status FIFO_enqueue(FIFO_Buff_t * fifo , element_type item);
FIFO_status FIFO_dequeue(FIFO_Buff_t * fifo , element_type* item);
FIFO_status FIFO_isFull(FIFO_Buff_t * fifo );
void FIFO_print(FIFO_Buff_t * fifo );





#endif /* FIFO_H_ */
