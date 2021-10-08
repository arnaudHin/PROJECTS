/**
 * @file IntercoreProtocol.c
 * @brief Ce fichier permet d'encoder et de décoder les trames d'octets envoyées
 * 		  et reçues par DSSupervisor via la Communication Intercoeur.
 * @date Juin 2021
 * @authors Robin
 * @version 1.0
 */

#include <pthread.h>
#include "IntercoreProtocol.h"

//////////////////////////////////////////////////////////////////////////////
//							Varialbes privées								//
//////////////////////////////////////////////////////////////////////////////

static pthread_mutex_t mutexDecode;
static pthread_mutex_t mutexEncode;

//////////////////////////////////////////////////////////////////////////////
//							Fonctions publiques								//
//////////////////////////////////////////////////////////////////////////////

void IntercoreProtocol_init()
{
	int check = pthread_mutex_init(&mutexDecode, NULL);
	if (check == -1){
		int codeErreur = errno;
	}

	check = pthread_mutex_init(&mutexEncode, NULL);
	if (check == -1){
		int codeErreur = errno;
	}
}

void IntercoreProtocol_free()
{

}

void IntercoreProtocol_decodeMessage(uint8_t *bufferToRead, M_MessageAnswer_t *messageToRead, uint16_t bytesToDecode)
{
	pthread_mutex_lock(&mutexDecode);
	int byteIndex = 0;

	if(bytesToDecode == 3){
		
		/* Conversion de la taille de l'enum CMD_e : depuis DSSupervisor vers DSMonitor */
		uint8_t * cmd = (uint8_t *) (bufferToRead);	// DSMonitor recoit des enum de 1 octet
		messageToRead->command = (CMD_e) *cmd;	// 1 octet
		byteIndex+=sizeof(uint8_t);

		uint16_t size = (uint16_t) *(bufferToRead + byteIndex);
		messageToRead->size = (Size) size;
		byteIndex += sizeof(Size);

	}

	else if(bytesToDecode > 3){
		
		if (messageToRead->command == ACK_MA)
		{

			SessionId * sessionId = (SessionId *) (bufferToRead + byteIndex);
			messageToRead->dataToRead.sessionId = (SessionId) *sessionId;		// 2 octets
			byteIndex+=sizeof(SessionId);

			TimeMeasures_t * time = (TimeMeasures_t *) (bufferToRead + byteIndex);
			messageToRead->dataToRead.time = (TimeMeasures_t) *time;			// 4 octets
			byteIndex+=sizeof(TimeMeasures_t);

			uint8_t * sensorNb = (uint8_t *) (bufferToRead + byteIndex);
			messageToRead->dataToRead.sensorNb = (uint8_t) *sensorNb;			// 1 octet
			byteIndex+=sizeof(uint8_t);

			for (int i = 0; i < messageToRead->dataToRead.sensorNb; i++)
			{
				uint8_t * sensorId = (uint8_t *) (bufferToRead + byteIndex);
				messageToRead->dataToRead.measuresArray[i].sensorId = (SensorId_e) *sensorId;	// 1 octet
				byteIndex+=sizeof(uint8_t);

				SensorId_e currentSensorId = messageToRead->dataToRead.measuresArray[i].sensorId;

				if (currentSensorId == TEMP || currentSensorId == PRES || currentSensorId == HUMI)
				{
					SensorMeasure * measure1 = (SensorMeasure *) (bufferToRead + byteIndex);
					messageToRead->dataToRead.measuresArray[i].measure[0] = (SensorMeasure) *measure1;		// 4 octets
																							// 4 octets
																							// 4 octets
					byteIndex+=(3*sizeof(SensorMeasure)); 	// On ignore les 2 autres mesures de 4 octets chacune du tableau
				}
				else if (currentSensorId == ACCE || currentSensorId == GYRO || currentSensorId == MAGN)
				{
					SensorMeasure * measure1 = (SensorMeasure *) (bufferToRead + byteIndex);
					messageToRead->dataToRead.measuresArray[i].measure[0] = (SensorMeasure) *measure1;		// 4 octets
					byteIndex+=sizeof(SensorMeasure);

					SensorMeasure * measure2 = (SensorMeasure *) (bufferToRead + byteIndex);
					messageToRead->dataToRead.measuresArray[i].measure[1] = (SensorMeasure) *measure2;		// 4 octets
					byteIndex+=sizeof(SensorMeasure);

					SensorMeasure * measure3 = (SensorMeasure *) (bufferToRead + byteIndex);
					messageToRead->dataToRead.measuresArray[i].measure[2] = (SensorMeasure) *measure3;		// 4 octets
					byteIndex+=sizeof(SensorMeasure);
				}
			}

		}
		
	}
	else{
		
	}
	

	pthread_mutex_unlock(&mutexDecode);
}

