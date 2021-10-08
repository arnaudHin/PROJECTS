/**
 * @file MetaMesuresMonitor.c
 * @brief 
 * @date Juin 2021
 * @authors Robin Leprince
 * @version 1.0
 */

#include <pthread.h>

#include "MetaMeasuresMonitor.h"
#include "../common.h"
#include "../comDSMonitorApp/ProxySessionArchiver.h"

//////////////////////////////////////////////////////////////////////////////
//								Structures									//
//////////////////////////////////////////////////////////////////////////////

/**
 * Etats que peut prendre la MàE
 *
 * \enum state MàE MetaMeasuresMonitor
 */
typedef enum
{
	S_MMM_FORGET=0,			/*< S_FORGET */
	S_MMM_WAITING_ORDER,	/*< S_WAITING_ORDER */
	S_MMM_RUNNING,			/*< S_RUNNNING */
	S_MMM_DEATH,			/*< S_DEATH */
	MMM_NB_STATE,			/*< NB_STATE */
} M_MetaMeasures_State_e;

/**
 * Actions que la MàE doit effectuer
 *
 * \enum Action MàE MetaMeasuresMonitor
 */
typedef enum
{
	A_MMM_NOP=0,       		/**< A_IDLE */
	A_MMM_WAITING_ORDER,	/**< A_WAITING_ORDER */
	A_MMM_RUNNING,			/**< A_RUNNING */
	A_MMM_TIMEOUT,			/**< A_TIMEOUT */
	MMM_NB_ACTION			/*< NB_ACTION */
} M_MetaMeasures_Action_e;

/**
 * Evènements que la MàE doit gérer
 *
 * \enum Event MàE MetaMeasuresMonitor
 */
typedef enum
{
	E_MMM_START=0, 		/**< E_START */
	E_MMM_STOP,			/**< E_STOP */
	E_MMM_START_MM,		/**< E_START_MM */
	E_MMM_STOP_MM,		/**< E_STOP_MM */
	E_MMM_TIMEOUT,		/**< E_TIMEOUT */
	MMM_NB_EVENT		/**< NB_EVENT */
} M_MetaMeasures_Event_e;

/**
 * Transitions d'états de la MàE
 *
 * \struct transition MàE MetaMeasuresMonitor
 */
typedef struct
{
	M_MetaMeasures_State_e destinationState;
	M_MetaMeasures_Action_e action;
} M_MetaMeasures_Transition_t;

struct MetaMeasuresMonitor
{
	M_MetaMeasures_State_e currentState;
	M_MetaMeasures_Event_e currentEvent;
	M_MetaMeasures_Event_e currentAction;
};

static M_MetaMeasures_Transition_t stateMachine [MMM_NB_STATE][MMM_NB_EVENT] =
{
		//Start
		[S_MMM_DEATH][E_MMM_START] = {S_MMM_WAITING_ORDER, A_MMM_NOP},
		
		//Running
		[S_MMM_WAITING_ORDER][E_MMM_START_MM] = {S_MMM_RUNNING, A_MMM_RUNNING},

		//Waiting Order
		[S_MMM_RUNNING][E_MMM_STOP_MM] = {S_MMM_WAITING_ORDER, A_MMM_WAITING_ORDER},

		//Timeout
		[S_MMM_RUNNING][E_MMM_TIMEOUT] = {S_MMM_RUNNING, A_MMM_TIMEOUT},

		//Stop
		[S_MMM_WAITING_ORDER][E_MMM_STOP] = {S_MMM_DEATH, A_MMM_NOP},
		[S_MMM_RUNNING][E_MMM_STOP] = {S_MMM_DEATH, A_MMM_NOP},
};

//////////////////////////////////////////////////////////////////////////////
//							Variables privées								//
//////////////////////////////////////////////////////////////////////////////

/**
 * @brief Déclaration du Thread pour la fonction run
 */
static pthread_t threadRun;

static SessionId currentSessionId;

static MetaMeasuresMonitor_t myMetaMeasuresMonitor;
static M_MetaMeasures_Transition_t * myTransition;

static MetaMeasuresArray_t * myMetaMeasuresArray;

static Location_e location = MONITOR;

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions privées						//
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction MetaMeasuresMonitor_getMetaMeasuresMonitor
 * 
 * @brief	Met à jour le tableau de Meta Mesures capturées pour un 
 * 			Champ De Mesures.
 */
static void MetaMeasuresMonitor_getMetaMeasuresMonitor();

/**
 * Fonction MetaMeasuresMonitor_getClockCycleCount
 * 
 * @brief	Récupère le nombre de cycles d'horloge pour un Champ De 
 * 			Mesures.
 * 
 * @return Le nombre de cycles d'horloge
 */
static uint32_t MetaMeasuresMonitor_getClockCycleCount();

/**
 * Fonction MetaMeasuresMonitor_getTasksPerCycleCount
 * 
 * @brief	Récupère le nombre de taches par cycle d'horloge pour un 
 * 			Champ De Mesures.
 * 
 * @return Le nombre de taches par cycle d'horloge
 */
static uint32_t MetaMeasuresMonitor_getTasksPerCycleCount();

