/**
  ******************************************************************************
  * @file    ipcc.c
  * @brief   This file provides code for the configuration
  *          of the IPCC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <utils/IPCC.h>
#include "commun.h"


IPCC_HandleTypeDef hipcc;

DavidsonStatus_e IPCC_Init(void)
{

  hipcc.Instance = IPCC;
  return (DavidsonStatus_e) HAL_IPCC_Init(&hipcc);

}

void HAL_IPCC_MspInit(IPCC_HandleTypeDef* ipccHandle)
{

  if(ipccHandle->Instance==IPCC)
  {

    /* IPCC clock enable */
    __HAL_RCC_IPCC_CLK_ENABLE();

    /* IPCC interrupt Init */
    HAL_NVIC_SetPriority(IPCC_RX1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(IPCC_RX1_IRQn);
    HAL_NVIC_SetPriority(IPCC_TX1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(IPCC_TX1_IRQn);

  }
}

void HAL_IPCC_MspDeInit(IPCC_HandleTypeDef* ipccHandle)
{

  if(ipccHandle->Instance==IPCC)
  {

    /* Peripheral clock disable */
    __HAL_RCC_IPCC_CLK_DISABLE();

    /* IPCC interrupt Deinit */
    HAL_NVIC_DisableIRQ(IPCC_RX1_IRQn);
    HAL_NVIC_DisableIRQ(IPCC_TX1_IRQn);

  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
