/**
 * @file : GPIOS.h
 * @brief :
 * @version
 * @date : May 10, 2021
 * @author: Arnaud
 */

#ifndef GPIO_H__
#define GPIO_H__

#include "main.h"
#include "stm32mp1xx_hal_gpio.h"

//////////////////////////////////////////////////////////////////////////////////
//				Define						//
//////////////////////////////////////////////////////////////////////////////////

#define LED5_PORT 					GPIOA
#define LED5_PIN 					GPIO_PIN_14
#define LED6_PORT 					GPIOA
#define LED6_PIN 					GPIO_PIN_13
#define LED7_PORT 					GPIOH
#define LED7_PIN 					GPIO_PIN_7
#define LED8_PORT 					GPIOD
#define LED8_PIN 					GPIO_PIN_11

#define BUTTON_USER1_PORT			GPIOA
#define BUTTON_USER1_PIN			GPIO_PIN_14
#define BUTTON_USER2_PORT			GPIOA
#define BUTTON_USER2_PIN			GPIO_PIN_13

//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////


typedef enum{
	LED5_GREEN=0,
	LED6_RED,
	LED7_ORANGE,
	LED8_BLUE
}LED_e;

//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn void GPIO_Init(void)
 * @brief
 * @pre
 * @post
 */
extern void GPIO_Init(void);

/**
 * @fn void BSP_GPIO_PinCfg(GPIO_TypeDef*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)
 * @brief
 * @param GPIOx
 * @param GPIO_Pin
 * @param GPIO_Mode
 * @param GPIO_Pull
 * @param GPIO_Speed
 * @param GPIO_Alternate
 */
extern void BSP_GPIO_PinCfg(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin, uint32_t GPIO_Mode, uint32_t GPIO_Pull, uint32_t GPIO_Speed, uint32_t GPIO_Alternate);

/**
 * @fn void ON_LED(LED_e)
 * @brief
 * @param led
 */
extern void ON_LED(LED_e led);

/**
 * @fn void OFF_LED(LED_e)
 * @brief
 * @param led
 */
extern void OFF_LED(LED_e led);

/**
 * @fn void TOGGLE_LED(LED_e)
 * @brief
 * @param led
 */
extern void TOGGLE_LED(LED_e led);



#endif /*GPIO_H__ */

