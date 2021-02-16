/*
 * bluetooth.c



 *
 *  Created on: 22 mars 2020
 *      Author: Martin ARONDEL & Arnaud HINCELIN
 */


#include "bluetooth.h"
#include "drone_def.h"
#include "datas_process.h"


static drone_data_t * drone_data;
static ctr_send_data = 0;


void BLUETOOTH_init(drone_data_t * drone_data_){
	UART_init(UART2_ID, 38400);
	drone_data = drone_data_;

}

//envoie un caractï¿½re
void BLUETOOTH_envoi_caractere(uint8_t c){
	c=UART_get_next_byte(UART2_ID);
	UART_putc(UART2_ID,c);
}


//reception d'un caractï¿re
char BLUETOOTH_reception_caractere(void){
	if(UART_data_ready(UART2_ID)){
		char c;
		c = UART_getc(UART2_ID);
		return c;
	}
	else{
		return 0;
	}
}

//reception d'une Trame de 4 informations
uint8_t *BLUETOOTH_reception_trame(void){
	static uint8_t trame[1];
	if(UART_data_ready(UART2_ID)){
		UART_gets(UART2_ID, trame, 1);
		return trame;
	}
	else{
		return 0;
	}
}

void BLUETOOTH_envoi_trame7(uint8_t info1, uint8_t info2, uint8_t info3, uint8_t info4, uint8_t info5, uint8_t info6, uint8_t info7){
	static uint8_t trame[7];
	trame[0] = info1;
	trame[1] = info2;
	trame[2] = info3;
	trame[3] = info4;
	trame[4] = info5;
	trame[5] = info6;
	trame[6] = info7;
	UART_puts(UART2_ID, trame, 7);
}

void BLUETOOTH_envoi_trame3(uint8_t info1, uint8_t info2, uint8_t info3){
	static uint8_t trame[3];
	trame[0] = info1;
	trame[1] = info2;
	trame[2] = info3;
	UART_puts(UART2_ID, trame, 3);
}

void BLUETOOTH_envoi_trame5(uint8_t info1, uint8_t info2, uint8_t info3, uint8_t info4, uint8_t info5){
	static uint8_t trame[5];
	trame[0] = info1;
	trame[1] = info2;
	trame[2] = info3;
	trame[3] = info4;
	trame[4] = info5;
	UART_puts(UART2_ID, trame, 5);
}

void BLUETOOTH_envoi_trame2(uint8_t info1, uint8_t info2){
	static uint8_t trame[2];
	trame[0] = info1;
	trame[1] = info2;
	UART_puts(UART2_ID, trame, 2);
}



//48.8 => 49 | 48.3 => 48
#define FLOAT_TO_UINT8(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

#define TOF_DATAS			4
#define MPU_DATAS			3
#define MOTOR_DATAS			8
#define PID_DATAS			4
#define TARGET_DATAS		4

//1 octet = 1 byte = 8 bits
#define SIZE_BYTE_BUFFER_TRAME	(TOF_DATAS+MPU_DATAS+MOTOR_DATAS+PID_DATAS+TARGET_DATAS)*2


