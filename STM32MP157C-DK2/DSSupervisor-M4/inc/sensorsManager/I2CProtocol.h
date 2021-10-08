/*
 * I2CProtocol.h
 *
 *  Created on: May 10, 2021
 *      Author: Arnaud
 */

#ifndef I2CPROTOCOL_H__
#define I2CPROTOCOL_H__


#include "main.h"
#include "utils/stm32mp1xx_hal_i2c.h"
#include <commun.h>



extern DavidsonStatus_e I2CProtocol_InitI2C5(void);
extern DavidsonStatus_e I2CProtocol_InitSensor(SensorId_e sensorId);
extern DavidsonStatus_e I2CProtocol_GetSensorMeasure(SensorId_e sensorId);
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);

#endif /* I2CPROTOCOL_H__ */

