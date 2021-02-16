/*
 * regulation.c
 *
 *  Created on: 24 sept. 2020
 *      Author: Theo
 */

#include "regulation.h"
#include "drone_def.h"
#include <stdbool.h>

static drone_data_t * drone_data;

//Pointeurs sur les structure utilis�es par la r�gulation
static datas_sensors_pooling_t * datas_sensors_pooling;
static target_values_t * target_values;
static PID_correction_t * PID_correction;
//Param�tres pour les pid
#define PID_ANGLE_FREQUENCY 250
#define PID_ANGLE_MAX_OUTPUT 200	//En admettant que mon signal moteur vari de 0 � 1000
#define PID_DIST_FREQUENCY 250
#define PID_DIST_MAX_OUTPUT 200
//Param�tre pour la correction des angles
#define ANGLE_CORRECTION_AMOUNT 42

static uint8_t time_round = 0;


//pid par d�faut									P		I	  D			Frequence			Output Max
static float PID0_Settings_Roll[PID_NB_SETTINGS] = {10.0f, 6.0f, 6.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID0_Settings_Pitch[PID_NB_SETTINGS] = {10.0f, 6.0f, 6.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID0_Settings_Yaw[PID_NB_SETTINGS] = {5.0f, 3.0f, 3.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID0_Settings_Z[PID_NB_SETTINGS] = {0.6f, 0.1f, 0.1f, PID_DIST_FREQUENCY, PID_DIST_MAX_OUTPUT};

static float PID1_Settings_Roll[PID_NB_SETTINGS] = {14.0f, 3.0f, 3.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID1_Settings_Pitch[PID_NB_SETTINGS] = {14.0f, 3.0f, 3.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID1_Settings_Yaw[PID_NB_SETTINGS] = {5.0f, 3.0f, 3.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID1_Settings_Z[PID_NB_SETTINGS] = {0.5f, 0.1f, 0.1f, PID_DIST_FREQUENCY, PID_DIST_MAX_OUTPUT};

static float PID2_Settings_Roll[PID_NB_SETTINGS] = {7.0f, 3.0f, 3.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID2_Settings_Pitch[PID_NB_SETTINGS] = {7.0f, 3.0f, 3.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID2_Settings_Yaw[PID_NB_SETTINGS] = {4.0f, 2.0f, 2.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID2_Settings_Z[PID_NB_SETTINGS] = {0.4f, 0.1f, 0.1f, PID_DIST_FREQUENCY, PID_DIST_MAX_OUTPUT};

static float PID3_Settings_Roll[PID_NB_SETTINGS] = {4.0f, 4.0f, 1.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID3_Settings_Pitch[PID_NB_SETTINGS] = {4.0f, 4.0f, 1.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID3_Settings_Yaw[PID_NB_SETTINGS] = {2.0f, 2.0f, 2.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID3_Settings_Z[PID_NB_SETTINGS] = {0.4f, 0.1f, 0.1f, PID_DIST_FREQUENCY, PID_DIST_MAX_OUTPUT};

static float PID4_Settings_Roll[PID_NB_SETTINGS] = {2.0f, 1.0f, 1.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID4_Settings_Pitch[PID_NB_SETTINGS] = {2.0f, 1.0f, 1.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID4_Settings_Yaw[PID_NB_SETTINGS] = {2.0f, 1.0f, 1.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID4_Settings_Z[PID_NB_SETTINGS] = {0.4f, 0.1f, 0.1f, PID_DIST_FREQUENCY, PID_DIST_MAX_OUTPUT};

static float PID5_Settings_Roll[PID_NB_SETTINGS] = {14.0f, 0.0f, 0.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID5_Settings_Pitch[PID_NB_SETTINGS] = {14.0f, 0.0f, 0.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID5_Settings_Yaw[PID_NB_SETTINGS] = {5.0f, 0.0f, 0.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID5_Settings_Z[PID_NB_SETTINGS] = {0.5f, 0.0f, 0.0f, PID_DIST_FREQUENCY, PID_DIST_MAX_OUTPUT};

static float PID6_Settings_Roll[PID_NB_SETTINGS] = {10.0f, 0.0f, 0.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID6_Settings_Pitch[PID_NB_SETTINGS] = {10.0f, 0.0f, 0.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID6_Settings_Yaw[PID_NB_SETTINGS] = {5.0f, 0.0f, 0.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID6_Settings_Z[PID_NB_SETTINGS] = {0.6f, 0.0f, 0.0f, PID_DIST_FREQUENCY, PID_DIST_MAX_OUTPUT};

static float PID7_Settings_Roll[PID_NB_SETTINGS] = {7.0f, 0.0f, 0.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID7_Settings_Pitch[PID_NB_SETTINGS] = {7.0f, 0.0f, 0.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID7_Settings_Yaw[PID_NB_SETTINGS] = {4.0f, 0.0f, 0.0f, PID_ANGLE_FREQUENCY, PID_ANGLE_MAX_OUTPUT};
static float PID7_Settings_Z[PID_NB_SETTINGS] = {0.4f, 0.0f, 0.0f, PID_DIST_FREQUENCY, PID_DIST_MAX_OUTPUT};


//Tableaux pids
PID_t pids[PID_COUNT];


//Init du module, on rep�re o� sont les structures que l'on va utiliser par la suite
void REGULATION_init(datas_sensors_pooling_t * datas_sensors_pooling_,target_values_t * target_values_,  PID_correction_t * PID_correction_, uint8_t preset){
	//On m�morise nos structures de donn�es que l on va utiliser
	datas_sensors_pooling = datas_sensors_pooling_;
	target_values = target_values_;
	//printf("Init Angle target: %d\n",(int) target_values->pitch_target);
	PID_correction = PID_correction_;

	//Configuration de nos pid
	REGULATION_config_pids(preset);

}

void REGULATION_process_angle(void){
	PID_correction->roll_pid = PID_compute(&pids[PID_ANGLE_ROLL], target_values->roll_target, datas_sensors_pooling->roll_angle);
	PID_correction->pitch_pid = PID_compute(&pids[PID_ANGLE_PITCH], target_values->pitch_target, datas_sensors_pooling->pitch_angle);
}

void REGULATION_process_yaw(void){
	PID_correction->yaw_pid = PID_compute(&pids[PID_ANGLE_YAW], target_values->yaw_target, datas_sensors_pooling->yaw_angle);
}

void REGULATION_process_z(void){
	 PID_correction->Z_pid  = PID_compute(&pids[PID_DIST_Z], target_values->z_target, datas_sensors_pooling->dist_low_Z);
}

void REGULATION_process_x(void){
	static bool CORRECTION_IN_PROGRESS = FALSE;
	static bool PITCH_90 = FALSE;
	static bool PITCH_RETURN = FALSE;
	if(drone_data->datas_sensors_pooling.dist_backward_X<=550 || drone_data->datas_sensors_pooling.dist_backward_X>=1150){
		drone_data->target_values.pitch_target = 90;
		//printf("pitch target %d\n",(int)drone_data->target_values.pitch_target);
		//printf("%d\n",drone_data->datas_sensors_pooling.dist_backward_X);
		CORRECTION_IN_PROGRESS = TRUE;
	}
	if(CORRECTION_IN_PROGRESS){ //Si on a demandé une correction d'angle
		if((drone_data->datas_sensors_pooling.pitch_angle>=(float)85 && drone_data->datas_sensors_pooling.pitch_angle<=(float)95)){ //Rotation à 90 ok
			PITCH_90 = TRUE;
			drone_data->target_values.z_target = 920;
			REGULATION_process_z();
		}
		if((drone_data->datas_sensors_pooling.dist_low_Z>=870 && drone_data->datas_sensors_pooling.dist_low_Z<=970) && PITCH_90){ //Déplacement sur x ok
			drone_data->target_values.pitch_target = 0.0f; //Rotation inverse
			PITCH_90 = FALSE;
			PITCH_RETURN = TRUE;
		}
		if((drone_data->datas_sensors_pooling.pitch_angle>=(float)-10 && drone_data->datas_sensors_pooling.pitch_angle<=(float)10) && PITCH_RETURN){
			drone_data->target_values.z_target = 850;
			REGULATION_process_z();
			CORRECTION_IN_PROGRESS = FALSE;
		}
	}
}

//modifie la valeur de consigne du pitch en corrigant l'angle vis� selon les donn�es de Novespace
//Doit �tre appel�e toutes les 500ms
void REGULATION_update_angle(void){
	static float angle_value [ANGLE_CORRECTION_AMOUNT] = {37.5952, 35.9033, 34.1455, 32.2778, 30.3003, 28.2568, 26.2134, 24.0601, 21.9946, 19.9731, 17.9297, \
			15.7983 , 13.5352 , 11.1401 , 8.6353 , 6.0425 , 3.3618 , 0.6592 , -1.9995 , -4.79 , -7.4487 , -10.0635 , -12.5903 , -15.0732 , -16.9849 , -19.9292, \
			-22.3022 , -24.6313 , -26.9604 , -29.2236 , -31.355 , -33.3545 , -35.2222 , -36.936 , -38.562 , -40.1221 , -41.6821 , -43.2861 , -44.9121 , -46.5381, \
			-48.0542 , -49.1089 };
	static float correction=0;
	if (time_round<ANGLE_CORRECTION_AMOUNT-2){
		time_round++;
		correction=(angle_value[time_round]-angle_value[time_round+1]);
		target_values->pitch_target=target_values->pitch_target+correction;
	}
}

//preset doit �tre un chiffre entre 0 et 2
void REGULATION_config_pids(uint8_t preset){
	if(preset == 0){
		PID_init(&pids[PID_ANGLE_ROLL], PID0_Settings_Roll);
		PID_init(&pids[PID_ANGLE_PITCH], PID0_Settings_Pitch);
		PID_init(&pids[PID_ANGLE_YAW], PID0_Settings_Yaw);
		PID_init(&pids[PID_DIST_Z], PID0_Settings_Z);
	}else if (preset == 1){
		PID_init(&pids[PID_ANGLE_ROLL], PID1_Settings_Roll);
		PID_init(&pids[PID_ANGLE_PITCH], PID1_Settings_Pitch);
		PID_init(&pids[PID_ANGLE_YAW], PID1_Settings_Yaw);
		PID_init(&pids[PID_DIST_Z], PID1_Settings_Z);
	}else if (preset == 2){
		PID_init(&pids[PID_ANGLE_ROLL], PID2_Settings_Roll);
		PID_init(&pids[PID_ANGLE_PITCH], PID2_Settings_Pitch);
		PID_init(&pids[PID_ANGLE_YAW], PID2_Settings_Yaw);
		PID_init(&pids[PID_DIST_Z], PID2_Settings_Z);
	}else if (preset == 3){
		PID_init(&pids[PID_ANGLE_ROLL], PID3_Settings_Roll);
		PID_init(&pids[PID_ANGLE_PITCH], PID3_Settings_Pitch);
		PID_init(&pids[PID_ANGLE_YAW], PID3_Settings_Yaw);
		PID_init(&pids[PID_DIST_Z], PID3_Settings_Z);
	}else if (preset == 4){
		PID_init(&pids[PID_ANGLE_ROLL], PID4_Settings_Roll);
		PID_init(&pids[PID_ANGLE_PITCH], PID4_Settings_Pitch);
		PID_init(&pids[PID_ANGLE_YAW], PID4_Settings_Yaw);
		PID_init(&pids[PID_DIST_Z], PID4_Settings_Z);
	}else if (preset == 5){
		PID_init(&pids[PID_ANGLE_ROLL], PID5_Settings_Roll);
		PID_init(&pids[PID_ANGLE_PITCH], PID5_Settings_Pitch);
		PID_init(&pids[PID_ANGLE_YAW], PID5_Settings_Yaw);
		PID_init(&pids[PID_DIST_Z], PID5_Settings_Z);
	}else if (preset == 6){
		PID_init(&pids[PID_ANGLE_ROLL], PID6_Settings_Roll);
		PID_init(&pids[PID_ANGLE_PITCH], PID6_Settings_Pitch);
		PID_init(&pids[PID_ANGLE_YAW], PID6_Settings_Yaw);
		PID_init(&pids[PID_DIST_Z], PID6_Settings_Z);
	}else if (preset == 7){
		PID_init(&pids[PID_ANGLE_ROLL], PID7_Settings_Roll);
		PID_init(&pids[PID_ANGLE_PITCH], PID7_Settings_Pitch);
		PID_init(&pids[PID_ANGLE_YAW], PID7_Settings_Yaw);
		PID_init(&pids[PID_DIST_Z], PID7_Settings_Z);
	}else{
		PID_init(&pids[PID_ANGLE_ROLL], PID0_Settings_Roll);
		PID_init(&pids[PID_ANGLE_PITCH], PID0_Settings_Pitch);
		PID_init(&pids[PID_ANGLE_YAW], PID0_Settings_Yaw);
		PID_init(&pids[PID_DIST_Z], PID0_Settings_Z);
	}
}


