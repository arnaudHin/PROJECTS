/**
 * @file WifiProtocol.h
 * @brief 
 * @date Juin 2021
 * @authors Nisrine Tougui
 * @version 1.0
 * @copyright CC BY 4.0
 */

#ifndef WIFI_PROTOCOL_H
#define WIFI_PROTOCOL_H

#include <stdint.h>
#include "PostmanDSMonitorApp.h"
#include "../common.h"

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

/**
 * @fn      extern void WifiProtocol_decodeToDSMonitor(DataRead *myDataRead, M_MessageToReadFromDSApp_t *messageToReadFromDSApp)
 *
 * @brief  Fonction permettant de décoder les valeurs de la trame 
 *
 * @param   myDataRead          : Pointeur vers la structure contenant les données provenant du postman 
 * @param   myFrameQueueMessage : Pointeur vers la structure dans laquelle les données décodées sont enregistrées 
 *
 */
extern void WifiProtocol_decodeToDSMonitor(uint8_t *dataRead, M_MessageToReadFromDSApp_t *myMessageToReadFromDSApp, ssize_t octetToRead);

/**
 * @fn     extern void WifiProtocol_encodeToDSAppSessionArchiverStoreSessionMeasures(DataToWrite myDataToWrite); 
 *
 * @brief   Fonction permettant d'encoder le storeSession Measures pour la classes Session Archiver
 *
 * @param   myDataToWrite           : Pointeur vers la structure contenant les données à destnation du Postman
 * @param   sessionId               : 
 * @param   modeId                  : 
 * @param   submodeId               : 
 * @param   sensorsArray            : 
 * @param   time                    : 
 *
 *
 */
extern void WifiProtocol_encodeToDSAppStoreBeginSession(uint8_t *dataToWriteBuffer, M_MessageToReadFromDSApp_t *messageFromDSApp);

/**
 * @fn      extern void WifiProtocol_encodeToDSAppSessionArchiverStoreEndSession(DataToWrite myDataToWrite); 
 *
 * @brief   Fonction permettant d'encoder un message à destination du proxy SessionArchiver lors d'un storeEndSession
 *
 * @param   myDataToWrite           : 
 * @param   time                    : 
 */
extern void WifiProtocol_encodeToDSAppStoreEndSession(uint8_t *dataToWriteBuffer, M_MessageToReadFromDSApp_t *messageFromDSApp);


/**
 * @fn     WifiProtocol_encodeToDSAppMeasuresProcessorAppStoreMeasuresArray(DataToWrite myDataToWrite, MeasuresArray_t messuresArray)
 *
 * @brief  Fonction permettant d'encoder un message à destination du proxy MeasuresProcessorApp pour storeMeasuresArray
 *
 * @param   myDataToWrite          : 
 */
// extern void WifiProtocol_encodeToDSAppMeasuresProcessorAppStoreMeasuresArray(uint8_t *dataToWriteBuffer, M_DataAnswer_t mydataToReadFromDSupervisor);


extern void WifiProtocol_encodeToDSAppStoreMeasuresArray(uint8_t *dataToWriteBuffer, M_MessageAnswer_t *messageToWrite);


/**
 * @fn      extern void WifiProtocol_encodeToDSAppSessionArchiverStoreMetaMeasures(DataToWrite myDataToWrite)
 *
 * @brief   Fonction permettant d'encoder le store MetaMeasures pour la classes Session Archiver
 *
 * @param   myDataToWrite          : Pointeur vers la structure contenant les données à destnation du Postman
 *
 *
 */
extern void WifiProtocol_encodeToDSAppSessionArchiverStoreMetaMeasures(uint8_t *dataToWriteBuffer);



/**
 * @fn      extern void WifiProtocol_encodeToDSAppMonitorGUI(DataToWrite myDataToWrite)
 *
 * @brief   Fonction permettant d'encoder un message à destination de Monitor GUI
 *
 * @param   myDataToWrite          : 
 *
 */
extern void WifiProtocol_encodeToDSAppMonitorGUI(uint8_t *dataToWriteBuffer);


#endif /* WIFI_PROTOCOL_H */