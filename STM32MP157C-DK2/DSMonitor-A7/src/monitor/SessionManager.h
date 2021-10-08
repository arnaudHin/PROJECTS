/**
 * @file SessionManager.h
 * @brief 
 * @date Juin 2021
 * @authors Robin Leprince
 * @version 1.0
 */

#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include "../common.h"

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction StartSession SessionManager
 * 
 * @brief Envoie les paramètres de la Session à SessionArchiver de DSApp via la 
 * 		  Communication Wifi. Envoie une trame ASK_START à MeasuresProcessorSupervisor 
 * 		  de DSSupervisor via la Communication Intercoeur.
 * @param sessionId : l'ID de la Session à démarrer
 * @param modeId : l'ID du mode de la Session
 * @param subModeId : l'ID du sous-mode de la Session
 * @param sensorsArray : le tableau contenant l'id des capteurs à solliciter et leur période de capture
 * @param time : la date et l'heure du démarrage de la Session
 */
extern void SessionManager_startSession(SessionId sessionId, ModeId_e modeId, SubModeId_e submodeId, SensorsArray_t sensorsArray, Time time); 

/**
 * Fonction StopSession SessionManager
 * 
 * @brief Envoie une trame ASK_STOP à DSSupervisor via le protocole
 * 
 * @param stopTime : la date et l'heure de l'arrêt de la Session en cours
 */
extern void SessionManager_stopSession(Time stopTime);

#endif /* SESSION_MANAGER_H */