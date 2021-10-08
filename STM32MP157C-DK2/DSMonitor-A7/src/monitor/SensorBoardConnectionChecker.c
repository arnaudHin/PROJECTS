/**
 * @file SensorBoardConnectionChecker.c
 * @brief 
 * @date Juin 2021
 * @authors Arnaud hincelin
 * @version 1.0
 */

#include <stdlib.h>
#include <pthread.h>
#include <mqueue.h>

#include "../utils.h"
#include "../common.h"
#include "SensorBoardConnectionChecker.h"


//////////////////////////////////////////////////////////////////////////////
//								Structures									//
//////////////////////////////////////////////////////////////////////////////

typedef enum
{
	S_FORGET=0,
    S_NEW,
    S_WAITING_GUI,
    S_WAITING_NEW_SESSION,
    S_RUNNING,
	S_DEATH,
    NB_STATE
} State_e;

typedef enum
{
    E_NEW=0,
    E_SET_SB_CONNECTION_STATUS,
	E_ASK_SB_CONNECTION_STATUS,
	E_START_CHECK_SB_CONNECTION_STATUS,
	E_STOP_CHECK_SB_CONNECTION_STATUS,
    NB_EVENT
} Event_e;

// typedef enum
// {
//     A_NOP=0,
// 	A_ASK_STATUS,
//     A_UPDTAE_STATUS,
//     NB_ACTION
// } Action_e;

/* Action de transition d'états */
typedef enum {
    A_NOP = 0, // Rien à faire
    A_FROM_WAITING_GUI_TO_WAITING_NEW_SESSION, /*ACTION entrée dans état waiting events count*/
    A_FROM_WAITING_NEW_SESSION_TO_RUNNING,
    A_FROM_RUNNING_TO_WAITU,
    A_FROM_LOGSCREEN_TO_WAITING_EVENTS_COUNT,
    A_FROM_LOGSCREEN_TO_MAINSCREEN,
    A_FROM_LOGSCREEN_TO_DEATH,
    A_FROM_MAINSCREEN_TO_DEATH,
} AdminUITransitionAction;

typedef struct{
	State_e nextState;
	Event_e actionToDo;
} Transition_t;



struct SBConnection_Checker{
    State_e myState;
    Event_e myEvent;
};

//////////////////////////////////////////////////////////////////////////////
//							Variables Privées								//
//////////////////////////////////////////////////////////////////////////////

// static Transition_t transitionSystem[NB_STATE-1][NB_EVENT] = {
// 	[S_NEW][E_NEW] = {S_WAITING_GUI, A_ASK_STATUS},
// 	[S_WAITING_GUI][E_SET_STATUS] = {S_WAITING_NEW_SESSION, A_UPDTAE_STATUS},


// };

static SBConnection_Checker_t mySBCC;
static Transition_t * myTransition;

static SensorBoardConnectionStatus_e mySensorBoardConnectionStatus;

//////////////////////////////////////////////////////////////////////////////
//					   Prototypes de fonctions Privées						//
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction SensorBoardConnectionChecker_run
 * 
 * @brief	Gère les états de la MAE de SBCC et les actions à réaliser d'un 
 * 			état à l'autre lorsqu'un évènement intervient.
 */
static void SensorBoardConnectionChecker_run();

/**
 * Fonction SensorBoardConnectionChecker_performAction
 * 
 * @brief	Réalise les actions.
 */
// static void SensorBoardConnectionChecker_performAction (Action_e act);

//////////////////////////////////////////////////////////////////////////////
//							Fonctions Publiques								//
//////////////////////////////////////////////////////////////////////////////

void SensorBoardConnectionChecker_New()
{

    mySBCC.myState = S_NEW;
    mySBCC.myEvent = E_NEW;
}

void SensorBoardConnectionChecker_start()
{
	
}

void SensorBoardConnectionChecker_stop()
{

}

void SensorBoardConnectionChecker_free()
{

}

SBConnection_Checker_t * SensorBoardConnectionChecker_Get()
{
    return &mySBCC;
}

void SensorBoardConnectionChecker_setSensorBoardConnectionStatus(SensorBoardConnectionStatus_e sensorBoardConnectionStatus)
{
	mySensorBoardConnectionStatus = sensorBoardConnectionStatus;
}

//////////////////////////////////////////////////////////////////////////////
//							  Fonctions Privées								//
//////////////////////////////////////////////////////////////////////////////

//------------------ Code non temriné ----------------------------------------

// static void SensorBoardConnectionChecker_run()
// {
// 	State_e currentState = mySBCC.myState;
// 	State_e newState;
// 	Event_e anEvent = mySBCC.myEvent;
// 	Action_e anAction;
// 	while(currentState != S_DEATH)
// 	{
// 		anAction = transitionSystem[currentState][anEvent].actionToDo;
// 		newState = transitionSystem[currentState][anEvent].nextState;
// 		if (transitionSystem[currentState][anEvent].nextState != S_FORGET)
// 		{
// 			SensorBoardConnectionChecker_performAction(anAction);
// 			mySBCC.myState = newState;
// 		}
// 	}
// }

// static void SensorBoardConnectionChecker_performAction (Action_e act)
// {
// 	switch (act)
// 	{
// 	case A_NOP :
// 		break;
// 	case A_ASK_STATUS :
// 		break;
// 	case A_UPDTAE_STATUS :
// 		break;
// 	default :
// 		break;
// 	}
// }
