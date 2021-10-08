/**
 * @file : SensorManager.c
 * @brief :
 * @version
 * @date : May 10, 2021
 * @author: Arnaud
 */


#include "utils/GPIOS.h"
#include "commun.h"
#include <stdbool.h>

#include "sensorsManager/sensors/Temperature.h"
#include "sensorsManager/sensors/Pressure.h"
#include "sensorsManager/sensors/Humidity.h"
#include "sensorsManager/SensorManager.h"
#include "processorSupervisor/MeasuresProcsessorSupervisor.h"

#include "utils/TIMER.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////

typedef enum{
	S_FORGET=0,
	S_CHECK,
	S_IDLE,
	S_RUNNING,
	S_ERROR,
	NB_STATE
}State_e;

typedef enum{
	A_NOP=0,
	A_START_CONNECT_SB_AND_VERIFY,
	A_VERIFY_CONNECTION_SB,
	A_SET_CONNECTION_SB_DEMANDED_TRUE,
	A_SET_CONNECTION_SB,
	A_CAPTURE_MA,
	A_SET_MA,
	A_SET_SA,
	A_START_SESSON,
	A_STOP_DESTROY,
	NB_ACTION
}Action_e;

typedef enum{
	E_NOP=0,
	E_START,
	E_ASK_CONNECTION_STATUS_SB,
	E_CONNECTION_SB_OK,
	E_CONNECTION_SB_KO,
	E_CONNECTION_SB_KO_C_MAX,
	E_CONNECTION_SB_DEMANDED_TRUE,
	E_START_SESSION,
	E_STOP_SESSION,
	E_TIMER_IT,
	E_ASK_MA,
	E_SET_SA,
	E_STOP,
	NB_EVENT
}Event_e;


typedef struct{
	State_e nexteState;
	Action_e actionToDo;
}Transition_t;


struct SensorManager{
	Sensors_t sensors;
	Event_e myEvent;
	State_e myState;
};


//////////////////////////////////////////////////////////////////////////////////
//				Variables Privées				//
//////////////////////////////////////////////////////////////////////////////////
static Transition_t transitionSystem[NB_STATE-1][NB_EVENT] = {
	[S_CHECK][E_START] = {S_CHECK, A_START_CONNECT_SB_AND_VERIFY},
	[S_CHECK][E_ASK_CONNECTION_STATUS_SB] = {S_CHECK, A_SET_CONNECTION_SB_DEMANDED_TRUE},
	[S_CHECK][E_CONNECTION_SB_KO_C_MAX] = {S_ERROR, A_NOP},
	[S_CHECK][E_CONNECTION_SB_KO] = {S_CHECK, A_START_CONNECT_SB_AND_VERIFY},
	[S_CHECK][E_CONNECTION_SB_OK] = {S_IDLE, A_NOP},
	[S_IDLE][E_ASK_CONNECTION_STATUS_SB] = {S_IDLE, A_SET_CONNECTION_SB},
	[S_IDLE][E_CONNECTION_SB_DEMANDED_TRUE] = {S_IDLE, A_SET_CONNECTION_SB},
	[S_IDLE][E_START_SESSION] = {S_RUNNING, A_START_SESSON},
	[S_RUNNING][E_STOP_SESSION] = {S_IDLE, A_NOP},
	[S_RUNNING][E_ASK_CONNECTION_STATUS_SB] = {S_RUNNING, A_SET_CONNECTION_SB},
	[S_RUNNING][E_ASK_MA] = {S_RUNNING, A_SET_MA},
	[S_RUNNING][E_SET_SA] = {S_RUNNING, A_SET_SA},
	[S_RUNNING][E_TIMER_IT] = {S_RUNNING, A_CAPTURE_MA},
	[S_RUNNING][E_CONNECTION_SB_KO] = {S_ERROR, A_NOP}

};


static SensorManager_t * mySensorManager;
static SessionId mySessionId;
static ModeId_e myModeId;
static SubModeId_e mySubModeId;
static SensorsArray_t mySensorsArray;
static MeasureArray_t myMeasuresArray[NB_SENSORS];
static bool myMeasuresArrayReady;
static SensorConnectionStatus_e mySensorConnectionStatus[NB_SENSORS];
static SensorBoardConnectionStatus_e mySensorBoardConectionStatus;

static volatile bool mySensorReaderStatus;
static volatile bool mySensorCounter;


static Transition_t * myTransition;

static volatile TimeMeasure myTimeMeasure;
static volatile uint64_t myCounetrSensors;


