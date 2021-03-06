/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_EXTI_driver.h"
#include "Stm32_F103C6_USART_driver.h"
#include "Stm32_F103C6_SPI_driver.h"


#define MCU_Act_As_Master
//#define MCU_Act_As_Slave

void clock_init()
{
	//Enable Clock
	RCC_GPIOA_CLK_EN ();
	RCC_GPIOB_CLK_EN ();
	//Enable AFIO
	RCC_AFIO_CLK_EN ();
}



unsigned char ch ;
void SPI1_IRQ_Callback(struct S_IRQ_SRC irq_src)
{
#ifdef MCU_Act_As_Slave
	if (irq_src.RXNE)
	{
		ch = 0xf;
		MCAL_SPI_TX_RX(SPI1, &ch, Pollingenable);
		MCAL_UART_SendData(USART1, &ch, enable);
	}
#endif
}


void UART_IRQ_Callback(void)
{
#ifdef MCU_Act_As_Master
	MCAL_USART_ReceiveData(USART1, &ch, disable);
	MCAL_USART_SendData(USART1, &ch, enable);
	//Send to SPI
	MCAL_GPIO_WritePin(GPIOA, 4, 0);
	MCAL_SPI_TX_RX(SPI1, &ch, PollingEnable);
	MCAL_GPIO_WritePin(GPIOA, 4, 1);

#endif
}

int main(void)
{
	//================UART INIT=================
	USART_Config_t uartCFG;
	clock_init();
	uartCFG.BaudRate = USART_BaudRate_115200 ;
	uartCFG.HWFlowCtl = USART_HWFlowCtl_NONE ;
	uartCFG.IRQ_Enable = USART_IRQ_Enable_RXNEIE ;
	uartCFG.P_IRQ_CallBack = UART_IRQ_Callback ;
	uartCFG.Parity = USART_Parity_NONE ;
	uartCFG.Payload_Length = USART_Payload_Length_8B ;
	uartCFG.StopBits = USART_StopBits__1 ;
	uartCFG.USART_MODE = USART_MODE_TX_RX ;

	MCAL_USART_Init(USART1, &uartCFG);
	MCAL_USART_GPIO_Set_Pins(USART1);


	//SPI INIT
	SPI_Config_t SPI1CFG ;

	//Common configuration
	SPI1CFG.CLKPhase = SPI_CLKPhase_2EDGE_first_DataCapture ;
	SPI1CFG.CLKPolarity = SPI_CLKPolarity_HIGH_whenIdle ;
	SPI1CFG.DataSize = SPI_DataSize_8Bit ;
	SPI1CFG.Frame_Format = SPI_Frame_Format_MSB_TXFirst ;
	SPI1CFG.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8 ;

	#ifdef MCU_Act_As_Master
		SPI1CFG.Device_MODE = SPI_Device_MODE_Master ;
		SPI1CFG.IRQ_Enable = SPI_IRQ_Enable_NONE ;
		SPI1CFG.NSS = SPI_NSS_SW_internal_Set ;
		SPI1CFG.P_IRQ_CallBack = NULL ;
	#endif

	MCAL_SPI_Init(SPI1, &SPI1CFG);
	MCAL_SPI_GPIO_Set_Pins(SPI1);

	//Configure SS on PORTA Pin4 By GPIO
	GPIO_PinConfig_t PinCfg ;

	PinCfg.GPIO_PinNumber = GPIO_PIN_4;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	//Force the Slave Select (High) idle mide
	MCAL_GPIO_WritePin(GPIOA, 4, 1);

	#ifdef MCU_Act_As_Slave
		SPI1CFG.Device_Mode = SPI_Device_Mode_SLAVE;
		SPI1CFG.IRQ_Enable = SPI_IRQ_Enable_RXNEIE;
		SPI1CFG.NSS = SPI_NSS_Hard_Slave;
		SPI1CFG.P_IRQ_Callback = SPI1_IRQ_Callback;
	#endif

		MCAL_SPI_Init(SPI1, &SPI1CFG);
		MCAL_SPI_GPIO_Set_Pins(SPI1);
	while(1)
    {


    }

	return 0;
}
