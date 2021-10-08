/**
 * @file SessionManager.c
 * @brief 
 * @date Juin 2021
 * @authors Robin Leprince
 * @version 1.0
 */


#include "SessionManager.h"

#include "../comDSMonitorSupervisor/ProxyMeasuresProcessorSupervisor.h"
#include "../comDSMonitorApp/ProxySessionArchiver.h"
#include "../comDSMonitorSupervisor/DispatcherDSMonitorSupervisor.h"
#include "MetaMeasuresMonitor.h"
#include "../utils.h"

//////////////////////////////////////////////////////////////////////////////
//							Variables privées								//
//////////////////////////////////////////////////////////////////////////////

static SessionId mySessionId;
static ModeId_e myModeId;
static SubModeId_e mySubModeId;
static SensorsArray_t mySensorArray;
static Time myTimeStart;
static M_DataOrder_t mydataToWrite;

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions privées						//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//							Fonctions publiques								//
//////////////////////////////////////////////////////////////////////////////

void SessionManager_startSession(SessionId sessionId, ModeId_e modeId, SubModeId_e submodeId, SensorsArray_t sensorsArray, Time time)
{

	/* Assignation des paramètres aux variables privées */
	mySessionId = sessionId;
	myModeId = modeId;
	mySubModeId = submodeId;
	mySensorArray.sensorNb = sensorsArray.sensorNb;
	for (int i = 0; i < mySensorArray.sensorNb; i++)
	{
		mySensorArray.sensorActive[i] = sensorsArray.sensorActive[i];
		mySensorArray.sensors[i] = sensorsArray.sensors[i];
		mySensorArray.periodSensor[i] = sensorsArray.periodSensor[i];
	}
	myTimeStart = time;

	DispatcherDSMS_setInstant( ((bool)submodeId) );

	/* Transmission des parametres de la Session au Proxy SessionArchiver pour envoi à DSApp */
	ProxySessionArchiver_storeBeginSession(sessionId, modeId, submodeId, sensorsArray, time);
	
	/* Transmission de Start Session avec l'ID à MetaMeasuresMonitor */
	// MetaMeasuresMonitor_startMetaMeasures(currentSessionId);

	/* Creation de la trame de DataOrder ASK_START */
	mydataToWrite.sessionId = mySessionId;
	mydataToWrite.modeId = myModeId;
	mydataToWrite.subModeId = mySubModeId;
	mydataToWrite.sensorsArray.sensorNb = mySensorArray.sensorNb;
	for (int i = 0; i < mySensorArray.sensorNb; i++)
	{
		mydataToWrite.sensorsArray.sensorActive[i] = mySensorArray.sensorActive[i];
		mydataToWrite.sensorsArray.sensors[i] = mySensorArray.sensors[i];
		mydataToWrite.sensorsArray.periodSensor[i] = mySensorArray.periodSensor[i];
	}
	/* Transmission de la trame au Proxy MeasuresProcessorSupervisor pour envoi à DSSupervisor */
	ProxyMeasuresProcessorSupervisor_askStartSession(&mydataToWrite);

	usleep(100 * 1000);
	DispatcherDSMS_toggleCapture();

}

void SessionManager_stopSession(Time stopTime)
{

	DispatcherDSMS_toggleCapture();
	usleep(100 * 1000);

	ProxySessionArchiver_storeEndSession(stopTime);
	
	/* Creation de la trame de DataOrder ASK_STOP */
	/* trame vide car DataOrder inutile dans le cas d'un ASK_STOP */
	/* Transmission de la trame au Proxy MeasuresProcessorSupervisor pour envoi à DSSupervisor */
	ProxyMeasuresProcessorSupervisor_askStopSession();

	// /* Transmission de Stop Session à MetaMeasuresMonitor */
	// MetaMeasuresMonitor_stopMetaMeasures();
}