/**
 * @file MetaMesuresMonitor.h
 * @brief 
 * @date Juin 2021
 * @authors Robin Leprince
 * @version 1.0
 */

#ifndef META_MEASURES_MONITOR_H_
#define META_MEASURES_MONITOR_H_

#include "../common.h"

typedef struct MetaMeasuresMonitor MetaMeasuresMonitor_t;

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction New MetaMeasuresMonitor
 * 
 * @brief 
 */
extern void MetaMeasuresMonitor_new();

/**
 * Fonction Start MetaMeasuresMonitor
 * 
 * @brief 
 */
extern void MetaMeasuresMonitor_start();

/**
 * Fonction Stop MetaMeasuresMonitor
 * 
 * @brief 
 */
extern void MetaMeasuresMonitor_stop();

/**
 * Fonction Free MetaMeasuresMonitor
 * 
 * @brief 
 */
extern void MetaMeasuresMonitor_free();

/**
 * Fonction Get MetaMeasuresMonitor
 * 
 * @brief 
 * @return
 */
extern MetaMeasuresMonitor_t * MetaMeasuresMonitor_get();

/**
 * Fonction Set MetaMeasuresMonitor
 * 
 * @brief 
 * @param
 */
extern void MetaMeasuresMonitor_set(MetaMeasuresMonitor_t *metaMeasuresMonitor);

/**
 * Fonction StopSession startMetaMeasures
 * 
 * @brief 
 *
 * @param sessionId : l'id de la session à démarrer
 */
extern void MetaMeasuresMonitor_startMetaMeasures(SessionId sessionId);

/**
 * Fonction StopSession startMetaMeasures
 * 
 * @brief 
 */
extern void MetaMeasuresMonitor_stopMetaMeasures();

#endif /* META_MEASURES_MONITOR_H_ */