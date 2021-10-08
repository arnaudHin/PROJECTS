/**
 * @file common.h
 * @brief Ce fichier contient tous les types et les structures utilisés.
 * @date Mai 2021
 * @authors Robin
 * @version 1.0
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>

//////////////////////////////////////////////////////////////////////////////
//									Macros									//
//////////////////////////////////////////////////////////////////////////////

#define MAX_ASK_MSG 26	// Taille maximale d'octets que peut contenir une trame de demande de DSMonitor : 20+3 car CMD_e sur 4 octets et non 1
#define MAX_ACK_MSG 88	// Taille maximale d'octets que peut contenir une trame d'acquittement de DSSupervisor

#define MIN_ASK_MSG 3	// Taille minimale d'octets que peut contenir une trame de demande de DSMonitor : 3+3 car CMD_e sur 4 octets et non 1
#define MIN_ACK_MSG 3	// Taille maximale d'octets que peut contenir une trame d'acquittement de DSSupervisor

#define MAX_ASK_DATA 23
#define MAX_ACK_DATA 85

#define MIN_ASK_DATA 0
#define MIN_ACK_DATA 0

#define OCTET_NUMBER_TIME 8

//////////////////////////////////////////////////////////////////////////////
//						  Types : Enums et Structs							//
//////////////////////////////////////////////////////////////////////////////


typedef uint16_t SessionId;			/* ID de la session en cours */
typedef uint16_t Size;				/* Taille des Datas de la trame */
typedef uint32_t TimeMeasures_t;	/* Date d'enregistrement pour les Champs De Mesures */
typedef uint64_t Time; 			/* Date de Démarrage/Arrêt de la Session */
typedef float SensorMeasure;		/* Valeur mesurée par les capteurs */

/**
 * \enum DavidsonStatus_e :	Le statut de fonctionnement.
 */
typedef enum{
    DAV_OK = 0,		/* Statut : OK */
    DAV_ERROR		/* Statut : Erreur */
}DavidsonStatus_e;

/**
 * \enum SensorConnnectionStatus_e :	Le statut de connection des Capteurs.
 */
typedef enum{
	SENSOR_CONNECTED = 0,	/* Statut : Connecté */
	SENSOR_NOTCONNECTED		/* Statut : Non connecté/Déconnecté */
}SensorConnnectionStatus_e;

/**
 * \enum SensorBoardConnectionStatus_e :	Le statut de connection à SENSORBOARD.
 */
typedef enum{
	CONNECTED = 0,		/* Statut : Connecté */
	NOTCONNECTED		/* Statut : Non connecté/Déconnecté */
}SensorBoardConnectionStatus_e;

/**
 * \enum Location_e :	ID de localisation des Meta Mesures.
 */
typedef enum
{
	APP	= 0,	/* ID : DSApp */
	MONITOR,	/* ID : DSMonitor */
} Location_e;

/**
 * \enum ModeId_e :	ID du Mode de capture de la session.
 */
typedef enum
{
	SOC = 0,	/* ID : Session Only Capture */
	SST,		/* ID : Session Supervisor Treatment */
	SAT,		/* ID : Session App Treatment */
	SSTI,		/* ID : Session Supervisor Treatment Intelligent */
} ModeId_e;

/**
 * \enum SubModeId_e :	ID du Sous Mode de capture de la session.
 */
typedef enum
{
	CONTINUOUS = 0,	/* ID : capture Continue */
	INSTANT,		/* ID : capture Instantanée */
} SubModeId_e;

/**
 * \enum SensorId_e :	ID du capteur à interroger.
 */
typedef enum
{
	TEMP=0,		/* ID : Temperature */
	PRES,		/* ID : Pression */	
	HUMI,		/* ID : Humidité */
	ACCE,		/* ID : Accéléromètre */
	GYRO,		/* ID : Gyroscope */
	MAGN,		/* ID : Magnétomètre */
	NB_SENSOR,	/* Nombre d'ID de capteurs */	
} SensorId_e;

/**
 * \enum Period_e :	ID de Période de capture associée à un capteur.
 */
typedef enum
{
	PRES_DSAPP = 0,
	MAGN_DSAPP,
	TEMP_DSAPP, 
	ACCE_DSAPP,
	HUMI_DSAPP,
	GYRO_DSAPP,
	NB_SENSOR_DSAPP,
} SensorIdDSApp_e;

typedef enum
{
	P_50_MS=0,	/* ID : 50ms */
	P_100_MS,	/* ID : 100ms */
	P_500_MS,	/* ID : 500ms */
	P_1000_MS,	/* ID : 1000ms */
	P_5000_MS,	/* ID : 5000ms */
} Period_e;

/**
 * \enum CMD_e :	Les Commandes entre DSMonitor et DSSupervisor.
 */
typedef enum
{
	ASK_START=1,	/* Demande : Start Session */
	ASK_STOP, 		/* Demande : Stop Session */
	ASK_NEW_MSG, 	/* Demande : Nouveau Message de DSSupervisor */
	ACK_MA, 		/* Acquittement : MeasuresArray Ready*/
	ACK_NO_MA, 		/* Acquittement : MeasuresArray Not Ready*/
	ACK_SBC_OK,		/* Acquittement : SENSORBOARD Connection_KO */
	ACK_SBC_KO 		/* Acquittement : SENSORBOARD Connection_OK */
} CMD_e;

/**
 * \enum	CMD_APP_e : Les commandes entre DSApp et DSMonitor.
 */
