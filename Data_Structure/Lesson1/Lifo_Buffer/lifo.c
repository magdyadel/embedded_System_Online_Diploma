/*
 * lifo.c
 *
 *  Created on: Feb 6, 2022
 *      Author: Magdy
 */

#include "lifo.h"

LIFO_status LIFO_PUSH_Item (LIFO_Buf_t* lifoBuf, unsigned int item)
{
	//check LIFO is valid
	if(!lifoBuf->base || !lifoBuf->head)
		return LIFO_NULL;

	//check LIFO is fill
	if(lifoBuf->count == lifoBuf->length)
		return LIFO_full;

	//ADD Value
	*(lifoBuf->head)=item;
	lifoBuf->head++; //to point next head
	lifoBuf->count++;
	return LIFO_no_error;
}


LIFO_status LIFO_POP_Item (LIFO_Buf_t* lifoBuf, unsigned int* item)
{
	//check LIFO is valid
	if(!lifoBuf->base || !lifoBuf->head)
		return LIFO_NULL;

	//check LIFO is fill
	if(lifoBuf->count==0)
		return LIFO_empty;

	//POP Value
	lifoBuf->head--;
	*item = *(lifoBuf->head);
	lifoBuf->count--;
	return LIFO_no_error;
}

LIFO_status LIFO_init (LIFO_Buf_t* lifoBuf, unsigned int* buf, unsigned int len)
{
	if(buf == NULL)
		return LIFO_NULL;
	lifoBuf->base=buf;
	lifoBuf->head=buf;
	lifoBuf->length=len;
	lifoBuf->count=0;

	return LIFO_no_error;
}
