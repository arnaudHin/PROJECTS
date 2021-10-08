/**
 * @file ProxyMeasuresProcessorSupervisor.h
 * @brief Ce fichier imite la classe MeasuresProcessor de DSSupervisor.
 * @date Mai 2021
 * @authors Robin
 * @version 1.0
 */

#ifndef PROXY_MEASURES_PROCESSOR_SUPERVISOR_H_
#define PROXY_MEASURES_PROCESSOR_SUPERVISOR_H_

#include "../common.h"
#include "../utils.h"

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction askStartSession ProxyMeasuresProcessorSupervisor
 * 
 * @brief	Crée une trame de demande de StartSession à envoyer, l'encode, puis 
 * 			l'envoie à DSSupervisor via la Communication Intercoeur.
 * 
 * @param dataToWrite : le pointeur vers la trame de Data décodée en structure à encoder puis envoyer
 */
extern void ProxyMeasuresProcessorSupervisor_askStartSession(M_DataOrder_t *dataToWrite);

/**
 * Fonction askStopSession ProxyMeasuresProcessorSupervisor
 * 
 * @brief	Crée une trame de demande de StopSession à envoyer, l'encode, puis 
 * 			l'envoie à DSSupervisor via la Communication Intercoeur.
 */
extern void ProxyMeasuresProcessorSupervisor_askStopSession();

/**
 * Fonction askMeasuresArray ProxyMeasuresProcessorSupervisor
 * 
 * @brief	Crée une trame de demande de MeasureArray à envoyer, l'encode, puis 
 * 			l'envoie à DSSupervisor via la Communication Intercoeur.
 */
extern void ProxyMeasuresProcessorSupervisor_askMeasuresArray();

// extern void ProxyMeasuresProcessorSupervisor_storeMeasuresArray(MeasuresArray_t *measuresArray);

#endif /* PROXY_MEASURES_PROCESSOR_SUPERVISOR_H_ */