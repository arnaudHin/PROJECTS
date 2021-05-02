/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED4_PORT 					GPIOA
#define LED4_PIN 					GPIO_PIN_14
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

#define I2C5_SDA_PIN				GPIO_PIN_12
#define I2C5_SCL_PIN				GPIO_PIN_11
#define I2C5_PORT					GPIOA
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void BSP_GPIO_PinCfg(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin, uint32_t GPIO_Mode, uint32_t GPIO_Pull, uint32_t GPIO_Speed, uint32_t GPIO_Alternate);
void GPIO_LED_tests();
void init_leds();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
