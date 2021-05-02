/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN 0 */

//#define BUFFER_RX_SIZE 128
//
//static UART_HandleTypeDef handleUart;
//static const USART_TypeDef typedefUart = USART2;
//static const IRQn_Type nvic_irqUart = USART2_IRQn;
//
//static uint8_t buffer_rx[BUFFER_RX_SIZE];
//static uint8_t buffer_rx_write_index;
//static uint32_t buffer_rx_read_index;
//static volatile uint8_t buffer_rx_data_ready;
//static volatile uint8_t uart_init;
//
//void UART_init(uint32_t baudrate){
//
//	buffer_rx_read_index = 0;
//	buffer_rx_write_index = 0;
//	buffer_rx_data_ready = 0;
//
//	handleUart.Instance = (USART_TypeDef*) &typedefUart;
//	handleUart.Init.BaudRate = baudrate;
//	handleUart.Init.WordLength = UART_WORDLENGTH_8B;
//	handleUart.Init.StopBits = UART_STOPBITS_1;
//	handleUart.Init.Parity = UART_PARITY_NONE;
//	handleUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//	handleUart.Init.Mode = UART_MODE_TX_RX;
//	handleUart.Init.OverSampling = UART_OVERSAMPLING_16;
//
//	HAL_UART_Init(&handleUart);
//
//	__HAL_UART_ENABLE(&handleUart);
//
//	HAL_NVIC_SetPriority(nvic_irqUart, 1, 1);
//	HAL_NVIC_EnableIRQ(nvic_irqUart);
//	HAL_UART_Receive_IT(&handleUart, &buffer_rx[buffer_rx_write_index], 1);
//
//	setvbuf(stdout, NULL, _IONBF, 0);
//	setvbuf(stderr, NULL, _IONBF, 0);
//	setvbuf(stdin, NULL, _IONBF, 0);
//
//
//	__HAL_RCC_GPIOD_CLK_ENABLE();		//Horloge des broches a utiliser
//	BSP_GPIO_PinCfg(GPIOD, GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF); //Configure Tx as AF
//	BSP_GPIO_PinCfg(GPIOD, GPIO_PIN_6, GPIO_MODE_AF, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH); //Configure Rx as AF
//
//	uart_init = 1;
//}
//
//
//uint8_t UART_data_ready(){
//	return buffer_rx_data_ready;
//}
//
//
///*
// * @brief	Fonction permettant de récupérer le prochain caractère reçu dans le buffer.
// * @ret 	Retourne le prochain caractère reçu. Ou 0 si rien n'a été reçu.
// * @post 	Le caractère renvoyé par cette fonction ne sera plus renvoyé.
// */
//uint8_t UART_get_next_byte(){
//
//	uint8_t ret;
//	if(!buffer_rx_data_ready){
//		return 0;
//	}
//
//	ret = buffer_rx[buffer_rx_read_index];
//	buffer_rx_read_index = (buffer_rx_read_index + 1) % BUFFER_RX_SIZE;
//
//	NVIC_DisableIRQ(nvic_irqUart);
//	if(buffer_rx_write_index == buffer_rx_read_index){
//		buffer_rx_data_ready = 0;
//	}
//	NVIC_EnableIRQ(nvic_irqUart);
//
//	return ret;
//}
//
//uint8_t UART_getc(){
//	return UART_get_next_byte();
//}



/* USER CODE END 0 */




//UART_HandleTypeDef huart4;
//
//
//
///* UART4 init function */
//void MX_UART4_Init(void)
//{
//
//  /* USER CODE BEGIN UART4_Init 0 */
//
//  /* USER CODE END UART4_Init 0 */
//
//  /* USER CODE BEGIN UART4_Init 1 */
//
//  /* USER CODE END UART4_Init 1 */
//  huart4.Instance = UART4;
//  huart4.Init.BaudRate = 115200;
//  huart4.Init.WordLength = UART_WORDLENGTH_8B;
//  huart4.Init.StopBits = UART_STOPBITS_1;
//  huart4.Init.Parity = UART_PARITY_NONE;
//  huart4.Init.Mode = UART_MODE_TX_RX;
//  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
//  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
//  huart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
//  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
//  if (HAL_UART_Init(&huart4) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  if (HAL_UARTEx_SetTxFifoThreshold(&huart4, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  if (HAL_UARTEx_SetRxFifoThreshold(&huart4, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  if (HAL_UARTEx_DisableFifoMode(&huart4) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN UART4_Init 2 */
//
//  /* USER CODE END UART4_Init 2 */
//
//}
//
//void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
//{
//
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
//  if(uartHandle->Instance==UART4)
//  {
//  /* USER CODE BEGIN UART4_MspInit 0 */
//
//  /* USER CODE END UART4_MspInit 0 */
//  if(IS_ENGINEERING_BOOT_MODE())
//  {
//  /** Initializes the peripherals clock
//  */
//    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_UART24;
//    PeriphClkInit.Uart24ClockSelection = RCC_UART24CLKSOURCE_PCLK1;
//    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
//    {
//      Error_Handler();
//    }
//
//  }
//
//    /* UART4 clock enable */
//    __HAL_RCC_UART4_CLK_ENABLE();
//
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    __HAL_RCC_GPIOH_CLK_ENABLE();
//    /**UART4 GPIO Configuration
//    PB9     ------> UART4_TX
//    PH14     ------> UART4_RX
//    */
//    GPIO_InitStruct.Pin = GPIO_PIN_9;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//    GPIO_InitStruct.Pin = GPIO_PIN_14;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
//    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
//
//  /* USER CODE BEGIN UART4_MspInit 1 */
//
//  /* USER CODE END UART4_MspInit 1 */
//  }
//}
//
//void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
//{
//
//  if(uartHandle->Instance==UART4)
//  {
//  /* USER CODE BEGIN UART4_MspDeInit 0 */
//
//  /* USER CODE END UART4_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_UART4_CLK_DISABLE();
//
//    /**UART4 GPIO Configuration
//    PB9     ------> UART4_TX
//    PH14     ------> UART4_RX
//    */
//    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);
//
//    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_14);
//
//  /* USER CODE BEGIN UART4_MspDeInit 1 */
//
//  /* USER CODE END UART4_MspDeInit 1 */
//  }
//}




/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
