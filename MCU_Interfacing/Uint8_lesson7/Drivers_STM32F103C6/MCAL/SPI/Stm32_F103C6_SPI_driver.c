/*
 * Stm32_F103C6_SPI_driver.c
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
#include "Stm32_F103C6_SPI_driver.h"


/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/
SPI_Config_t* Global_SPI_Config[2] = {NULL, NULL} ;
SPI_Config_t Global_SPI_Config1 ;
SPI_Config_t Global_SPI_Config2 ;
/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/
#define SPI1_Index				0
#define SPI2_Index				1

#define SPI_SR_TXE				((uint8_t)0x02)		//Transmit buffer empty
#define SPI_SR_RXNE				((uint8_t)0x01)		//Receive buffer Not empty

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
 * @Fn 				-	MCAL_SPI_Init
 * @brief 			-	Initialize SPI according to the specified parameters
 * @param[in]		-	SPIx: where x can be (1..2 depending on device used)
 * @param[in]		-	SPI_Config: All SPI Configuration EXTI_PinConfig_t
 * @retval 			-	none
 * Note 			-	Support for SPI full-duplex Master/Slave only & NSS HW/SW
 * 					-	in case of master you have to configure pin and drive it
 */
void MCAL_SPI_Init (SPI_TypeDef * SPIx, SPI_Config_t * SPI_Config )
{
	//Safety for registers
	uint16_t tmpreg_CR1 = 0;
	uint16_t tmpreg_CR2 = 0;

	if (SPIx == SPI1)
	{
		Global_SPI_Config1 = *SPI_Config;
		Global_SPI_Config[SPI1_Index] = &Global_SPI_Config1;
		RCC_SPI1_CLK_EN();

	}else if (SPIx == SPI2)
	{
		Global_SPI_Config2 = *SPI_Config;
		Global_SPI_Config[SPI2_Index] = &Global_SPI_Config2;
		RCC_SPI2_CLK_EN();
	}

	//Enable SPI Module
	//CR1 Bit 6 SPE: SPI enable
	tmpreg_CR1 = (0x1U<<6) ;

	//Enable MASTER/SLAVE
	tmpreg_CR1 |= SPI_Config->Device_MODE ;

	//SPI_Communication_Mode
	tmpreg_CR1 |= SPI_Config->Commnication_Mode ;

	//SPI_Frame_Format
	tmpreg_CR1 |= SPI_Config->Frame_Format ;

	//SPI_DATA_SIZE
	tmpreg_CR1 |= SPI_Config->DataSize ;

	//SPI_CLKPolarity
	tmpreg_CR1 |= SPI_Config->CLKPolarity ;

	//SPI_CLCPhase
	tmpreg_CR1 |= SPI_Config->CLKPhase ;

	//=====================NSS======================
	if (SPI_Config->NSS == SPI_NSS_HW_Master_SS_Output_EN)
	{
		tmpreg_CR2 |= SPI_Config->NSS ;

	}else if(SPI_Config->NSS == SPI_NSS_HW_Master_SS_Output_EN)
	{
		tmpreg_CR2 &= SPI_Config->NSS ;

	}else
	{
		tmpreg_CR1 |= SPI_Config->NSS ;
	}

	//SPI_BaudRatePrescaler
	tmpreg_CR1 |= SPI_Config->SPI_BaudRatePrescaler ;

	//SPI_IRQ_Enable
	if (SPI_Config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		tmpreg_CR2 |= SPI_Config->IRQ_Enable ;

		//Enable NVIC for SPIx IRQ
		if (SPIx == SPI1)
			NVIC_IRQ35_SPI1_Enable;
		else if (SPIx == SPI2)
			NVIC_IRQ36_SPI2_Enable;
	}

	SPIx->CR1 = tmpreg_CR1 ;
	SPIx->CR2 = tmpreg_CR2 ;

}


/**================================================================
 * @Fn 				-	MCAL_SPI_DeInit
 * @brief 			-	DeInitialize SPI
 * @param[in]		-	SPIx: where x can be (1..2 depending on device used)
 * @retval 			-	none
 * Note 			-	Reset the model by RCC
 */
void MCAL_SPI_DeInit (SPI_TypeDef * SPIx)
{
	if (SPIx == SPI1)
	{
		RCC_SPI1_Reset();
		NVIC_IRQ35_SPI1_Disable;
	}
	else if (SPIx == SPI2)
	{
		RCC_SPI2_Reset();
		NVIC_IRQ36_SPI2_Disable;
	}



}


