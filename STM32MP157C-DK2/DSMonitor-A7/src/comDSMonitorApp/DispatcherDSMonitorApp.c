/**
 * @file DispatcherDSMonitorApp.c
 * @brief 
 * @date Juin 2021
 * @authors Nisrine Tougui
 * @version 1.0
 * @copyright CC BY 4.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>

#include "WifiProtocol.h"
#include "PostmanDSMonitorApp.h"
#include "DispatcherDSMonitorApp.h"
#include "../utils.h"
#include "../common.h"

#include "../monitor/SessionManager.h"

#define OCTET_NUMBER_CMD_AND_SIZE (3)

#define EV_START_SESSION (0)
#define EV_STOP_SESSION (1)
#define EV_CHECK_SENSORBOARD_CONNECTION (3)

//////////////////////////////////////////////////////////////////////////////
//							Variables Privées								//
//////////////////////////////////////////////////////////////////////////////
static pthread_t myThread;
static M_MessageToReadFromDSApp_t myMessageToReadFromDSApp;
static uint8_t * myBufferWifiGeneral;
static uint8_t myBufferWifi[3];

static bool run = false;

//////////////////////////////////////////////////////////////////////////////
//					   Prototypes de fonctions Privées						//
//////////////////////////////////////////////////////////////////////////////

/**
 * @fn      static void DispatcherDSMonitorApp_read()
 *
 * @brief   Fonction permettant d'appeler les fonctions de lecture du postmanDSMonitorApp et de décodage du wifiProtocol. 
 *
 */

static void DispatcherDSMonitorApp_read();

/**
 * @fn      static void *DispatcherDSMonitorApp_run()
 *
 * @brief   Fonction run de la classe DispatcherDSMonitorApp. 
 *
 */
static void * DispatcherDSMonitorApp_run();

//////////////////////////////////////////////////////////////////////////////
//							      Fonctions 			    	            //
//////////////////////////////////////////////////////////////////////////////

extern void DispatcherDSMonitorApp_new()
{
    run = true;
}

extern void DispatcherDSMonitorApp_start()
{
    int check;
    check = pthread_create(&myThread, NULL, DispatcherDSMonitorApp_run, NULL);

    if (check == -1)
    {
        int codeErreur = errno;
    }
}

extern void DispatcherDSMonitorApp_stop()
{
    int check;
    check = pthread_join(myThread, NULL);
    if (check == -1)
    {
        int codeErreur = errno;
    }
}

extern void DispatcherDSMonitorApp_free()
{
    run = false;
}

static void DispatcherDSMonitorApp_read()
{
    int resultRead = 0;

    ssize_t byteToRead;

    byteToRead = OCTET_NUMBER_CMD_AND_SIZE;

    /* Lecture des 3 premiers octets de la trame */
    resultRead = PostmanDSMonitorApp_read(myBufferWifi, byteToRead);
    if (resultRead == -1){
        perror("ERROR POSTMAN MONITOR APP READ CMD SIZE \n");
    }
    else{
            
    }

    WifiProtocol_decodeToDSMonitor(myBufferWifi, &myMessageToReadFromDSApp, byteToRead);
    
    if( myMessageToReadFromDSApp.sizeMsg != 0){

        ssize_t dataSize = myMessageToReadFromDSApp.sizeMsg;
                
        myBufferWifiGeneral = calloc(1, dataSize);

        /* Lecture de la trame */
        resultRead = PostmanDSMonitorApp_read(myBufferWifiGeneral, dataSize);
        if (resultRead == -1)
        {
            perror("ERROR POSTMAN MONITOR APP READ DATA \n");
        }

        WifiProtocol_decodeToDSMonitor(myBufferWifiGeneral, &myMessageToReadFromDSApp, dataSize);

        free(myBufferWifiGeneral);
    }

}

static void * DispatcherDSMonitorApp_run()
{

    uint8_t a = 1;
    while (a)
    { 

        DispatcherDSMonitorApp_read();
        CMD_APP_e commandMsg = myMessageToReadFromDSApp.commandMsg;

        switch ( (uint8_t) commandMsg)
        {
            case START_SESSION:

                SessionManager_startSession(
                    myMessageToReadFromDSApp.sessionInformationMsg.sessionId,
                    myMessageToReadFromDSApp.sessionInformationMsg.modeId,
                    myMessageToReadFromDSApp.sessionInformationMsg.subModeId,
                    myMessageToReadFromDSApp.sessionInformationMsg.sensorsArray,
                    myMessageToReadFromDSApp.sessionInformationMsg.time);

                break;

            case STOP_SESSION:

                SessionManager_stopSession(myMessageToReadFromDSApp.sessionInformationMsg.time);
                
                sleep(2);
                
            break;

            case CHECK_SENSORBOARD_CONNECTION : 


            break;

            case DSAPP_QUIT : 
                a = 0;
            break;

             

        }
    }

    return NULL;
}