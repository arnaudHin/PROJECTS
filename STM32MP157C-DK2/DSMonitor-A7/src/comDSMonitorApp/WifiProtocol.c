/**
 * @file WifiProtocol.c
 *
 * @brief Classe wifiProtocol. 
 *        Cette classe permet  : 
 *              - d'encoder les trames à envoyer à DSApp 
 *              - de décoder les trames provenant de DSApp
 * @date Mai 2021
 *
 * @authors Nisrine Tougui
 *
 * @version 1
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <endian.h>
#include "WifiProtocol.h"
#include "../common.h"
#include "../utils.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//					                   PROTOTYPES DES FONCTIONS PRIVEES DE DECODAGE                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void WifiProtocol_decodeCommandSize(uint8_t *bufferRead ,  M_MessageToReadFromDSApp_t *messageToReadFromDSApp);

static void WifiProtocol_decodeData(uint8_t *bufferRead ,  M_MessageToReadFromDSApp_t *messageToReadFromDSApp, CMD_APP_e command); 

static void WifiProtocol_floatLittleEndianToBigEndian(const float value, uint8_t * tab);


extern void WifiProtocol_decodeToDSMonitor(uint8_t *bufferRead ,  M_MessageToReadFromDSApp_t *messageToReadFromDSApp, ssize_t octetToRead)
{
    if(octetToRead == 3)
    {
        WifiProtocol_decodeCommandSize(bufferRead , messageToReadFromDSApp);  // BufferRead 
    }
    else if (octetToRead > 3)
    {
        WifiProtocol_decodeData(bufferRead , messageToReadFromDSApp, messageToReadFromDSApp->commandMsg); 
    }
}

// Faire une seule fonction externe : ajouter 3ème paramètre : sizeToRead   unint8_t
static void WifiProtocol_decodeCommandSize(uint8_t *dataReadBuffer ,  M_MessageToReadFromDSApp_t *messageToReadFromDSApp) // BufferRead
{

    uint16_t index = 0;
    
    uint8_t * cmd = (uint8_t*) dataReadBuffer;
    messageToReadFromDSApp->commandMsg = (CMD_APP_e) *cmd;
    index += sizeof(uint8_t);

    uint8_t size0 = (uint8_t) *(dataReadBuffer + index);
    index++;
    uint8_t size1 = (uint8_t) ( (uint8_t) *(dataReadBuffer + index) );
    messageToReadFromDSApp->sizeMsg = ( (uint16_t) size0 << 8 | size1 );
}

static void WifiProtocol_decodeData(uint8_t *dataReadBuffer ,  M_MessageToReadFromDSApp_t *messageToReadFromDSApp, CMD_APP_e command)
{
    uint16_t index = 0;
    switch (command)
    {
        case START_SESSION : 

            if(1){}

            uint16_t indexStart = 0;

            uint8_t size0 = (uint8_t) *(dataReadBuffer + index);
            index++;
            uint8_t size1 = (uint8_t) ( (uint8_t) *(dataReadBuffer + index) );
            index++;
            messageToReadFromDSApp->sessionInformationMsg.sessionId = ( (uint16_t) size0 << 8 | size1 );



            uint8_t * modId = (uint8_t*) dataReadBuffer + index;
            messageToReadFromDSApp->sessionInformationMsg.modeId = (ModeId_e) *modId;
            index += sizeof(uint8_t);

            uint8_t * subModId = (uint8_t*) dataReadBuffer + index;
            messageToReadFromDSApp->sessionInformationMsg.subModeId = (SubModeId_e) *subModId;
            index += sizeof(uint8_t);

            uint8_t a;
            Time timeStart;
            for (size_t i = 0; i < sizeof(uint64_t); i++)
            {
                a = *(dataReadBuffer + index);
                timeStart = (timeStart << 8) | a;
                index += sizeof(uint8_t);
            }
            messageToReadFromDSApp->sessionInformationMsg.time = timeStart;

            uint8_t * nbS = (uint8_t*) dataReadBuffer + index;
            messageToReadFromDSApp->sessionInformationMsg.sensorsArray.sensorNb = (uint8_t) *nbS;
            index += sizeof(uint8_t);

            for (int i = 0 ; i <  messageToReadFromDSApp->sessionInformationMsg.sensorsArray.sensorNb ; i++)
	        {
                uint8_t * idS = (uint8_t*) dataReadBuffer + index;
                messageToReadFromDSApp->sessionInformationMsg.sensorsArray.sensors[i] = (SensorId_e) *idS;
                index += sizeof(uint8_t);
                
                uint8_t * Ps = (uint8_t*) dataReadBuffer + index;
                messageToReadFromDSApp->sessionInformationMsg.sensorsArray.periodSensor[i] = (Period_e) *Ps;
                index += sizeof(uint8_t);
            }

        break; 

        case STOP_SESSION : 
            if(1){}

            uint8_t aa;
            Time timeStop;
            for (size_t i = 0; i < sizeof(uint64_t); i++)
            {
                aa = *(dataReadBuffer + index);
                timeStop = (timeStop << 8) | aa;
                index += sizeof(uint8_t);
            }
            messageToReadFromDSApp->sessionInformationMsg.time = timeStop;

        break; 

        default: 
        break; 

    }

}

/*------------------------------------------------------------------- FONCTIONS D'ENCODAGE -------------------------------------------------------------------*/

