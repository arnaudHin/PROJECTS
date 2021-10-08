/**
 * @file : I2CCommunication.c
 * @brief :
 * @version
 * @date : May 10, 2021
 * @author: Arnaud
 */

#include <utils/GPIOS.h>
#include "utils/stm32mp1xx_hal_i2c.h"
#include <sensorsManager/sensors/Temperature.h>
#include <sensorsManager/sensors/Pressure.h>
#include <sensorsManager/sensors/Humidity.h>
#include <commun.h>
#include <sensorsManager/I2CCommunication.h>



//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//				Variables Privées				//
//////////////////////////////////////////////////////////////////////////////////
static I2C_HandleTypeDef hi2c5;



//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Privées			//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn DavidsonStatus_e I2CProtocol_Read(uint8_t, uint8_t, uint8_t*)
 * @brief
 * @param address
 * @param reg
 * @param received_data
 * @return
 */
static DavidsonStatus_e I2CProtocol_Read(uint8_t address, uint8_t reg, uint8_t * received_data);

/**
 * @fn DavidsonStatus_e I2CProtocol_Write(uint8_t, uint8_t, uint8_t*)
 * @brief
 * @param address
 * @param reg
 * @param data_wrtitten
 * @return
 */
static DavidsonStatus_e I2CProtocol_Write(uint8_t address, uint8_t reg, uint8_t * data_wrtitten);

/**
 * @fn DavidsonStatus_e I2CProtocol_ReadMulti(uint8_t, uint8_t, uint8_t*, uint16_t)
 * @brief
 * @param address
 * @param reg
 * @param tab_received_data
 * @param count
 * @return
 */
static DavidsonStatus_e I2CProtocol_ReadMulti(uint8_t address, uint8_t reg, uint8_t * tab_received_data, uint16_t count);



//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Publiques				//
//////////////////////////////////////////////////////////////////////////////////
extern DavidsonStatus_e I2CProtocol_InitI2C5(void){

	HAL_StatusTypeDef status;

	hi2c5.Instance = I2C5;
	hi2c5.Init.Timing = 0x10707DBC;
	hi2c5.Init.OwnAddress1 = 0;
	hi2c5.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c5.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c5.Init.OwnAddress2 = 0;
	hi2c5.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c5.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c5.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	status = HAL_I2C_Init(&hi2c5);
	if (status != HAL_OK){
		Error_Handler();
	}
	/* Configure Analogue filter */
	status = HAL_I2CEx_ConfigAnalogFilter(&hi2c5, I2C_ANALOGFILTER_ENABLE);
	if ( status != HAL_OK){
		Error_Handler();
	}
	/* Configure Digital filter */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c5, 0) != HAL_OK){
		Error_Handler();
	}

	HAL_I2C_MspInit(&hi2c5);

	 return (DavidsonStatus_e) status;
}


