/*
 * dialog.h
 *
 *  Created on: 27 sept. 2020
 *      Author: Arnaud
 */

#ifndef APPLI_DIALOG_H_
#define APPLI_DIALOG_H_

#include "macro_types.h"
#include "stm32f4_uart.h"
#include "stm32f4xx_hal_def.h"


typedef void(*callback_dialog_send_byte_t)(uint8_t c);	//Type pointeur sur fonction


void DIALOG_DEMO(void);

void DIALOG_init(callback_dialog_send_byte_t callback);

void DIALOG_callback_send_byte(uint8_t c);


HAL_StatusTypeDef DIALOG_process_byte(uint8_t c, uint8_t ** pdatas);


/**
 * @brief	Cette fonction permet l'envoi d'un message sur la liaison série.
 * @pre		Le tableau datas doit contenir au moins 'size' octet. Sinon, le pointeur 'datas' peut être NULL.
 */
void DIALOG_send_packet(uint16_t size, uint8_t * datas);




#endif /* APPLI_DIALOG_H_ */
