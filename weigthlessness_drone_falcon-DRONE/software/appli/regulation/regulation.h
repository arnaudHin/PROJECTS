/*
 * regulation.h
 *
 *  Created on: 24 sept. 2020
 *      Author: Theo
 */

#ifndef APPLI_REGULATION_REGULATION_H_
#define APPLI_REGULATION_REGULATION_H_

#include "../../lib/btm/Pid.h"
#include "drone_def.h"

// COMMENT CA MARCHE
//On modifi les coefs des pids dans le regulation.c il y a les tableaux en haut
//Regulation_init une fois dans le main en passant en paramètre nos structure de données
//Pi on appelle regulation_procces à 250 Hz avant l'envoit aux moteurs
//Et voilà :)

//Nom des pids
typedef enum{
	PID_ANGLE_ROLL,
	PID_ANGLE_PITCH,
	PID_ANGLE_YAW,
	PID_DIST_Z,
	PID_COUNT
}PID_names_t;


//Init du module, on repère où sont les structures que l'on va utiliser par la suite
void REGULATION_init(datas_sensors_pooling_t * datas_sensors_pooling_,target_values_t * target_values_,  PID_correction_t * PID_correction_, uint8_t preset);

//Process des pids et mise à jour structures pid_outputs_t
void REGULATION_process_angle(void);

void REGULATION_process_yaw(void);

void REGULATION_process_z(void);

void REGULATION_process_x(void);

void REGULATION_config_pids(uint8_t preset);

void REGULATION_update_angle(void);



#endif /* APPLI_REGULATION_REGULATION_H_ */
