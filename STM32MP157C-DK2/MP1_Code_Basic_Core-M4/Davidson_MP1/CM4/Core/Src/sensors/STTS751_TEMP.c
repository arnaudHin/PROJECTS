/*
 * temperature.c
 *
 *  Created on: Apr 22, 2021
 *      Author: Arnaud
 */

#include "i2c.h"
#include "stm32mp1xx_hal.h"
#include "xnucelo_sensors.h"


static 	uint8_t adressSlaveTemp = ADRESS_SLAVE_TEMP_H_8; //0x94U
static uint8_t numberTrials = 3;
static uint8_t timeOutTrial = I2C_TIMEOUT;

HAL_StatusTypeDef Init_Temperature(){

	HAL_StatusTypeDef state_temperature;


	if( (&hi2c5 == NULL) || hi2c5.Instance != I2C5  ){
		return HAL_ERROR;//OK, pas de soucis ici
	}

	/* Verifier si sensor temperature connecte */
	state_temperature = HAL_I2C_IsDeviceReady(&hi2c5 , adressSlaveTemp, numberTrials, timeOutTrial);
	if(state_temperature != HAL_OK){
		return state_temperature;
	}

	/* Verifier communication */
	uint8_t register_manufactor = TEMP_REG_ID_MANUFACTOR_8;
	uint8_t manufactor_temp = 0x00;
	state_temperature = I2C_Read_nucleo(adressSlaveTemp, register_manufactor, &manufactor_temp);
	if( state_temperature != HAL_OK || manufactor_temp != TEMP_REG_ID_MANUFACTOR_VALUE_8){
		return HAL_ERROR;
	}

	/* Configurer */
	uint8_t register_config = TEMP_REG_CONFIG_8;
	uint8_t config_value = TEMP_REG_CONFIG_VALUE_8;
	state_temperature = I2C_Write_nucleo(adressSlaveTemp, register_config, &config_value);
	if(state_temperature != HAL_OK){
		return state_temperature;
	}


	return state_temperature;
}




HAL_StatusTypeDef Read_Temperature(X_NUCLEO_SENSORS_t * nucleoStruct){

	uint8_t register_temp_H = TEMP_REG_HIGH_BYTE_8;
	uint8_t register_temp_L = TEMP_REG_LOW_BYTE_8;

	uint8_t dataTemp_H = 0;
	uint8_t dataTemp_L = 0;


	int16_t temp = 0;

	HAL_StatusTypeDef status;

	status = I2C_Read_nucleo(adressSlaveTemp, register_temp_H, &dataTemp_H);

	status = I2C_Read_nucleo(adressSlaveTemp, register_temp_L, &dataTemp_L);

	temp = (int16_t) (dataTemp_H);

	nucleoStruct->Temperature = (float) temp;


	return status;
}







