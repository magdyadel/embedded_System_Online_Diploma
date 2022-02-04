
#include <stdint.h>

//Register Address
#define RCC_Base 		0x40021000
#define GPIOA_Base 		0x40010800
#define RCC_APB2ENR 	*(volatile uint32_t*) (RCC_Base + 0x18)
#define GPIOA_CRH 		*(volatile uint32_t*) (GPIOA_Base + 0x04)
#define GPIOA_ODR	 	*(volatile uint32_t*) (GPIOA_Base + 0x0C)
#define RCC_IOPAEN 		(1<<2)	

typedef volatile unsigned int vuint32_t;
typedef union {
	vuint32_t all_fields;
	struct{
		vuint32_t reserved:13;
		vuint32_t P_13:1;
	} SPin;
}R_ODR_t;

volatile R_ODR_t * R_ODR = (volatile R_ODR_t*)(GPIOA_Base + 0x0C);
unsigned char g_variables[3]={1,2,3};
unsigned char const const_variables[3]={1,2,3};

int main(void)
{
	RCC_APB2ENR |=RCC_IOPAEN ;
	GPIOA_CRH &= 0xff0fffff;
	GPIOA_CRH |= 0x00200000;

	while(1)
	{
		R_ODR->SPin.P_13 =1;
		for(int i =0; i<5000;i++);
		R_ODR->SPin.P_13=0;
		for(int i =0; i<5000;i++);
	}
}
