/*
 * datas_process.h

 *
 *  Created on: 23 juin 2020
 *      Author: Arnaud
 */

#ifndef APPLI_DATAS_PROCESS_H_
#define APPLI_DATAS_PROCESS_H_

#include "save_old/tests_methods.h"
#include "mpu6050.h"
#include "drone_def.h"

#define CAT(A, B) A ## B


#define DIST_FORWARD 1
#define DIST_HEIGHT 1
#define DIST_FACE 1

#define TOF_ID_AXE_X 0
#define TOF_ID_AXE_Y 1
#define TOF_ID_AXE_Z 2

#define TIME_MS_POOLING_TOF 4 //frequence de 250Hz
#define TIME_MS_POOLING_MPU 4
#define TIME_MS_UPDATE_PITCH_COR 500


#define MESURE_HAUEUR_DRONE_CM 10
#define MESURE_LARGEUR_DRONE_CM 30


extern uint32_t compteur_no_pooling_tof;
extern uint32_t compteur_no_pooling_mpu;

extern bool_e TOF_OK;


void TIMER2_user_handler_it_1ms(void);
void datas_tof_maj(void);
void data_process_init(drone_data_t * drone_data);
void data_process_stop(void);




#endif /* APPLI_DATAS_PROCESS_H_ */
