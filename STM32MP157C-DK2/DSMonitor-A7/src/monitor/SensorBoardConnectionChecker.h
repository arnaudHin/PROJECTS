/**
 * @file SensorBoardConnectionChecker.h
 * @brief 
 * @date Juin 2021
 * @authors Arnaud hincelin
 * @version 1.0
 */

#ifndef SB_CONNECTION_CHECKER_H_
#define SB_CONNECTION_CHECKER_H_

typedef struct SBConnection_Checker SBConnection_Checker_t;

//////////////////////////////////////////////////////////////////////////////
//					   Prototypes de fonctions Publiques				    //
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction New SensorBoardConnectionChecker
 * 
 * @brief 
 */
extern void SensorBoardConnectionChecker_New();

/**
 * Fonction Start SensorBoardConnectionChecker
 * 
 * @brief 
 */
extern void SensorBoardConnectionChecker_start();

/**
 * Fonction Stop SensorBoardConnectionChecker
 * 
 * @brief 
 */
extern void SensorBoardConnectionChecker_stop();

/**
 * Fonction Free SensorBoardConnectionChecker
 * 
 * @brief 
 */
extern void SensorBoardConnectionChecker_free();

/**
 * Fonction SensorBoardConnectionChecker_Get
 * 
 * @brief 
 * 
 * @return
 */
extern SBConnection_Checker_t * SensorBoardConnectionChecker_Get();

/**
 * Fonction SensorBoardConnectionChecker_SetSensorBoardConnectionStatus
 * 
 * @brief Met à jour le statut actuel de connection à SENSORBOARD.
 * 
 * @param sensorBoardConnectionStatus : le statut à définir.
 */
extern void SensorBoardConnectionChecker_setSensorBoardConnectionStatus(SensorBoardConnectionStatus_e sensorBoardConnectionStatus);


#endif /* SB_CONNECTION_CHECKER_H_ */


