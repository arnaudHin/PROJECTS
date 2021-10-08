 /**
 * @file PostmanDSMonitorApp.h
 * @brief 
 * @date Mai 2021
 * @authors Nisrine Tougui
 * @version 1.0
 * @copyright CC BY 4.0
 */
 
#ifndef POSTMAN_DSMONITOR_APP_H
#define POSTMAN_DSMONITOR_APP_H

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

/**
 * @def Taille maximale du tableau d'octet à envoyer 
 */
#define TAB_SIZE_WRITE 28

/**
 * @def Taille maximale du tableau d'octet à lire
 */
#define TAB_SIZE_READ 28

/**
 * @def Taille maximale des tableaux
 */
#define TAILLE_TAB 28

typedef uint8_t DataToWrite[TAB_SIZE_WRITE];
typedef uint8_t OctetNumber; 

/* READ */
typedef uint8_t DataReadTab[TAILLE_TAB]; // mettre en statique dans dispatcher


/**
 * @fn      extern int PostmanDSMonitorApp_new()
 *
 * @brief   Fonction permettant de créer le postmanMonitorApp
 *
 * @return  int : Fonction renvoyant un entier. 
 *
 * @retval  0   : En fonctionnement 
 * @retval  -1  : En cas d'erreur
 */
extern int PostmanDSMonitorApp_new();


/**
 * @fn      extern int PostmanDSMonitorApp_start()
 *
 * @brief   Fonction permettant de créer le postmanMonitorApp
 *
 * @return  int : Fonction renvoyant un entier. 
 *
 * @retval  0   : En fonctionnement 
 * @retval  -1  : En cas d'erreur
 */
extern int PostmanDSMonitorApp_start();


/**
 * @fn      extern int PostmanDSMonitorApp_write(DataToWrite message)
 *
 * @param   message    : 
 *
 * @brief   Fonction permettant d'envoyer un message à destination de DSApp.
 *
 * @return  int : Fonction renvoyant un entier. 
 *
 * @retval  0   : En fonctionnement 
 * @retval  -1  : En cas d'erreur
 */

extern ssize_t PostmanDSMonitorApp_write(uint8_t *message , ssize_t octetNumber); 


/**
 * @fn      extern ssize_t PostmanDSMonitorApp_read (DataRead *dataRead, ssize_t octetNumber)
 *
 * @param   dataRead    : 
 * @param   octetNumber : 
 *
 * @brief   Fonction permettant de lire un message en provenance de DSApp.
 *
 * @return  int : Fonction renvoyant un entier. 
 *
 * @retval  0   : En fonctionnement 
 * @retval  -1  : En cas d'erreur
 */
extern ssize_t PostmanDSMonitorApp_read (uint8_t *dataRead, ssize_t octetNumber); 


/**
 * @fn      extern int PostmanDSMonitorApp_stop()
 *
 * @brief   Fonction permettant de créer le postmanMonitorApp
 *
 * @return  int : Fonction renvoyant un entier. 
 *
 * @retval  0   : En fonctionnement 
 * @retval  -1  : En cas d'erreur
 */
extern int PostmanDSMonitorApp_stop();


#endif /* POSTMAN_DSMONITOR_APP_H*/


