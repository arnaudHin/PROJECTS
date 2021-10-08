/**
 * @file ProxySessionArchiver.h
 * @brief 
 * @date Juin 2021
 * @authors Nisrine Tougui
 * @version 1.0
 * @copyright CC BY 4.0
 */

#ifndef PROXY_SESSION_ARCHIVER_H
#define PROXY_SESSION_ARCHIVER_H

#include "PostmanDSMonitorApp.h"
#include "../common.h"

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

/**
 * @fn     extern void ProxySessionArchiver_storeBeginSession(SessionId sessionId, ModeId_e modeId, SubModeId_e submodeId, SensorsArray_t sensorsArray, Time time)
 *
 * @brief   Fonction permettant d'appeller la bonne méthode d'encodage qui est présente dans la classes wifiProtocol. 
 *
 * @param   sessionId               : 
 * @param   modeId                  : 
 * @param   submodeId               : 
 * @param   sensorsArray            : 
 * @param   time                    : 
 *
 *
 */
extern void ProxySessionArchiver_storeBeginSession(SessionId sessionId, ModeId_e modeId, SubModeId_e submodeId, SensorsArray_t sensorsArray, Time time); 


/**
 * @fn     extern void ProxySessionArchiver_storeEndSession(Time time)
 *
 * @brief   Fonction permettant d'appeller la bonne méthode d'encodage qui est présente dans la classes wifiProtocol. Encodage signalant fin de session.
 *
 * @param   time                    : 
 *
 */
extern void ProxySessionArchiver_storeEndSession(Time time); 

extern void ProxySessionArchiver_storeMeasuresArray(MeasuresArray_t *measuresArray);

extern void ProxySessionArchiver_storeMetaMeasures(MetaMeasuresArray_t *metaMeasuresArray, Location_e location);

#endif /* PROXY_SESSION_ARCHIVER_H */