/**
 * @file : Humidity.h
 * @brief :
 * @version
 * @date : May 10, 2021
 * @author: Arnaud
 */


#ifndef HUMIDITY_H__
#define HUMIDITY_H__

#include <commun.h>


//////////////////////////////////////////////////////////////////////////////////
//				Define						//
//////////////////////////////////////////////////////////////////////////////////

//Adresse I2C du capteur de humidité
#define ADRESS_SLAVE_HUMID_H_8_R	 		0xBF
#define ADRESS_SLAVE_HUMID_H_8_W	 		0xBE
//Adresse I2C des registres du capteur de humidité
#define HUMID_REG_WHO_I_AM_8				0x0F
#define HUMID_REG_WHO_I_AM_VALUE_8			0xBC
#define HUMID_REG_OUT_L_8				0x28
#define HUMID_REG_OUT_H_8				0x29
#define HUMID_REG_H0_RH_X2_8				0x30
#define HUMID_REG_H1_RH_X2_8				0x31
#define HUMID_REG_H0_T0_OUT_L_8				0x36
#define HUMID_REG_H0_T0_OUT_H_8				0x37
#define HUMID_REG_H1_T0_OUT_L_8				0x3A
#define HUMID_REG_H1_T0_OUT_H_8				0x3B

#define HUMID_REG_AVCONF_8				0x10
#define HUMID_REG_CTRL1_8				0x20
#define HUMID_REG_CTRL2_8				0x21
#define HUMID_REG_CTRL3_8				0x22

#define HUMID_REG_AVCONF_VALUE_8			0x1B //Precision : Humidité de 0.15 rH% (2.1 uA -> selon précision)
#define HUMID_REG_CTRL1_VALUE_8				0x01 //[7] = ON/OFF | [2] = BDU | [1/0] = ODR
#define HUMID_REG_CTRL2_VALUE_8				0x00 //[7] = BOOT | [1] = ONESHOT | [1/0] = Heater (sleep mode)
#define HUMID_REG_CTRL3_VALUE_8				0x00

//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @struct
 * @brief
 */
typedef struct {
	uint8_t humidityWhoIAmValue;
	uint8_t humidityCrtl1Value;
	uint8_t humidityCrtl2Value;

}HumidityConfig_t;

/**
 * @struct
 * @brief
 */
typedef struct{
	SensorConnectionStatus_e humidityStatus;
	uint8_t humidityAdress;
	uint8_t humidityRegWhoIAm;
	uint8_t humidityRegValueHigh;
	uint8_t humidityRegValueLow;

	uint8_t humidityRegH0rHx2;
	uint8_t humidityRegH1rHx2;
	uint8_t humidityRegH0T0OUTHigh;
	uint8_t humidityRegH0T0OUTLow;
	uint8_t humidityRegH1T0OUTHigh;
	uint8_t humidityRegH1T0OUTLow;

	uint8_t humidityRegCrtl1;
	uint8_t humidityRegCrtl2;

	HumidityConfig_t humidityConfig;
	float humidityValue;
}Humidity_t;



//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn DavidsonStatus_e Humidity_New()
 * @brief
 * @return
 */
extern DavidsonStatus_e Humidity_New();


/**
 * @fn DavidsonStatus_e Humidity_Free()
 * @brief
 * @return
 */
extern DavidsonStatus_e Humidity_Free();


/**
 * @fn SensorConnectionStatus_e Humidity_InitConnectionSensorBoard()
 * @brief
 * @return
 */
extern SensorConnectionStatus_e Humidity_InitConnectionSensorBoard();


/**
 * @fn DavidsonStatus_e Humidity_GetMeasure()
 * @brief
 * @return
 */
extern DavidsonStatus_e Humidity_GetMeasure();


/**
 * @fn Humidity_t Humidity_Get*()
 * @brief
 * @return
 */
extern Humidity_t * Humidity_Get();



/**
 * @fn float Humidity_GetValue()
 * @brief
 * @return
 */
extern float Humidity_GetValue();




/**
 * @fn void Humidity_Convert(uint8_t*, float*)
 * @brief
 * @param tabTempIn
 * @param dataTempOut
 */
extern void Humidity_Convert(uint8_t * tabTempIn, float * dataTempOut);


#endif /* HUMIDITY_H__ */


