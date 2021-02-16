/**
 * UART.h
 *
 *  Created on: 29 oct. 2013
 *      Author: spoiraud
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_hal.h"
	#include "macro_types.h"

	typedef enum
	{
		UART1_ID = 0,
		UART2_ID,
		UART3_ID,
		UART4_ID,
		UART5_ID,
		UART6_ID,
		UART_ID_NB
	}uart_id_e;

	//Initialise l'UART uart_id
	void UART_init(uart_id_e uart_id, uint32_t baudrate);

	//Deinitialise l'UART uart_id
	void UART_DeInit(uart_id_e uart_id);

	//Renvoi le dernier caractere recu ou 0 si pas de caractere disponible
	uint8_t UART_getc(uart_id_e uart_id);

	//Envoi d'un caractere sur l'UART uart_id
	void UART_putc(uart_id_e uart_id, uint8_t c);

	//Pour savoir si une donnée a été reçue sur l'UART uart_id
	bool_e UART_data_ready(uart_id_e uart_id);

	//Pour lire la dernière donnée reçue sur l'UART uart_id
	uint8_t UART_get_next_byte(uart_id_e uart_id);

	//Fonction blocante de test pour montrer une utilisation de ce module logiciel
	void UART_test(void);


#endif /* UART_H_ */
