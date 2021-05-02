/*
 * accelerometre.c
 *
 *  Created on: Apr 22, 2021
 *      Author: Arnaud
 */


#include "i2c.h"
#include "stm32mp1xx_hal.h"
#include "xnucelo_sensors.h"


static uint8_t adressSlaveAcc = ADRESS_SLAVE_ACC_H_8;
static uint8_t numberTrials = 3;
static uint8_t timeOutTrial = I2C_TIMEOUT;

HAL_StatusTypeDef Init_Accelerometer(){

	HAL_StatusTypeDef state_acc;

	if( (&hi2c5 == NULL) || hi2c5.Instance != I2C5  ){
		return HAL_ERROR;//OK, pas de soucis ici
	}

	/* Verifier si sensor temperature connecte */
	state_acc = HAL_I2C_IsDeviceReady(&hi2c5 , adressSlaveAcc, numberTrials, timeOutTrial);
	if(state_acc != HAL_OK){
		return state_acc;
	}

	/* Verifier communication */
	uint8_t register_who_i_am = ACC_REG_WHO_AM_I_8;
	uint8_t who_i_am = 0x00;

	state_acc = I2C_Read_nucleo(adressSlaveAcc, register_who_i_am, &who_i_am);
	if( state_acc != HAL_OK || who_i_am != ACC_REG_WHO_AM_I_VALUE_8){
		return HAL_ERROR;
	}

	/* Configurer */
//	uint8_t register_config = TEMP_REG_CONFIG_8;
//	uint8_t config_value = TEMP_REG_CONFIG_VALUE_8;
//
//	state_temperature = I2C_Write_nucleo(adressSlaveTemp, register_config, &config_value);
//	if(state_temperature != HAL_OK){
//		return state_temperature;
//	}


	return state_acc;
}




HAL_StatusTypeDef Read_Accelerometer(X_NUCLEO_SENSORS_t * nucleoStruct){

	uint8_t register_acc_X_L = ACC_REG_OUT_X_L_8;

	uint8_t dataAcc[6];

	HAL_StatusTypeDef status;

	status = I2C_ReadMulti_nucleo(adressSlaveAcc, register_acc_X_L, &dataAcc, 6);

	nucleoStruct->Accelerometer_X = (int16_t) (dataAcc[1] << 8 | dataAcc[0]);
	nucleoStruct->Accelerometer_Y = (int16_t) (dataAcc[3] << 8 | dataAcc[2]);
	nucleoStruct->Accelerometer_Z = (int16_t) (dataAcc[5] << 8 | dataAcc[4]);

	return status;
}

void Compute_ACC(X_NUCLEO_SENSORS_t * nucleoStruct){

	Read_Accelerometer(nucleoStruct);

	nucleoStruct->Accelerometer_X /= 420;
	nucleoStruct->Accelerometer_Y /= 420;
	nucleoStruct->Accelerometer_Z /= 420;

}



