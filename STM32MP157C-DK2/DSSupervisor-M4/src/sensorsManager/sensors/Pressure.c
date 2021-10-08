/**
 * @file : Pressure.c
 * @brief :
 * @version
 * @date : May 10, 2021
 * @author: Arnaud
 */

#include <stdlib.h>
#include <sensorsManager/sensors/Pressure.h>
#include <commun.h>
#include <sensorsManager/I2CCommunication.h>
#include "utils/stm32mp1xx_hal_i2c.h"


//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//				Variables Privées				//
//////////////////////////////////////////////////////////////////////////////////

static Pressure_t * myPressure;


//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Privées			//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Publiques				//
//////////////////////////////////////////////////////////////////////////////////
extern DavidsonStatus_e Pressure_New(){

	myPressure = NULL;

	myPressure = calloc(1, sizeof(Pressure_t));

	if(myPressure == NULL){
		return DAV_ERROR;
	}

	myPressure->pressureStatus = NOTCONNECTED;
	myPressure->pressureAdress = ADRESS_SLAVE_PRESS_H_8_R;
	myPressure->pressureRegWhoIAm = PRESS_REG_WHO_I_AM_8;
	myPressure->pressureRegValueXLow = PRESS_REG_OUT_XL_8;
	myPressure->pressureRegValueLow = PRESS_REG_OUT_L_8;
	myPressure->pressureRegValueHigh = PRESS_REG_OUT_H_8;
	myPressure->pressureRegCrtl1 = PRESS_REG_CTRL1_8;
	myPressure->pressureRegCrtl2 = PRESS_REG_CTRL2_8;

	myPressure->pressureConfig.pressureWhoIAmValue = PRESS_REG_WHO_I_AM_VALUE_8;
	myPressure->pressureConfig.pressureCrtl1Value = PRESS_REG_CTRL1_VALUE_8;
	myPressure->pressureConfig.pressureCrtl2Value = PRESS_REG_CTRL2_VALUE_8;

	return DAV_OK;
}


extern DavidsonStatus_e Pressure_Free(){

	free(myPressure);

	if(myPressure != NULL){
		return DAV_ERROR;
	}

	return DAV_OK;
}


extern SensorConnectionStatus_e Pressure_InitConnectionSensorBoard(){

	DavidsonStatus_e status;
	status = I2CProtocol_InitSensor(PRES);

	if(status == DAV_OK){
		myPressure->pressureStatus = CONNECTED;
	}
	else {
		myPressure->pressureStatus = NOTCONNECTED;
	}

	return myPressure->pressureStatus;
}



extern DavidsonStatus_e Pressure_GetMeasure(){

	DavidsonStatus_e status;

	if(myPressure->pressureStatus != CONNECTED){
		return DAV_ERROR;
	}

	status = I2CProtocol_GetSensorMeasure(PRES);

	return (DavidsonStatus_e) status;
}

extern Pressure_t * Pressure_Get(){
	return myPressure;
}

extern float Pressure_GetValue(){
	return myPressure->pressureValue;
}

extern void Pressure_Convert(uint8_t * tabTempIn, float * dataTempOut){

	uint8_t dataTemp_H = tabTempIn[0];
	uint8_t dataTemp_L = tabTempIn[1];
	uint8_t dataTemp_XL = tabTempIn[2];

	int32_t dataTemp = (int32_t)(dataTemp_H)<<16 | (int16_t)dataTemp_L<<8 | dataTemp_XL;

	*dataTempOut = ( (float)dataTemp/4096 );
}


//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Privées				//
//////////////////////////////////////////////////////////////////////////////////





















