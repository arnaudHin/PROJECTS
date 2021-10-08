 /**
 * @file DispatcherDSMonitorApp.h
 * @brief 
 * @date Mai 2021
 * @authors Nisrine Tougui
 * @version 1.0
 * @copyright CC BY 4.0
 */

#ifndef DISPATCHER_DSMONITOR_APP_H
#define DISPATCHER_DSMONITOR_APP_H

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions publiques						//
//////////////////////////////////////////////////////////////////////////////

/**
 * @fn  extern void DispatcherDSMonitorApp_new()
 *
 * @brief Constructeur de la classe DispatcherDSMonitorApp
 *
 */
extern void DispatcherDSMonitorApp_new();

/**
 * @fn  extern void DispatcherDSMonitorApp_start()
 *
 * @brief Démarrage de l'objet
 */
extern void DispatcherDSMonitorApp_start();

/**
 * @fn  extern void DispatcherDSMonitorApp_stop()
 *
 * @brief Arrêt du fonctionnement de l'objet
 */
extern void DispatcherDSMonitorApp_stop();

/**
 * @fn  extern void DispatcherDSMonitorApp_free()
 *
 * @brief Destructeur de l'objet 
 */
extern void DispatcherDSMonitorApp_free();

#endif /* DISPATCHER_MONITOR_APP_H*/