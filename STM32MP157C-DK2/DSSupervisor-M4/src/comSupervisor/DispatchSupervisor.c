/**
 * @file : DispatchSupervisor.c
 * @brief :
 * @version
 * @date : June 4, 2021
 * @author: Arnaud
 */

#include "sensorsManager/SensorManager.h"
#include "comSupervisor/PostmanSupervisor.h"
#include "processorSupervisor/MeasuresProcsessorSupervisor.h"
#include "comSupervisor/InterCoreProtocol.h"
#include "comSupervisor/DispatchSupervisor.h"
#include "commun.h"
#include "utils/GPIOS.h"



//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////
//				Variables Privées				//
//////////////////////////////////////////////////////////////////////////////////

static S_MessageToRead_t myMessageToRead;
static uint8_t * myVUARTbufferGeneral;
static uint8_t myVUARTbuffer[3];

//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Privées			//
//////////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Publiques				//
//////////////////////////////////////////////////////////////////////////////////


extern void DispatchSupervisor_Run(){

	uint16_t bytesToRead = sizeof(CMD_e) + sizeof(uint16_t);

	if( PostmanSupervisor_Recept() == false ){
		return;
	}

	/* Lecture de la commande et de la taille du message */
	PostmanSupervisor_Read(myVUARTbuffer, bytesToRead);

	InterCoreProtocol_decodeMessage(myVUARTbuffer, &myMessageToRead, bytesToRead);
	bytesToRead += myMessageToRead.size;

	myVUARTbufferGeneral = calloc(1, bytesToRead);

	/* Switch de la lecture de trame */
	if(myMessageToRead.size != 0){
	    	/* Lecture de l'ensemble de la trame */
		PostmanSupervisor_Read(myVUARTbufferGeneral, bytesToRead);
		InterCoreProtocol_decodeMessage(myVUARTbufferGeneral, &myMessageToRead, bytesToRead );
	}

	free(myVUARTbufferGeneral);


	/* Switch de l'opération de la trame */
	switch (myMessageToRead.command) {

		case ASK_START:

			if(1){}

			SensorsArray_t array = myMessageToRead.dataToRead.sensorsArray;
			ModeId_e mode = myMessageToRead.dataToRead.modeId;
			SessionId session = myMessageToRead.dataToRead.sessionId;
			SubModeId_e subMode = myMessageToRead.dataToRead.subModeId;

			SensorManager_startSession(session , mode, subMode , array);
			MeasuresProcessor_StartSession(session , mode, subMode , array);

			break;

		case ASK_STOP:

			SensorManager_stopSession();
			break;

		case ASK_NEW_MSG:

			MeasuresProcessor_AskMeasuresArray();

			break;

		default:
			break;
	}

}





