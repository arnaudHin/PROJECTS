/*
 * pid.c
 *
 *  Created on: 22 mars 2020
 *      Author: Theo
 */

#include "Pid.h"

//renvoit la sortie du pid
float PID_compute(PID_t * pid, float consigne, float measurement){
	//Calcul de l'erreur
	pid->error = measurement - consigne ;

	//printf("PID error : %d\n",(int) pid->error);


	//Calcul des P I D
	pid->P = pid->settings[PID_KP] * pid->error ;
	pid->I += pid->settings[PID_KI] * pid->error / pid->settings[PID_FREQUENCY];
	pid->D = pid->settings[PID_KD] * (measurement - pid->previous_measurement) * pid->settings[PID_FREQUENCY] ;


	//On somme le tout
	pid->output = pid->P + pid->I + pid->D;

	//Check mid and max
	pid->output = MIN(pid->settings[PID_MAX_OUTPUT], pid->output);
	pid->output = MAX(-pid->settings[PID_MAX_OUTPUT], pid->output);

	//Mise à jour des valeurs antérieures
	pid->previous_measurement = measurement ;
	return pid->output ;
}



//Init des valeurs sur le pid donné
void PID_init(PID_t * pid, float settings[PID_NB_SETTINGS]){
	//Set settings
	for(uint8_t s = 0 ; s < PID_NB_SETTINGS; s++)
		pid->settings[s] = settings[s] ;

	//Init values
	pid->I = 0 ;
}

