/*
 * Stm32_F103C6_EXTI_driver.c
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
#include "Stm32_F103C6_EXTI_driver.h"


/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/
void (* GP_IRQ_CallBack[15])(void);


/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/
#define AFIO_GPIO_EXTI_Mapping(x)			( (x==GPIOA)?0:\
											  (x==GPIOB)?1:\
											  (x==GPIOC)?2:\
											  (x==GPIOD)?3:0 )


/*
 *=======================================================================
 *						GENERIC FUNCTIONS
 *=======================================================================
 *
*/

void Enable_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		break;

	}
}

void Disable_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		break;

	}
}

void EXTI_Update (EXTI_PinConfig_t * EXTI_Config)
{
	//1- Configure GPIO to be AF Input -->Floating INPUT

	GPIO_PinConfig_t PinCfg ;
	//Update the GPIO Pin to be Floating INPUT
	PinCfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_Port, &PinCfg);
	//=====================================================


	//2- UPDATE AFIO to Route between EXTI Line with PORT A,B,C,D

	uint8_t AFIO_EXTICR_Index = EXTI_Config->EXTI_PIN.ETI_InputLineNumber / 4;
	uint8_t AFIO_EXTICR_Position = (EXTI_Config->EXTI_PIN.ETI_InputLineNumber % 4) * 4 ;

	//clear four bit
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xf <<AFIO_EXTICR_Position);
	AFIO->EXTICR[AFIO_EXTICR_Index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port)& 0xf) << AFIO_EXTICR_Position);
	//=====================================================


	//3- Update Rising or falling Register

	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	if(EXTI_Config->Trigger_Case == EXTI_Trigger_RISING)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_FALLING)
	{
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	}
	//=====================================================


	//4- Update IRQ Handling CallBack

	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.ETI_InputLineNumber] =EXTI_Config->P_IRQ_CallBack;
	//=====================================================


	//5- Enable/Disable IRQ EXTI & NVIC

	if(EXTI_Config->IRQ_EN==EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber) ;
		Enable_NVIC (EXTI_Config->EXTI_PIN.ETI_InputLineNumber) ;
	}else
	{
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber) ;
		Disable_NVIC (EXTI_Config->EXTI_PIN.ETI_InputLineNumber) ;
	}
	//=====================================================

}



/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

/**================================================================
 * @Fn 				-	MCAL_EXTI_GPIO_DeInit
 * @brief 			-	Reset EXTI registers to their initial values and NVIC corresponding IRQ mask
 * @retval 			-	none
 * Note 			-	none
 */
void MCAL_EXTI_GPIO_DeInit (void)
{
	EXTI->IMR = 	0x00000000 ;
	EXTI->EMR = 	0x00000000 ;
	EXTI->RTSR = 	0x00000000 ;
	EXTI->FTSR =	0x00000000 ;
	EXTI->SWIER = 	0x00000000 ;
	EXTI->PR = 		0xFFFFFFFF ; //rc_w1 cleared by writing a '1' into the PR

	//Disable EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_Disable ;
	NVIC_IRQ7_EXTI1_Disable ;
	NVIC_IRQ8_EXTI2_Disable ;
	NVIC_IRQ9_EXTI3_Disable  ;
	NVIC_IRQ10_EXTI4_Disable ;
	NVIC_IRQ23_EXTI5_9_Disable ;
	NVIC_IRQ40_EXTI10_15_Disable ;
}

/**================================================================
 * @Fn 				-	MCAL_EXTI_GPIO_Init
 * @brief 			-	Initializes GPIO pin to be used with EXTI according to the specified parameters in pinConfig
 * @param [in] 		- 	EXTI_Config : includes pin configuration for EXTI
 * 									  set by @ref EXTI_DEFINE , @ref EXTI_TRIGGER_DEFINE and @ref EXTI_IRQ_DEFINE
 * @retval 			-	none
 * Note 			-	STM32f103c6 MCU has GPIO A,B,B,D,E modules
 *                      but LQFP48 Package has only A,B, Part of C,D
 *                      Also mandatory to enable RCC clock for AFIO and the corresponding GPIO
 */
void MCAL_EXTI_GPIO_Init (EXTI_PinConfig_t * EXTI_Config)
{
	EXTI_Update(EXTI_Config);
}

/**================================================================
 * @Fn 				-	MCAL_EXTI_GPIO_Update
 * @brief 			-	Update GPIO pin to be used with EXTI according to the specified parameters in pinConfig
 * @param [in] 		- 	EXTI_Config :includes pin configuration for EXTI
 * 									 set by @ref EXTI_DEFINE , @ref EXTI_TRIGGER_DEFINE and @ref EXTI_IRQ_DEFINE
 * @retval 			-	none
 * Note 			-	none
 */

void MCAL_EXTI_GPIO_Update (EXTI_PinConfig_t * EXTI_Config)
{
	EXTI_Update(EXTI_Config);
}



/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
void EXTI0_IRQHandler (void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1<<0 ;
	//Call IRQ_CallBack
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler (void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1<<1 ;
	//Call IRQ_CallBack
	GP_IRQ_CallBack[1]();
}

void EXTI2_IRQHandler (void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1<<2 ;
	//Call IRQ_CallBack
	GP_IRQ_CallBack[2]();
}

void EXTI3_IRQHandler (void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1<<3 ;
	//Call IRQ_CallBack
	GP_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler (void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1<<4 ;
	//Call IRQ_CallBack
	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler (void)
{
	if(EXTI->PR & 1 << 5)	{EXTI->PR |= (1 << 5) 	;GP_IRQ_CallBack[5]()	;	}
	if(EXTI->PR & 1 << 6)	{EXTI->PR |= (1 << 6) 	;GP_IRQ_CallBack[6]()	;	}
	if(EXTI->PR & 1 << 7)	{EXTI->PR |= (1 << 7) 	;GP_IRQ_CallBack[7]()	;	}
	if(EXTI->PR & 1 << 8)	{EXTI->PR |= (1 << 8) 	;GP_IRQ_CallBack[8]()	;	}
	if(EXTI->PR & 1 << 9)	{EXTI->PR |= (1 << 9) 	;GP_IRQ_CallBack[9]()	;	}
}

void EXTI15_10_IRQHandler (void)
{
	if(EXTI->PR & 1 << 10)	{EXTI->PR |= (1 << 10) 	;GP_IRQ_CallBack[10]()	;	}
	if(EXTI->PR & 1 << 11)	{EXTI->PR |= (1 << 11) 	;GP_IRQ_CallBack[11]()	;	}
	if(EXTI->PR & 1 << 12)	{EXTI->PR |= (1 << 12) 	;GP_IRQ_CallBack[12]()	;	}
	if(EXTI->PR & 1 << 13)	{EXTI->PR |= (1 << 13) 	;GP_IRQ_CallBack[13]()	;	}
	if(EXTI->PR & 1 << 14)	{EXTI->PR |= (1 << 14) 	;GP_IRQ_CallBack[14]()	;	}
	if(EXTI->PR & 1 << 15)	{EXTI->PR |= (1 << 15) 	;GP_IRQ_CallBack[15]()	;	}
}






