/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
void BSP_GPIO_PinCfg(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin, uint32_t GPIO_Mode, uint32_t GPIO_Pull, uint32_t GPIO_Speed, uint32_t GPIO_Alternate)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//Structure contenant les arguments de la fonction GPIO_Init

	GPIO_InitStructure.Pin = GPIO_Pin;
	GPIO_InitStructure.Mode = GPIO_Mode;
	GPIO_InitStructure.Pull = GPIO_Pull;
	GPIO_InitStructure.Speed = GPIO_Speed;
	GPIO_InitStructure.Alternate = GPIO_Alternate;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
}
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
void GPIO_LED_tests(){
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(LED7_PORT, LED7_PIN);
	  //HAL_GPIO_TogglePin(LED6_PORT, LED6_PIN);
	  HAL_GPIO_TogglePin(LED8_PORT, LED8_PIN);
	  HAL_GPIO_TogglePin(LED4_PORT, LED4_PIN);
}

void init_leds(){
	BSP_GPIO_PinCfg(BUTTON_USER1_PORT, BUTTON_USER1_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);
	//Button user2
	BSP_GPIO_PinCfg(BUTTON_USER2_PORT, BUTTON_USER2_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);

	//Config des leds
	BSP_GPIO_PinCfg(LED4_PORT, LED4_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);
	BSP_GPIO_PinCfg(LED6_PORT, LED6_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);
	BSP_GPIO_PinCfg(LED7_PORT, LED7_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);
	BSP_GPIO_PinCfg(LED8_PORT, LED8_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);

}
/* USER CODE END 1 */

/** Pinout Configuration
*/
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
