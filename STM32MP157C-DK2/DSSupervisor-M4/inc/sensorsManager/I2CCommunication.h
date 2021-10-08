/**
 * @file : I2CCommunication.h
 * @brief :
 * @version
 * @date : May 10, 2021
 * @author: Arnaud
 */

#ifndef I2CPROTOCOL_H__
#define I2CPROTOCOL_H__


#include "main.h"
#include "utils/stm32mp1xx_hal_i2c.h"
#include <commun.h>

//////////////////////////////////////////////////////////////////////////////////
//				Define						//
//////////////////////////////////////////////////////////////////////////////////

#define I2C5_SDA_PIN				GPIO_PIN_12
#define I2C5_SCL_PIN				GPIO_PIN_11
#define I2C5_PORT				GPIOA
#define I2C_TIMEOUT_TRIAL			100
#define I2C_NB_TRIALS				3



//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn DavidsonStatus_e I2CProtocol_InitI2C5(void)
 * @brief
 * @return
 */
extern DavidsonStatus_e I2CProtocol_InitI2C5(void);


/**
 * @fn DavidsonStatus_e I2CProtocol_InitSensor(SensorId_e)
 * @brief
 * @param sensorId
 * @return
 */
extern DavidsonStatus_e I2CProtocol_InitSensor(SensorId_e sensorId);


/**
 * @fn DavidsonStatus_e I2CProtocol_GetSensorMeasure(SensorId_e)
 * @brief
 * @param sensorId
 * @return
 */
extern DavidsonStatus_e I2CProtocol_GetSensorMeasure(SensorId_e sensorId);


/**
 * @fn void HAL_I2C_MspInit(I2C_HandleTypeDef*)
 * @brief
 * @param hi2c
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);



#endif /* I2CPROTOCOL_H__ */