extern void WifiProtocol_encodeToDSAppStoreBeginSession(uint8_t * dataToWriteBuffer, M_MessageToReadFromDSApp_t * messageFromDSApp)
{
    uint16_t index = 0;
   
    uint8_t * cmd = calloc(1, sizeof(uint8_t));
    *cmd = (uint8_t) messageFromDSApp->commandMsg;
    memcpy(dataToWriteBuffer+index, cmd, sizeof(uint8_t));
    free(cmd);
    index += sizeof(uint8_t);

    uint8_t size0 = (uint8_t) (messageFromDSApp->sizeMsg) ;
    uint8_t size1 = (uint8_t) ( (uint8_t) (messageFromDSApp->sizeMsg)>>8) ;
    *(dataToWriteBuffer + index) = size1;
    index++;
    *(dataToWriteBuffer + index) = size0;
    index++;

    uint8_t sessId0 = (uint8_t) (messageFromDSApp->sessionInformationMsg.sessionId) ;
    uint8_t sessId1 = (uint8_t) ( (uint8_t) (messageFromDSApp->sessionInformationMsg.sessionId)>>8) ;
    *(dataToWriteBuffer + index) = sessId1;
    index++;
    *(dataToWriteBuffer + index) = sessId0;
    index++;
            
    uint8_t* mId = calloc(1,sizeof(uint8_t) );
    *mId = (uint8_t) messageFromDSApp->sessionInformationMsg.modeId;
    memcpy(dataToWriteBuffer+index, mId, sizeof(uint8_t));
    free(mId);
    index += sizeof(uint8_t);
            
    uint8_t* sbmId = calloc(1, sizeof(uint8_t) );
    *sbmId = (uint8_t) messageFromDSApp->sessionInformationMsg.subModeId ;
    memcpy(dataToWriteBuffer+index, sbmId, sizeof(uint8_t));
    free(sbmId);
    index += sizeof(uint8_t);

    Time * startTime = calloc(1, sizeof(uint64_t));
    *startTime = (uint64_t) htobe64(messageFromDSApp->sessionInformationMsg.time);
    memcpy(dataToWriteBuffer+index, startTime, sizeof(uint64_t));
    free(startTime);
    index += sizeof(uint64_t);


    uint8_t * nbSensors = calloc(1, sizeof(uint8_t));
    *nbSensors = messageFromDSApp->sessionInformationMsg.sensorsArray.sensorNb;
    memcpy(dataToWriteBuffer+index, nbSensors, sizeof(uint8_t) );
    free(nbSensors);
    index += sizeof(uint8_t);
            
    for (int i = 0; i <  messageFromDSApp->sessionInformationMsg.sensorsArray.sensorNb ; i++)
	{
        uint8_t * sensorId = calloc(1, sizeof(uint8_t) );
		* sensorId = (uint8_t) messageFromDSApp->sessionInformationMsg.sensorsArray.sensors[i] ; 
        memcpy(dataToWriteBuffer+index, sensorId, sizeof(uint8_t));  // 1 OCTET 
        free(sensorId);
        index += sizeof(uint8_t);
        
        uint8_t * periodSensor = calloc(1, sizeof(uint8_t) );
        * periodSensor = (uint8_t) messageFromDSApp->sessionInformationMsg.sensorsArray.periodSensor[i];
        memcpy(dataToWriteBuffer+index, periodSensor, sizeof(uint8_t));  // 1 OCTET
        free(periodSensor);
        index += sizeof(uint8_t);
    }
}


extern void WifiProtocol_encodeToDSAppStoreEndSession(uint8_t * dataToWriteBuffer, M_MessageToReadFromDSApp_t *messageFromDSApp)
{
    uint16_t index = 0; 

    uint8_t * cmd = calloc(1, sizeof(uint8_t));
    *cmd = (uint8_t) messageFromDSApp->commandMsg;
    memcpy(dataToWriteBuffer+index, cmd, sizeof(uint8_t));
    free(cmd);
    index += sizeof(uint8_t);

    uint8_t size0 = (uint8_t) (messageFromDSApp->sizeMsg) ;
    uint8_t size1 = (uint8_t) ( (uint8_t) (messageFromDSApp->sizeMsg)>>8) ;
    *(dataToWriteBuffer + index) = size1;
    index++;
    *(dataToWriteBuffer + index) = size0;
    index++;

    uint8_t sessId0 = (uint8_t) (messageFromDSApp->sessionInformationMsg.sessionId) ;
    uint8_t sessId1 = (uint8_t) ( (uint8_t) (messageFromDSApp->sessionInformationMsg.sessionId)>>8) ;
    *(dataToWriteBuffer + index) = sessId1;
    index++;
    *(dataToWriteBuffer + index) = sessId0;
    index++;

    Time * stopTime = calloc(1, sizeof(uint64_t));
    *stopTime = (uint64_t) htobe64(messageFromDSApp->sessionInformationMsg.time);
    memcpy(dataToWriteBuffer+index, stopTime, sizeof(uint64_t));
    free(stopTime);
    index += sizeof(uint64_t);

}

