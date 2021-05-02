/*
 * LIS2MDL_MAGN.c
 *
 *  Created on: May 2, 2021
 *      Author: Arnaud
 */

#include "i2c.h"
#include "stm32mp1xx_hal.h"
#include "xnucelo_sensors.h"

static 	uint8_t adressSlaveMagn = ADRESS_SLAVE_MAGN_H_8; //0x94U
static uint8_t numberTrials = 3;
static uint8_t timeOutTrial = I2C_TIMEOUT;



