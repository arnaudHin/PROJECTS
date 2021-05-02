/*
 * xnucleo_sensors.c
 *
 *  Created on: Apr 20, 2021
 *      Author: Arnaud
 */

#include "main.h"
#include "i2c.h"
#include "gpio.h"
#include "xnucelo_sensors.h"



HAL_StatusTypeDef I2C_Read_nucleo(uint8_t address, uint8_t reg, uint8_t * received_data)
{

	uint16_t memAddressSize = I2C_MEMADD_SIZE_8BIT;

	return HAL_I2C_Mem_Read(&hi2c5, address, reg, memAddressSize, received_data, 1, I2C_TIMEOUT);
}



HAL_StatusTypeDef I2C_Write_nucleo(uint8_t address, uint8_t reg, uint8_t * data_wrtitten){

	uint16_t memAddressSize = I2C_MEMADD_SIZE_8BIT;

	return HAL_I2C_Mem_Write(&hi2c5, address, reg, memAddressSize, data_wrtitten, 1, I2C_TIMEOUT);
}

HAL_StatusTypeDef I2C_ReadMulti_nucleo(uint8_t address, uint8_t reg, uint8_t * tab_received_data, uint16_t count){

	uint16_t memAddressSize = I2C_MEMADD_SIZE_8BIT;

	return HAL_I2C_Mem_Write(&hi2c5, address, reg, memAddressSize, tab_received_data, count, I2C_TIMEOUT);

}


HAL_StatusTypeDef Init_all_sensors(){

	HAL_StatusTypeDef status;

	status = Init_Temperature();

	if(status != HAL_OK){
		return HAL_ERROR;
	}

	status = Init_Accelerometer();

	if(status != HAL_OK){
		return HAL_ERROR;
	}

	status = Init_Gyroscope();

	if(status != HAL_OK){
		return HAL_ERROR;
	}

	return status;
}





