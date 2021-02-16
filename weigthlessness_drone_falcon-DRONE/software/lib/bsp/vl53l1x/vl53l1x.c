/*
 * VL53_becon.h
 *
 *  Created on: 3 nov. 2019
 *      Author: Guillaume D.
 */

#include "stm32f4xx.h"
#include "stm32f4_gpio.h"
#include "stm32f4_i2c.h"
#include "vl53l1x/low_layer/core/VL53L1X_api.h"
#include "vl53l1x.h"
#include "macro_types.h"
#include "systick.h"



#define VL53L1_DISTANCEMODE_SHORT 1
#define VL53L1_DISTANCEMODE_LONG 2

#define VL53_RESET_STATE	0
#define VL53_ON_STATE		1

//ROI : Region Of Interest
#define VIEW_ANGLE_OF_ROI	402

typedef enum{
	INIT,
	SENSOR_INIT_FIRST_STEP,
	WAIT_BEFORE_TALKING_TO_SENSOR_AFTER_RESET,
	SET_ADDRESS,
	CONFIGURE,
	ASK_AND_GET_DATA,
	FAIL,
	PUIT
}state_vl53_e;



typedef struct{
	GPIO_TypeDef * GPIO_Port;
	uint16_t GPIO_Pin;
}VL53L1X_config;


/*
 * @brief structure d'un capteur VL53L1X
 */
typedef struct{
	bool_e enable;
	Uint16 data_ready;
	Uint16 distance;
	VL53L1X_RangeStatus rangeStatus;
	VL53L1_Dev_t  vl53l1_i2c;
	VL53L1_DEV    Dev;
	state_vl53_e state;
	bool_e asked;
}BEACON_data_sensor;


/*
 * @brief Tableau contenant toutes les info des capteur d'une carte sensor_expander
 */
static BEACON_data_sensor sensors[VL53_NB];
static volatile bool_e flag_send_can_msg = FALSE;

static const VL53L1X_config sensor_reset_pins[VL53_NB] = {
		(VL53L1X_config){VL_0},
		(VL53L1X_config){VL_1},
		(VL53L1X_config){VL_2},
		(VL53L1X_config){VL_3},
		(VL53L1X_config){VL_4},
};


bool_e VL53L1X_init(){
	for (uint16_t id = 0; id < VL53_NB; id++)
	{
		sensors[id].state = INIT;
		BSP_GPIO_PinCfg(sensor_reset_pins[id].GPIO_Port, sensor_reset_pins[id].GPIO_Pin,GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FAST, 0);
		HAL_GPIO_WritePin(sensor_reset_pins[id].GPIO_Port, sensor_reset_pins[id].GPIO_Pin, VL53_RESET_STATE);
	}
	I2C_Init(VL53L1X_I2C, 400000);

	return TRUE;
}


