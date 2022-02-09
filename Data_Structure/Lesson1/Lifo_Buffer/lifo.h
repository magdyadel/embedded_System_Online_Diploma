/*
 * lifo.h
 *
 *  Created on: Feb 6, 2022
 *      Author: Kero
 */

#ifndef LIFO_H_
#define LIFO_H_

#include <stdio.h>
#include <stdlib.h>

//Type Definitions

typedef struct {
	unsigned int length;
	unsigned int count;
	unsigned int *base;
	unsigned int *head;
}LIFO_Buf_t;

typedef enum{
	LIFO_no_error,
	LIFO_full,
	LIFO_empty,
	LIFO_NULL
}LIFO_status;

//APIs
LIFO_status LIFO_PUSH_Item ( LIFO_Buf_t* lifoBuf, unsigned int item);
LIFO_status LIFO_POP_Item ( LIFO_Buf_t* lifoBuf,unsigned int* item);
LIFO_status LIFO_init ( LIFO_Buf_t* lifoBuf, unsigned int* buf, unsigned int len);


#endif /* LIFO_H_ */
