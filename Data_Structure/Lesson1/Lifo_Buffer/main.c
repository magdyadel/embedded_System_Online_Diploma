/*
 * main.c
 *
 *  Created on: Feb 6, 2022
 *      Author: Magdy
 */



#include "lifo.h"


unsigned int Buf1[5]; //5*4 =20Bytes  initialized in Data Memory

int main()
{
	unsigned char i ,temp;
	LIFO_Buf_t uart_lifo ,I2C_lifo;

	//static allocation
	LIFO_init(&uart_lifo, Buf1,5);

	//dynamic allocation
	unsigned int* Buf2 = (unsigned int *) malloc( 5 * sizeof(unsigned int) );   //initialized in heap
	LIFO_init(&I2C_lifo, Buf2, 5);

	for(i =0;i<5;i++)
	{
		if( LIFO_PUSH_Item(&uart_lifo, i) ==LIFO_no_error)
			printf("UART LIFO ADD : %d \n",i);
	}

	for(i =0;i<5;i++)
	{
		if( LIFO_POP_Item( &uart_lifo,  &temp) == LIFO_no_error)
			printf("UART LIFO get : %d \n",temp);
	}


	return 0;
}