timeslot_e VL53L1X_process_it(void){
	static VL53L1X_ERROR erro = SOFT_RESET;
	static uint8_t timeslot = 0;
	static bool_e flag_one_sensor_is_on_default_address = FALSE;

	for (uint16_t id = 0;  id < VL53_NB; id++)
	{
		switch (sensors[id].state)
		{
			case INIT:
				if(timeslot == (timeslot_e)id)	//Si le time_slot correspond à l'id parcouru.
				{
					sensors[id].enable = FALSE;
					if(flag_one_sensor_is_on_default_address == FALSE)
					{

						//RESET
						HAL_GPIO_WritePin(sensor_reset_pins[id].GPIO_Port ,sensor_reset_pins[id].GPIO_Pin, VL53_RESET_STATE);

						//delay 100us
						Delay_us(100);

						//SET
						HAL_GPIO_WritePin(sensor_reset_pins[id].GPIO_Port ,sensor_reset_pins[id].GPIO_Pin, VL53_ON_STATE);

						flag_one_sensor_is_on_default_address = TRUE;

						// ajout de l'i2c vers le capteur
						sensors[id].vl53l1_i2c.I2cHandle = VL53L1X_I2C;
						sensors[id].vl53l1_i2c.I2cDevAddr = 0x52; //vl53l1x embedded address

						//sensors[id].time_slot.get = (timeslot_e)id + TIMESLOT_GET_BEGIN;
						sensors[id].distance = 0;
						sensors[id].data_ready = 0;

						sensors[id].state = SET_ADDRESS;
					}
				}
				break;


			case SET_ADDRESS:	// premier contact avec le capteur + changement de son adresse
				//2 timeslots après avoir lâché le reset, on peut causer au capteur
				//	(il emprunte exceptionennellement le timeslot de qn d'autre !)
				if(timeslot == ((timeslot_e)id + 2)%TIMESLOT_NB)
				{
					uint8_t new_address;
					new_address = (uint8_t)(sensors[id].vl53l1_i2c.I2cDevAddr + 2*id + 2);

					erro = VL53L1X_SetI2CAddress(sensors[id].vl53l1_i2c,new_address);
					//it_printf("[id=%d] SetI2CAddress : %d \n", id, erro);

					sensors[id].vl53l1_i2c.I2cDevAddr = new_address;

					uint8_t asked_id;
					erro |= VL53L1X_GetSensorId(sensors[id].vl53l1_i2c, &asked_id);
					//it_printf("[id=%d] GetSensorId : %d \n", id, erro);

					if (asked_id != 0xEA)
						erro |= 1;

					sensors[id].distance = 0;
					if(erro)
					{
						//échec, on reset le capteur, et on libère le flag.
						HAL_GPIO_WritePin(sensor_reset_pins[id].GPIO_Port ,sensor_reset_pins[id].GPIO_Pin, VL53_RESET_STATE);
						flag_one_sensor_is_on_default_address = FALSE;
						sensors[id].state = INIT;
						sensors[id].enable = FALSE;
					}
					else
					{
						//réussite du changement d'adresse, on libère le flag et on continue !
						sensors[id].state = SENSOR_INIT_FIRST_STEP;
						flag_one_sensor_is_on_default_address = FALSE;
					}

				}
				break;
			case SENSOR_INIT_FIRST_STEP:
				if(timeslot == (timeslot_e)id)
				{

					//erro = VL53L1X_SensorInit(sensors[id].vl53l1_i2c);// gestion error

					erro = VL53L1X_SensorInit_FIRST_STEP(sensors[id].vl53l1_i2c);
					/*while(VL53L1X_SensorInit_SECOND_STEP(sensors[id].vl53l1_i2c));*/
					sensors[id].state = CONFIGURE;
				}
				break;
			case CONFIGURE:
				if(timeslot == (timeslot_e)id)	//Si le time_slot correspond à l'id parcouru.
				{
					if(VL53L1X_SensorInit_SECOND_STEP(sensors[id].vl53l1_i2c) == 0)
					{
						//paramétrage du capteur
						erro=0;

						erro = VL53L1X_SetDistanceMode(sensors[id].vl53l1_i2c, VL53L1_DISTANCEMODE_SHORT);
						//it_printf("[id=%d] SetDistanceMode : %d \n", id, erro);

						erro |= VL53L1X_SetTimingBudgetInMs(sensors[id].vl53l1_i2c, 20 );		//On demande une mesure en 20ms..
						//it_printf("[id=%d] SetTimingBudgetInMs : %d \n", id, erro);

						erro |= VL53L1X_SetInterMeasurementInMs(sensors[id].vl53l1_i2c, 40 );	//Objectif : on l'aura arreté et relancé avant qu'il redémarre un nouveau ranging !
						//it_printf("[id=%d] SetInterMeasurementInMs : %d \n", id, erro);

						erro |= VL53L1X_StartRanging(sensors[id].vl53l1_i2c);

						if(!erro)
						{
							sensors[id].enable = TRUE;
							sensors[id].state = ASK_AND_GET_DATA;
						}
						else
						{
							HAL_GPIO_WritePin(sensor_reset_pins[id].GPIO_Port ,sensor_reset_pins[id].GPIO_Pin, VL53_RESET_STATE);
							sensors[id].enable = FALSE;
							sensors[id].state = INIT;
						}
					}
				}
				break;
			case ASK_AND_GET_DATA:
				if(timeslot == (timeslot_e)id)
				{
					erro = VL53L1X_GetDistance(sensors[id].vl53l1_i2c, &sensors[id].distance);
					erro |= VL53L1X_GetRangeStatus(sensors[id].vl53l1_i2c, (uint8_t*)&sensors[id].rangeStatus);
					erro |= VL53L1X_StopRanging(sensors[id].vl53l1_i2c);						//on force un arrêt
					erro |= VL53L1X_StartRanging(sensors[id].vl53l1_i2c);						//puis un redémarrage pour être sûr de l'instant où on redémarre.
					//erro |= VL53L1X_ClearInterrupt(sensors[id].vl53l1_i2c);
					if(erro)
						sensors[id].state = FAIL;
				}
				break;

			case FAIL:
				sensors[id].state = INIT;
				HAL_GPIO_WritePin(sensor_reset_pins[id].GPIO_Port ,sensor_reset_pins[id].GPIO_Pin, VL53_RESET_STATE);
				break;

			default :
				break;
		}
	}
	/*for(Uint8 id = 0; id < VL53_NB; id++ ){
		it_printf("Id = %d %d\n", id, sensors[id].state);
	}*/
	if(timeslot == TIMESLOT_ASK_END)//TIMESLOT_GET_END)
	{
		flag_send_can_msg = TRUE;
	}
	timeslot_e ret;
	ret = timeslot;
	timeslot = (timeslot + 1) % TIMESLOT_NB;
	return ret;
}

void VL53L1X_process_main(void){
	char buf[100];
	uint8_t index = 0;
	if(flag_send_can_msg)
	{
		flag_send_can_msg = FALSE;

		for(uint8_t i = 0; i<VL53_NB; i++)
		{
			if(sensors[i].rangeStatus)
				index += sprintf(buf+index,"E%x ",sensors[i].rangeStatus);
			else
				index += sprintf(buf+index,"%d ",sensors[i].distance/10);
			for(;index<4*(i+1);)
				index += sprintf(buf+index," ");
		}
		debug_printf("%s\n",buf);
	}
}


uint16_t VL53L1X_get_distance(uint8_t id){
	assert(id<VL53_NB);
	return sensors[id].distance;
}



