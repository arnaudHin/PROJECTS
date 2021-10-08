/**
 * @file : InterCoreProtocol.c
 * @brief :
 * @version
 * @date : May 28, 2021
 * @author: Arnaud
 */


#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "comSupervisor/InterCoreProtocol.h"
#include "utils/GPIOS.h"


//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Publiques				//
//////////////////////////////////////////////////////////////////////////////////


extern void InterCoreProtocol_encodeMessage(uint8_t * buffer, S_MessageToWrite_t * msg){

	uint32_t index = 0;
	uint8_t i;

	uint8_t * CMD = calloc(1, sizeof(uint8_t) );
	*CMD = (uint8_t) msg->command;
	memcpy(buffer + index, CMD, sizeof(uint8_t));
	free(CMD);
	index += sizeof(uint8_t);

	uint16_t* size = calloc(1, sizeof(uint16_t) );
	*size = msg->size;
	memcpy(buffer + index, size, 2);
	free(size);
	index += sizeof(uint16_t);

	switch (msg->size) {
		case 0:

			break;
		default:

			if(1){}

			uint16_t* sId = calloc(1, sizeof(uint16_t) );
			*sId = msg->dataToWrite.sessionId;
			memcpy(buffer + index, sId, 2);
			free(sId);
			index += sizeof(uint16_t);

			TimeMeasure * time = calloc(1, sizeof(TimeMeasure));
			*time = msg->dataToWrite.time;
			memcpy(buffer + index, time, sizeof(TimeMeasure));
			free(time);
			index += sizeof(TimeMeasure);

			uint8_t * nbSensors = calloc(1, sizeof(uint8_t) );
			*nbSensors = msg->dataToWrite.sensorNb;
			memcpy(buffer + index, nbSensors, sizeof(uint8_t) );
			free(nbSensors);
			index += sizeof(uint8_t);


			for (i = 0; i < msg->dataToWrite.sensorNb; ++i) {

			    uint8_t * sensorId = calloc(1, sizeof(uint8_t) );
			    *sensorId = (uint8_t) msg->dataToWrite.measuresArray[i].sensorId;
			    memcpy(buffer + index, sensorId, sizeof(uint8_t) );
			    free(sensorId);
			    index += sizeof(uint8_t);

			    SensorMeasure * sensorM0 = calloc(1, sizeof(SensorMeasure) );
			    *sensorM0 = (SensorMeasure) msg->dataToWrite.measuresArray[i].measure[0];
			    memcpy(buffer + index, sensorM0, sizeof(SensorMeasure) );
			    free(sensorM0);
			    index += sizeof(SensorMeasure);

			    SensorMeasure * sensorM1 = calloc(1, sizeof(SensorMeasure) );
			    *sensorM1 = (SensorMeasure) msg->dataToWrite.measuresArray[i].measure[1];
			    memcpy(buffer + index, sensorM1, sizeof(SensorMeasure) );
			    free(sensorM1);
			    index += sizeof(SensorMeasure);

			    SensorMeasure * sensorM2 = calloc(1, sizeof(SensorMeasure) );
			    *sensorM2 = (SensorMeasure) msg->dataToWrite.measuresArray[i].measure[2];
			    memcpy(buffer + index, sensorM2, sizeof(SensorMeasure) );
			    free(sensorM2);
			    index += sizeof(SensorMeasure);

			}

			break;
	}
}



extern void InterCoreProtocol_decodeMessage(uint8_t * buffer, S_MessageToRead_t * msg, uint16_t sizeToDecode){

	  uint16_t index = 0;

	  uint8_t * CMD = (uint8_t*) buffer;
	  msg->command = (CMD_e) *CMD;
	  index += sizeof(uint8_t);

	  uint16_t * size = (uint16_t*) (buffer + index);
	  msg->size = *size;
	  index += sizeof(uint16_t);


	  if(sizeToDecode > 3){

		uint8_t i;

		SessionId * sId = (SessionId*) (buffer + index);
		msg->dataToRead.sessionId = *sId;
		index += sizeof(SessionId);

		uint8_t* modeId = (uint8_t*) (buffer + index);
		msg->dataToRead.modeId = (ModeId_e) *modeId;
		index += sizeof(uint8_t);

		uint8_t* subModeId = (uint8_t*) (buffer + index);
		msg->dataToRead.subModeId = (SubModeId_e) *subModeId;
		index += sizeof(uint8_t);

		uint8_t* nbSensors = (uint8_t*) (buffer + index);
		msg->dataToRead.sensorsArray.sensorNb = (uint8_t) *nbSensors;
		index += sizeof(uint8_t);

		for (i = 0; i < msg->dataToRead.sensorsArray.sensorNb; ++i) {

		    msg->dataToRead.sensorsArray.sensorsActive[i] = (bool) *(buffer + index);
		    index += sizeof(uint8_t);

		    msg->dataToRead.sensorsArray.sensors[i] = (SensorId_e) *(buffer + index);
		    index += sizeof(uint8_t);

		    msg->dataToRead.sensorsArray.periodSensor[i] = (Period_e) *(buffer + index);
		    index += sizeof(uint8_t);

		}

	  }

}
