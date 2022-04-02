/*
 * Stm32_F103C6_USART_driver.c
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
#include "Stm32_F103C6_USART_driver.h"


/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/
USART_Config_t* Global_USART_Config[3] = {NULL, NULL, NULL} ;

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
/**================================================================
 * @Fn 				-	MCAL_USART_Init
 * @brief 			-	Initialize USART (Support feature ASYNCH. Only)
 * @param[in]		-	USARTx: where x can be (1..3 depending on device used)
 * @param[in]		-	USART_Config: All USART Configuration EXTI_PinConfig_t
 * @retval 			-	none
 * Note 			-	Support for now Asynch mode & Clock 8Mhz
 */
void MCAL_USART_Init (USART_TypeDef * USARTx, USART_Config_t * USART_Config )
{
	uint32_t pclk ,BRR ;

	//enable the Clock for given USART peripheral
	if (USARTx == USART1)
	{
		Global_USART_Config[0] = USART_Config;
		RCC_USART1_CLK_EN();
	}
	else if (USARTx == USART2)
	{
		Global_USART_Config[1] = USART_Config;
		RCC_USART2_CLK_EN();
	}
	else if (USARTx == USART3)
	{
		Global_USART_Config[2] = USART_Config;
		RCC_USART3_CLK_EN();
	}

	//Enable USART Module
	//	Bit 13 UE: USART enable
	USARTx->CR1 |= (1<<13) ;

	//Enable TX/RX engines according to the USART_Mode Configuration item
	//USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR1 |= USART_Config->USART_MODE ;

	//PAYLOAD Width
	//USART_CR1 Bit 12 M: Word length
	USARTx->CR1 |= USART_Config->Payload_Length ;

	//Configuration of parity control bit fields
	//USART_CR1 Bit 9 PS: Parity selection----Bit 10 PCE: Parity control enable
	USARTx->CR1 |= USART_Config->Parity ;

	//Configure the number of stop bits
	//USART_CR2 Bit 13:12 STOP: STOP bits
	USARTx->CR1 |= USART_Config->StopBits ;

	//USART hardware flow control
	//USART_CR3 //Bit 9 CTSE: CTS enable------Bit 8 RTSE: RTS enable
	USARTx->CR1 |= USART_Config->HWFlowCtl ;

	//Configuration of BRR(Baudrate register)
	//PCLK1 for USART2,3
	//PCLK1 for USART1
	if (USARTx == USART1)
	{
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else
	{
		pclk = MCAL_RCC_GetPCLK1Freq();
	}
	BRR = USART_BRR_Register(pclk, USART_Config->BaudRate);
	USARTx->BRR = BRR;

	//ENABLE / DISABLE Interrupt
	//UASRT_CR1
	if (USART_Config->IRQ_Enable != USART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= USART_Config->IRQ_Enable ;

		//Enable NVIC for USARTx IRQ
		if (USARTx == USART1)
			NVIC_IRQ37_USART1_Enable;

		else if (USARTx == USART2)
			NVIC_IRQ38_USART2_Enable;

		else if (USARTx == USART3)
			NVIC_IRQ39_USART3_Enable;
	}
}


/**================================================================
 * @Fn 				-	MCAL_USART_DeInit
 * @brief 			-	DeInitialize USART (Support feature ASYNCH. Only)
 * @param[in]		-	USARTx: where x can be (1..3 depending on device used)
 * @retval 			-	none
 * Note 			-	Reset the model by RCC
 */
void MCAL_USART_DeInit (USART_TypeDef * USARTx)
{
	if (USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable;
	}
	else if (USARTx == USART2)
	{
		RCC_USART2_Reset();
		NVIC_IRQ38_USART2_Disable;
	}
	else if (USARTx == USART3)
	{
		RCC_USART3_Reset();
		NVIC_IRQ39_USART3_Disable;
	}
}


/**================================================================
* @Fn				-MCAL_USART_GPIO_Set_Pins
* @brief			-Initialize GPIO Pins
* @param [in] 		-USARTx: where x can be (1..3 depending on device used)
* @retval 			-None
* Note				-Should enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_USART_Init()
*/
void MCAL_USART_GPIO_Set_Pins (USART_TypeDef * USARTx)
{
	GPIO_PinConfig_t PinConfig;
	if (USARTx == USART1)
	{
		//PA9 TX
		PinConfig.GPIO_PinNumber = GPIO_PIN_9;
		PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinConfig);

		//PA10 Rx
		PinConfig.GPIO_PinNumber = GPIO_PIN_10;
		PinConfig.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinConfig);

		//PA11 CTS
		if (Global_USART_Config[0]->HWFlowCtl == USART_HWFlowCtl_CTS || Global_USART_Config[0]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_11;
			PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinConfig);
		}
		//PA12 RTS
		if (Global_USART_Config[0]->HWFlowCtl == USART_HWFlowCtl_RTS || Global_USART_Config[0]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_12;
			PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinConfig);
		}
	}

	else if (USARTx == USART2)
	{
		//PA2 TX
		PinConfig.GPIO_PinNumber = GPIO_PIN_2;
		PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinConfig);

		//PA3 Rx
		PinConfig.GPIO_PinNumber = GPIO_PIN_3;
		PinConfig.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinConfig);

		//PA0 CTS
		if (Global_USART_Config[1]->HWFlowCtl == USART_HWFlowCtl_CTS || Global_USART_Config[1]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_0;
			PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinConfig);
		}
		//PA1 RTS
		if (Global_USART_Config[1]->HWFlowCtl == USART_HWFlowCtl_RTS || Global_USART_Config[1]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_1;
			PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinConfig);
		}
	}

	else if (USARTx == USART3)
	{
		//PB10 TX
		PinConfig.GPIO_PinNumber = GPIO_PIN_10;
		PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinConfig);

		//PB11 Rx
		PinConfig.GPIO_PinNumber = GPIO_PIN_11;
		PinConfig.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB, &PinConfig);

		//PB13 CTS
		if (Global_USART_Config[2]->HWFlowCtl == USART_HWFlowCtl_CTS || Global_USART_Config[2]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_13;
			PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinConfig);
		}
		//PB14 RTS
		if (Global_USART_Config[2]->HWFlowCtl == USART_HWFlowCtl_RTS || Global_USART_Config[2]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_14;
			PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinConfig);
		}
	}

}


