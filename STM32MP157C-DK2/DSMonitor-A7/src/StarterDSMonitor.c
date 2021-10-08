/**
 * @file StarterDSMonitor.c
 * @brief Classe principale qui démarre les objets actifs 
 * @date Mai 2021
 * @authors Robin
 * @version 1.0
 */

#include <unistd.h>
#include <stdio.h>

#include "StarterDSMonitor.h"
#include "common.h"
#include "comDSMonitorSupervisor/DispatcherDSMonitorSupervisor.h"
#include "comDSMonitorSupervisor/PostmanDSMonitorSupervisor.h"
#include "comDSMonitorSupervisor/IntercoreProtocol.h"
#include "comDSMonitorApp/DispatcherDSMonitorApp.h"
#include "monitor/SensorBoardConnectionChecker.h"
#include "monitor/MetaMeasuresMonitor.h"
#include "comDSMonitorApp/PostmanDSMonitorApp.h"
#include"comDSMonitorApp/WifiProtocol.h"

/*----------------------------------- Fin Code Test --------------------------------------*/

//////////////////////////////////////////////////////////////////////////////
//							Variables Privées								//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//					   Prototypes de fonctions Privées						//
//////////////////////////////////////////////////////////////////////////////

static void StarterDSSupervisor_new();
static void StarterDSSupervisor_stop();

//////////////////////////////////////////////////////////////////////////////
//							Fonctions Publiques								//
//////////////////////////////////////////////////////////////////////////////

int main (void)
{
	///////////////		NEW		///////////////
	PostmanDSMonitorApp_new(); 
	DispatcherDSMonitorApp_new();
	IntercoreProtocol_init();
	PostmanDSMS_new();
	DispatcherDSMS_new();
	StarterDSSupervisor_new();


	/////////////////		START	///////////////
	PostmanDSMonitorApp_start();
	DispatcherDSMonitorApp_start();
	PostmanDSMS_start();
	DispatcherDSMS_start();


	///////////////		STOP	///////////////
	DispatcherDSMonitorApp_stop();
	DispatcherDSMS_stop();
	PostmanDSMS_stop();
	StarterDSSupervisor_stop();


	///////////////		FREE	///////////////
	DispatcherDSMonitorApp_free();
	DispatcherDSMS_free();
	PostmanDSMS_free();
	SensorBoardConnectionChecker_free();
	IntercoreProtocol_free();

	return 0;
}

static void StarterDSSupervisor_new(){
	/* Lancement du scipt bash pour démarrer le M4 */
	fprintf(stderr, "\n--BOOT du M4--\n");
	int check = system("bash /usr/local/script/push_m4_fw.sh");
	if (check == -1)
	{
		int codeErreur = errno;
		fprintf(stderr, "Erreur au lancement du script bash' : %s\n", strerror(codeErreur));
	}
	usleep (1000 * 1000);
}

static void StarterDSSupervisor_stop(){
	
	fprintf(stderr, "\n--ARRET du M4--\n");
	/* Arrêt du script bash pour terminer l'exécution du M4 */
	int status = system("echo stop > /sys/class/remoteproc/remoteproc0/state");
	if (status == -1)
	{
		int codeErreur = errno;
		fprintf(stderr, "Erreur à l'arrêt du script bash' : %s\n", strerror(codeErreur));
	}
	usleep(1000 * 1000);
}


//////////////////////////////////////////////////////////////////////////////
//							Fonctions Privées								//
//////////////////////////////////////////////////////////////////////////////



