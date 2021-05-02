/*
 * LSM6DSO_ACC-GYRO.c
 *
 *  Created on: Apr 23, 2021
 *      Author: Arnaud
 */

#include "i2c.h"
#include "stm32mp1xx_hal.h"
#include "xnucelo_sensors.h"


static uint16_t adressSlaveGyro = ADRESS_SLAVE_GYRO_H_8;
static uint32_t numberTrials = 3;
static uint32_t timeOutTrial = I2C_TIMEOUT;


HAL_StatusTypeDef Init_Gyroscope(){

	HAL_StatusTypeDef state_gyro;

	if( (&hi2c5 == NULL) || hi2c5.Instance != I2C5  ){
		return HAL_ERROR;//OK, pas de soucis ici
	}

	/* Verifier si sensor temperature connecte */
	state_gyro = HAL_I2C_IsDeviceReady(&hi2c5 , adressSlaveGyro, numberTrials, timeOutTrial);
	if(state_gyro != HAL_OK){
		return state_gyro;
	}

	/* Verifier communication */
	uint8_t register_who_i_am = GYRO_REG_WHO_AM_I_8;
	uint8_t who_i_am = 0x00;

	state_gyro = I2C_Read_nucleo(adressSlaveGyro, register_who_i_am, &who_i_am);
	if( state_gyro != HAL_OK || who_i_am != GYRO_REG_WHO_AM_I_VALUE_8){
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

	return state_gyro;
}


HAL_StatusTypeDef Read_Gyroscope(X_NUCLEO_SENSORS_t * nucleoStruct){

	uint8_t register_gyro_X_L = GYRO_REG_OUT_XG_L_8;

	uint8_t dataGyro[6];

	HAL_StatusTypeDef status;

	status = I2C_ReadMulti_nucleo(adressSlaveGyro, register_gyro_X_L, &dataGyro[0], 6);

	nucleoStruct->Gyroscope_X = (int16_t) ( (int16_t)dataGyro[1] << 8) | dataGyro[0];
	nucleoStruct->Gyroscope_Y = (int16_t) ( (int16_t)dataGyro[3] << 8) | dataGyro[2];
	nucleoStruct->Gyroscope_Z = (int16_t) ( (int16_t)dataGyro[5] << 8) | dataGyro[4];

//	nucleoStruct->Gyroscope_X = ( ((int16_t) (dataGyro[1] << 8)) + (int16_t) dataGyro[0] ) ;
//	nucleoStruct->Gyroscope_Y = ( ((int16_t) (dataGyro[3] << 8)) + (int16_t) dataGyro[2] ) ;
//	nucleoStruct->Gyroscope_Z = ( ((int16_t) (dataGyro[5] << 8)) + (int16_t) dataGyro[4] ) ;

//	uint8_t register_gyro_X_H = GYRO_REG_OUT_XG_H_8;
//	uint8_t register_gyro_Y_L = GYRO_REG_OUT_YG_L_8;
//	uint8_t register_gyro_Y_H = GYRO_REG_OUT_YG_H_8;
//	uint8_t register_gyro_Z_L = GYRO_REG_OUT_ZG_L_8;
//	uint8_t register_gyro_Z_H = GYRO_REG_OUT_ZG_H_8;
//
//	uint8_t dataGyroX_L = 0;
//	uint8_t dataGyroX_H = 0;
//	uint8_t dataGyroY_L = 0;
//	uint8_t dataGyroY_H = 0;
//	uint8_t dataGyroZ_L = 0;
//	uint8_t dataGyroZ_H = 0;
//
//	HAL_StatusTypeDef status;
//
//	status = I2C_Read_nucleo(adressSlaveGyro, register_gyro_X_L, &dataGyroX_L);
//	status = I2C_Read_nucleo(adressSlaveGyro, register_gyro_X_H, &dataGyroX_H);
//	status = I2C_Read_nucleo(adressSlaveGyro, register_gyro_Y_L, &dataGyroY_L);
//	status = I2C_Read_nucleo(adressSlaveGyro, register_gyro_Y_H, &dataGyroY_H);
//	status = I2C_Read_nucleo(adressSlaveGyro, register_gyro_Z_L, &dataGyroZ_L);
//	status = I2C_Read_nucleo(adressSlaveGyro, register_gyro_Z_H, &dataGyroZ_H);
//
//	nucleoStruct->Gyroscope_X = (int16_t) (dataGyroX_H << 8 | dataGyroX_L);
//	nucleoStruct->Gyroscope_Y = (int16_t) (dataGyroY_H << 8 | dataGyroY_L);
//	nucleoStruct->Gyroscope_Z = (int16_t) (dataGyroZ_H << 8 | dataGyroZ_L);


	return status;
}











