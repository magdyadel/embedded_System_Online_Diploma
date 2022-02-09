/*
 * fifo.c
 *
 *  Created on: Feb 7, 2022
 *      Author: Magdy
 */

#include "fifo.h"


FIFO_status FIFO_init(FIFO_Buff_t * fifo , element_type * buf, uint32_t length)
{
	if(buf == NULL)
		return FIFO_NULL;
	fifo->base =buf;
	fifo->head =buf;
	fifo->tail =buf;
	fifo->len=length;
	fifo->count=0;
	return FIFO_no_error;
}

FIFO_status FIFO_enqueue(FIFO_Buff_t * fifo , element_type item)
{
	//check FIFO is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_NULL;

	//check FIFO is full
	if(FIFO_isFull(fifo) == FIFO_full)
		return FIFO_full;

	//Enqueue Value
	*(fifo->head)=item;
	fifo->count++;

	/* Circular FIFO */

	if( fifo->head == ( fifo->base + (fifo->len * sizeof(element_type) ))) //to know head is MAX (0x0 + 5*1)=5
		fifo->head ==fifo->base;
	else
		fifo->head++;

	return FIFO_no_error;
}

FIFO_status FIFO_dequeue(FIFO_Buff_t * fifo , element_type* item)
{
	//check FIFO is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_NULL;

	//check FIFO is full
	if(fifo->count == 0)
		return FIFO_empty;

	//Dequeue Value
	*item = *(fifo->tail);
	fifo->count--;
	if( fifo->tail == ( fifo->base + (fifo->len * sizeof(element_type) ))) //to know head is MAX (0x0 + 5*1)=5
		fifo->tail == fifo->base ;
	else
		fifo->tail++;

	return FIFO_no_error;
}

FIFO_status FIFO_isFull(FIFO_Buff_t * fifo )
{
	//check FIFO is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_NULL;
	else if(fifo->count == fifo->len)
		return FIFO_full;
	else
		return FIFO_no_error;
}


void FIFO_print(FIFO_Buff_t * fifo )
{
	element_type* temp;
	int i;
	if(fifo->count == 0)
		printf("FIFO is Empty");
	else{
		temp=fifo->tail;
		printf("=====FIFO print====\n");
		for(i=0 ;i<fifo->count;i++)
		{
			printf("\t %X \n",*temp);
			temp++;
		}
		printf("==================\n");

	}

}

