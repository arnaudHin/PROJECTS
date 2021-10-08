/**
 * @file PostmanDSMonitorSupervisor.h
 * @brief Ce fichier reçoit et envoie des messages sur les cannaux de 
 * 		  Communication Intercoeur.
 * @date Mai 2021
 * @authors Robin
 * @version 1.0
 */

#ifndef POSTMAN_DSMONITOR_SUPERVISOR_H_
#define POSTMAN_DSMONITOR_SUPERVISOR_H_

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>

#include "../common.h"
#include "../utils.h"

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction new PostmanDSMS
 * 
 * @brief
 */
extern void PostmanDSMS_new();

/**
 * Fonction start PostmanDSMS
 * 
 * @brief Configure le Descripteur de fichier pour chaque port série, les ouvre 
 * 		  et se met en écoute pour chacun.
 */
extern void PostmanDSMS_start();

/**
 * Fonction stop PostmanDSMS
 * 
 * @brief Ferme les ports série.
 */
extern void PostmanDSMS_stop();

/**
 * Fonction free PostmanDSMS
 * 
 * @brief 
 */
extern void PostmanDSMS_free();

/**
 * Fonction read PostmanDSMS
 * 
 * @brief	Envoie sur le canal fd0 un ASK_NEW_MSG à DSSupervisor via la 
 * 			Communication Intercoeur et lit les données reçues.
 * 
 * @param bufferToRead : le pointeur vers le message en octet où écrire le message reçu
 * @param sizeToRead : le nombre d'octets à lire
 */
extern void PostmanDSMS_read(uint8_t *bufferToRead, uint16_t sizeToRead);

/**
 * Fonction read PostmanDSMS
 * 
 * @brief	envoie sur le canal fd1 un ASK_START ou ASK_STOP à DSSupervisor 
 * 			via la Communication Intercoeur et lit les acquittements reçus.
 * 
 * @param bufferToWrite : le pointeur vers le message en octet à envoyer
 * @param sizeToWrite : le nombre d'octets à ecrire
 */
extern void PostmanDSMS_write(uint8_t *bufferToWrite, uint16_t sizeToWrite);

#endif /* POSTMAN_DSMONITOR_SUPERVISOR_H_ */