extern void WifiProtocol_encodeToDSAppStoreMeasuresArray(uint8_t * dataToWriteBuffer, M_MessageAnswer_t * messageAnswer)
{

    uint16_t index = 0;

    uint8_t * cmd = calloc(1, sizeof(uint8_t));
    *cmd = (uint8_t) messageAnswer->command;
    memcpy(dataToWriteBuffer+index, cmd, sizeof(uint8_t));
    free(cmd);
    index += sizeof(uint8_t);

    Size * size = calloc(1, sizeof(Size));
    *size = (Size) htobe16(messageAnswer->size);
    memcpy(dataToWriteBuffer+index, size, sizeof(Size));
    free(size);
    index += sizeof(Size);

    switch(messageAnswer->size)
    {
        case 0:
            /* Rien à envoyer */        
        break;

        default :
            /* Send Measures */

            if(1){}

            uint16_t* sessionId = calloc(1, sizeof(uint16_t) );
            *sessionId = (uint16_t) htobe16(messageAnswer->dataToRead.sessionId);
            memcpy(dataToWriteBuffer+index, sessionId, sizeof(uint16_t));
            free(sessionId);
            index += sizeof(uint16_t);
            
            TimeMeasures_t * time = calloc(1, sizeof(uint32_t));
            *time = (TimeMeasures_t) htobe32(messageAnswer->dataToRead.time);
            memcpy(dataToWriteBuffer+index, time, sizeof(uint32_t));
            free(time);
            index += sizeof(uint32_t);


            uint8_t * nbSensors = calloc(1, sizeof(uint8_t));
            *nbSensors = messageAnswer->dataToRead.sensorNb;
            memcpy(dataToWriteBuffer+index, nbSensors, sizeof(uint8_t) );
            free(nbSensors);
            index += sizeof(uint8_t);

            uint8_t bufferFloat[4];
            
            for (int i = 0; i < messageAnswer->dataToRead.sensorNb ; i++)
			{
                uint8_t * sensorId = calloc(1, sizeof(uint8_t) );
				* sensorId = (uint8_t) messageAnswer->dataToRead.measuresArray[i].sensorId;  
                memcpy(dataToWriteBuffer+index, sensorId, sizeof(uint8_t));  // 1octet
                free(sensorId);
                index += sizeof(uint8_t);

                if (messageAnswer->dataToRead.measuresArray[i].sensorId == TEMP || messageAnswer->dataToRead.measuresArray[i].sensorId== PRES || messageAnswer->dataToRead.measuresArray[i].sensorId == HUMI )
				{

                    float value = messageAnswer->dataToRead.measuresArray[i].measure[0];
                    WifiProtocol_floatLittleEndianToBigEndian(value, bufferFloat);
                    memcpy(dataToWriteBuffer+index, &bufferFloat, sizeof(float));
                    index += sizeof(float);

				}
				else if (messageAnswer->dataToRead.measuresArray[i].sensorId == ACCE || messageAnswer->dataToRead.measuresArray[i].sensorId== GYRO || messageAnswer->dataToRead.measuresArray[i].sensorId == MAGN )
				{

                    float value1 = (messageAnswer->dataToRead.measuresArray[i].measure[0]);
                    WifiProtocol_floatLittleEndianToBigEndian(value1, bufferFloat);
                    memcpy(dataToWriteBuffer+index, &bufferFloat, sizeof(float));
                    index += sizeof(float);

                    float value2 = (messageAnswer->dataToRead.measuresArray[i].measure[1]);
                    WifiProtocol_floatLittleEndianToBigEndian(value2, bufferFloat);
                    memcpy(dataToWriteBuffer+index, &bufferFloat, sizeof(float));
                    index += sizeof(float);

                    float value3 = (messageAnswer->dataToRead.measuresArray[i].measure[2]);
                    WifiProtocol_floatLittleEndianToBigEndian(value3, bufferFloat);
                    memcpy(dataToWriteBuffer+index, &bufferFloat, sizeof(float));
                    index += sizeof(float);

				}else {
                    fprintf(stderr,"Error"); 
                }
			 }
        break;
    }

}



static void WifiProtocol_floatLittleEndianToBigEndian(const float value, uint8_t * tab){

        uint8_t tabTemp[4];
        memcpy(tabTemp, &value, sizeof(float));

        for (size_t i = 0; i < 4; i++)
        {
            tab[i] = tabTemp[3-i];
        }
}

