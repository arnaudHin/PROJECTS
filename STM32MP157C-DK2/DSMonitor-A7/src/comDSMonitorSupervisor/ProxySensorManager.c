/**
 * @file ProxySensorManager.c
 * @brief Ce fichier imite la classe SensorManager de DSSupervisor.
 * @date Mai 2021
 * @authors Robin
 * @version 1.0
 */

#include "common.h"

#include "ProxySensorManager.h"
#include "PostmanDSMonitorSupervisor.h"
#include "IntercoreProtocol.h"

//////////////////////////////////////////////////////////////////////////////
//							Variables Privées								//
//////////////////////////////////////////////////////////////////////////////

static uint8_t bufferAskSBC[MIN_ASK_MSG];	// message ASK_SBC encodé à envoyer via la Communication Intercoeur

static M_MessageOrder_t messageToWrite;

//////////////////////////////////////////////////////////////////////////////
//							Fonctions Publiques								//
//////////////////////////////////////////////////////////////////////////////

void ProxySensorManager_askSensorBoardConnectionStatus()
{
	/* Creation de la trame de MessageOrder ASK_NEW_MSG */
	messageToWrite.command = ASK_NEW_MSG;
	messageToWrite.size = MIN_ASK_DATA;
	
	IntercoreProtocol_encodeMessage(&messageToWrite, bufferAskSBC);
	PostmanDSMS_write(bufferAskSBC, messageToWrite.size + MIN_ASK_MSG);
}
