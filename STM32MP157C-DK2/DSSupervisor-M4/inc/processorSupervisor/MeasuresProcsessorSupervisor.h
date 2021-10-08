/**
 * @file : MeasuresProcessorSupervisor.h
 * @brief :
 * @version
 * @date : June 4, 2021
 * @author: Arnaud
 */


#ifndef MEASURESPROCESSORSUPERVISOR_H_
#define MEASURESPROCESSORSUPERVISOR_H_

#include "commun.h"
#include "sensorsManager/SensorManager.h"
#include "comSupervisor/ProxySupervisorMeasuresProcessorApp.h"


//////////////////////////////////////////////////////////////////////////////////
//				Types énumérés					//
//////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn DavidsonStatus_e MeasuresProcessor_New()
 * @brief
 * @return
 */
extern DavidsonStatus_e MeasuresProcessor_New();



/**
 * @fn void MeasuresProcessor_SetMeasuresArray(MeasureArray_t[])
 * @brief
 * @param measuresArray :
 */
extern void MeasuresProcessor_SetMeasuresArray(MeasureArray_t * measuresArray);



/**
 * @fn void MeasuresProcessor_AskMeasuresArray()
 * @brief
 */
extern void MeasuresProcessor_AskMeasuresArray();


extern void MeasuresProcessor_StartSession(SessionId sessionId, ModeId_e modeId, SubModeId_e subeModeId, SensorsArray_t sensorsArray);

#endif /* MEASURESPROCESSORSUPERVISOR_H_ */
