 /**
 * @file PostmanDSMonitorApp.c
 * @brief 
 * @date Mai 2021
 * @authors Nisrine Tougui
 * @version 1.0
 * @copyright CC BY 4.0
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <pthread.h>

#include "PostmanDSMonitorApp.h"

#define PORT_DU_SERVEUR (8080)
#define MAX_PENDING_CONNECTIONS (5) 

typedef uint8_t DataWriteTab[TAILLE_TAB];

static int socketDSMonitor; 
static int socketDSApp;
struct sockaddr_in myAddress;

static pthread_mutex_t mutexLockWrite;	

//////////////////////////////////////////////////////////////////////////////
//						                	Fonctions Publiques								          //
//////////////////////////////////////////////////////////////////////////////

extern int PostmanDSMonitorApp_new()
{
  int resultBind = 0; 
  socketDSMonitor = socket (AF_INET, SOCK_STREAM, 0);
  myAddress.sin_family = AF_INET;
  myAddress.sin_port = htons (PORT_DU_SERVEUR);
  myAddress.sin_addr.s_addr = htonl (INADDR_ANY); 
  resultBind = bind (socketDSMonitor, (struct sockaddr *)&myAddress, sizeof (myAddress));

  if (resultBind == -1){
    perror("ERROR POSTMAN MONITOR APP NEW\n");
  }

  pthread_mutex_init(&mutexLockWrite, NULL);

  return resultBind; 
}

extern int PostmanDSMonitorApp_start()
{
  fprintf(stderr, "\n_____Bienvenue sur Davidson Consulting App_____\n\n");

  int resultListen = 0;
  resultListen = listen (socketDSMonitor, MAX_PENDING_CONNECTIONS);
  if (resultListen == -1){
    perror("ERROR POSTMAN MONITOR APP START\n");
  }

  fprintf(stderr, "Serveur en attente de client...\n");

  socketDSApp = accept(socketDSMonitor, NULL, 0);

  fprintf(stderr, "Client connecte\n");

  return resultListen; 
}

extern ssize_t PostmanDSMonitorApp_write(uint8_t * message , ssize_t octetNumber)
{ 
  pthread_mutex_lock(&mutexLockWrite);
  int resultWrite = 0;

  resultWrite = write (socketDSApp, message, octetNumber);

  if (resultWrite == -1)
  {
    perror("ERROR POSTMAN MONITOR APP WRITE\n");
  }
  pthread_mutex_unlock(&mutexLockWrite);
  
  return resultWrite;
}

extern ssize_t PostmanDSMonitorApp_read(uint8_t *dataRead, ssize_t octetNumber)
{
 	int resultRead = 0;
	resultRead  = recv(socketDSApp, dataRead, octetNumber, MSG_WAITALL);

  if (resultRead == -1)
  {
    perror("ERROR POSTMAN MONITOR APP READ\n");
  }

  return resultRead;
}

extern int PostmanDSMonitorApp_stop()
{
  int resultSocket; 

  resultSocket = close (socketDSMonitor);
  if (resultSocket == -1 )
  {
    perror("ERROR POSTMAN MONITOR APP STOP -> SOCKETDSMONITOR \n");
  }

  resultSocket = close (socketDSApp);
  if (resultSocket == -1 )
  {
    perror("ERROR POSTMAN MONITOR APP STOP -> SOCKETDSAPP \n");
  }

  return resultSocket; 
}