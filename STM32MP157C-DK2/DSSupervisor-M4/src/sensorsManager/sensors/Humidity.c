/**
 * @file : Humidity.c
 * @brief :
 * @version
 * @date : May 10, 2021
 * @author: Arnaud
 */


#include <stdlib.h>
#include <sensorsManager/sensors/Humidity.h>
#include <commun.h>
#include <sensorsManager/I2CCommunication.h>
#include <utils/stm32mp1xx_hal_i2c.h>
#include <string.h>



//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//				Variables Privées				//
//////////////////////////////////////////////////////////////////////////////////
static Humidity_t * myHumidity;


//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Privées			//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Publiques				//
//////////////////////////////////////////////////////////////////////////////////
extern DavidsonStatus_e Humidity_New(){
	myHumidity = NULL;

	myHumidity = calloc(1, sizeof(Humidity_t));

	if(myHumidity == NULL){
		return DAV_ERROR;
	}

	myHumidity->humidityStatus = NOTCONNECTED;
	myHumidity->humidityAdress = ADRESS_SLAVE_HUMID_H_8_R;
	myHumidity->humidityRegWhoIAm = HUMID_REG_WHO_I_AM_8;
	myHumidity->humidityRegValueLow = HUMID_REG_OUT_L_8;
	myHumidity->humidityRegValueHigh = HUMID_REG_OUT_H_8;
	myHumidity->humidityRegH0rHx2 = HUMID_REG_H0_RH_X2_8;
	myHumidity->humidityRegH1rHx2 = HUMID_REG_H1_RH_X2_8;
	myHumidity->humidityRegH0T0OUTLow = HUMID_REG_H0_T0_OUT_L_8;
	myHumidity->humidityRegH0T0OUTHigh = HUMID_REG_H0_T0_OUT_H_8;
	myHumidity->humidityRegH1T0OUTLow = HUMID_REG_H1_T0_OUT_L_8;
	myHumidity->humidityRegH1T0OUTHigh = HUMID_REG_H1_T0_OUT_H_8;

	myHumidity->humidityRegCrtl1 = HUMID_REG_CTRL1_8;
	myHumidity->humidityRegCrtl2 = HUMID_REG_CTRL2_8;

	myHumidity->humidityConfig.humidityCrtl1Value = HUMID_REG_CTRL1_VALUE_8;
	myHumidity->humidityConfig.humidityCrtl2Value = HUMID_REG_CTRL2_VALUE_8;
	myHumidity->humidityConfig.humidityWhoIAmValue = HUMID_REG_WHO_I_AM_VALUE_8;

	return DAV_OK;
}
extern DavidsonStatus_e Humidity_Free(){

	free(myHumidity);

	if(myHumidity != NULL){
		return DAV_ERROR;
	}

	return DAV_OK;


}
extern SensorConnectionStatus_e Humidity_InitConnectionSensorBoard(){

	DavidsonStatus_e status;
	status = I2CProtocol_InitSensor(HUMI);

	if(status == DAV_OK){
		myHumidity->humidityStatus = CONNECTED;
	}
	else {
		myHumidity->humidityStatus = NOTCONNECTED;
	}

	return myHumidity->humidityStatus;

}
extern DavidsonStatus_e Humidity_GetMeasure(){

	DavidsonStatus_e status;

	if(myHumidity->humidityStatus != CONNECTED){
		return DAV_ERROR;
	}

	status = I2CProtocol_GetSensorMeasure(HUMI);

	return (DavidsonStatus_e) status;

}



extern Humidity_t * Humidity_Get(){
	return myHumidity;

}


extern float Humidity_GetValue(){
  return myHumidity->humidityValue;
}


extern void Humidity_Convert(uint8_t * tabTempIn, float * dataTempOut){

	uint8_t dataHumid[8];
	memcpy(&dataHumid, tabTempIn, 8);

	int16_t H0_T0_out, H1_T0_out, H_T_out;
	int16_t H0_rh, H1_rh;
	int32_t temp;
	uint16_t value;

	H0_rh = (int32_t) dataHumid[0];
	H1_rh = (int32_t) dataHumid[1];
	H0_rh /=2;
	H1_rh /=2;

	H0_T0_out = ( ((uint16_t)dataHumid[3])<<8) | (uint16_t)dataHumid[2] ;

	H1_T0_out = ( ((uint16_t)dataHumid[5])<<8) | (uint16_t)dataHumid[4] ;

	H_T_out = ( ((uint16_t)dataHumid[7])<<8) | (uint16_t)dataHumid[6] ;

	temp = ( (int32_t)(H_T_out - H0_T0_out) )*( (int32_t)(H1_rh - H0_rh)*10 ) ;
	value = (uint16_t) (temp/(H1_T0_out - H0_T0_out) +H0_rh*10 );

	if(value > 1000){
	    value = 1000;
	}

	float hum = (float)value;
	/* Mettre en pourcentage */
	hum /= 10;

	*dataTempOut = hum;

}





//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Privées				//
//////////////////////////////////////////////////////////////////////////////////




