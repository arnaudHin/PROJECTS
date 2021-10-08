/**
 * @file ProxySessionArchiver.c
 * @brief 
 * @date Juin 2021
 * @authors Nisrine Tougui
 * @version 1.0
 * @copyright CC BY 4.0
 */

#include <stdio.h>
#include <stdlib.h>

#include "ProxySessionArchiver.h"
#include "PostmanDSMonitorApp.h"
#include "WifiProtocol.h"
#include "../common.h"

#define OCTET_NUMBER_CMD_AND_SIZE (3)

static M_MessageToReadFromDSApp_t myMessageFromDSApp;
static uint8_t *myDataBuffer;
static uint8_t octetNumber = OCTET_NUMBER_CMD_AND_SIZE;

void ProxySessionArchiver_storeBeginSession(SessionId sessionId, ModeId_e modeId, SubModeId_e submodeId, SensorsArray_t sensorsArray, Time time)
{
    uint16_t sizeMessage = 28;
    uint32_t size = 25;

    myMessageFromDSApp.commandMsg = STORE_START_SESSION;
    myMessageFromDSApp.sizeMsg = size;
    myMessageFromDSApp.sessionInformationMsg.sessionId = sessionId;
    myMessageFromDSApp.sessionInformationMsg.modeId = modeId;
    myMessageFromDSApp.sessionInformationMsg.subModeId = submodeId;
    myMessageFromDSApp.sessionInformationMsg.time = time;
    myMessageFromDSApp.sessionInformationMsg.sensorsArray.sensorNb = sensorsArray.sensorNb;

    for (int i = 0; i < myMessageFromDSApp.sessionInformationMsg.sensorsArray.sensorNb; i++)
    {
        myMessageFromDSApp.sessionInformationMsg.sensorsArray.sensors[i] = sensorsArray.sensors[i];
    }

    for (int i = 0; i < myMessageFromDSApp.sessionInformationMsg.sensorsArray.sensorNb; i++)
    {
        myMessageFromDSApp.sessionInformationMsg.sensorsArray.periodSensor[i] = sensorsArray.periodSensor[i];
    }
    
    sizeMessage = sizeof(uint8_t) + sizeof(uint16_t) + myMessageFromDSApp.sizeMsg;
    myDataBuffer = calloc(1, sizeMessage);

    WifiProtocol_encodeToDSAppStoreBeginSession(myDataBuffer, &myMessageFromDSApp);

    fprintf(stderr, "--- Session de mesures Start : Id %d en mode %d ---\n", sessionId, modeId);

    PostmanDSMonitorApp_write(myDataBuffer, sizeMessage);

    free(myDataBuffer);
}

void ProxySessionArchiver_storeEndSession(Time time)
{
    uint16_t sizeMessage = 0;
    uint32_t size = 8 + 2;

    myMessageFromDSApp.commandMsg = STORE_END_SESSION;
    myMessageFromDSApp.sizeMsg = size;
    myMessageFromDSApp.sessionInformationMsg.time = time;

    sizeMessage = sizeof(uint8_t) + sizeof(uint16_t) + myMessageFromDSApp.sizeMsg;
    myDataBuffer = calloc(1, sizeMessage);

    WifiProtocol_encodeToDSAppStoreEndSession(myDataBuffer, &myMessageFromDSApp);

    fprintf(stderr, "--- Session de mesures Stop : Id %d en mode %d ---\n", myMessageFromDSApp.sessionInformationMsg.sessionId, myMessageFromDSApp.sessionInformationMsg.modeId);

    PostmanDSMonitorApp_write(myDataBuffer, sizeMessage);

    free(myDataBuffer);
}

void ProxySessionArchiver_storeMeasuresArray(MeasuresArray_t *measuresArray)
{
    //myDataToWrite
    //encode
    //postman_write
}

void ProxySessionArchiver_storeMetaMeasures(MetaMeasuresArray_t *metaMeasuresArray, Location_e location)
{
    //myDataToWrite
    //encode
    //postman_write
    
    uint16_t sizeMessage = sizeof(CMD_TO_APP_e) + sizeof(uint16_t) + myMessageFromDSApp.sizeMsg;
    myDataBuffer = calloc(1, sizeMessage);

    // WifiProtocol_encodeToDSAppSessionArchiverStoreEndSession(myDataBuffer, myMessageFromDSApp);
    PostmanDSMonitorApp_write(myDataBuffer, sizeMessage);

    free(myDataBuffer);
}

// extern void ProxySessionArchiver_storeMetaMeasures(){}