extern DavidsonStatus_e I2CProtocol_InitSensor(SensorId_e sensorId){

	HAL_StatusTypeDef status;

	uint8_t adressSlave = 0;
	uint8_t adressRegister = 0;
	uint8_t valueRegister = 0;
	uint8_t dataTemp = 0;

	switch (sensorId) {

		case TEMP:

			if( (&hi2c5 == NULL) || hi2c5.Instance != I2C5  ){
				return HAL_ERROR;
			}

			Temperature_t * temperatureTemp = (Temperature_t*) Temperature_Get();
			adressSlave = temperatureTemp->temperatureAdress;

			/* Verifier si sensor temperature connecte */
			status = HAL_I2C_IsDeviceReady(&hi2c5 , adressSlave, I2C_NB_TRIALS, I2C_TIMEOUT_TRIAL);
			if(status != HAL_OK){
				return status;
			}

			/* Verifier communication */
			adressRegister = temperatureTemp->temperatureRegIDManufactor;
			valueRegister = temperatureTemp->temperatureConfig.temperatureIDManufactorValue;

			status = I2CProtocol_Read(adressSlave, adressRegister, &dataTemp);
			if( status != HAL_OK || dataTemp != valueRegister){
				return HAL_ERROR;
			}
			dataTemp = 0;

			/* Configurer */
			adressRegister = temperatureTemp->temperatureRegConfig;
			valueRegister = temperatureTemp->temperatureConfig.temperatureConfigValue ;

			status = I2CProtocol_Write(adressSlave, adressRegister, &valueRegister);
			if(status != HAL_OK){
				return status;
			}
			/* Vérifier Configuration */
			status = I2CProtocol_Read(adressSlave, adressRegister, &dataTemp);
			if(dataTemp != valueRegister){
				return DAV_ERROR;
			}
			break;


		case PRES:
			if( (&hi2c5 == NULL) || hi2c5.Instance != I2C5  ){
				return HAL_ERROR;
			}

			Pressure_t * pressureTemp = (Pressure_t*) Pressure_Get();
			adressSlave = pressureTemp->pressureAdress;

			/* Verifier si sensor temperature connecte */
			status = HAL_I2C_IsDeviceReady(&hi2c5 , adressSlave, I2C_NB_TRIALS, I2C_TIMEOUT_TRIAL);
			if(status != HAL_OK){
				return status;
			}

			/* Verifier communication */
			adressRegister = pressureTemp->pressureRegWhoIAm;
			valueRegister = pressureTemp->pressureConfig.pressureWhoIAmValue;

			status = I2CProtocol_Read(adressSlave, adressRegister, &dataTemp);
			if( status != HAL_OK || dataTemp != valueRegister){
				return HAL_ERROR;
			}

			/* Configuration */
			adressRegister = pressureTemp->pressureRegCrtl1;
			valueRegister = pressureTemp->pressureConfig.pressureCrtl1Value;
			status = I2CProtocol_Write(adressSlave, adressRegister, &valueRegister);
			if(status != HAL_OK){
				return status;
			}

			status = I2CProtocol_Read(adressSlave, adressRegister, &dataTemp);
			if(status != HAL_OK){
				return status;
			}

			adressRegister = pressureTemp->pressureRegCrtl2;
			valueRegister = pressureTemp->pressureConfig.pressureCrtl2Value;
			status = I2CProtocol_Write(adressSlave, adressRegister, &valueRegister);
			if(status != HAL_OK){
				return status;
			}

			status = I2CProtocol_Read(adressSlave, adressRegister, &dataTemp);
			if(status != HAL_OK){
				return status;
			}

			break;


		case HUMI:
			if( (&hi2c5 == NULL) || hi2c5.Instance != I2C5  ){
				return HAL_ERROR;
			}

			Humidity_t * humidityTemp = (Humidity_t*) Humidity_Get();
			adressSlave = humidityTemp->humidityAdress;

			/* Verifier si sensor temperature connecte */
			status = HAL_I2C_IsDeviceReady(&hi2c5 , adressSlave, I2C_NB_TRIALS, I2C_TIMEOUT_TRIAL);
			if(status != HAL_OK){
				return status;
			}

			/* Verifier communication */
			adressRegister = humidityTemp->humidityRegWhoIAm;
			valueRegister = humidityTemp->humidityConfig.humidityWhoIAmValue;
			dataTemp = 0;

			status = I2CProtocol_Read(adressSlave, adressRegister, &dataTemp);
			if( status != HAL_OK || dataTemp != valueRegister){
				return HAL_ERROR;
			}
			dataTemp = 0;

			/* Configurer CTRL 1 */
			adressRegister = humidityTemp->humidityRegCrtl1;
			valueRegister = humidityTemp->humidityConfig.humidityCrtl1Value;

			status = I2CProtocol_Write(adressSlave, adressRegister, &valueRegister);
			if(status != HAL_OK){
				return status;
			}
			/* Vérifier Configuration CTRL1 */
			status = I2CProtocol_Read(adressSlave, adressRegister, &dataTemp);
			if(dataTemp != valueRegister){
				return DAV_ERROR;
			}

			/* Configurer CTRL 2 */
			adressRegister = humidityTemp->humidityRegCrtl2;
			valueRegister = humidityTemp->humidityConfig.humidityCrtl2Value;

			status = I2CProtocol_Write(adressSlave, adressRegister, &valueRegister);
			if(status != HAL_OK){
				return status;
			}
			/* Vérifier Configuration CTRL1 */
			status = I2CProtocol_Read(adressSlave, adressRegister, &dataTemp);
			if(dataTemp != valueRegister){
				return DAV_ERROR;
			}


		break;


		case MAGN:



		break;




		default:
			break;
	}

	return DAV_OK;
}



