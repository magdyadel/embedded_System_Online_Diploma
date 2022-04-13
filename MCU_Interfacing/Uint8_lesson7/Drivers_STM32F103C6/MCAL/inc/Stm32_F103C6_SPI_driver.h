/*
 * Stm32_F103C6_SPI_driver.h
 *
 *  Created on: Mar 23, 2022
 *      Author: Magdy
 */

#ifndef INC_STM32_F103C6_SPI_DRIVER_H_
#define INC_STM32_F103C6_SPI_DRIVER_H_

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
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/
struct S_IRQ_SRC
{
	uint8_t TXE:1 ; //TX buffer empty interrupt.
	uint8_t RXNE:1 ; //RX buffer not empty interrupt.
	uint8_t ERRI:1 ; //Error interrupt.
	uint8_t Reserved:5 ;
};


/*
 *=======================================================================
 *				User type definitions (Configuration structures)
 *=======================================================================
 *
*/
typedef struct
{
	uint16_t Device_MODE			;//Specifies the SPI operating mode
									//this parameter must be set based on @ref SPI_Device_MODE_define

	uint16_t Commnication_Mode		;//Specifies the SPI bidirectional mode state
									//this parameter must be set based on @ref SPI_Commnication_Mode_define

	uint16_t Frame_Format			;//Specifies LSB Or MSB
									//this parameter must be set based on @ref SPI_Frame_Format_define

	uint16_t DataSize				;//Specifies the Data size
									//this parameter must be set based on @ref SPI_DataSize_define

	uint16_t CLKPolarity			;//Specifies the CLOCK Polarity
									//this parameter must be set based on @ref SPI_CLKPolarity_define

	uint16_t CLKPhase				;//Specifies the CLOCK Phase
									//this parameter must be set based on @ref SPI_CLKPhase_define

	uint16_t NSS					;//Specifies whether the NSS signal is managed by HW(NSS pin) or by SW sing bit enable
									//this parameter must be set based on @ref SPI_NSS_define

	uint16_t SPI_BaudRatePrescaler	;//Specifies the baud rate prescaler value which will be used to configure TX/RX SCK clock.
									//this parameter must be set based on @ref SPI_BaudRatePrescaler_define
									//@note the communication clock is derived from the master clock. the slave clock
									//doesn't need to be set. %Take Care% you have to configure RCC enter
									//the correct clock to APB2 >> to SPI.

	uint8_t IRQ_Enable				;//Enable or Disable UART IRQ TX/RX
									//this parameter must be set based on @ref SPI_IRQ_Enable_define

	void (* P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);	//Set the C Function() which will be called once the IRQ Happen

}SPI_Config_t;


/*
 *=======================================================================
 *						Macros Configuration References
 *=======================================================================
 *
*/
//@ref SPI_Device_MODE_define
#define SPI_Device_MODE_Slave					(0x00000000U)
#define SPI_Device_MODE_Master					(0x1U<<2) //CR1>> MSTR:1: Master configuration


//@ref SPI_Commnication_Mode_define
//CR1 Register
#define SPI_Direction_2Lines					(0x00000000U)
#define SPI_Direction_2Lines_RXOnly				(0x1U<<10) //Bit 10 RXONLY: Receive only
#define SPI_Direction_1Lines_RXOnly				(0x1U<<15) //Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_Direction_1Lines_TXOnly				((0x1U<<10) | (0x1U<<15)) //Bit 15 BIDIMODE: Bidirectional data mode enable & Bit 14 BIDIOE: Output enable in bidirectional mode


//@ref SPI_Frame_Format_define
//Bit 7 LSBFIRST: Frame format
#define SPI_Frame_Format_MSB_TXFirst			(0x00000000U)
#define SPI_Frame_Format_LSB_TXFirst			(0x1U<<7)


//@ref SPI_DataSize_define
//CR1. Bit 11 DFF: Data frame format
#define SPI_DataSize_8Bit						(0x00000000U)
#define SPI_DataSize_9Bit						(0x1U<<11)


//@ref SPI_CLKPolarity_define
//Bit1 CPOL: Clock polarity
#define SPI_CLKPolarity_LOW_whenIdle			(0x00000000U)
#define SPI_CLKPolarity_HIGH_whenIdle			(0x1U<<1)


//@ref SPI_CLKPhase_define
//Bit 0 CPHA: Clock phase
#define SPI_CLKPhase_1EDGE_first_DataCapture	(0x00000000U)
#define SPI_CLKPhase_2EDGE_first_DataCapture	(0x1U<<1)


//@ref SPI_NSS_define
//HardWare
//SPI_CR2 Bit 2 SSOE: SS output enable
#define SPI_NSS_HW_Slave						(0x00000000U)
#define SPI_NSS_HW_Master_SS_Output_EN			(0x1U<<2)
#define SPI_NSS_HW_Master_SS_Output_Disable		~(0x1U<<2)

//SW (Master or Slave)
#define SPI_NSS_SW_internal_Reset				(0x1U<<9)
#define SPI_NSS_SW_internal_Set					((0x1U<<9) | (0x1U<<8))


//@ref SPI_BaudRatePrescaler_define
//SPI_CR1 Bits 5:3 BR[2:0]: Baud rate control
#define SPI_BaudRatePrescaler_2					(0x00000000U)
#define SPI_BaudRatePrescaler_4					(0b001U << 3)
#define SPI_BaudRatePrescaler_8					(0b010U << 3)
#define SPI_BaudRatePrescaler_16				(0b011U << 3)
#define SPI_BaudRatePrescaler_32				(0b100U << 3)
#define SPI_BaudRatePrescaler_64				(0b101U << 3)
#define SPI_BaudRatePrescaler_128				(0b110U << 3)
#define SPI_BaudRatePrescaler_256				(0b111U << 3)

//@ref SPI_IRQ_Enable_define
//CR2
#define SPI_IRQ_Enable_NONE					(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE				(uint32_t)(0x1U<<7)//Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE				(uint32_t)(0x1U<<6)//Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE				(uint32_t)(0x1U<<5)//Bit 5 ERRIE: Error interrupt enable




enum PollingMechanism
{
	PollingEnable,
	PollingDisable
};

/*
* ===================================================================================
* 						APIs Supported by "MCAL SPI DRIVER"
* ===================================================================================
*/
void MCAL_SPI_Init (SPI_TypeDef * SPIx, SPI_Config_t * SPI_Config );
void MCAL_SPI_DeInit (SPI_TypeDef * SPIx);

void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef * SPIx);

void MCAL_SPI_SendData (SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum PollingMechanism PollingEn);
void MCAL_SPI_ReceiveData (SPI_TypeDef * SPIx, uint16_t *pRxBuffer, enum PollingMechanism PollingEn);

void MCAL_SPI_TX_RX (SPI_TypeDef * SPIx, uint16_t *pTRxBuffer, enum PollingMechanism PollingEn);

void MCAL_SPI_WAIT_TC (SPI_TypeDef * SPIx);




#endif /* INC_STM32_F103C6_SPI_DRIVER_H_ */
