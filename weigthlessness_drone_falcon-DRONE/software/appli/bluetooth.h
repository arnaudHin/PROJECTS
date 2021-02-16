/*
 * bluetooth.h
 *
 *  Created on: 22 mars 2020
 *      Author: martin
 */

#ifndef APPLI_BLUETOOTH_H_
#define APPLI_BLUETOOTH_H_

#include "stm32f4xx_hal.h"
#include "macro_types.h"
#include "stm32f4_uart.h"
#include "stm32f4_sys.h"
#include "dialog.h"
#include "drone_def.h"
#include "motors_control.h"



void BLUETOOTH_init(drone_data_t * drone_data);
void BLUETOOTH_envoi_trame7(uint8_t info1, uint8_t info2, uint8_t info3, uint8_t info4, uint8_t info5, uint8_t info6, uint8_t info7);
void BLUETOOTH_envoi_trame2(uint8_t info1, uint8_t info2);
void BLUETOOTH_envoi_trame3(uint8_t info1, uint8_t info2, uint8_t info3);
void BLUETOOTH_envoi_trame5(uint8_t info1, uint8_t info2, uint8_t info3, uint8_t info4, uint8_t info5);
void BLUETOOTH_envoi_caractere(uint8_t c);

char BLUETOOTH_reception_caractere(void);
uint8_t *BLUETOOTH_reception_trame(void);

void main_bluetooth ();
#endif /* APPLI_BLUETOOTH_H_ */
