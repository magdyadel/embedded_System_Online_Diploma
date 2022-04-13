/*
 * Stm32_F103C6_I2C_driver.c
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
#include "Stm32_F103C6_I2C_driver.h"


/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/
I2C_Config_t Global_I2C_Config[2] = {NULL ,NULL};




/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/
#define I2C1_INDEX		0
#define I2C2_INDEX		1


/*
 *=======================================================================
 *						GENERIC FUNCTIONS
 *=======================================================================
 *
*/
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState state)
{
	if(state == ENABLE)
	{
		I2Cx->I2C_CR1 |= I2C_CR1_ACK;
	}
	else
	{
		I2Cx->I2C_CR1 &= ~(I2C_CR1_ACK);
	}
}

void I2C_GenerateSTART (I2C_TypeDef * I2Cx, FunctionalState NewState, Repeated_Start start)
{
	if(start != repeated_start)
	{
		//check if the BUS is idle
		while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	}
	//Bit 8 START: Start generation
	//This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	//In Master Mode:
	//0: No Start generation
	//1: Repeated start generation
	//In Slave mode:
	//0: No Start generation
	//1: Start generation when the bus is free
	if(NewState != DISABLE)
	{
		/* Generate a start condition */
		I2Cx->I2C_CR1 |= I2C_CR1_START ;
	}else
	{
		/* Disable the start condition generation */
		I2Cx->I2C_CR1 &= ~(I2C_CR1_START) ;
	}

}

FlagStatus I2C_GetFlagStatus (I2C_TypeDef * I2Cx, Status flag)
{
	volatile uint32_t dummyRead ;
	FlagStatus bitStatus = RESET ;
	uint32_t flag1 =0 , flag2 = 0;
	uint32_t lastevent = 0;

	switch (flag)
	{
	case I2C_FLAG_BUSY:
	{
		//Bit 1 BUSY: Bus busy
		//0: No communication on the bus
		//1: Communication ongoing on the bus
		//– Set by hardware on detection of SDA or SCL low
		//– cleared by hardware on detection of a Stop condition.
		//It indicates a communication in progress on the bus. This information is still updated when
		//the interface is disabled (PE=0).
		if( (I2Cx->I2C_SR2) & (I2C_SR2_BUSY) )
			bitStatus = SET ;
		else
			bitStatus = RESET ;
		break;
	}
	case EV5:
	{
		//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
		//Bit 0 SB: Start bit (Master mode)
		//0: No Start condition
		//1: Start condition generated.
		//– Set when a Start condition generated.
		//– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//hardware when PE=0
		if( (I2Cx->I2C_SR1) & (I2C_SR1_SB) )
			bitStatus = SET ;
		else
			bitStatus = RESET ;
		break;
	}
	case EV6:
	{
		//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
		//Bit 1 ADDR: Address sent (master mode)/matched (slave mode)

		if( (I2Cx->I2C_SR1) & (I2C_SR1_ADDR) )
			bitStatus = SET ;
		else
			bitStatus = RESET ;

		//to clear ADDR field : cleared by reading SR1 register followed by reading SR2
		dummyRead = I2Cx->I2C_SR2 ;
		break;
	}

	case MASTER_BYTE_TRANSMITTING:
	{
		//read the I2Cx status register
		flag1 = I2Cx->I2C_SR1 ;
		flag2 = I2Cx->I2C_SR2 ;
		flag2 = flag2<<16 ;
		//get the last event value from I2C status register
		lastevent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF) ;
		//Check whether the last event value from I2C status register
		if( (lastevent & flag) == flag )
			bitStatus = SET ;
		else
			bitStatus = RESET ;

		break;
	}

	case EV8_1://EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	case EV8:
	{
		//Bit 7 TxE: Data register empty (transmitters)
		//0: Data register not empty
		//1: Data register empty
		if( (I2Cx->I2C_SR1) & (I2C_SR1_TXE) )
			bitStatus = SET ;
		else
			bitStatus = RESET ;

		break;
	}

	case EV7:
	{
		//Bit 6 RxNE: Data register not empty (receivers)
		//0: Data register empty
		//1: Data register not empty
		if( (I2Cx->I2C_SR1) & (I2C_SR1_RXNE) )
			bitStatus = SET ;
		else
			bitStatus = RESET ;

		break;
	}


	}

	return bitStatus ;
}

