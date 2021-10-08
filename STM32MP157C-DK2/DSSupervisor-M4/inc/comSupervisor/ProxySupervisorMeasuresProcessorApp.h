/**
 * @file : ProxySupervisorMeasuresProcessorApp.h
 * @brief :
 * @version
 * @date : June 3, 2021
 * @author: Arnaud
 */


#include <commun.h>
#include <comSupervisor/PostmanSupervisor.h>
#include <processorSupervisor/MeasuresProcsessorSupervisor.h>


#ifndef PROXYSUPERVISORMEASURESPROCESSORAPP_H__
#define PROXYSUPERVISORMEASURESPROCESSORAPP_H__


//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn void ProxySupervisorMeasuresProcessorApp_SetMeasuresArray(S_DataToWrite_t*)
 * @brief
 * @param dataToWrite
 */
extern void ProxySupervisorMeasuresProcessorApp_SetMeasuresArray(S_DataToWrite_t * dataToWrite);


/**
 * @fn void ProxySupervisorMeasuresProcessorApp_SetNoMeasuresArray()
 * @brief
 */
extern void ProxySupervisorMeasuresProcessorApp_SetNoMeasuresArray();


#endif /* PROXYSUPERVISORMEASURESPROCESSORAPP_H__ */

