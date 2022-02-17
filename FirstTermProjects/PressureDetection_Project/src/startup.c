/* strtup.c
Eng.Magdy Adel
*/

#include<stdint.h>


extern int main(void);
void Reset_Handler();
void Default_Handler()
{
	Reset_Handler();
}

void NMI_Handler() __attribute__((weak, alias("Default_Handler")));
void H_Fault_Handler() __attribute__((weak, alias("Default_Handler")));
void MM_Fault_Handler() __attribute__((weak, alias("Default_Handler")));
void Bus_Fault_Handler() __attribute__((weak, alias("Default_Handler")));
void Usage_Fault_Handler() __attribute__((weak, alias("Default_Handler")));

//Booking 1024 Byte located by .bss through un intialized array of int 256 element (256*4=1024B)
static unsigned long Stack_top[256];

void (*const g_p_fn_Vectors[])() __attribute__((section(".vectors"))) =
{
	(void (*)()) ((unsigned long)Stack_top + sizeof(Stack_top)),//SRAM_START+SRAM_SIZE= stack star || SRAM End
    &Reset_Handler,
    &NMI_Handler,
    &H_Fault_Handler,
    &MM_Fault_Handler,
    &Bus_Fault_Handler,
    &Usage_Fault_Handler
};


//Symbols for copying data from flash to sram 
extern unsigned int _E_text;
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;

void Reset_Handler(void)
{
	

	//copy data from FLASH to SRAM
	uint32_t DATA_SIZE = (uint8_t*)&_E_DATA - (uint8_t*)&_S_DATA;
	uint8_t* P_src = (uint8_t*)&_E_text;
	uint8_t* P_dis = (uint8_t*)&_S_DATA;
	for( int i=0 ; i<DATA_SIZE ; i++)
	{
		*((uint8_t*)P_dis++) = *((uint8_t*)P_src++);
	}

	//initialize .bss with 0
	uint32_t BSS_SIZE = (uint8_t*)&_E_bss - (uint8_t*)&_S_bss;
	P_dis = (uint8_t*)&_S_bss;
	for( int i=0 ; i<BSS_SIZE ; i++)
	{
		*((uint8_t*)P_dis++) = (uint8_t)0;
	}
	//call main
	main();
}