void  I2C_SendAddress (I2C_TypeDef * I2Cx, uint16_t Address, I2C_Direction Direction)
{
	//supported only 7Bit mode
	uint8_t index = (I2Cx==I2C1)? I2C1_INDEX:I2C2_INDEX ;
	if(Global_I2C_Config[index].I2C_Slave_Address.I2C_Addressing_Slave_mode == I2C_Addressing_Slave_mode_7Bit)
	{
		Address = (Address << 1 );
		if(Direction!=I2C_Direction_Transmitter)
		{
			/* Set the address bit 0 for read */
			Address |= 1<<0;
		}else
		{
			/* Reset the address bit 0 for write */
			Address &= ~(1<<0);
		}

	}else
	{
		//10bit not supported yet
	}

	/* Send the Address */
	I2Cx->I2C_DR = Address ;
}

void I2C_GenerateSTOP (I2C_TypeDef * I2Cx, FunctionalState NewState)
{
	if(NewState != DISABLE)
	{
		/* Generate a STOP condition */
		I2Cx->I2C_CR1 |= I2C_CR1_STOP ;
	}else
	{
		/* Disable the STOP condition generation */
		I2Cx->I2C_CR1 &= ~(I2C_CR1_STOP) ;
	}
}




/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
void MCAL_I2C_Init (I2C_TypeDef * I2Cx, I2C_Config_t * I2C_Config )
{
	uint16_t tmpReg = 0 , freqrange = 0 ;
	uint32_t pclk1 = 8000000 ;
	uint16_t result = 0;

	//enable RCC clock
	if (I2Cx == I2C1)
	{
		Global_I2C_Config[I2C1_INDEX] = *I2C_Config ;
		RCC_I2C1_CLK_EN();

	}else
	{
		Global_I2C_Config[I2C2_INDEX] = *I2C_Config ;
		RCC_I2C2_CLK_EN();
	}

	if (I2C_Config->I2C_Mode == I2C_Mode_I2C)
	{
		/*------------------------- INIT Timing --------------------------*/
		//---I2C_CR2 Bits 5:0 FREQ[5:0]: Peripheral clock frequency
		/* Get the I2Cx CR2 value */
		tmpReg = I2Cx->I2C_CR2 ;
		/*clear frequency FREQ[5:0] bits */
		tmpReg &= ~(I2C_CR2_FREQ_Msk) ;
		/* Get pclk1 frequency value */
		pclk1 = MCAL_RCC_GetPCLK1Freq();
		/* Set frequency  bits depending on pclk1 value */
		freqrange = (uint16_t)(pclk1 / 1000000) ;
		tmpReg |= freqrange ;
		/* Write to I2Cx CR2 */
		I2Cx->I2C_CR2 = tmpReg ;

		//• Configure the clock control registers (I2C_CCR)
		/* Disable the selected I2C peripheral to configure time */
		I2Cx->I2C_CR1 &= ~(I2C_CR1_PE) ;
		tmpReg = 0;
		/* configure speed in Standard mode */
		if ( (I2C_Config->I2C_ClockSpeed == I2C_SCLK_SM_50k) || (I2C_Config->I2C_ClockSpeed == I2C_SCLK_SM_100k) )
		{
			/* Standard mode speed calculate */
			//		Tclk/2 = CRR * Tpclk1
			//		CRR = Tclk / (2 * Tpclk1)
			//		CRR = Fpclk1 / (2 * I2C_ClockFrequency)
			result = (uint16_t)(pclk1 / (I2C_Config->I2C_ClockSpeed <<1) ) ;// *2 => <<1
			tmpReg |= result ;

			/* Write to I2Cx CCR */
			I2Cx->I2C_CCR = tmpReg ;

			/*------------------------- I2C_TRISE Configuration --------------------------*/
			// For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
			// If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			// therefore the TRISE[5:0] bits must be programmed with 09h.
			I2Cx->I2C_TRISE = freqrange + 1 ;

		}else
		{
			//FAST MODE Not supported yet
		}


		/*------------------------- I2C_CR1 Configuration --------------------------*/
		/* Get the I2Cx CR1 value */
		tmpReg = I2Cx->I2C_CR1 ;
		tmpReg |= (uint16_t)(I2C_Config->I2C_ACK_Control | I2C_Config->General_Call_Address_Detection
				| I2C_Config->I2C_Mode | I2C_Config->StretchMode) ;
		/* Write to I2Cx CR1 */
		I2Cx->I2C_CR1 = tmpReg ;


		/*------------------------- I2Cx OAR1 & I2Cx OAR2 Configuration --------------------------*/
		tmpReg = 0 ;
		if (I2C_Config->I2C_Slave_Address.Enable_Dual_ADD == 1)
		{
			tmpReg = I2C_OAR2_ENDUAL ;
			tmpReg |= I2C_Config->I2C_Slave_Address.Secondary_slave_address << I2C_OAR2_ADD2_Pos ;
			I2Cx->I2C_OAR2 = tmpReg ;
		}

		tmpReg = 0 ;
		tmpReg |= I2C_Config->I2C_Slave_Address.Primary_slave_address << 1 ;
		tmpReg |= I2C_Config->I2C_Slave_Address.I2C_Addressing_Slave_mode ;
		I2Cx->I2C_OAR1 = tmpReg ;


	}else
	{
		//SMBus Not supported yet
	}

	//Interrupt mode (Slave Mode) //Check callback pointer != NULL
	if(I2C_Config->P_Slave_Event_CallBack != NULL ) //that enable Slave IRQ States Mode
	{
		//Enable IRQ
		I2Cx->I2C_CR2 |= (I2C_CR2_ITERREN) ;
		I2Cx->I2C_CR2 |= (I2C_CR2_ITEVTEN) ;
		I2Cx->I2C_CR2 |= (I2C_CR2_ITBUFEN) ;
		if (I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable;
			NVIC_IRQ32_I2C1_ER_Enable;

		}else if (I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_Enable;
			NVIC_IRQ34_I2C2_ER_Enable;
		}

		I2Cx->I2C_SR1 = 0 ;
		I2Cx->I2C_SR2 = 0 ;
	}

	//Enable the selected I2C peripheral
	I2Cx->I2C_CR1 |= I2C_CR1_PE;

}


