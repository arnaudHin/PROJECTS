/*
 * datas_process.c

 *
 *  Created on: 23 juin 2020
 *      Author: Arnaud
 */


#include "datas_process.h"
#include "stm32f4_timer.h"
#include "regulation/regulation.h"
#include "motors_control.h"
#include <stdbool.h>

static drone_data_t * drone_data;


bool_e TOF_OK = 0;
uint32_t compteur_no_pooling_tof = 0;
uint32_t compteur_no_pooling_mpu = 0;
uint16_t counter_pitch_correction = 0;



/// INTERROGATION AVEC IT DE TIMER 2   ///
//IT 1ms, de plus basse priorit� que l'IT du systick !
//TODO mettre un seul compteur pour les tofs et le mpu
//TODO c'est encore tr�s lourd
void TIMER5_user_handler_it_1ms(void)
{
	static timeslot_e timeslot;

		//compteur declar� dans tests_methods.h
			if(compt <= 5000){ compt += 1; }
			else{ compt = 0; }
			//Fonction d'interrogation des ToFs toutes les TIME_NO_POOLING_TOF ms, si en communication TOF_OK = 0, sinon, TOF_OK = 1

			if(compteur_no_pooling_tof <= TIME_MS_POOLING_TOF && TOF_OK ==1){
				compteur_no_pooling_tof++;
				TOF_OK = 1;
			}


			if(compteur_no_pooling_tof > TIME_MS_POOLING_TOF || TOF_OK == 0){
				TOF_OK = 0;
				compteur_no_pooling_tof = 0;

				timeslot = VL53L1X_process_it();

				//TODO if() encore utile ?
				if(timeslot == TIMESLOT_ASK_END){ //Si fin de com avec les ToFs
					TOF_OK = 1; //Alors TOF_OK = 1, on peut alors parler en I2C au gyro et lire les valeurs des tofs
					datas_tof_maj();
				}
				else{
					TOF_OK = 0; //sinon communication pas finie
				}

			}
			if(drone_data->process_data == 1){
				if(drone_data->pitch_correction == 1){
					if(counter_pitch_correction < TIME_MS_UPDATE_PITCH_COR){
						counter_pitch_correction += 1;
					}else{
						counter_pitch_correction = 0;
						REGULATION_update_angle();
					}
				}
			}

			//on utilise le compteur du mpu pour le traitement des donn�es toutes les 4ms
			if(compteur_no_pooling_mpu <= TIME_MS_POOLING_MPU){
				compteur_no_pooling_mpu++;
			}
			else{
				MPU_angle_computer();
				compteur_no_pooling_mpu = 0;

				if(drone_data->process_data == 1){
					REGULATION_process_angle();
					if(drone_data->z_correction == 1){
						REGULATION_process_z();
					}
					if(drone_data->yaw_regulation == 1){
						REGULATION_process_yaw();
					}
					if(drone_data->x_correction == 1){
						REGULATION_process_x();
					}
					MC_PID_correction();
					MC_update_motors();
				}

			}

}



void data_process_init(drone_data_t * drone){
	drone_data = drone;
	drone_data->block_config = 1;
	drone_data->process_data = 1;
	MPU_init(drone_data);
	VL53L1X_init();
	REGULATION_init(&(drone->datas_sensors_pooling),&(drone->target_values),&(drone->pid_correction),drone->preset_pid);
	TIMER5_run_1ms();
}


void datas_tof_maj(){
	drone_data->datas_sensors_pooling.dist_backward_X = VL53L1X_get_distance(0);
	drone_data->datas_sensors_pooling.dist_side_Y = VL53L1X_get_distance(1);
	drone_data->datas_sensors_pooling.dist_forward_X = VL53L1X_get_distance(2);
	drone_data->datas_sensors_pooling.dist_low_Z = VL53L1X_get_distance(3);
	drone_data->datas_sensors_pooling.dist_high_Z = VL53L1X_get_distance(4);
}

void data_process_stop(){
	MC_put_all_motors_off();
	TIMER5_stop();
	drone_data->process_data = 0;
	MC_put_all_motors_off();

}
