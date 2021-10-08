/**
 * @file : Pressure.h
 * @brief :
 * @version
 * @date : April 29, 2021
 * @author: Arnaud
 */


#ifndef PRESSURE_H__
#define PRESSURE_H__

#include <commun.h>

//////////////////////////////////////////////////////////////////////////////////
//				Define						//
//////////////////////////////////////////////////////////////////////////////////

//Adresse I2C du capteur de pression
#define ADRESS_SLAVE_PRESS_H_8_R	 			0xBB
#define ADRESS_SLAVE_PRESS_H_8_W	 			0xBA
//Adresse I2C des registres du capteur de pression
#define PRESS_REG_WHO_I_AM_8				0x0F
#define PRESS_REG_WHO_I_AM_VALUE_8			0xB3
#define PRESS_REG_OUT_XL_8				0x28
#define PRESS_REG_OUT_L_8				0x29
#define PRESS_REG_OUT_H_8				0x2A

#define PRESS_REG_CTRL1_8				0x10
#define PRESS_REG_CTRL2_8				0x11

#define PRESS_REG_CTRL1_VALUE_8			0x00 //Si 00
#define PRESS_REG_CTRL2_VALUE_8			0x01

#define PRESS_REG_STATUS_8					0x27 //



//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////


typedef struct {
	uint8_t pressureWhoIAmValue;
	uint8_t pressureCrtl1Value;
	uint8_t pressureCrtl2Value;

}PressureConfig_t;

typedef struct{
	SensorConnectionStatus_e pressureStatus;
	uint8_t pressureAdress;
	uint8_t pressureRegWhoIAm;
	uint8_t pressureRegValueHigh;
	uint8_t pressureRegValueLow;
	uint8_t pressureRegValueXLow;
	uint8_t pressureRegCrtl1;
	uint8_t pressureRegCrtl2;

	PressureConfig_t pressureConfig;
	float pressureValue;

}Pressure_t;



//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn DavidsonStatus_e Pressure_New()
 * @brief
 * @return
 */
extern DavidsonStatus_e Pressure_New();


/**
 * @fn DavidsonStatus_e Pressure_Free()
 * @brief
 * @return
 */
extern DavidsonStatus_e Pressure_Free();


/**
 * @fn SensorConnectionStatus_e Pressure_InitConnectionSensorBoard()
 * @brief
 * @return
 */
extern SensorConnectionStatus_e Pressure_InitConnectionSensorBoard();


/**
 * @fn DavidsonStatus_e Pressure_GetMeasure()
 * @brief
 * @return
 */
extern DavidsonStatus_e Pressure_GetMeasure();


/**
 * @fn Pressure_t Pressure_Get*()
 * @brief
 * @return
 */
extern Pressure_t * Pressure_Get();


/**
 * @fn float Pressure_GetValue()
 * @brief
 * @return
 */
extern float Pressure_GetValue();



/**
 * @fn void Pressure_Convert(uint8_t*, float*)
 * @brief
 * @param tabTempIn
 * @param dataTempOut
 */
extern void Pressure_Convert(uint8_t * tabTempIn, float * dataTempOut);



#endif /* PRESSURE_H__ */





//Adresse
#define ADRESS_SLAVE_PRESS_H_8	 			0xBA
#define ADRESS_SLAVE_PRESS_L_8	 			0xB8
