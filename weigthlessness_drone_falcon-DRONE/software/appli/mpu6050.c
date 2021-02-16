
#include "mpu6050.h"
#include "datas_process.h" // A MODIF ULTERIEUREMENT
#include <stdbool.h>
#include "main.h"
#include "stm32f4xx_hal.h"


//* boolean de l'init du mpu
bool_e mpu_init_OK;

static drone_data_t* drone_data;
static Gyro_datas_t angular_speed;
static MPU6050_t MPU6050_Data;


static float AVERAGE_X;
static float AVERAGE_Y;
static float AVERAGE_Z;

bool_e MPU_init(drone_data_t* drone){
	drone_data = drone;
	//on init le mpu, structure et boolean de .h
	if(MPU6050_Init(&MPU6050_Data, MPU6050_VCC_GPIO, MPU6050_VCC_PIN, MPU6050_Device_0, MPU6050_Accelerometer_8G, MPU6050_Gyroscope_2000s) == MPU6050_Result_Ok)
		mpu_init_OK = TRUE;
	AVERAGE_X = 34;
	AVERAGE_Y = 7;
	AVERAGE_Z = 16;
	return mpu_init_OK;
}

void MPU_angle_computer(void)
{
	//Le MPU doit �tre pr�alablement initialis�
	MPU6050_ReadGyroscope(&MPU6050_Data);
	//printf("Brut value (int) X : %d\n",MPU6050_Data.Gyroscope_X);
	angular_speed.Gyro_X += ((float)(MPU6050_Data.Gyroscope_X+AVERAGE_X)*INT_TIME);
	angular_speed.Gyro_Y += ((float)(MPU6050_Data.Gyroscope_Y+AVERAGE_Y)*INT_TIME);
	angular_speed.Gyro_Z += ((float)(MPU6050_Data.Gyroscope_Z+AVERAGE_Z )*INT_TIME);
	//printf("int�gration (float) X : %d\n",(int)angular_speed.Gyro_X);
	drone_data->datas_sensors_pooling.roll_angle = (float)(angular_speed.Gyro_X/MPU_RANGE_X*360);
	drone_data->datas_sensors_pooling.pitch_angle = (float)(angular_speed.Gyro_Y/MPU_RANGE_Y*360);
	drone_data->datas_sensors_pooling.yaw_angle = -(float)(angular_speed.Gyro_Z/MPU_RANGE_Z*360);
	//printf("Roll angle : %d\n",(int)drone_data->datas_sensors_pooling.roll_angle);
}
