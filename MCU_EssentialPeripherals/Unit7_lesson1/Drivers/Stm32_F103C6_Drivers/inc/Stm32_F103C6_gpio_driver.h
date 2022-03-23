/*
 * Stm32_F103C6_gpio_driver.h
 *
 *  Created on: Mar 22, 2022
 *      Author: Magdy
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_

//---------------------------------------------------------
//Includes
//---------------------------------------------------------
#include "stm32f103x6.h"


//---------------------------------------------------------
//User type definitions (structures)
//---------------------------------------------------------
typedef struct{
	uint16_t GPIO_PinNumber		;//Specifies the GPIO pins to be configure
								//this parameter must be set based on @ref GPIO_PINS_define
	uint8_t GPIO_MODE			;//Specifies the operation mode for the selected pins
								//this parameter must be set based on @ref GPIO_MODE_define
	uint8_t GPIO_OUTPUT_SPEED	;//Specifies the Speed for the selected pins
								//this parameter must be set based on @ref GPIO_SPEED_define
}GPIO_PinConfig_t;
//-------------------------end-----------------------------

//---------------------------------------------------------
//Macros Configuration References
//---------------------------------------------------------

//@ref GPIO_PINS_define
#define GPIO_PIN_0						((uint16_t)0x0001) /* PIN 0 selected	*/
#define GPIO_PIN_1						((uint16_t)0x0002) /* PIN 1 selected	*/
#define GPIO_PIN_2						((uint16_t)0x0004) /* PIN 2 selected	*/
#define GPIO_PIN_3						((uint16_t)0x0008) /* PIN 3 selected	*/
#define GPIO_PIN_4						((uint16_t)0x0010) /* PIN 4 selected	*/
#define GPIO_PIN_5						((uint16_t)0x0020) /* PIN 5 selected	*/
#define GPIO_PIN_6						((uint16_t)0x0040) /* PIN 6 selected	*/
#define GPIO_PIN_7						((uint16_t)0x0080) /* PIN 7 selected	*/
#define GPIO_PIN_8						((uint16_t)0x0100) /* PIN 8 selected	*/
#define GPIO_PIN_9						((uint16_t)0x0200) /* PIN 9 selected	*/
#define GPIO_PIN_10						((uint16_t)0x0400) /* PIN 10 selected	*/
#define GPIO_PIN_11						((uint16_t)0x0800) /* PIN 11 selected	*/
#define GPIO_PIN_12						((uint16_t)0x1000) /* PIN 12 selected	*/
#define GPIO_PIN_13						((uint16_t)0x2000) /* PIN 13 selected	*/
#define GPIO_PIN_14						((uint16_t)0x4000) /* PIN 14 selected	*/
#define GPIO_PIN_15						((uint16_t)0x8000) /* PIN 15 selected	*/
#define GPIO_PIN_All					((uint16_t)0xFFFF) /* All Pins selected	*/

#define GPIO_PIN_MASK					0x0000FFFFu /* PIN Mask for assert test */


//@ref GPIO_MODE_define
#define GPIO_MODE_Analog				0x00000000u //0: Analog mode
#define GPIO_MODE_INPUT_FLO				0x00000001u //1: Floating input (reset state)
#define GPIO_MODE_INPUT_PU				0x00000002u //2: Input with pull-up / pull-down
#define GPIO_MODE_INPUT_PD				0x00000003u //3: pull-down
#define GPIO_MODE_OUTPUT_PP				0x00000004u //4: General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD				0x00000005u //5: General purpose output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP			0x00000006u //6: Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD			0x00000007u //7: Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT					0x00000008u //8: Alternate function Input


//@ref GPIO_SPEED_define
#define GPIO_SPEED_10M					0x00000001u //1: Output mode, max speed 10 MHz.
#define GPIO_SPEED_2M					0x00000002u //2: Output mode, max speed 2 MHz.
#define GPIO_SPEED_50M					0x00000003u //3: Output mode, max speed 50 MHz.

// @ref GPIO_PIN_state
#define GPIO_PIN_SET					1
#define GPIO_PIN_RESET					0

//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_EN				1
#define GPIO_RETURN_LOCK_ERROR			0


//-------------------------end-----------------------------

//============================================================================================


/*
* ============================================================================================
* 							APIs Supported by "MCAL GPIO DRIVER"
* ============================================================================================
*/

void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx,uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t Value);
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);


#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