extern DavidsonStatus_e I2CProtocol_GetSensorMeasure(SensorId_e sensorId){

	HAL_StatusTypeDef status;

	uint8_t adressSlave = 0;
	uint8_t adressRegister = 0;
	uint8_t valueRegister = 0;
	uint8_t data = 0;

	switch (sensorId) {
		case TEMP:

			if(1){

			}

			Temperature_t * temperatureTemp = (Temperature_t*) Temperature_Get();
			uint8_t adressSlaveTempRead = temperatureTemp->temperatureAdress;


			uint8_t register_temp_H = temperatureTemp->temperatureRegValueHigh;
			uint8_t register_temp_L = temperatureTemp->temperatureRegValueLow;

			uint8_t dataTemp_H = 0;
			uint8_t dataTemp_L = 0;

			uint8_t dataTemp[2];

			status = I2CProtocol_Read(adressSlaveTempRead, register_temp_H, &dataTemp_H);
			status = I2CProtocol_Read(adressSlaveTempRead, register_temp_L, &dataTemp_L);

			dataTemp[0] = dataTemp_H;
			dataTemp[1] = dataTemp_L;

			Temperature_Convert(dataTemp, &(temperatureTemp->Temperature_value) );


			break;

		case PRES:
			if(1){

			}


			Pressure_t * pressureTemp = (Pressure_t*) Pressure_Get();
			uint8_t adressSlavePressRead = pressureTemp->pressureAdress;

			uint8_t register_press_H = pressureTemp->pressureRegValueHigh;
			uint8_t register_press_L = pressureTemp->pressureRegValueLow;
			uint8_t register_press_XL = pressureTemp->pressureRegValueXLow;

			uint8_t dataPress_H = 0;
			uint8_t dataPress_L = 0;
			uint8_t dataPress_XL = 0;

			uint8_t dataPress[3];

			status = I2CProtocol_Read(adressSlavePressRead , 0x27, &dataPress_H);

			status = I2CProtocol_Read(adressSlavePressRead, register_press_H, &dataPress_H);
			status = I2CProtocol_Read(adressSlavePressRead, register_press_L, &dataPress_L);
			status = I2CProtocol_Read(adressSlavePressRead, register_press_XL, &dataPress_XL);

			dataPress[0] = dataPress_H;
			dataPress[1] = dataPress_L;
			dataPress[2] = dataPress_XL;

			Pressure_Convert(dataPress, &(pressureTemp->pressureValue));

			break;


		case HUMI:

			if(1){

			}

			Humidity_t * humidityTemp = (Humidity_t*) Humidity_Get();
			adressSlave = humidityTemp->humidityAdress;
			uint8_t dataHumid[8];

			/* Récupérer coefficient rH_x2 */
			adressRegister = humidityTemp->humidityRegH0rHx2;
			status = I2CProtocol_Read(adressSlave, adressRegister, &data);
			dataHumid[0] = data;

			adressRegister = humidityTemp->humidityRegH1rHx2;
			status = I2CProtocol_Read(adressSlave, adressRegister, &data);
			dataHumid[1] = data;

			/* Récupérer valeurs de conversion H0 et H1 */
			adressRegister = humidityTemp->humidityRegH0T0OUTLow;
			status = I2CProtocol_Read(adressSlave, adressRegister, &data);
			dataHumid[2] = data;

			adressRegister = humidityTemp->humidityRegH0T0OUTHigh;
			status = I2CProtocol_Read(adressSlave, adressRegister, &data);
			dataHumid[3] = data;

			adressRegister = humidityTemp->humidityRegH1T0OUTLow;
			status = I2CProtocol_Read(adressSlave, adressRegister, &data);
			dataHumid[4] = data;

			adressRegister = humidityTemp->humidityRegH1T0OUTHigh;
			status = I2CProtocol_Read(adressSlave, adressRegister, &data);
			dataHumid[5] = data;

			/* Récupérer valeurs  */
			adressRegister = humidityTemp->humidityRegValueLow;
			status = I2CProtocol_Read(adressSlave, adressRegister, &data);
			dataHumid[6] = data;

			adressRegister = humidityTemp->humidityRegValueHigh;
			status = I2CProtocol_Read(adressSlave, adressRegister, &data);
			dataHumid[7] = data;

			Humidity_Convert(dataHumid, &(humidityTemp->humidityValue) );

			break;



		default:
			break;
	}

	return (DavidsonStatus_e) status;
}


//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Privées				//
//////////////////////////////////////////////////////////////////////////////////
static DavidsonStatus_e I2CProtocol_Read(uint8_t address, uint8_t reg, uint8_t * received_data)
{
	DavidsonStatus_e status;

	uint16_t memAddressSize = I2C_MEMADD_SIZE_8BIT;

	status = (DavidsonStatus_e) HAL_I2C_Mem_Read(&hi2c5, address, reg, memAddressSize, received_data, 1, I2C_TIMEOUT_TRIAL);

	return status;
}



static DavidsonStatus_e I2CProtocol_Write(uint8_t address, uint8_t reg, uint8_t * data_wrtitten){

	DavidsonStatus_e status;

	uint16_t memAddressSize = I2C_MEMADD_SIZE_8BIT;

	status = (DavidsonStatus_e) HAL_I2C_Mem_Write(&hi2c5, address, reg, memAddressSize, data_wrtitten, 1, I2C_TIMEOUT_TRIAL);

	return status;
}


static DavidsonStatus_e I2CProtocol_ReadMulti(uint8_t address, uint8_t reg, uint8_t * tab_received_data, uint16_t count){

	DavidsonStatus_e status;

	uint16_t memAddressSize = I2C_MEMADD_SIZE_8BIT;

	status = (DavidsonStatus_e) HAL_I2C_Mem_Write(&hi2c5, address, reg, memAddressSize, tab_received_data, count, I2C_TIMEOUT_TRIAL);

	return status;
}


void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c){
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  if(IS_ENGINEERING_BOOT_MODE())
  {
  /** Initialiser les périphériques d'horloge */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C35;
    PeriphClkInit.I2c35ClockSelection = RCC_I2C35CLKSOURCE_PCLK1;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK){
    	Error_Handler();
    }
  }

  BSP_GPIO_PinCfg(I2C5_PORT, I2C5_SDA_PIN, GPIO_MODE_AF_OD, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_AF4_I2C5);
  BSP_GPIO_PinCfg(I2C5_PORT, I2C5_SCL_PIN, GPIO_MODE_AF_OD, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_AF4_I2C5);

    /* I2C5 clock enable */
    __HAL_RCC_I2C5_CLK_ENABLE();
}