void MCAL_I2C_DeInit (I2C_TypeDef * I2Cx)
{
	if (I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_IRQ_Disable;
		NVIC_IRQ32_I2C1_ER_IRQ_Disable;
		RCC_I2C1_Reset();
	}
	else if (I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_IRQ_Disable;
		NVIC_IRQ34_I2C2_ER_IRQ_Disable;
		RCC_I2C2_Reset();
	}

}


void MCAL_I2C_GPIO_Set_Pins (I2C_TypeDef * I2Cx)
{
	GPIO_PinConfig_t PinCfg ;

	if(I2Cx == I2C1)
	{
		//	PB6 : I2C1_SCL
		//	PB7 : I2C1_SDA

		//	PB6 : I2C1_SCL
		PinCfg.GPIO_PinNumber = GPIO_PIN_6;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD ;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//	PB7 : I2C1_SDA
		PinCfg.GPIO_PinNumber = GPIO_PIN_7;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD ;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &PinCfg);


	}else if (I2Cx == I2C2)
	{
		//	PB10 : I2C1_SCL
		//	PB11 : I2C1_SDA

		//	PB10 : I2C1_SCL
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD ;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//	PB11 : I2C1_SDA
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD ;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
	}
}




void MCAL_I2C_Master_TX (I2C_TypeDef * I2Cx, uint16_t devAddr, uint8_t *dataOut,
		uint32_t dataLen, Stop_Condition Stop, Repeated_Start start)
{
	int i=0;
	//1- Set the START bit in the I2C_CR1 register to generate a Start condition
	I2C_GenerateSTART(I2Cx, ENABLE, start);

	//2- wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(I2C_GetFlagStatus(I2Cx, EV5));

	//3- Send Address
	I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Transmitter);//address

	//4- wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(I2C_GetFlagStatus(I2Cx, EV6));

	//5- Check TRA, BSUY, MSL, TXE flags
	while(I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANSMITTING));

	for (i = 0; i < dataLen; ++i)
	{
		//Write in the DR register the data to be sent
		I2Cx->I2C_DR = dataOut[i];
		//6- wait for EV8
		//EV8: TxE=1, shift register not empty, .data register empty, cleared by writing DR register
		while(I2C_GetFlagStatus(I2Cx, EV8));

	}

	//7- wait for EV8_2
	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	//	while(I2C_GetFlagStatus(I2Cx, EV8_2));

	if(Stop == With_Stop)
	{
		//8- Send Stop condition
		I2C_GenerateSTOP(I2Cx, ENABLE);
	}
}



void MCAL_I2C_Master_RX (I2C_TypeDef * I2Cx, uint16_t devAddr, uint8_t *dataOut,
		uint32_t dataLen, Stop_Condition Stop, Repeated_Start start)
{
	int i =0;
	uint8_t index = (I2Cx == I2C1) ? I2C1_INDEX : I2C2_INDEX;
	//1- Set the START bit in the I2C_CR1 register to generate a Start condition
	I2C_GenerateSTART(I2Cx, ENABLE, start);

	//2- wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(I2C_GetFlagStatus(I2Cx, EV5));

	//3- Send Address
	I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Receiver);//address

	//4- wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(I2C_GetFlagStatus(I2Cx, EV6));

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	if(dataLen)
	{
		//read data until Len be zero
		for (i = dataLen; i > 1; i--)
		{
			//wait until RXNE becomes 1
			while(I2C_GetFlagStatus(I2Cx, EV7));
			//read data from data register into buffer
			*dataOut = I2Cx->I2C_DR ;
			//increment the buffer address
			dataOut++;
		}
		I2C_AcknowledgeConfig(I2Cx, DISABLE);
	}

	if(Stop == With_Stop)
	{
		//8- Send Stop condition
		I2C_GenerateSTOP(I2Cx, ENABLE);
	}

	if(Global_I2C_Config[index].I2C_ACK_Control == I2C_ACK_Enable)
	{
		I2C_AcknowledgeConfig(I2Cx, ENABLE);
	}
}




