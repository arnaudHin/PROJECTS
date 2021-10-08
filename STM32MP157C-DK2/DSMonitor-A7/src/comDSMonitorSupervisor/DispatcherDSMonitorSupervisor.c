/**
 * @file DispatcherDSMonitorSupervisor.c
 * @brief Ce fichier lit en permanence la boite aux lettres et décide de ce 
 * 		  qu'il faut faire en conséquence.
 * @date Mai 2021
 * @authors Robin
 * @version 1.0
 * @copyright CC BY 4.0
 */

#include <pthread.h>

#include "DispatcherDSMonitorSupervisor.h"
#include "PostmanDSMonitorSupervisor.h"
#include "IntercoreProtocol.h"
#include "../comDSMonitorApp/ProxyMeasuresProcessorApp.h"
#include "../comDSMonitorApp/ProxyMonitorGUI.h"


//////////////////////////////////////////////////////////////////////////////
//								Structures									//
//////////////////////////////////////////////////////////////////////////////

/**
 * Etats que peut prendre la MàE
 *
 * \enum	state MàE DispatcherDSMS
 */
typedef enum
{
	S_DSMS_FORGET=0,		/*< S_FORGET */
	S_DSMS_WAITING_ORDER,	/*< S_WAITING_ORDER */
	S_DSMS_RUNNING,			/*< S_RUN */
	S_DSMS_DEATH,			/*< S_DEATH */
	DSMS_NB_STATE,			/*< NB_STATE */
} DispatcherDSMS_State;

struct DispatcherDSMS
{
	DispatcherDSMS_State currentState;
	bool session;
};

//////////////////////////////////////////////////////////////////////////////
//							Variables Privées								//
//////////////////////////////////////////////////////////////////////////////

/**
 * @var pthread_t threadRun
 *
 * @brief Déclaration du Thread pour la fonction run.
 */
static pthread_t threadRun;

static uint8_t bufferASK[3];		// Tableau de 6 octets
static uint8_t * bufferACK;
static M_MessageAnswer_t messageToReadFromSupervisor;
static DispatcherDSMS_t myDispatcherDSMS;
static bool instantSession = false;

//////////////////////////////////////////////////////////////////////////////
//					   Prototypes de fonctions Privées						//
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction run DispatcherDSMS
 * 
 * @brief	Gère la MAE de DispatcherDSMS : Lit constamment les messages qui 
 * 			arrivent sur Postman. Redirige les messages reçus en fonction de 
 * 			leur type vers les objets adéquats.
 */
static void * DispatcherDSMS_run();

//////////////////////////////////////////////////////////////////////////////
//							Fonctions Publiques								//
//////////////////////////////////////////////////////////////////////////////

void DispatcherDSMS_new()
{
	myDispatcherDSMS.currentState = S_DSMS_DEATH;
	myDispatcherDSMS.session = false;
}

void DispatcherDSMS_start()
{
	myDispatcherDSMS.currentState = S_DSMS_WAITING_ORDER;
	/* Ouverture du thread */
	int check = pthread_create(&threadRun, NULL, DispatcherDSMS_run, NULL); // Création d'un thread qui appelle la fonction DispatcherDSMS_run
	if (check == -1)
	{
		int codeErreur = errno;
	}
}

void DispatcherDSMS_stop()
{
	myDispatcherDSMS.currentState = S_DSMS_DEATH;
	/* Fermeture du thread */
	uint8_t check = pthread_join(threadRun, NULL);
	if (check == -1){
		int codeErreur = errno;
	}
}

void DispatcherDSMS_free()
{
	myDispatcherDSMS.currentState = S_DSMS_DEATH;
	myDispatcherDSMS.session = false;
}

DispatcherDSMS_t * DispatcherDSMS_get()
{
	return &myDispatcherDSMS;
}

void DispatcherDSMS_set(DispatcherDSMS_t *dispatcherDSMS)
{
	myDispatcherDSMS.currentState = dispatcherDSMS->currentState;
}

void DispatcherDSMS_setInstant(bool instant){
	instantSession = instant;
}

/*----------------------------------------------- POUR LE DEBOGGAGE : -------------------------------------------------*/
void DispatcherDSMS_toggleCapture()
{
	if(myDispatcherDSMS.session == false)
	{
		myDispatcherDSMS.session  = true;
		myDispatcherDSMS.currentState = S_DSMS_RUNNING;
	}
	else
	{
		myDispatcherDSMS.session = false;
		myDispatcherDSMS.currentState = S_DSMS_WAITING_ORDER;
	}
}

//////////////////////////////////////////////////////////////////////////////
//							  Fonctions Privées								//
//////////////////////////////////////////////////////////////////////////////

static void * DispatcherDSMS_run()
{

	while(myDispatcherDSMS.currentState != S_DSMS_DEATH)
	{
	
		switch (myDispatcherDSMS.currentState)
		{
			/* Etat d'activité (Session de mesures en cours) */
			case S_DSMS_RUNNING:
			
				/* Lecture et décodage de CMD et Size du message reçu */
				PostmanDSMS_read(bufferASK, MIN_ACK_MSG);
				IntercoreProtocol_decodeMessage(bufferASK, &messageToReadFromSupervisor, MIN_ASK_MSG);
				
				uint16_t dataBytesToread = messageToReadFromSupervisor.size;
				/* Initialisation de la taille du tableau d'octets en fonction de la Size du message reçu */
				bufferACK = calloc(dataBytesToread, sizeof(uint8_t));

				/* Lecture et décodage du message entier reçu */
				PostmanDSMS_read(bufferACK, dataBytesToread);
				IntercoreProtocol_decodeMessage(bufferACK, &messageToReadFromSupervisor, dataBytesToread);

				free(bufferACK);

				switch (messageToReadFromSupervisor.command)
				{
					case ACK_MA :
						ProxyMeasuresProcessorApp_storeMeasuresArray( &(messageToReadFromSupervisor.dataToRead) );

						break;
					case ACK_SBC_KO :
						/* Réception des ACK autres que ACK_MA pas encore gérée par SessionManager */

						break;
					case ACK_SBC_OK :
						/* Réception des ACK autres que ACK_MA pas encore gérée par SessionManager */
						
						break;
					default:

						break;
				}
				if(instantSession == true){
				myDispatcherDSMS.currentState = S_DSMS_WAITING_ORDER;
				instantSession = false;
				break;	
				}

			break;

		/* Etat d'inactivité (Pas de Session de mesures en cours) */
		case S_DSMS_WAITING_ORDER:
			/* code */
			break;

		default:
			break;
		}
			
		usleep(1000*30);
		
	}
	return NULL;

}
