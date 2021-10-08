/**
 * @file : MeasuresProcessorSupervisor.c
 * @brief :
 * @version
 * @date : April 4, 2021
 * @author: Arnaud
 */

#include <stdlib.h>
#include <sensorsManager/sensors/Temperature.h>
#include <commun.h>
#include <sensorsManager/I2CCommunication.h>
#include "utils/stm32mp1xx_hal_i2c.h"


//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//				Variables Privées				//
//////////////////////////////////////////////////////////////////////////////////
static Temperature_t * myTemperature;


//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Privées			//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Publiques				//
//////////////////////////////////////////////////////////////////////////////////
extern DavidsonStatus_e Temperature_New(){

	myTemperature = NULL;

	myTemperature = calloc(1, sizeof(Temperature_t));

	if(myTemperature == NULL){
		return DAV_ERROR;
	}

	myTemperature->TemperatureStatus = NOTCONNECTED;
	myTemperature->temperatureAdress = ADRESS_SLAVE_TEMP_H_8_R;
	myTemperature->temperatureRegIDManufactor = TEMP_REG_ID_MANUFACTOR_8;
	myTemperature->temperatureRegConfig = TEMP_REG_CONFIG_8;
	myTemperature->temperatureRegValueHigh = TEMP_REG_HIGH_BYTE_8;
	myTemperature->temperatureRegValueLow = TEMP_REG_LOW_BYTE_8;
	myTemperature->temperatureConfig.temperatureConfigValue = TEMP_REG_CONFIG_VALUE_8;
	myTemperature->temperatureConfig.temperatureIDManufactorValue = TEMP_REG_ID_MANUFACTOR_VALUE_8;

	return DAV_OK;
}


extern DavidsonStatus_e Temperature_Free(){

	free(myTemperature);

	if(myTemperature != NULL){
		return DAV_ERROR;
	}

	return DAV_OK;
}


extern SensorConnectionStatus_e Temperature_InitConnectionSensorBoard(){

	DavidsonStatus_e status;
	status = I2CProtocol_InitSensor(TEMP);

	if(status == DAV_OK){
		myTemperature->TemperatureStatus = CONNECTED;
	}
	else {
		myTemperature->TemperatureStatus = NOTCONNECTED;
	}

	return myTemperature->TemperatureStatus;
}


extern DavidsonStatus_e Temperature_GetMeasure(){

	DavidsonStatus_e status;

	if(myTemperature->TemperatureStatus != CONNECTED){
		return DAV_ERROR;
	}

	status = I2CProtocol_GetSensorMeasure(TEMP);

	return (DavidsonStatus_e) status;
}



extern Temperature_t * Temperature_Get(){
	return myTemperature;
}

extern float Temperature_GetValue(){
	return myTemperature->Temperature_value;
}

extern void Temperature_Convert(uint8_t * tabTempIn, float * dataTempOut){

	uint8_t dataTemp_H = tabTempIn[0];
	uint8_t dataTemp_L = tabTempIn[1];

	int16_t dataTemp = (int16_t)(dataTemp_H)<<8|dataTemp_L;

	*dataTempOut = ( (float)dataTemp/256 );
}


//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Privées				//
//////////////////////////////////////////////////////////////////////////////////








