/*
 * Stm32_F103C6_gpio_driver.c
 *
 *  Created on: Mar 22, 2022
 *      Author: Magdy
 */

//---------------------------------------------------------
//Includes
//---------------------------------------------------------
#include "Stm32_F103C6_gpio_driver.h"

uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;
	}
}


/**=======================================================================
 * @Fn			-MCAL_GPIO_Init
 * @brief 		-Initializes GPIOx PINy according to the specified
 * 				 parameters in the PinConfig
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @param[in] 	-PinConfig: pointer to a GPIO_PinConfig_t structure that
 * 				 contains the configuration information for the specified
 * 				  GPIO PIN.
 *
 * @retval		-None
 *
 * Note			-STM32F103C6 MCU has GPIO A,B,C,D and E Modules but LQFP4
 *              	 package has only GPIO A,B and part of C AND D exported as
 *                external PINs from the MCU.
 */
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t *PinConfig)
{
	//Port configuration register low (GPIOx_CRL) Configure PINS from 0 till 7
	//Port configuration register low (GPIOx_CRh) Configure PINS from 8 till 15
	volatile uint32_t * configregister = NULL;
	uint8_t PIN_Config =0;

	configregister =(PinConfig-> GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL:&GPIOx->CRH;

	//clear MODEy[1:0] CNFy[1:0]
	(*configregister) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	//if Pin is output
	if( (PinConfig->GPIO_MODE==GPIO_MODE_OUTPUT_AF_OD)
			||(PinConfig->GPIO_MODE==GPIO_MODE_OUTPUT_AF_PP)
			||(PinConfig->GPIO_MODE==GPIO_MODE_OUTPUT_OD)
			||(PinConfig->GPIO_MODE==GPIO_MODE_OUTPUT_PP) )
	{
		//Set  CNFy[1:0] MODEy[1:0]
		PIN_Config =( (((PinConfig->GPIO_MODE - 4) << 2) | (PinConfig->GPIO_OUTPUT_SPEED)) &0x0f) ;
		(*configregister) |= ((PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
	}
	//if Pin is input
	else //MODE= 00: Input mode (reset state)
	{
		if( (PinConfig->GPIO_MODE==GPIO_MODE_INPUT_FLO) || (PinConfig->GPIO_MODE==GPIO_MODE_Analog) )
		{
			//Set  CNFy[1:0] MODEy[1:0]00
			PIN_Config =( (((PinConfig->GPIO_MODE ) << 2) | 0x0) &0x0f) ;
		}
		else if (PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT) //Consider it as input floating
		{
			PIN_Config =( (((GPIO_MODE_INPUT_FLO ) << 2) | 0x0) &0x0f) ;
		}
		else //PU PD Input
		{
			PIN_Config =( (((GPIO_MODE_INPUT_PU ) << 2) | 0x0) &0x0f) ;
			if( (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU) )
			{
				//PxODR=1 Input pull-up :Table 20. Port bit configuration table
				GPIOx->ODR |= PinConfig->GPIO_PinNumber ;
			}
			else
			{
				//PxODR=0 Input pull-up :Table 20. Port bit configuration table
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber) ;
			}
		}
	}
	//write on the CRL or CRH
	(*configregister) |= ((PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
}



/**=======================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief 		-Reset GPIOx PINy according to the specified
 * 				 parameters in the PinConfig
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @retval		-None
 *
 * Note			-None
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	//APB2 peripheral reset register (RCC_APB2RSTR)
	//Set and cleared by software.
	if(GPIOx==GPIOA)
	{
		RCC->APB2RSTR |= (1<<2); //Bit 2 IOPARST: I/O port A reset
		RCC->APB2RSTR &= ~(1<<2);

	}else if(GPIOx==GPIOB)
	{
		RCC->APB2RSTR |= (1<<3); //Bit 3 IOPARST: I/O port B reset
		RCC->APB2RSTR &= ~(1<<3);

	}else if(GPIOx==GPIOC)
	{
		RCC->APB2RSTR |= (1<<4); //Bit 4 IOPARST: I/O port C reset
		RCC->APB2RSTR &= ~(1<<4);

	}else if(GPIOx==GPIOD)
	{
		RCC->APB2RSTR |= (1<<5);//Bit 5 IOPARST: I/O port D reset
		RCC->APB2RSTR &= ~(1<<5);

	}else  if(GPIOx==GPIOE)
	{
		RCC->APB2RSTR |= (1<<6); //Bit 6 IOPARST: I/O port E reset
		RCC->APB2RSTR &= ~(1<<6);

	}
}




/**=======================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-Read specific PIN
 * 				 parameters in the PinConfig
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 * @param[in] 	-PinNumber: Set PinNumber according GPIO_PINS_define
 *
 * @retval		-the input pin value (two values based on @ref GPIO_PIN_state)
 *
 * Note			-None
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
	uint8_t bitstatus;
	if( ( GPIOx->IDR & PinNumber ) != (uint32_t)GPIO_PIN_RESET)
	{
		bitstatus =GPIO_PIN_SET;
	}else
	{
		bitstatus =GPIO_PIN_RESET;
	}
	return bitstatus;
}



/**=======================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief 		-Read the input PORT value
 * 				 parameters in the PinConfig
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 * @retval		-the input PORT value
 * Note			-None
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	uint16_t portValue;
	portValue = (uint16_t)GPIOx->IDR ;
	return portValue;
}


/**=======================================================================
 * @Fn			-MCAL_GPIO_WritePin
 * @brief 		-Write specific input PIN
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @param[in] 	-PinNumber: Set PinNumber according GPIO_PINS_define
 * @param[in] 	-Value: Pin Value
 *
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value)
{
	uint8_t bitstatus;
		if( Value != (uint32_t)GPIO_PIN_RESET)
		{
			//GPIOx->ODR |= PinNumber;
			//or
			GPIOx->BSRR |= (uint32_t)PinNumber;

		}else
		{
			GPIOx->BRR |= (uint32_t)PinNumber;
		}
}



/**=======================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief 		-Write on output PORT
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @param[in] 	-Value: Pin Value
 *
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t Value)
{
	GPIOx->ODR = Value;
}


/**=======================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief 		-Toggle the specified GPIO pin
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @param[in] 	-PinNumber: Set PinNumber according GPIO_PINS_define
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= PinNumber;
}


/**=======================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief 		-The locking mechanism aloows the IO configuration
 * 				 to be frozen
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @param[in] 	-PinNumber: Set PinNumber according GPIO_PINS_define
 * @retval		-OK, if pin Config is locked Or ERROR if pin not locked
 * 				 (OK & ERROR are defined @ref GPIO_RETURN_LOCK)
 * Note			-None
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	/*Bit 16 LCKK[16]: Lock key
	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	0: Port configuration lock key not active
	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	LOCK key writing sequence:
	Write 1
	Write 0
	Write 1
	Read 0
	Read 1 (this read is optional but confirms that the lock is active)
	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	Any error in the lock sequence will abort the lock.
	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	These bits are read write but can only be written when the LCKK bit is 0.
	0: Port configuration not locked
	1: Port configuration locked.*/
	volatile uint32_t tmp=1<<16;
	//set the LCKy
	tmp |=PinNumber;

	//Write 1
	GPIOx->LCKR =tmp;

	//Write 0
	GPIOx->LCKR =PinNumber;

	//Write 1
	GPIOx->LCKR =tmp;

	//Read 0
	tmp =GPIOx->LCKR;
	//Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOx->LCKR & 1<<16))
	{
		return GPIO_RETURN_LOCK_EN;

	}else
	{
		return GPIO_RETURN_LOCK_ERROR;
	}

}

