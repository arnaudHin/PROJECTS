/**
 * @file : Temperature.h
 * @brief :
 * @version
 * @date : April 29, 2021
 * @author: Arnaud
 */


#ifndef TEMPERATURE_H__
#define TEMPERATURE_H__

#include <commun.h>

//////////////////////////////////////////////////////////////////////////////////
//				Define						//
//////////////////////////////////////////////////////////////////////////////////

//Adresse I2C du capteur de temperature
#define ADRESS_SLAVE_TEMP_H_8_R	 			0x95
#define ADRESS_SLAVE_TEMP_H_8_W	 			0x94
//Adresse I2C des registres du capteur de temperature
#define TEMP_REG_ID_MANUFACTOR_8			0xFE
#define TEMP_REG_ID_MANUFACTOR_VALUE_8		0x53
#define TEMP_REG_HIGH_BYTE_8				0x00
#define TEMP_REG_LOW_BYTE_8					0x02
#define TEMP_REG_CONFIG_8					0x03
#define TEMP_REG_CONFIG_VALUE_8				0x0C //00001100 -> 12bits
#define TEMP_REG_STATUS_8					0x01 //si b7 == 1 -> conversion en cours

//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @struct
 * @brief
 */
typedef struct {
	uint8_t temperatureIDManufactorValue;
	uint8_t temperatureConfigValue;
}TemperatureConfig_t;

/**
 * @struct
 * @brief
 */
typedef struct{
	SensorConnectionStatus_e TemperatureStatus;
	uint8_t temperatureAdress;
	uint8_t temperatureRegIDManufactor;
	uint8_t temperatureRegValueHigh;
	uint8_t temperatureRegValueLow;
	uint8_t temperatureRegConfig;

	TemperatureConfig_t temperatureConfig;

	float Temperature_value;
}Temperature_t;




//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn DavidsonStatus_e Temperature_New()
 * @brief
 * @return
 */
extern DavidsonStatus_e Temperature_New();


/**
 * @fn DavidsonStatus_e Temperature_Free()
 * @brief
 * @return
 */
extern DavidsonStatus_e Temperature_Free();


/**
 * @fn SensorConnectionStatus_e Temperature_InitConnectionSensorBoard()
 * @brief
 * @return
 */
extern SensorConnectionStatus_e Temperature_InitConnectionSensorBoard();


/**
 * @fn DavidsonStatus_e Temperature_GetMeasure()
 * @brief
 * @return
 */
extern DavidsonStatus_e Temperature_GetMeasure();


/**
 * @fn Temperature_t Temperature_Get*()
 * @brief
 * @return
 */
extern Temperature_t * Temperature_Get();


/**
 * @fn float Temperature_GetValue()
 * @brief
 * @return
 */
extern float Temperature_GetValue();



/**
 * @fn void Temperature_Convert(uint8_t*, float*)
 * @brief
 * @param tabTempIn
 * @param dataTempOut
 */
extern void Temperature_Convert(uint8_t * tabTempIn, float * dataTempOut);




#endif /* TEMPERATURE_H__ */