/**================================================================
 * @Fn 				-	MCAL_USART_SendData
 * @brief 			-	Send buffer on USART
 * @param[in]		-	USARTx: where x can be (1..3 depending on device used)
 * @param[in]		-	pTxBuffer: Buffer
 * @param[in]		-	PollingEn: Enable or Disable polling
 * @retval 			-	none
 * Note 			-	Should initialize USART first
 * 						When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
 * 						the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
 * 						because it is replaced by the parity.
 * 						When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
 */
void MCAL_USART_SendData (USART_TypeDef * USARTx, uint16_t *pTxBuffer, enum Polling_mechanism PollingEn)
{
	uint8_t i;
	i = (USARTx == USART1)?0 : (USARTx == USART2)?1 : 2 ;

	//wait until TXE flag is set in the SR (is empty)
	if (PollingEn == enable)
		while(! (USARTx->SR & 1<<7));

	//Check the USART_WordLength item for 8bit or 9bit in a frame
	if (Global_USART_Config[i]->Payload_Length == USART_Payload_Length_9B)
	{
		//This is 9bit data transfer
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);

	}else
	{
		//This is 8bit data transfer
		USARTx->DR = (*pTxBuffer & (uint16_t)0xFF);
	}
}


/**================================================================
* @Fn				-MCAL_USART_ReceiveData
* @brief			-Receive Buffer on USART
* @param [in] 		-USARTx: where x can be (1..3 depending on device used)
* @param [in] 		-pRxBuffer Buffer
* @param [in] 		-PollingEn Enable/Disable polling
* @retval 			-None
* Note				-None
*/
void MCAL_USART_ReceiveData (USART_TypeDef * USARTx, uint16_t *pRxBuffer, enum Polling_mechanism PollingEn)
{
	uint8_t i;
	i = (USARTx == USART1)?0 : (USARTx == USART2)?1 : 2 ;

	//wait until RXNE flag is set in the SR
	if (PollingEn == enable)
		while(! (USARTx->SR & 1<<5));

	//Check the USART_WordLength item for 8bit or 9bit in a frame
	if (Global_USART_Config[i]->Payload_Length == USART_Payload_Length_9B)
	{
		//This is 9bit data
		if (Global_USART_Config[i]->Parity == USART_Parity_NONE)
		{
			//no parity so All 9bit are considered data
			*((uint16_t*) pRxBuffer) = USARTx->DR ;

		}else
		{
			//Parity is used, so 8bit will be of user data and bit is parity
			*((uint16_t*) pRxBuffer) = ( USARTx->DR & (uint8_t)0xFF ) ;
		}

	}else
	{
		//This is 8bit data
		if (Global_USART_Config[i]->Parity == USART_Parity_NONE)
		{
			//no parity so All 8bit are considered data
			*((uint16_t*) pRxBuffer) = USARTx->DR ;

		}else
		{
			//Parity is used, so 7bit will be of user data and bit is parity
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0x7F );
		}

	}

}


/**================================================================
* @Fn				-MCAL_USART_WAIT_TC
* @brief			-Wait till all data is sent
* @param [in] 		-USARTx: where x can be (1..3 depending on device used)
* @retval 			-None
* Note				-None
*/
void MCAL_USART_WAIT_TC (USART_TypeDef * USARTx)
{
	//wait until TC flag is set in the SR
	while(! (USARTx->SR & 1<<6));
}



/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
void USART1_IRQHandler(void)
{
	Global_USART_Config[0]->P_IRQ_CallBack();
}

void USART2_IRQHandler(void)
{
	Global_USART_Config[1]->P_IRQ_CallBack();
}

void USART3_IRQHandler(void)
{
	Global_USART_Config[2]->P_IRQ_CallBack();
}





