/**
 * @file IntercoreProtocol.h
 * @brief Ce fichier permet d'encoder et de décoder les trames d'octets envoyées
 * 		  et reçues par DSSupervisor via la Communication Intercoeur.
 * @date Juin 2021
 * @authors Robin
 * @version 1.0
 */

#ifndef INTERCORE_PROTOCOL_H_
#define INTERCORE_PROTOCOL_H_

#include "../common.h"
#include "../utils.h"

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

void IntercoreProtocol_init();


extern void IntercoreProtocol_free();

/**
 * Fonction decodeMessage IntercoreProtocol
 * 
 * @brief	Décode les messages d'acquittement (ACK_START, ACK_STOP, ACK_NO_MA, 
 *			ACK_MA, ACK_SBC_KO et ACK_SBC_OK) reçus via la Communication Intercoeur. 
 *			Convertit le tableau d'octets passé en 1er paramètre en tableau de 
 * 			structure et flottants passé en 2e paramètre.
 * 
 * @param bufferToRead : le pointeur vers le message en octet à décoder
 * @param messageToRead : le pointeur vers le message décodé en strcuture et flottants
 */
extern void IntercoreProtocol_decodeMessage(uint8_t *bufferToRead, M_MessageAnswer_t *messageToReadn, uint16_t bytesToDecode);

/**
 * Fonction encodeMessage IntercoreProtocol
 * 
 * @brief	Encode les messages de demande (ASK_START, ASK_STOP et ASK_NEW_MSG) 
 * 			à envoyer via la Communication Intercoeur. 
 * 			Convertit le tableau de structures et flottants passé en 1er 
 * 			paramètre en tableau d'octets passé en 2e paramètre.
 * 
 * @param messageToWrite : le pointeur vers le message en strcuture et flottants  à encoder
 * @param bufferToWrite : le pointeur vers le message encodé en octets
 */
extern void IntercoreProtocol_encodeMessage(M_MessageOrder_t *messageToWrite, uint8_t *bufferToWrite);

#endif /* INTERCORE_PROTOCOL_H_ */