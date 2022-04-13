/*
 * Stm32_F103C6_USART_driver.h
 *
 *  Created on: Mar 23, 2022
 *      Author: Magdy
 */

#ifndef INC_STM32_F103C6_USART_DRIVER_H_
#define INC_STM32_F103C6_USART_DRIVER_H_

/*
 *=======================================================================
 *								INCLUDES
 *=======================================================================
 *
*/
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_RCC_driver.h"

/*
 *=======================================================================
 *				User type definitions (Configuration structures)
 *=======================================================================
 *
*/
typedef struct{
	uint8_t USART_MODE			;//Specifies TX/RX Enable\Disable
								//this parameter must be set based on @ref USART_MODE_define

	uint8_t BaudRate			;//This member configures the UART communication baud rate
								//this parameter must be set based on @ref USART_BaudRate_define

	uint8_t Payload_Length		;//Specifies the number of data bits transmitted or received in a frame.
								//this parameter must be set based on @ref USART_Payload_Length_define

	uint8_t Parity				;//Specifies the Parity Mode
								//this parameter must be set based on @ref USART_Parity_define

	uint8_t StopBits			;//Specifies the number of stop bits transmitted
								//this parameter must be set based on @ref USART_StopBits_define

	uint8_t HWFlowCtl			;//Specifies whether the hardware flow control mode is enable/disable
								//this parameter must be set based on @ref USART_HWFlowCtl_define

	uint8_t IRQ_Enable			;//Enable or Disable UART IRQ TX/RX
								//this parameter must be set based on @ref USART_IRQ_Enable_define

	void (* P_IRQ_CallBack)(void);			//Set the C Function() which will be called once the IRQ Happen

}USART_Config_t;


/*
 *=======================================================================
 *						Macros Configuration References
 *=======================================================================
 *
*/
//@ref USART_MODE_define
#define USART_MODE_RX						(uint32_t)(1<<2) //Bit 2 RE: Receiver enable
#define USART_MODE_TX						(uint32_t)(1<<3) //Bit 3 TE: Transmitter enable
#define USART_MODE_TX_RX					(uint32_t)((1<<2) | (1<<3))

//@ref USART_BaudRate_define
#define USART_BaudRate_2400					2400
#define USART_BaudRate_9600					9600
#define USART_BaudRate_19200				19200
#define USART_BaudRate_57600				57600
#define USART_BaudRate_115200				115200
#define USART_BaudRate_230400				230400
#define USART_BaudRate_460800				460800
#define USART_BaudRate_921600				921600
#define USART_BaudRate_2250000				2250000
#define USART_BaudRate_4500000				4500000

//@ref USART_Payload_Length_define
//Bit 12 M: Word length
#define USART_Payload_Length_8B				(uint32_t)(0)		 //0: 1 Start bit, 8 Data bits, n Stop bit
#define USART_Payload_Length_9B				(uint32_t)(1<<12)//1: 1 Start bit, 9 Data bits, n Stop bit

//@ref USART_Parity_define
//Bit 9 PS: Parity selection----Bit 10 PCE: Parity control enable
#define USART_Parity_NONE					(uint32_t)(0)
#define USART_Parity_EVEN					(uint32_t)(1<<10)
#define USART_Parity_ODD					(uint32_t)((1<<10) | (1<<9))

//@ref USART_StopBits_define
//Bits 13:12 STOP: STOP bits
#define USART_StopBits__half				(uint32_t)(1<<12)
#define USART_StopBits__1					(uint32_t)(0)
#define USART_StopBits__1_half				(uint32_t)(3<<12)
#define USART_StopBits__2					(uint32_t)(2<<12)

//@ref USART_HWFlowCtl_define
//Bit 9 CTSE: CTS enable------Bit 8 RTSE: RTS enable
#define USART_HWFlowCtl_NONE				(uint32_t)(0)
#define USART_HWFlowCtl_RTS					(uint32_t)(1<<8)
#define USART_HWFlowCtl_CTS					(uint32_t)(1<<9)
#define USART_HWFlowCtl_RTS_CTS				(uint32_t)(1<<8 | 1<<9)

//@ref USART_IRQ_Enable_define
//Table 196. USART interrupt requests
#define USART_IRQ_Enable_NONE				(uint32_t)(0)
#define USART_IRQ_Enable_TXE				(uint32_t)(1<<7) //Transmit data register empty
#define USART_IRQ_Enable_TC					(uint32_t)(1<<6) //Transmission complete
#define USART_IRQ_Enable_RXNEIE				(uint32_t)(1<<5) //Received data ready to be read & Overrun error detected
#define USART_IRQ_Enable_PE					(uint32_t)(1<<8) //Parity error


enum Polling_mechanism
{
	enable,
	disable
};


//BaudRate Calculation
//USARTDIV = fclk / (16 * BaudRate)
//USARTDIV_MUL100 = uint32_t((100 * fclk) / (16 * BaudRate) == (25 * fclk) / (4 * BaudRate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV) * 100
//DIV_Mantissa = Integer Part (USARTDIV)
//DIV_Fraction = ( (USARTDIV_MUL100 - DIV_Mantissa_MUL100) * 16) /100

#define USARTDIV(_PCLK_, _BAUD_)						(uint32_t) (_PCLK_ / (16 * _BAUD_))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)					(uint32_t) (25 * _PCLK_ / (4 * _BAUD_))
#define Mantissa_MUL100(_PCLK_, _BAUD_)					(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)						(uint32_t) (USARTDIV(_PCLK_, _BAUD_))
#define DIV_Fraction(_PCLK_, _BAUD_)					(uint32_t) (( (USARTDIV_MUL100(_PCLK_, _BAUD_) - Mantissa_MUL100(_PCLK_, _BAUD_)) * 16) /100)
#define USART_BRR_Register(_PCLK_, _BAUD_)				((Mantissa(_PCLK_, _BAUD_)) << 4) | ( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )



/*
* ===================================================================================
* 						APIs Supported by "MCAL USART DRIVER"
* ===================================================================================
*/
void MCAL_USART_Init (USART_TypeDef * USARTx, USART_Config_t * USART_Config );
void MCAL_USART_DeInit (USART_TypeDef * USARTx);

void MCAL_USART_GPIO_Set_Pins (USART_TypeDef * USARTx);

void MCAL_USART_SendData (USART_TypeDef * USARTx, uint16_t *pTxBuffer, enum Polling_mechanism PollingEn);
void MCAL_USART_ReceiveData (USART_TypeDef * USARTx, uint16_t *pRxBuffer, enum Polling_mechanism PollingEn);

void MCAL_USART_WAIT_TC (USART_TypeDef * USARTx);




#endif /* INC_STM32_F103C6_USART_DRIVER_H_ */
