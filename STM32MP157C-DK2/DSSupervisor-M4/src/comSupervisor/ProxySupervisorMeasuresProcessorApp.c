/**
 * @file : ProxySupervisorMeasuresProcessorApp.c
 * @brief :
 * @version
 * @date : June 3, 2021
 * @Author: Arnaud
 */


#include "comSupervisor/ProxySupervisorMeasuresProcessorApp.h"
#include "comSupervisor/PostmanSupervisor.h"
#include "commun.h"
#include <stdlib.h>
#include "utils/GPIOS.h"
#include "comSupervisor/InterCoreProtocol.h"

//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//				Variables Privées				//
//////////////////////////////////////////////////////////////////////////////////

static S_MessageToWrite_t myMessageToWrite;
static uint8_t * myVUARTbuffer;

//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Privées			//
//////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Publiques				//
//////////////////////////////////////////////////////////////////////////////////

extern void ProxySupervisorMeasuresProcessorApp_SetMeasuresArray(S_DataToWrite_t * dataToWrite){

	uint16_t sizeMsg = 2 + 4 + 1 + 6*(3*4 +1) ;

	myMessageToWrite.command = ACK_MA;
	myMessageToWrite.size = sizeMsg;
	myMessageToWrite.dataToWrite = *dataToWrite;

	sizeMsg = sizeof(CMD_e) + sizeof(uint16_t) + myMessageToWrite.size ;

	myVUARTbuffer = calloc(1, sizeMsg ); //Allocation dynamique du CDM

	InterCoreProtocol_encodeMessage(myVUARTbuffer, &myMessageToWrite);

	PostmanSupervisor_Write(myVUARTbuffer, sizeMsg );

	free(myVUARTbuffer);
}












