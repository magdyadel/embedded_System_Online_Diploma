/* 
Eng.Magdy
*/
#include <stdint.h>

//Register Address
#define SYSCTL_RCGC2_R		(*((volatile unsigned long*)0x400FE108))
#define GPIO_PORTF_DIR_R	(*((volatile unsigned long*)0x40025400))		//DIR Register
#define GPIO_PORTF_DEN_R 	(*((volatile unsigned long*)0x4002551C))		//Enable Register
#define GPIO_PORTF_DATA_R 	(*((volatile unsigned long*)0x400253FC))		// DataRegister


int main()
{
	volatile unsigned long delay_count;
	SYSCTL_RCGC2_R = 0x20;
	//delay to make sure GPIOF is up running
	for(delay_count=0;delay_count<200;delay_count++);
	GPIO_PORTF_DIR_R |= 1<<3; 											//DiIR is output for pin3 port F
	GPIO_PORTF_DEN_R |= 1<<3;
	while(1)
	{
		GPIO_PORTF_DATA_R |= 1<<3;
		for(delay_count=0;delay_count<200000;delay_count++);
		GPIO_PORTF_DATA_R &= ~(1<<3);
		for(delay_count=0;delay_count<200000;delay_count++);

	}
	
	
	return 0;
}