void MCAL_I2C_SlaveSendData (I2C_TypeDef* I2Cx, uint8_t data)
{
	I2Cx->I2C_DR = data ;
}
uint8_t MCAL_I2C_SlaveReceiveData (I2C_TypeDef* I2Cx)
{
	return (uint8_t)I2Cx->I2C_DR;
}

/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
void I2C1_EV_IRQHandler(void)
{
	volatile uint32_t dummyRead ;
	I2C_TypeDef *I2Cx = I2C1;
	/* Interrupt handling for both master and slave mode of the device */
	uint32_t Temp_1, Temp_2, Temp_3;

	Temp_1 = I2Cx->I2C_CR2 & (I2C_CR2_ITEVTEN) ;// Event interrupt enable
	Temp_1 = I2Cx->I2C_CR2 & (I2C_CR2_ITBUFEN) ;// Buffer interrupt enable

	Temp_1 = I2Cx->I2C_SR1 & (I2C_SR1_STOPF) ;// Stop detection (slave mode)

	/* Handle Stop Condition Event */
	if(Temp_1 && Temp_3)
	{
		/* STOPF Cleared by software reading the SR1 register followed by a write in the CR1 register,
		 * i have already read SR1 in Temp_3
		 * then next statement i write to CR1
		 */
		I2Cx->I2C_CR1 = 0x0000;
		Global_I2C_Config[I2C1_INDEX].P_Slave_Event_CallBack(I2C_EV_STOP);
	}

	/********************************************************************/
	Temp_3 = I2Cx->I2C_SR1 &(I2C_SR1_ADDR);		//ADDR

	if(Temp_1 && Temp_3)
	{
		/* clear ADDR flag
		 * In slave mode, it is recommended to perform the complete clearing sequence (READ SR1 then READ SR2) after ADDR is set.
		 */

		/* Check master mode or slave mode */
		if(I2Cx->I2C_SR2 &(I2C_SR2_MSL))
		{ /* Master mode (Using polling mechanism not interrupt) */ }
		else
		{
			/* Slave mode */
			Global_I2C_Config[I2C1_INDEX].P_Slave_Event_CallBack(I2C_EV_ADDR_Matched);
		}
	}

	/********************************************************************/
	/* Handle TxE: Data register empty (Master request data from slave)--> slave_transmitter */
	Temp_3 = I2Cx->I2C_SR1 &(I2C_SR1_TXE);		// TXE

	if(Temp_1 && Temp_2 && Temp_3)				// In case TXE=1, ITEVTEN=1, ITBUFEN=1
	{
		/* Check master mode or slave mode */
		if(I2Cx->I2C_SR2 &(I2C_SR2_MSL))
		{ /* Master mode (Using polling mechanism not interrupt) */ }
		else
		{
			/* Slave mode */
			/* Check if slave in transmit mode */
			if(I2Cx->I2C_SR2 &(I2C_SR2_TRA))		//TRA: Transmitter/receiver: 1: Data bytes transmitted
			{
				Global_I2C_Config[I2C1_INDEX].P_Slave_Event_CallBack(I2C_EV_DATA_REQ);
			}
		}
	}

	/********************************************************************/
	/* Handle RxNE: Data register not empty (slave receive data)-->slave_Receiver */
	Temp_3 = I2Cx->I2C_SR1 &(I2C_SR1_RXNE);		// RXNE

	if(Temp_1 && Temp_2 && Temp_3)				// In case RXNE=1, ITEVTEN=1, ITBUFEN=1
	{
		/* Check master mode or slave mode */
		if(I2Cx->I2C_SR2 &(I2C_SR2_MSL))
		{ /* Master mode (Using polling mechanism not interrupt) */ }
		else
		{
			/* Slave mode */
			if(!(I2Cx->I2C_SR2 &(I2C_SR2_TRA)))		//TRA: Transmitter/receiver: 0: Data bytes received
			{
				Global_I2C_Config[I2C1_INDEX].P_Slave_Event_CallBack(I2C_EV_DATA_RCV);
			}
		}
	}
}

void I2C1_ER_IRQHandler(void)
{

}


void I2C2_EV_IRQHandler(void)
{

}
void I2C2_ER_IRQHandler(void)
{

}