/**
 * Fonction MetaMeasuresMonitor_getCPUPercentagePerTask
 * 
 * @brief	Récupère le pourcentage d'utilisation du CPU par tache 
 * 			pour un Champ De Mesures.
 * 
 * @return Le pourcentage d'utilisation du CPU par tache
 */
static float MetaMeasuresMonitor_getCPUPercentagePerTask();

/**
 * Fonction MetaMeasuresMonitor_run
 * 
 * @brief	Gère les états de la MAE de MMM et les actions à réaliser d'un 
 * 			état à l'autre lorsqu'un évènement intervient.
 */
static void * MetaMeasuresMonitor_run();

/**
 * Fonction MetaMeasuresMonitor_performAction
 * 
 * @brief	Réalise les actions.
 */
static void MetaMeasuresMonitor_performAction (M_MetaMeasures_Action_e act);

//////////////////////////////////////////////////////////////////////////////
//							Fonctions publicques							//
//////////////////////////////////////////////////////////////////////////////

void MetaMeasuresMonitor_new()
{
	myMetaMeasuresMonitor.currentState = S_MMM_DEATH;
}

void MetaMeasuresMonitor_start()
{
	/* Création d'un thread qui appelle la fonction run() */
	uint8_t result = pthread_create(&threadRun, NULL, MetaMeasuresMonitor_run, NULL);
	if (result == -1)
	{
		int codeErreur = errno;
		printf("Erreur à la création du thread : %s\n", strerror(codeErreur));
	}
	myMetaMeasuresMonitor.currentEvent = E_MMM_START;
}

void MetaMeasuresMonitor_stop()
{
	/* Fermeture du thread */
	uint8_t result = pthread_join(threadRun, NULL);
	if (result == -1){
		int codeErreur = errno;
		printf("Erreur en joignant le thread : %s\n", strerror(codeErreur));
	}
	myMetaMeasuresMonitor.currentEvent = E_MMM_STOP;
}

void MetaMeasuresMonitor_free()
{
	myMetaMeasuresMonitor.currentState = S_MMM_DEATH;
}

void MetaMeasuresMonitor_startMetaMeasures(SessionId sessionId)
{
	myMetaMeasuresMonitor.currentEvent = E_MMM_START_MM;
	currentSessionId = sessionId;
}

void MetaMeasuresMonitor_stopMetaMeasures()
{
	myMetaMeasuresMonitor.currentState = E_MMM_STOP_MM;
}

MetaMeasuresMonitor_t * MetaMeasuresMonitor_get()
{
	return &myMetaMeasuresMonitor;
}

void MetaMeasuresMonitor_set(MetaMeasuresMonitor_t *metaMeasuresMonitor)
{
	myMetaMeasuresMonitor.currentState = metaMeasuresMonitor->currentState;
	myMetaMeasuresMonitor.currentEvent = metaMeasuresMonitor->currentEvent;
	myMetaMeasuresMonitor.currentAction = metaMeasuresMonitor->currentAction;
}

//////////////////////////////////////////////////////////////////////////////
//							Fonctions privées								//
//////////////////////////////////////////////////////////////////////////////

static void MetaMeasuresMonitor_getMetaMeasuresMonitor()
{
	myMetaMeasuresArray->clockCycleCount = MetaMeasuresMonitor_getClockCycleCount();
	myMetaMeasuresArray->tasksPerCycleCount = MetaMeasuresMonitor_getTasksPerCycleCount();
	myMetaMeasuresArray->percentagePerTask = MetaMeasuresMonitor_getCPUPercentagePerTask();
}

static uint32_t MetaMeasuresMonitor_getClockCycleCount()
{
	return 0;
}

static uint32_t MetaMeasuresMonitor_getTasksPerCycleCount()
{
	return 0;
}

static float MetaMeasuresMonitor_getCPUPercentagePerTask()
{
	return (float) 0;
}

static void * MetaMeasuresMonitor_run()
{
	M_MetaMeasures_State_e currentState = myMetaMeasuresMonitor.currentState;
	M_MetaMeasures_State_e newState;
	M_MetaMeasures_Event_e anEvent = myMetaMeasuresMonitor.currentEvent;
	M_MetaMeasures_Action_e anAction;
	while(currentState != S_MMM_DEATH)
	{
		anAction = stateMachine[currentState][anEvent].action;
		newState = stateMachine[currentState][anEvent].destinationState;
		if (stateMachine[currentState][anEvent].destinationState != S_MMM_FORGET)
		{
			MetaMeasuresMonitor_performAction(anAction);
			myMetaMeasuresMonitor.currentState = newState;
			myMetaMeasuresMonitor.currentAction = anAction;
		}
	}
	return NULL;
}

static void MetaMeasuresMonitor_performAction (M_MetaMeasures_Action_e act)
{
	switch (act)
	{
	case A_MMM_NOP :
		break;
	case A_MMM_WAITING_ORDER :
		break;
	case A_MMM_RUNNING :
		break;
	case A_MMM_TIMEOUT :
		MetaMeasuresMonitor_getMetaMeasuresMonitor();
		ProxySessionArchiver_storeMetaMeasures(myMetaMeasuresArray, location);
		break;
	default :
		break;
	}
}