//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Privées			//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn DavidsonStatus_e SensorManager_StartITTimer()
 * @brief Démarrer l'interruption du timer 4
 * @return DavidsonStatus_e : Etat du système
 */
static DavidsonStatus_e SensorManager_StartITTimer();

/**
 * @fn DavidsonStatus_e SensorManager_StopITTimer()
 * @brief : Stopper l'interruption du timer 4
 * @return DavidsonStatus_e : Etat du système
 */
static DavidsonStatus_e SensorManager_StopITTimer();


/**
 * @fn SensorBoardConnectionStatus_e SensorManager_verifySensorBoardConnectionStatus()
 * @brief : Vérifier l'état de connexion avec tous les capteurs, et renvoyer l'état
 * 	général de le connexion avec SensorBoard. Si un seul capteur n'est pas connecté
 * 	alors cette fonction retourne NOT_CONNECTED.
 * @return SensorBoardConnectionStatus_e : Etat de connexion avec SensorBoard
 */
static SensorBoardConnectionStatus_e SensorManager_verifySensorBoardConnectionStatus();

/**
 * @fn bool SensorManager_CheckSensorId(SensorId_e, SensorId_e[], uint8_t)
 * @brief
 * @param sensorId
 * @param sensorIdTab
 * @param size
 * @return bool
 */
static bool SensorManager_CheckSensorId(SensorId_e sensorId, SensorId_e sensorIdTab[], uint8_t size);

/**
 * @fn void SensorManager_PerformAction(Action_e)
 * @brief
 * @param action
 */
static void SensorManager_PerformAction(Action_e action);

/**
 * @fn void updateCounter()
 * @brief : Mettre à jour les compteurs
 */
static void updateCounter();



//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Publiques				//
//////////////////////////////////////////////////////////////////////////////////

extern DavidsonStatus_e SensorManager_New(){

	DavidsonStatus_e status;
	uint8_t i;

	mySensorManager = NULL;

	mySensorManager = calloc(1, sizeof(SensorManager_t));

	if(mySensorManager == NULL){
		return DAV_ERROR;
	}

	myMeasuresArrayReady = false;
	mySensorReaderStatus = false;
	mySensorManager->myState = S_CHECK;
	mySensorManager->myEvent = E_START;

	for (i = 0;  i < NB_SENSORS; ++ i) {
	    myMeasuresArray[i].sensorId = (SensorId_e) i;
	}


	status = Temperature_New();
	mySensorManager->sensors.Temperature = Temperature_Get();

	status = Pressure_New();
	mySensorManager->sensors.Pressure = Pressure_Get();

	status = Humidity_New();
	mySensorManager->sensors.Humidity = Humidity_Get();

	TIMER4_init();

	return status;
}

extern DavidsonStatus_e SensorManager_Start(){

	SensorManager_ConnectToSensorBoard();
	SensorManager_verifySensorBoardConnectionStatus();

	SensorManager_StopITTimer();

	return DAV_OK;
}

extern void SensorManager_Run(){

	if(mySensorManager->myEvent != E_NOP){
	    myTransition = &transitionSystem[mySensorManager->myState][mySensorManager->myEvent];
	    SensorManager_PerformAction(myTransition->actionToDo);
	    mySensorManager->myState = myTransition->nexteState;
	}
}


extern DavidsonStatus_e SensorManager_Free(){

	SensorManager_StopITTimer();
	free(mySensorManager);
	return DAV_OK;
}


extern void SensorManager_ConnectToSensorBoard(){

	SensorConnectionStatus_e statusTemp;

	statusTemp = Temperature_InitConnectionSensorBoard();
	mySensorConnectionStatus[TEMP] = statusTemp;

	statusTemp = Pressure_InitConnectionSensorBoard();
	mySensorConnectionStatus[PRES] = statusTemp;

	statusTemp = Humidity_InitConnectionSensorBoard();
	mySensorConnectionStatus[HUMI] = statusTemp;
}

extern void SensorManager_startSession(SessionId sessionId, ModeId_e modeId, SubModeId_e subeModeId, SensorsArray_t sensorsArray){

	mySessionId = sessionId;
	myModeId = modeId;
	mySubModeId = subeModeId;
	mySensorsArray = sensorsArray;
	myTimeMeasure = 0;
	myCounetrSensors = 0;

	/* Démarrer interruption Timer */
	SensorManager_StartITTimer();
}