typedef enum 
{
    START_SESSION = 1, 						/* Demande : Start Session */
    STOP_SESSION,							/* Demande : Stop Session */
    CHECK_SENSORBOARD_CONNECTION,			/* Demande : Etat SB connexion*/
	START_CHECK_SENSORBOARD,				/* Demande : Démarrer le demande continue de vérifier l'état de sensorboard  */
	STOP_CHECK_SENSORBOARD,					/* Demande : Stopper le demande continue de vérifier l'état de sensorboard  */
	DSAPP_QUIT,								/* Demande : Arrêt des logiciels*/
} CMD_APP_e;


/**
 * \enum	CMD_APP_e : Les commandes de DSMonitor vers DSApp.
 */
typedef enum 
{
	STORE_START_SESSION = 1, 				/* Stockage : Start session*/
    STORE_END_SESSION,						/* Stockage : End session*/
    STORE_MA,								/* Stockage : Champ De Mesures*/
    SEND_SENSORBOARD_CONNECTION,			/* Envoi : Etat connexion à SENSORBOARD */
    STORE_META_MEASURES,					/* Stockage : Meta-Mesures*/
} CMD_TO_APP_e;

/**
 * \enum	SensorsArray_t : Les instructions de capture pour la session,
 * 			indiquant quels capteurs à interroger, quelle période pour chacun.
 */
typedef struct
{
	uint8_t sensorNb;					/* Nombre de capteurs interrogés */
	bool sensorActive[NB_SENSOR];		/* Tableau de booléens déterminant quels capteurs doivent être interrogés */
	SensorId_e sensors[NB_SENSOR];		/* Tableau de SensorId contenant les ID de chaque capteur à associer à leur période */
	Period_e periodSensor[NB_SENSOR];	/* Tableau de Period contenant la période de capture pour chaque capteur interrogé */
} SensorsArray_t;

/**
 * \enum	MeasuresArray_t : Le tableau de mesures pour un capteur.
 */
typedef struct
{
	SensorId_e sensorId;		// ID du sensor interrogé
	SensorMeasure measure[3];	// Tableau des 3 mesures collectées (1 seule case si 1 seule mesure)
} MeasuresArray_t;

/**
 * \enum	MetaMeasuresArray_t : Le tableau de Meta Mesures pour un Champ De Mesures.
 */
typedef struct
{
	uint32_t clockCycleCount;		// Nombre de cycles d'horloge
	uint32_t tasksPerCycleCount;		// Nombre de taches par cycle
	float percentagePerTask;		// Pourcentage d'utilisation du CPU par tache
} MetaMeasuresArray_t;

/**
 * \enum SessionInformation_t :	Les infos de la Session.
 */
typedef struct
{
	SessionId sessionId;					/* ID : de la Session */
	ModeId_e modeId;						/* ID : du Mode */
	SubModeId_e subModeId;					/* ID : du Sous Mode */
	Time time;	/* Date du début de la Session */
	SensorsArray_t sensorsArray;			/* Tableau des capteurs à interroger et leur période */
} SessionInformation_t;

//////////////////////////////////////////////////////////////////////////////
//							comDSMonitorSupervisor							//
//////////////////////////////////////////////////////////////////////////////

/**
 * \enum M_DataAnswer_t :	Les données de Réponse de DSSupervisor pour DSMonitor.
 */
typedef struct
{
	SessionId sessionId;						// ID de la session
	TimeMeasures_t time;						// Date de capture du Champ De Mesure
	uint8_t sensorNb;							// Nombre de captuers sollicités
	MeasuresArray_t measuresArray[NB_SENSOR];	// Tableau du Champ De Mesure capturé
} M_DataAnswer_t;

/**
 * \enum M_DataOrder_t :	Les données d'Ordre de DSMonitor pour DSSupervisor.
 */
typedef struct
{
	SessionId sessionId;			// ID de la Session
	ModeId_e modeId;				// ID du Mode
	SubModeId_e subModeId;			// ID du Sous Mode
	SensorsArray_t sensorsArray;	// Tableau des capteurs à interroger avec période associée
} M_DataOrder_t;

/**
 * \enum M_MessageAnswer_t :	Trame complète du Message de réponse de DSSupervisor pour DSMonitor.
 */
typedef struct
{
	CMD_e command;				// Commande
	Size size;					// Taille de la partie Data de la trame
	M_DataAnswer_t dataToRead;	// Data à recevoir via Protocole Intercoeur
} M_MessageAnswer_t;

/**
 * \enum M_MessageOrder_t :	Trame complète du Message d'Ordre de DSMonitor pour DSSupervisor.
 */
typedef struct
{
	CMD_e command;				// Commande
	Size size;					// Taille de la partie Data de la trame
	M_DataOrder_t dataToWrite;	// Data à envoyer via Protocole Intercoeur
} M_MessageOrder_t;


//////////////////////////////////////////////////////////////////////////////
//								comDSMonitorApp								//
//////////////////////////////////////////////////////////////////////////////

/**
 * \enum M_MessageToReadFromDSApp_t :	Trame complète du Message d'Ordre de DSApp pour DSMonitor.
 */
typedef struct {
	CMD_APP_e commandMsg;							/* Commande */
   	Size sizeMsg;									/* Taille de la partie Data de la trame */
    SessionInformation_t sessionInformationMsg;		/* Data à recevoir via Protocole Wifi */
} M_MessageToReadFromDSApp_t;

#endif /* INC_COMMON_H_ */