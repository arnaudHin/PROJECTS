/*
 * LPS22HH_PRESS.c
 *
 *  Created on: May 2, 2021
 *      Author: Arnaud
 */


#include "i2c.h"
#include "stm32mp1xx_hal.h"
#include "xnucelo_sensors.h"


static 	uint8_t adressSlavePress = ADRESS_SLAVE_PRESS_H_8;
static uint8_t numberTrials = 3;
static uint8_t timeOutTrial = I2C_TIMEOUT;

HAL_StatusTypeDef Init_Pressure(){

	HAL_StatusTypeDef state_pressure;


	if( (&hi2c5 == NULL) || hi2c5.Instance != I2C5  ){
		return HAL_ERROR;//OK, pas de soucis ici
	}

	/* Verifier si sensor temperature connecte */
	state_pressure = HAL_I2C_IsDeviceReady(&hi2c5 , adressSlavePress, numberTrials, timeOutTrial);
	if(state_pressure != HAL_OK){
		return state_pressure;
	}

	/* Verifier communication */
	uint8_t register_who_i_am = PRESS_REG_WHO_AM_I_8
	uint8_t who_i_am = 0x00;

	state_pressure = I2C_Read_nucleo(adressSlavePress, register_who_i_am, &who_i_am);
	if( state_pressure != HAL_OK || who_i_am != PRESS_REG_WHO_AM_I_VALUE_8){
		return HAL_ERROR;
	}

	/* Configurer */
//	uint8_t register_config = TEMP_REG_CONFIG_8;
//	uint8_t config_value = TEMP_REG_CONFIG_VALUE_8;
//	state_temperature = I2C_Write_nucleo(adressSlaveTemp, register_config, &config_value);
//	if(state_temperature != HAL_OK){
//		return state_temperature;
//	}


	return state_pressure;
}