void main_bluetooth(){
	/* reception du caractere start et stop : analyse de la trame */


	char c = BLUETOOTH_reception_caractere();
	/* Selection du preset : Attention, impossible de changer de preset pendant l'execution du programme !!!
	 *  a : selection du pid 1
	 * 	z : selection du pid 2
	 *  e : selection du pid 3
	 *  r : selection du pid 4
	 *  t : selection du pid 5
	 *  y : selection du pid 6
	 *  g : selection du pid 7
	 *  h : selection du pid 8
	 *
	 *
	 *  u : on DESACTIVE la regulation sur le yaw
	 *  i : on active la correction sur le pitch
	 *  o : on active la régulation sur z
	 *  p : on active la régulation sur x
	 *
	 *  s : démarrage de la régulation
	 *  d : arrêt de la régulation !!! Il faut relancer le programme pour relancer la régul !!!
	 *
	 * */
	switch(c){
		case ('a') :
			if(drone_data->block_config == 0){
				drone_data->preset_pid = 0; //on change la valeur
			}
			break;
		case ('z') :
			if(drone_data->block_config == 0){
				drone_data->preset_pid = 1; //on change la valeur
			}
			break;
		case ('e') :
			if(drone_data->block_config == 0){
				drone_data->preset_pid = 2; //on change la valeur
			}
			break;
		case ('r') :
			if(drone_data->block_config == 0){
				drone_data->preset_pid = 3; //on change la valeur
			}
			break;
		case ('t') :
			if(drone_data->block_config == 0){
				drone_data->preset_pid = 4; //on change la valeur
			}
			break;
		case ('y') :
			if(drone_data->block_config == 0){
				drone_data->preset_pid = 5; //on change la valeur
			}
			break;
		case ('g') :
			if(drone_data->block_config == 0){
		     	drone_data->preset_pid = 6; //on change la valeur
			}
			break;
		case ('h') :
			if(drone_data->block_config == 0){
				drone_data->preset_pid = 7; //on change la valeur
			}
		    break;
		case ('o') :
			if(drone_data->block_config == 0){
				drone_data->z_correction = 1; //on change la valeur
			}
			break;
		case ('u') :
			if(drone_data->block_config == 0){
				drone_data->yaw_regulation = 0; //on change la valeur
			}
			break;
		case ('p') :
			if(drone_data->block_config == 0){
				drone_data->x_correction = 1; //on change la valeur
			}
			break;
		case ('i') :
			if(drone_data->block_config == 0){
				drone_data->pitch_correction = 1; //on change la valeur
			}
			break;
		case ('s') :
			data_process_init(drone_data); //init de la lecture des capteurs, utilise TIMER5
			break;
		case ('d') :
			data_process_stop();
			break;
		default :
			break;
	}

	if(drone_data->process_data == 1 && ctr_send_data == 3){
	ctr_send_data = 0;
	uint16_t backward_X = drone_data->datas_sensors_pooling.dist_backward_X;
	uint16_t side_Y = drone_data->datas_sensors_pooling.dist_side_Y;
	uint16_t forward_X = drone_data->datas_sensors_pooling.dist_forward_X;
	uint16_t low_Z = drone_data->datas_sensors_pooling.dist_low_Z;

	int16_t roll_angle = (int16_t) drone_data->datas_sensors_pooling.roll_angle;
	int16_t pitch_angle = (int16_t) drone_data->datas_sensors_pooling.pitch_angle;
	int16_t yaw_angle = (int16_t) drone_data->datas_sensors_pooling.yaw_angle;

	int16_t roll_pid = (int16_t) drone_data->pid_correction.roll_pid;
	int16_t pitch_pid = (int16_t) drone_data->pid_correction.pitch_pid;
	int16_t yaw_pid = (int16_t) drone_data->pid_correction.yaw_pid;
	int16_t Z_pid = (int16_t) drone_data->pid_correction.Z_pid;

	int16_t roll_target = (int16_t) drone_data->target_values.roll_target;
	int16_t pitch_target = (int16_t) drone_data->target_values.pitch_target;
	int16_t yaw_target = (int16_t) drone_data->target_values.yaw_target;
	int16_t z_target = (int16_t) drone_data->target_values.z_target;

	uint16_t motor_sup_1 = drone_data->motor_cmd.m11;
	uint16_t motor_sup_2 = drone_data->motor_cmd.m12;
	uint16_t motor_sup_3 = drone_data->motor_cmd.m13;
	uint16_t motor_sup_4 = drone_data->motor_cmd.m14;
	uint16_t motor_inf_1 = drone_data->motor_cmd.m21;
	uint16_t motor_inf_2 = drone_data->motor_cmd.m22;
	uint16_t motor_inf_3 = drone_data->motor_cmd.m23;
	uint16_t motor_inf_4 = drone_data->motor_cmd.m24;

	//Négatif ==>> complément à deux (Changer en opposé jusqu'au dernier bit à 1, puis laisser le rste à 0)

	//convertir en paquet de 8 bits : uint8_t data[2] = {data16, (data16 >> 8)}; // {lower byte, upper byte)
	uint8_t buffer_uint8_to_send[SIZE_BYTE_BUFFER_TRAME];
	uint16_t size_ocets = SIZE_BYTE_BUFFER_TRAME;


	/* SEND ALL DATAS TRUE CODE */
	buffer_uint8_to_send[0] = (backward_X >> 8);
	buffer_uint8_to_send[1] = (backward_X);

	buffer_uint8_to_send[3] = (side_Y);
	buffer_uint8_to_send[2] = (side_Y >> 8);

	buffer_uint8_to_send[5] = (forward_X);
	buffer_uint8_to_send[4] = (forward_X >> 8);

	buffer_uint8_to_send[7] = (low_Z);
	buffer_uint8_to_send[6] = (low_Z >> 8);

	buffer_uint8_to_send[9] = (roll_angle);
	buffer_uint8_to_send[8] = (roll_angle >> 8);

	buffer_uint8_to_send[11] = (pitch_angle);
	buffer_uint8_to_send[10] = (pitch_angle >> 8);

	buffer_uint8_to_send[13] = (yaw_angle);
	buffer_uint8_to_send[12] = (yaw_angle >> 8);

	//_________________________________________________________

	buffer_uint8_to_send[15] = (roll_pid);
	buffer_uint8_to_send[14] = (roll_pid >> 8);

	buffer_uint8_to_send[17] = (pitch_pid);
	buffer_uint8_to_send[16] = (pitch_pid >> 8);

	buffer_uint8_to_send[19] = (yaw_pid);
	buffer_uint8_to_send[18] = (yaw_pid >> 8);

	buffer_uint8_to_send[21] = (Z_pid);
	buffer_uint8_to_send[20] = (Z_pid >> 8);

	//____________________________________________________________

	buffer_uint8_to_send[23] = (roll_target);
	buffer_uint8_to_send[22] = (roll_target >> 8);

	buffer_uint8_to_send[25] = (pitch_target);
	buffer_uint8_to_send[24] = (pitch_target >> 8);

	buffer_uint8_to_send[27] = (yaw_target);
	buffer_uint8_to_send[26] = (yaw_target >> 8);

	buffer_uint8_to_send[29] = (z_target);
	buffer_uint8_to_send[28] = (z_target >> 8);
	//____________________________________________________________

	buffer_uint8_to_send[31] = (motor_sup_1);
	buffer_uint8_to_send[30] = (motor_sup_1 >> 8);

	buffer_uint8_to_send[33] = (motor_sup_2);
	buffer_uint8_to_send[32] = (motor_sup_2 >> 8);

	buffer_uint8_to_send[35] = (motor_sup_3);
	buffer_uint8_to_send[34] = (motor_sup_3 >> 8);

	buffer_uint8_to_send[37] = (motor_sup_4);
	buffer_uint8_to_send[36] = (motor_sup_4 >> 8);

	buffer_uint8_to_send[39] = (motor_inf_1);
	buffer_uint8_to_send[38] = (motor_inf_1 >> 8);

	buffer_uint8_to_send[41] = (motor_inf_2);
	buffer_uint8_to_send[40] = (motor_inf_2 >> 8);

	buffer_uint8_to_send[43] = (motor_inf_3);
	buffer_uint8_to_send[42] = (motor_inf_3 >> 8);

	buffer_uint8_to_send[45] = (motor_inf_4);
	buffer_uint8_to_send[44] = (motor_inf_4 >> 8);


	DIALOG_send_packet(size_ocets, buffer_uint8_to_send);
	}else if(drone_data->process_data == 1){
		ctr_send_data++;
	}
}



