/*
 * xnucelo_sensors.h
 *
 *  Created on: Apr 19, 2021
 *      Author: Arnaud
 */


#ifndef INC_XNUCELO_SENSORS_H_
#define INC_XNUCELO_SENSORS_H_

/*
STTS751------> 	TEMP
LIS2DW12------> ACC
LSM6DSO------> 	ACC + GYRO
LPS22HH------> 	PRESS
LIS2MDL------> 	MAGN
HTS221 ------> 	HUMID
*/



/* TEMPERATURE SENSOR */
//Adresse
#define ADRESS_SLAVE_TEMP_H_8	 			0x94
#define ADRESS_SLAVE_TEMP_L_8				0x94
//Registres
#define TEMP_REG_ID_MANUFACTOR_8			0xFE
#define TEMP_REG_ID_MANUFACTOR_VALUE_8		0x53
#define TEMP_REG_HIGH_BYTE_8				0x00
#define TEMP_REG_LOW_BYTE_8					0x02
#define TEMP_REG_CONFIG_8					0x03
#define TEMP_REG_CONFIG_VALUE_8				0x00
#define TEMP_REG_STATUS_8					0x01 //si b7 == 1 -> conversion en cours

/* ACC SENSOR */
//Adresse
#define ADRESS_SLAVE_ACC_H_8	 			0x32
#define ADRESS_SLAVE_ACC_L_8				0x30
//Registres
#define ACC_REG_WHO_AM_I_8					0x0F
#define ACC_REG_WHO_AM_I_VALUE_8			0x44
#define ACC_REG_OUT_X_L_8					0x28
#define ACC_REG_OUT_X_H_8					0x29
#define ACC_REG_OUT_Y_L_8					0x2A
#define ACC_REG_OUT_Y_H_8					0x2B
#define ACC_REG_OUT_Z_L_8					0x2C
#define ACC_REG_OUT_Z_H_8					0x2D

/* ACC-GYRO SENSOR */
//Adresse
#define ADRESS_SLAVE_GYRO_H_8	 			0xD6
#define ADRESS_SLAVE_GYRO_L_8				0xD4
//Registres
#define GYRO_REG_WHO_AM_I_8					0x0F
#define GYRO_REG_WHO_AM_I_VALUE_8			0x6C
#define GYRO_REG_OUT_XG_L_8					0x22
#define GYRO_REG_OUT_XG_H_8					0x23
#define GYRO_REG_OUT_YG_L_8					0x24
#define GYRO_REG_OUT_YG_H_8					0x25
#define GYRO_REG_OUT_ZG_L_8					0x26
#define GYRO_REG_OUT_ZG_H_8					0x27
#define GYRO_REG_OUT_XA_L_8					0x28
#define GYRO_REG_OUT_XA_H_8					0x29
#define GYRO_REG_OUT_YA_L_8					0x2A
#define GYRO_REG_OUT_YA_H_8					0x2B
#define GYRO_REG_OUT_ZA_L_8					0x2C
#define GYRO_REG_OUT_ZA_H_8					0x2D

/* PRESSURE SENSOR */
//Adresse
#define ADRESS_SLAVE_PRESS_H_8	 			0xBA
#define ADRESS_SLAVE_PRESS_L_8	 			0xB8
//Registres
#define PRESS_REG_WHO_AM_I_8				0x0F
#define PRESS_REG_WHO_AM_I_VALUE_8			0xB3




#define ADRESS_SLAVE_MAGN_H_8	 			0x3C
#define ADRESS_SLAVE_HUMID_H_8	 			0xBE

#define ADRESS_SLAVE_MAGN_L_8				0x3C
#define ADRESS_SLAVE_HUMID_L_8	 			0xBE


typedef struct{
	int16_t Accelerometer_X; /* Accelerometre X */
	int16_t Accelerometer_Y; /* Accelerometer Y */
	int16_t Accelerometer_Z; /* Accelerometer Z */
	int16_t Gyroscope_X;     /* Gyroscope X */
	int16_t Gyroscope_Y;     /* Gyroscope Y */
	int16_t Gyroscope_Z;     /* Gyroscope Z */
	float Temperature;       /* Temperature en degres */
	int16_t Pressure;		 /* Pressure */
}X_NUCLEO_SENSORS_t;


HAL_StatusTypeDef I2C_Read_nucleo(uint8_t address, uint8_t reg, uint8_t * received_data);
HAL_StatusTypeDef I2C_Write_nucleo(uint8_t address, uint8_t reg, uint8_t * data_wrtitten);
HAL_StatusTypeDef I2C_ReadMulti_nucleo(uint8_t address, uint8_t reg, uint8_t * tab_received_data, uint16_t count);

HAL_StatusTypeDef Init_Temperature();
HAL_StatusTypeDef Read_Temperature(X_NUCLEO_SENSORS_t * nucleoStruct);

HAL_StatusTypeDef Init_Accelerometer();
HAL_StatusTypeDef Read_Accelerometer(X_NUCLEO_SENSORS_t * nucleoStruct);

HAL_StatusTypeDef Init_Gyroscope();
HAL_StatusTypeDef Read_Gyroscope(X_NUCLEO_SENSORS_t * nucleoStruct);


HAL_StatusTypeDef Init_all_sensors();










#endif /* INC_XNUCELO_SENSORS_H_ */
