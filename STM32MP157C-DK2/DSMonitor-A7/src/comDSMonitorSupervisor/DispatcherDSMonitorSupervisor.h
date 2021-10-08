/**
 * @file DispatcherDSMonitorSupervisor.h
 * @brief Ce fichier lit en permanence la boite aux lettres et décide de ce 
 * 		  qu'il faut faire en conséquence.
 * @date Mai 2021
 * @authors Robin
 * @version 1.0
 */

#ifndef DISPATCHER_DSMONITOR_SUPERVISOR_H_
#define DISPATCHER_DSMONITOR_SUPERVISOR_H_

#include "../common.h"
#include "../utils.h"

typedef struct DispatcherDSMS DispatcherDSMS_t;

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction new DispatcherDSMS
 * 
 * @brief	Initialise l'état de la MAE.
 */
extern void DispatcherDSMS_new();

/**
 * Fonction start DispatcherDSMS
 * 
 * @brief	Initialise le threadRun de DispatcherDSMS.
 */
extern void DispatcherDSMS_start();

/**
 * Fonction stop DispatcherDSMS
 * 
 * @brief	Met fin au threadRun de DispatcherDSMS.
 */
extern void DispatcherDSMS_stop();

/**
 * Fonction free DispatcherDSMS
 * 
 * @brief	Libère l'état de la MAE.
 */
extern void DispatcherDSMS_free();

/**
 * Fonction Get DispatcherDSMS
 * 
 * @brief 
 * @return
 */
extern DispatcherDSMS_t * DispatcherDSMS_get();

/**
 * Fonction Set DispatcherDSMS
 * 
 * @brief 
 * @param
 */
extern void DispatcherDSMS_set(DispatcherDSMS_t *dispatcherDSMS);


/**
 * 
 */
void DispatcherDSMS_setInstant(bool instant);

/*----------------------------------------------- POUR LE DEBOGGAGE : -------------------------------------------------*/

extern void DispatcherDSMS_toggleCapture();

#endif /* DISPATCHER_DSMONITOR_SUPERVISOR_H_ */
