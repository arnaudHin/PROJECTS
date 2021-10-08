/**
 * @file : PostmanSupervisor.h
 * @brief :
 * @version
 * @date : May 28, 2021
 * @author: Arnaud
 */


#ifndef POSTMANSUPERVISOR_H__
#define POSTMANSUPERVISOR_H__

#include <virt_uart.h>
#include "commun.h"


//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn DavidsonStatus_e PostmanSupervisor_Init()
 * @brief
 * @return
 */
extern DavidsonStatus_e PostmanSupervisor_Init();

/**
 * @fn void PostmanSupervisor_Write(uint8_t*, uint16_t)
 * @brief
 * @param buffer
 * @param bytesToSend
 */
extern void PostmanSupervisor_Write(uint8_t * buffer, uint16_t bytesToSend);


/**
 * @fn void PostmanSupervisor_Read(uint8_t*, uint16_t)
 * @brief
 * @param buffer
 * @param bytesToRead
 */
extern void PostmanSupervisor_Read(uint8_t * buffer, uint16_t bytesToRead);


/**
 * @fn bool PostmanSupervisor_Recept()
 * @brief
 * @return
 */
extern bool PostmanSupervisor_Recept();


/**
 * @fn void VIRT_UART0_RxCpltCallback(VIRT_UART_HandleTypeDef*)
 * @brief
 * @param huart
 */
void VIRT_UART0_RxCpltCallback(VIRT_UART_HandleTypeDef *huart);


/**
 * @fn void VIRT_UART1_RxCpltCallback(VIRT_UART_HandleTypeDef*)
 * @brief
 * @param huart
 */
void VIRT_UART1_RxCpltCallback(VIRT_UART_HandleTypeDef *huart);







#endif /* POSTMANSUPERVISOR_H__ */


