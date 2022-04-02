/*
 * Stm32_F103C6_RCC_driver.c
 *
 *  Created on: Mar 23, 2022
 *      Author: Magdy
 */


/*
 *=======================================================================
 *						INCLUDES
 *=======================================================================
 *
*/
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_RCC_driver.h"


/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/
//Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
//Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
const uint8_t APBPrescTable[8U] = {0, 0, 0, 0, 1, 2, 3, 4};//Shift 1 right == multiply by 2

//Bits 7:4 HPRE[3:0]: AHB prescaler
//Set and cleared by software to control AHB clock division factor.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const uint8_t AHBPrescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 1,
									2, 3, 4 ,5 ,6 ,7, 8, 9};//Shift 1 right == multiply by 2



/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/


/*
 *=======================================================================
 *						GENERIC FUNCTIONS
 *=======================================================================
 *
*/




/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
uint32_t MCAL_RCC_GetSYSCLKFreq(void)
{
	//	Bits 3:2 SWS[1:0]: System clock switch status
	//	Set and cleared by hardware to indicate which clock source is used as system clock.
	//	00: HSI oscillator used as system clock
	//	01: HSE oscillator used as system clock
	//	10: PLL used as system clock
	//	11: Not applicable
	switch ( (RCC->CFGR >>2) & 0b11)
	{
		case 0:
			return HSI_RC_clk ;
			break;

		case 1:
			//to do need to calculate it ----HSE user should specify it
			return HSE_Clock ;
			break;

		case 2:
			//to do need to calculate it PLLCLK and PLLMUL & PLL source MUX
			return 16000000 ;
			break;

	}
}


uint32_t MCAL_RCC_GetHCLKFreq(void)
{
	//	Bits 7:4 HPRE[3:0]: AHB prescaler
	return (MCAL_RCC_GetSYSCLKFreq() >> AHBPrescTable[(RCC->CFGR >> 4) & 0xF] ) ;//the first	shift is multiplication
}


uint32_t MCAL_RCC_GetPCLK1Freq(void)
{
	//	Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
	return (MCAL_RCC_GetHCLKFreq() >> APBPrescTable[(RCC->CFGR >> 8) & 0b111] ) ;//the first	shift is multiplication
}


uint32_t MCAL_RCC_GetPCLK2Freq(void)
{
	//	Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
	return (MCAL_RCC_GetHCLKFreq() >> APBPrescTable[(RCC->CFGR >> 11) & 0b111] ) ;//the first	shift is multiplication
}


/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/






