/*
 * Stm32_F103C6_RCC_driver.h
 *
 *  Created on: Mar 23, 2022
 *      Author: Magdy
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_

/*
 *=======================================================================
 *								INCLUDES
 *=======================================================================
 *
*/
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"


/*
 *=======================================================================
 *						User type definitions (structures)
 *=======================================================================
 *
*/


/*
 *=======================================================================
 *						Macros Configuration References
 *=======================================================================
 *
*/
#define HSE_Clock							(uint32_t)16000000
#define HSI_RC_clk							(uint32_t)16000000


/*
* ===================================================================================
* 						APIs Supported by "MCAL RCC DRIVER"
* ===================================================================================
*/
uint32_t MCAL_RCC_GetSYSCLKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);


#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
