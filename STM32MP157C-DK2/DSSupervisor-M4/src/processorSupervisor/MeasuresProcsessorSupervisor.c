/**
 * @file : MeasuresProcessorSupervisor.c
 * @brief :
 * @version
 * @date : June 4, 2021
 * @author: Arnaud
 */



#include "comSupervisor/DispatchSupervisor.h"
#include "comSupervisor/ProxySupervisorMeasuresProcessorApp.h"
#include "processorSupervisor/MeasuresProcsessorSupervisor.h"
#include "sensorsManager/SensorManager.h"
#include "commun.h"
#include "utils/GPIOS.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////
typedef enum{
	S_WAITING_ORDERS=0,
	S_RUNNING,
	NB_STATE
}State_e;

typedef enum{
	A_START_SESSION=0,
	A_STOP_SESSION,
	A_SET_MA,
	NB_ACTION
}Action_e;

typedef enum{
	E_START_SESSION=0,
	E_STOP_SESSION,
	E_SET_MA,
	NB_EVENT
}Event_e;


//////////////////////////////////////////////////////////////////////////////////
//				Variables Privées				//
//////////////////////////////////////////////////////////////////////////////////

static SessionId mySessionId;
static ModeId_e myModeId;
static SubModeId_e mySubModeId;
static SensorsArray_t mySensorsArray;
static MeasureArray_t myMeasuresArray[NB_SENSORS];
static MeasureArray_t myPreviousMeasuresArray[NB_SENSORS];
static MeasureArray_t myCurrentMeasuresArray[NB_SENSORS];

static bool sensorsToSend[NB_SENSORS];
static bool firstSession = true;
static S_DataToWrite_t myDataToWrite;

//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Privées			//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn void MeasuresProcessor_ComputeMeasuresArray()
 * @brief
 * @param
 */
static void MeasuresProcessor_ComputeMeasuresArray(MeasureArray_t * measuresArray);


//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Publiques				//
//////////////////////////////////////////////////////////////////////////////////


extern void MeasuresProcessor_SetMeasuresArray(MeasureArray_t * measuresArray){

	/* Mettre à jour la SensorArray */
	memcpy(&myCurrentMeasuresArray, measuresArray, sizeof(MeasureArray_t)*NB_SENSORS );

	/* compte */
	MeasuresProcessor_ComputeMeasuresArray(myCurrentMeasuresArray);

	/*  */
	myDataToWrite.sensorNb = mySensorsArray.sensorNb;
	myDataToWrite.sessionId = mySessionId;
	myDataToWrite.time = SensorManager_GetTimeMeasure();

	memcpy( &(myDataToWrite.measuresArray), &(myCurrentMeasuresArray), sizeof(MeasureArray_t)*NB_SENSORS);

	ProxySupervisorMeasuresProcessorApp_SetMeasuresArray(&myDataToWrite);
}



extern void MeasuresProcessor_AskMeasuresArray(){

	SensorManager_AskMeasuresArray();
}


extern void MeasuresProcessor_StartSession(SessionId sessionId, ModeId_e modeId, SubModeId_e subeModeId, SensorsArray_t sensorsArray){

  mySessionId = sessionId;
  myModeId = modeId;
  mySubModeId = subeModeId;
  mySensorsArray = sensorsArray;

}



extern void MeasuresProcessor_StopSession(){


}




//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Privées				//
//////////////////////////////////////////////////////////////////////////////////

static void MeasuresProcessor_ComputeMeasuresArray(MeasureArray_t * measuresArray){


	if(myModeId == SST)
	{

//	      for(int i=0; i<NB_SENSORS; i++)
//	      {
//		      SensorId_e currentSensorId = myCurrentMeasuresArray[i].sensorId;
//
//		      if(currentSensorId == TEMP || currentSensorId == PRES || currentSensorId == HUMI)
//		      {
//			      if( abs(myCurrentMeasuresArray[i].measure[0] - myPreviousMeasuresArray[i].measure[0]) )
//			      {
//				      /* Envoyer le CDM entier */
//				      //sizeToSend += 4;
//				      myMeasuresArrayToSend[i].sensorId = currentSensorId;
//				      myMeasuresArrayToSend[i]->measure[0] = myCurrentMeasuresArray[i].measure[0];
//			      }
//		      }
//		      else
//		      {
//			      if(myCurrentMeasuresArray[i].measure[0] != myPreviousMeasuresArray[i].measure[0])
//			      {
//				      /* Envoyer le CDM entier */
//				      //sizeToSend += 4;
//				      myMeasuresArrayToSend[i].sensorId = currentSensorId;
//				      myMeasuresArrayToSend[i]->measure[0] = myCurrentMeasuresArray[i].measure[0];
//			      }
//			      if(myCurrentMeasuresArray[i].measure[1] != myPreviousMeasuresArray[i].measure[1])
//			      {
//				      /* Envoyer le CDM entier */
//				      //sizeToSend += 4;
//				      myMeasuresArrayToSend[i].sensorId = currentSensorId;
//				      myMeasuresArrayToSend[i]->measure[1] = myCurrentMeasuresArray[i].measure[1];
//			      }
//			      if(myCurrentMeasuresArray[i].measure[2] != myPreviousMeasuresArray[i].measure[2])
//			      {
//				      /* Envoyer le CDM entier */
//				      //sizeToSend += 4;
//				      myMeasuresArrayToSend[i].sensorId = currentSensorId;
//				      myMeasuresArrayToSend[i]->measure[2] = myCurrentMeasuresArray[i].measure[2];
//			      }
//		      }
//	      }
//
//		//send?
//		//memoriser ancien CDM ici?

	    ON_LED(LED5_GREEN);


	}

	//myPreviousMeasuresArray = myCurrentMeasuresArray;

}