extern void SensorManager_stopSession(){

	myTimeMeasure = 0;
	myCounetrSensors = 0;
	/* Stopper interruption Timer */
	SensorManager_StopITTimer();
}

extern void SensorManager_ReadMeasuresArray(){

	if ( SensorManager_CheckSensorId(TEMP, mySensorsArray.sensors, mySensorsArray.sensorNb) ) {
		Temperature_GetMeasure();
	}

	if ( SensorManager_CheckSensorId(PRES, mySensorsArray.sensors, mySensorsArray.sensorNb) ) {
		Pressure_GetMeasure();
	}

	if ( SensorManager_CheckSensorId(HUMI, mySensorsArray.sensors, mySensorsArray.sensorNb) ) {
		Humidity_GetMeasure();
	}

	mySensorReaderStatus = false;

	myMeasuresArray[TEMP].measure[0] = Temperature_GetValue();
	myMeasuresArray[PRES].measure[0] = Pressure_GetValue();
	myMeasuresArray[HUMI].measure[0] = Humidity_GetValue();

	myMeasuresArray[GYRO].measure[0] = 30.5;
	myMeasuresArray[GYRO].measure[1] = 31.7;
	myMeasuresArray[GYRO].measure[2] = 32.9;

	myMeasuresArray[MAGN].measure[0] = 40.5;
	myMeasuresArray[MAGN].measure[1] = 41.7;
	myMeasuresArray[MAGN].measure[2] = 42.9;

	myMeasuresArray[ACCE].measure[0] = 50.5;
	myMeasuresArray[ACCE].measure[1] = 51.7;
	myMeasuresArray[ACCE].measure[2] = 52.9;

	mySensorReaderStatus = true;
}

extern void SensorManager_AskMeasuresArray(){

	/* Attente d'un champs de measure disponible */
	while(mySensorCounter != true){
	    uint8_t a;
	}

	MeasuresProcessor_SetMeasuresArray( myMeasuresArray );
	mySensorCounter = false;
}

void TIMER4_user_handler_it_1ms(){

	/* Mise à jour de l'état des capteurs */
	SensorManager_ReadMeasuresArray();
	updateCounter();
	TOGGLE_LED(LED7_ORANGE);

	if(mySensorReaderStatus != false){
	    mySensorCounter = true;
	}
}

extern SensorManager_t * SensorManager_Get(){
	return mySensorManager;
}



//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Privées				//
//////////////////////////////////////////////////////////////////////////////////


static void SensorManager_PerformAction(Action_e action){

	switch (action) {

		case A_NOP:

			break;
		case A_START_CONNECT_SB_AND_VERIFY:
			SensorManager_ConnectToSensorBoard();
			SensorManager_verifySensorBoardConnectionStatus();

			break;
		case A_VERIFY_CONNECTION_SB:
			SensorManager_verifySensorBoardConnectionStatus();

			break;
		case A_SET_CONNECTION_SB_DEMANDED_TRUE:


			break;
		case A_SET_CONNECTION_SB:

			break;

		case A_CAPTURE_MA:


			break;
		case A_SET_MA:

			break;
		case A_SET_SA:

			break;
		case A_START_SESSON:

			break;
		default:
			break;
	}

}



static SensorBoardConnectionStatus_e SensorManager_verifySensorBoardConnectionStatus(){

	SensorBoardConnectionStatus_e currentSensorBoardConectionStatus = CONNECTED;

	for (uint8_t sensor = 0; sensor < NB_SENSORS; ++sensor) {

	if(mySensorConnectionStatus[sensor] == SENSOR_NOTCONNECTED){
			currentSensorBoardConectionStatus = NOTCONNECTED;
		}
	}

	return currentSensorBoardConectionStatus;
}


static DavidsonStatus_e SensorManager_StartITTimer(){
	TIMER4_run();
	return DAV_OK;
}


static DavidsonStatus_e SensorManager_StopITTimer(){
	TIMER4_stop();
	return DAV_OK;
}

static bool SensorManager_CheckSensorId(SensorId_e sensorId, SensorId_e sensorIdTab[], uint8_t size){

	for(uint8_t i = 0 ; i<size ; i++){

		if(sensorIdTab[i] == sensorId){
			return true;
		}
	}

	return false;
}

extern uint32_t SensorManager_GetTimeMeasure(){
	return myTimeMeasure;
}

static void updateCounter(){

    myTimeMeasure += 50;
    myCounetrSensors += 50;
    //if(myCounetrSensors > )

}