void IntercoreProtocol_encodeMessage(M_MessageOrder_t *messageToWrite, uint8_t *bufferToWrite)
{
	pthread_mutex_lock(&mutexEncode);
	int byteIndex = 0;
	
	uint8_t * cmd = calloc(1, sizeof(uint8_t));
	*cmd = (CMD_e) messageToWrite->command;
	memcpy(bufferToWrite, cmd, sizeof(uint8_t));		// 1 octets
	byteIndex+=sizeof(uint8_t);
	free(cmd);

	Size * size = calloc(1, sizeof(Size));
	*size = (Size) messageToWrite->size;
	memcpy(bufferToWrite + byteIndex, size, sizeof(Size));		// 2 octets
	byteIndex+=sizeof(Size);
	free(size);

	switch(messageToWrite->command)
	{
		case ASK_START :
			if(1){}
			uint16_t * sessionId = calloc(1, sizeof(uint16_t));
			*sessionId = (SessionId) messageToWrite->dataToWrite.sessionId;
			memcpy(bufferToWrite + byteIndex, sessionId, sizeof(uint16_t));	// 2 octets
			byteIndex+=sizeof(uint16_t);
			free(sessionId);
			
			uint8_t * modeId = calloc(1, sizeof(uint8_t));
			*modeId = (uint8_t) messageToWrite->dataToWrite.modeId;
			memcpy(bufferToWrite + byteIndex, modeId, sizeof(uint8_t));		// 1 octet
			byteIndex+=sizeof(uint8_t);
			free(modeId);
			
			uint8_t * subModeId = calloc(1, sizeof(uint8_t));
			*subModeId = (uint8_t) messageToWrite->dataToWrite.subModeId;
			memcpy(bufferToWrite + byteIndex, subModeId, sizeof(uint8_t));		// 1 octet
			byteIndex+=sizeof(uint8_t);
			free(subModeId);

			uint8_t * sensorNb = calloc(1, sizeof(uint8_t));
			*sensorNb = (uint8_t) messageToWrite->dataToWrite.sensorsArray.sensorNb;
			memcpy(bufferToWrite + byteIndex, sensorNb, sizeof(uint8_t));		// 1 octet
			byteIndex+=sizeof(uint8_t);
			free(sensorNb);

			/* Pour tous les capteurs à solliciter */
			for (int i = 0; i < messageToWrite->dataToWrite.sensorsArray.sensorNb; i++)	
			{
				uint8_t * sensorActive = calloc(1, sizeof(uint8_t));
				*sensorActive = (uint8_t) messageToWrite->dataToWrite.sensorsArray.sensorActive[i];
				memcpy(bufferToWrite + byteIndex, sensorActive, sizeof(uint8_t));	// 1 octet
				byteIndex+=sizeof(uint8_t);
				free(sensorActive);

				uint8_t * sensors = calloc(1, sizeof(uint8_t));
				*sensors = (uint8_t) messageToWrite->dataToWrite.sensorsArray.sensors[i];
				memcpy(bufferToWrite + byteIndex, sensors, sizeof(uint8_t));		// 1 octet
				byteIndex+=sizeof(uint8_t);
				free(sensors);

				uint8_t * periodSensor = calloc(1, sizeof(uint8_t));
				*periodSensor = (uint8_t) messageToWrite->dataToWrite.sensorsArray.periodSensor[i];
				memcpy(bufferToWrite + byteIndex, periodSensor, sizeof(uint8_t));	// 1 octet
				byteIndex+=sizeof(uint8_t);
				free(periodSensor);
			}

			break;
		case ASK_STOP :
			break;
		case ASK_NEW_MSG :
			break;
		default :
			break;
	}
	pthread_mutex_unlock(&mutexEncode);
}
