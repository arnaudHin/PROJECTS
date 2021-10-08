/**
 * @file ProxyMeasuresProcessorSupervisor.c
 * @brief Ce fichier imite la classe MeasuresProcessor de DSSupervisor.
 * @date Mai 2021
 * @authors Robin
 * @version 1.0
 */

#include "common.h"

#include "ProxyMeasuresProcessorSupervisor.h"
#include "PostmanDSMonitorSupervisor.h"
#include "IntercoreProtocol.h"

//////////////////////////////////////////////////////////////////////////////
//							Variables Privées								//
//////////////////////////////////////////////////////////////////////////////

static uint8_t bufferAskStart[MAX_ASK_MSG];		// message ASK_START encodé à envoyer via la Communication Intercoeur
static uint8_t bufferAskStop[MIN_ASK_MSG];		// message ASK_STOP encodé à envoyer via la Communication Intercoeur
static uint8_t bufferAskNM[MIN_ASK_MSG];		// message ASK_MA encodé à envoyer via la Communication Intercoeur

static M_MessageOrder_t messageToWrite;

//////////////////////////////////////////////////////////////////////////////
//							Fonctions Publiques								//
//////////////////////////////////////////////////////////////////////////////

void ProxyMeasuresProcessorSupervisor_askStartSession(M_DataOrder_t *dataToWrite)
{
	//printf("Envoi de ASK_START à DSSupervisor via le Proxy MeasuresProcessorSupervisor\n");
	/* Creation de la trame de MessageOrder ASK_START */
	messageToWrite.command = ASK_START;
	messageToWrite.size = MAX_ASK_DATA;
	messageToWrite.dataToWrite = *dataToWrite;

	IntercoreProtocol_encodeMessage(&messageToWrite, bufferAskStart);
	PostmanDSMS_write(bufferAskStart, messageToWrite.size + MIN_ASK_MSG);
}

void ProxyMeasuresProcessorSupervisor_askStopSession()
{
	/* Creation de la trame de MessageOrder ASK_STOP */
	messageToWrite.command = ASK_STOP;
	messageToWrite.size = MIN_ASK_DATA;
	
	IntercoreProtocol_encodeMessage(&messageToWrite, bufferAskStop);
	PostmanDSMS_write(bufferAskStop, messageToWrite.size + MIN_ASK_MSG);
	//Display_display(bufferAskStop);
}

void ProxyMeasuresProcessorSupervisor_askMeasuresArray()
{
	printf("Ebvoi de ASK_MA à DSSupervisor via le Proxy MeasuresProcessorSupervisor\n");
	/* Creation de la trame de MessageOrder ASK_NEW_MSG */
	messageToWrite.command = ASK_NEW_MSG;
	messageToWrite.size = MIN_ASK_DATA;

	IntercoreProtocol_encodeMessage(&messageToWrite, bufferAskNM);
	PostmanDSMS_write(bufferAskNM, messageToWrite.size + MIN_ASK_MSG);
}
