/**
 * @file : SensorManager.h
 * @brief :
 * @version
 * @date : May 10, 2021
 * @author: Arnaud
 */

#ifndef SENSORMANAGER_H__
#define SENSORMANAGER_H__

#include "sensorsManager/sensors/Temperature.h"
#include "sensorsManager/sensors/Pressure.h"
#include "sensorsManager/sensors/Humidity.h"
#include "comSupervisor/ProxySupervisorGUI.h"
#include "commun.h"


//////////////////////////////////////////////////////////////////////////////////
//				Types						//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @typedef :
 */
typedef struct SensorManager SensorManager_t;



//////////////////////////////////////////////////////////////////////////////////
//				Types énumérés					//
//////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////

/*
STTS751------> 	TEMP
LIS2DW12------> ACC
LSM6DSO------> 	ACC + GYRO
LPS22HH------> 	PRESS
LIS2MDL------> 	MAGN
HTS221 ------> 	HUMID
*/

/**
 * @struct :
 * @brief :
 */
typedef struct{
	Temperature_t * Temperature;
	Pressure_t * Pressure;
	Humidity_t * Humidity;

}Sensors_t;


//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////


/**
 * @fn DavidsonStatus_e SensorManager_New()
 * @brief
 * @return
 */
extern DavidsonStatus_e SensorManager_New();


/**
 * @fn DavidsonStatus_e SensorManager_Free()
 * @brief
 * @return
 */
extern DavidsonStatus_e SensorManager_Free();


/**
 * @fn DavidsonStatus_e SensorManager_Start()
 * @brief
 * @return
 */
extern DavidsonStatus_e SensorManager_Start();


/**
 * @fn void SensorManager_Run()
 * @brief
 */
extern void SensorManager_Run();


/**
 * @fn DavidsonStatus_e SensorManager_Stop()
 * @brief
 * @return
 */
extern DavidsonStatus_e SensorManager_Stop();


/**
 * @fn void SensorManager_ConnectToSensorBoard()
 * @brief
 */
extern void SensorManager_ConnectToSensorBoard();


/**
 * @fn SensorManager_t SensorManager_Get*()
 * @brief
 * @return
 */
extern SensorManager_t * SensorManager_Get();


/**
 * @fn void setSensorBoardConnectionStatus(SensorBoardConnectionStatus_e*)
 * @brief
 * @param sensorBoardConectionStatus
 */
extern void setSensorBoardConnectionStatus(SensorBoardConnectionStatus_e * sensorBoardConectionStatus);


/**
 * @fn void SensorManager_ReadMeasuresArray()
 * @brief
 */
extern void SensorManager_ReadMeasuresArray();


/**
 * @fn void SensorManager_AskMeasuresArray()
 * @brief
 */
extern void SensorManager_AskMeasuresArray();


/**
 * @fn void SensorManager_startSession(SessionId, ModeId_e, SubModeId_e, SensorsArray_t)
 * @brief
 * @param sessionId
 * @param modeId
 * @param subeModeId
 */
extern void SensorManager_startSession(SessionId sessionId, ModeId_e modeId, SubModeId_e subeModeId, SensorsArray_t sensorsArray);

/**
 * @fn void stopSession()
 * @brief
 */
extern void SensorManager_stopSession();



/**
 * @fn uint32_t SensorManager_GetTimeMeasure()
 * @brief
 * @pre
 * @post
 * @return
 */
extern uint32_t SensorManager_GetTimeMeasure();



/**
 * @fn void TIMER4_user_handler_it_1ms()
 * @brief
 */
void TIMER4_user_handler_it_1ms();

#endif /* SENSORMANAGER_H__ */

