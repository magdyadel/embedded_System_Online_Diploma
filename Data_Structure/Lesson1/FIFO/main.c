/*
 * main.c
 *
 *  Created on: Feb 7, 2022
 *      Author: Magdy
 */

#include "fifo.h"

void main()
{
	element_type i ,temp=0;
	FIFO_Buff_t FIFO_UART ;

	//initial fifo
	if( FIFO_init( &FIFO_UART , uart_buff, 5 ) == FIFO_no_error)
		printf("FIFO Initial is.... Done \n");

	// Enqueue
	for(i=0;i<7;i++)
	{
		printf("FIFO Enqueue (%x) \n",i);
		if(FIFO_enqueue(&FIFO_UART, i) == FIFO_no_error)
				printf("\t FIFO Enqueue is.... Done \n");
		else
			printf("\t FIFO Enqueue is.... failed \n");
	}

	FIFO_print(&FIFO_UART);

	//Dequeue
	if(FIFO_dequeue(&FIFO_UART,&temp) == FIFO_no_error)
		printf("\t FIFO Dequeue (%x) \n",temp);
	else
		printf("\t FIFO Dequeue is.... failed \n");
	if(FIFO_dequeue(&FIFO_UART,&temp) == FIFO_no_error)
		printf("\t FIFO Dequeue (%x) \n",temp);
	else
		printf("\t FIFO Dequeue is.... failed \n");

	FIFO_print(&FIFO_UART);

}