/**================================================================
* @Fn				-MCAL_SPI_GPIO_Set_Pins
* @brief			-Initialize GPIO Pins
* @param [in] 		-SPIx: where x can be (1..2 depending on device used)
* @retval 			-None
* Note				-Should enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_SPI_Init()
*/
void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef * SPIx)
{
	GPIO_PinConfig_t PinCfg ;

	if(SPIx == SPI1)
	{
		//	PA4 : SPI1_NSS
		//	PA5 : SPI1_SCK
		//	PA6 : SPI1_MISO
		//	PA7 : SPI1_MOSI
		if(Global_SPI_Config[SPI1_Index]->Device_MODE == SPI_Device_MODE_Master)
		{
			//	PA4 : SPI1_NSS
			switch (Global_SPI_Config[SPI1_Index]->NSS)
			{
			case SPI_NSS_HW_Master_SS_Output_Disable:
				//HW Master/Slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;

			case SPI_NSS_HW_Master_SS_Output_EN:
				//HW Master/NSS Output enabled AF push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;
			}

			//	PA5 : SPI1_SCK
			//Master AF push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_5 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//	PA6 : SPI1_MISO (supported only full duplex)
			//full duplex / master Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//	PA7 : SPI1_MOSI
			//full duplex / master AF push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_7 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);


		}else //Slave
		{
			//	PA4 : SPI1_NSS
			if(Global_SPI_Config[SPI1_Index]->NSS == SPI_NSS_HW_Slave)
			{
				//HW Master/Slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

			//	PA5 : SPI1_SCK
			//Slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//	PA6 : SPI1_MISO (supported only full duplex)
			//full duplex /Slave AF push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_6 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//	PA7 : SPI1_MOSI
			//full duplex / Slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}


	}else if(SPIx == SPI2)
	{
		//	PB12 : SPI1_NSS
		//	PB13 : SPI1_SCK
		//	PB14 : SPI1_MISO
		//	PB15 : SPI1_MOSI
		if(Global_SPI_Config[SPI2_Index]->Device_MODE == SPI_Device_MODE_Master)
		{
			//	PB12 : SPI1_NSS
			switch (Global_SPI_Config[SPI2_Index]->NSS)
			{
			case SPI_NSS_HW_Master_SS_Output_Disable:
				//HW Master/Slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break;

			case SPI_NSS_HW_Master_SS_Output_EN:
				//HW Master/NSS Output enabled AF push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break;
			}

			//	PB13 : SPI1_SCK
			//Master AF push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_13 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//	PB14 : SPI1_MISO (supported only full duplex)
			//full duplex / master Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//	PB15 : SPI1_MOSI
			//full duplex / master AF push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_15 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);


		}else //Slave
		{
			//	PB12 : SPI1_NSS
			if(Global_SPI_Config[SPI2_Index]->NSS == SPI_NSS_HW_Slave)
			{
				//HW Master/Slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}

			//	PB13 : SPI1_SCK
			//Slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//	PB14 : SPI1_MISO (supported only full duplex)
			//full duplex /Slave AF push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_14 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//	PB15 : SPI1_MOSI
			//full duplex / Slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
	}
}


/**================================================================
 * @Fn 				-	MCAL_SPI_SendData
 * @brief 			-	Send buffer on SPI
 * @param[in]		-	SPIx: where x can be (1..2 depending on device used)
 * @param[in]		-	pRxBuffer: Buffer
 * @param[in]		-	PollingEn: Enable or Disable polling
 * @retval 			-	none
 * Note 			-	Should initialize SPI first
 */
void MCAL_SPI_SendData (SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum PollingMechanism PollingEn)
{
	if (PollingEn == PollingEnable)
		while(!(SPIx->SR & SPI_SR_TXE));

	SPIx->DR = *pTxBuffer ;
}


/**================================================================
* @Fn				-MCAL_SPI_ReceiveData
* @brief			-Receive Buffer on SPI
* @param [in] 		-SPIx: where x can be (1..2 depending on device used)
* @param [in] 		-pRxBuffer Buffer
* @param [in] 		-PollingEn Enable/Disable polling
* @retval 			-None
* Note				-None
*/
void MCAL_SPI_ReceiveData (SPI_TypeDef * SPIx, uint16_t *pRxBuffer, enum PollingMechanism PollingEn)
{
	if (PollingEn == PollingEnable)
		while(!(SPIx->SR & SPI_SR_RXNE));

	*pRxBuffer = SPIx->DR ;
}


/**================================================================
* @Fn				-MCAL_SPI_TX_RX
* @brief			-Send & Receive Buffer on SPI
* @param [in] 		-SPIx: where x can be (1..2 depending on device used)
* @param [in] 		-pTRxBuffer Buffer
* @param [in] 		-PollingEn Enable/Disable polling
* @retval 			-None
* Note				-None
*/
void MCAL_SPI_TX_RX (SPI_TypeDef * SPIx, uint16_t *pTRxBuffer, enum PollingMechanism PollingEn)
{
	//Transmit
	MCAL_SPI_SendData( SPIx, pTRxBuffer, PollingEn);

	//Receive
	MCAL_SPI_ReceiveData( SPIx, pTRxBuffer, PollingEn);
}





/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
void SPI1_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src ;
	irq_src.TXE = ( (SPI1->SR & (1<<1)) >>1 );
	irq_src.RXNE = ( (SPI1->SR & (1<<0)) >>1 );
	irq_src.ERRI = ( (SPI1->SR & (1<<4)) >>1 );

	Global_SPI_Config[SPI1_Index]->P_IRQ_CallBack(irq_src);
}

void SPI2_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src ;
	irq_src.TXE = ( (SPI2->SR & (1<<1)) >>1 );
	irq_src.RXNE = ( (SPI2->SR & (1<<0)) >>1 );
	irq_src.ERRI = ( (SPI2->SR & (1<<4)) >>1 );
	Global_SPI_Config[SPI2_Index]->P_IRQ_CallBack(irq_src);
}




