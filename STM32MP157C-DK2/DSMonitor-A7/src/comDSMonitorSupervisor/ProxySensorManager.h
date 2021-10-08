/**
 * @file ProxySensorManager.h
 * @brief Ce fichier imite la classe SensorManager de DSSupervisor.
 * @date Mai 2021
 * @authors Robin
 * @version 1.0
 */

#ifndef PROXY_SENSOR_MANAGER_H
#define PROXY_SENSOR_MANAGER_H

#include "../common.h"
#include "../utils.h"

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction askSensorBoardConnectionStatus ProxySensorManager
 * 
 * @brief	Crée une trame de demande de SensorBoardConnectionStatus à envoyer, 
 * 			l'encode, puis l'envoie à DSSupervisor via la Communication Intercoeur.
 */
extern void ProxySensorManager_askSensorBoardConnectionStatus();

#endif /* PROXY_SENSOR_MANAGER_H */