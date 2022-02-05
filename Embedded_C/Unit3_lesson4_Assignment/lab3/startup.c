/* strtup.c
Eng.Magdy
*/

#include<stdint.h>

extern int main(void);
unsigned int _stack_top;

void Reset_Handler(void);

void Default_Handler(){
	Reset_Handler();
}
void NMI_Handler() __attribute__((weak, alias ("Default_Handler")));
void H_Fault_Handler() __attribute__((weak, alias ("Default_Handler")));


//Booking 1024 Byte located by .bss through un intialized array of int 256 element (256*4=1024)
static unsigned long Stack_top[256];

void (* const g_p_fn_Vectors[])() __attribute__((section(".vectors"))) =
{
	(void (*)()) ((unsigned long)Stack_top + sizeof(Stack_top)),
	&Reset_Handler,
	&NMI_Handler,
	&H_Fault_Handler,
};

extern unsigned int _E_text;
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;

void Reset_Handler(void)
{
	/* Copy data from ROM to RAM */
	unsigned int DATA_size = (unsigned char*) &_E_DATA - (unsigned char*) &_S_DATA;
	unsigned char* P_src= (unsigned char*) &_E_text;
	unsigned char* P_dst= (unsigned char*) &_S_DATA;
	for (int i = 0; i < DATA_size; i++)
	{
		*((unsigned char*)P_dst++) = *((unsigned char*)P_src++);
	}

	// init bss sectio in sram with zero
	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
	P_dst = (unsigned char*)&_S_bss;
	for (int i = 0; i < bss_size; i++)
	{
		*((unsigned char*)P_dst++) = (unsigned char)0;
	}
	
	main();
}