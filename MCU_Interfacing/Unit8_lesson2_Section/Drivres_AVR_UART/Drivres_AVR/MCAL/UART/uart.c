/*
 * uart.c
 *
 * Created: 3/27/2022 4:10:29 PM
 *  Author: MAGDY
 */ 
#include "uart.h"

void UART_Init(void)
{
	/*----- Baud rate----*/
	// 9600 at 8M HZ
	UBRRL = 51 ;
	CLEARBIT(UCSRA,U2X); //normal mode (16bit)
	
	/*----- Frame-----*/
	//no parity
	// 8 bit data is initial value by default

	
	/*----- Enable UART Peripheral ----*/
	SETBIT(UCSRB,TXEN);
	SETBIT(UCSRB,RXEN);
	
}


void UART_Send(u8 data)
{
	while(!READBIT(UCSRA,UDRE)); //UDRE: USART Data Register Empty (FLAG)
	UDR = data ;
}

u8 UART_Receive(void)
{
	while(!READBIT(UCSRA,RXC)); //RXC: USART Receive Complete (FLAG)
	return UDR ;
}


void UART_SendNumberU32(u32 num)
{
	//1-Send int num with shifting .......ex send(300) 4bytes [0,0,256,44]
	//UART_Send((u8)num);   //[0,0,0,256]
	//UART_Send((u8)num>>8);
	//UART_Send((u8)num>>16);
	//UART_Send((u8)num>>32);
	u8 *p = &num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
}

u32 UART_ReceiveNumberU32(void)
{
	//u8 take[4] ,i;
	//u32 num = 0 ;
	//for(i=3;i<=0;i--)
	//{
		//take[i]=UART_Receive();
		//num |= take[i];
	//}
	u32 num;
	u8 *p = &num;
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	return num;
}


void UART_SendString(char *data)
{
	while(*data != '\0')
	{
		UART_Send(*data);
		data++;
	}
}

char * UART_ReceiveString(void)
{
	char data[50],i=0;
	char get =UART_Receive();
	
	while(get!='#')
	{
		data[i]=get;
		get =UART_Receive();
		i++;
	}
	data[i]='\0';
	return data;
}