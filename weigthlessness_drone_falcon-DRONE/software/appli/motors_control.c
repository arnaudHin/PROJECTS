#include "motors_control.h"
#include "config.h"

static TIM_HandleTypeDef TimHandle_1;	//Structure contenant les infos concernant l'�tat du timer 1
static TIM_HandleTypeDef TimHandle_3;	//Structure contenant les infos concernant l'�tat du timer 3

static drone_data_t * drone_data;

void MC_init_pwm_tim1_tim3(drone_data_t * drone_data_){

	drone_data = drone_data_;
	TimHandle_1.Instance = TIM1;
	TimHandle_3.Instance = TIM3;
	TIM_OC_InitTypeDef TIM_OCInitStruct;

	// mode AF (Alternate Function)
	BSP_GPIO_PinCfg(PWM_MOT_11,GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FAST, GPIO_AF2_TIM3);
	BSP_GPIO_PinCfg(PWM_MOT_12,GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FAST, GPIO_AF2_TIM3);
	BSP_GPIO_PinCfg(PWM_MOT_13,GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FAST, GPIO_AF2_TIM3);
	BSP_GPIO_PinCfg(PWM_MOT_14,GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FAST, GPIO_AF2_TIM3);

	BSP_GPIO_PinCfg(PWM_MOT_21, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FAST, GPIO_AF1_TIM1);
	BSP_GPIO_PinCfg(PWM_MOT_22, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FAST, GPIO_AF1_TIM1);
	BSP_GPIO_PinCfg(PWM_MOT_23, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FAST, GPIO_AF1_TIM1);
	BSP_GPIO_PinCfg(PWM_MOT_24, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FAST, GPIO_AF1_TIM1);

	HAL_GPIO_WritePin(PWM_MOT_11, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWM_MOT_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWM_MOT_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWM_MOT_14, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(PWM_MOT_21, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWM_MOT_22, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWM_MOT_23, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWM_MOT_24, GPIO_PIN_RESET);

	//autorisations des clocks TIM 1 et 3
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_TIM1_CLK_ENABLE();

	TimHandle_1.Init.Period = PWM_PERIOD_TIM - 1; //0 � periode
	TimHandle_1.Init.Prescaler = PWM_PRESC_TIM_1 - 1;
	TimHandle_1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TimHandle_1.Init.CounterMode = TIM_COUNTERMODE_UP;

	TimHandle_3.Init.Period = PWM_PERIOD_TIM - 1; //0 � periode
	TimHandle_3.Init.Prescaler = PWM_PRESC_TIM_3 - 1;
	TimHandle_3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TimHandle_3.Init.CounterMode = TIM_COUNTERMODE_UP;

	//init des timer
	HAL_TIM_Base_Init(&TimHandle_1);
	HAL_TIM_Base_Init(&TimHandle_3);

	TIM_OCInitStruct.OCMode = TIM_OCMODE_PWM1;
	TIM_OCInitStruct.Pulse = 0;
	TIM_OCInitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OCInitStruct.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	TIM_OCInitStruct.OCFastMode = TIM_OCFAST_DISABLE;

	//Channels 1,2,3,4 des timers 1 et 3
	if(HAL_TIM_OC_Init(&TimHandle_1) != HAL_OK){

	}
	HAL_TIM_OC_ConfigChannel(&TimHandle_1, &TIM_OCInitStruct, TIM_CHANNEL_1 );
	HAL_TIM_OC_ConfigChannel(&TimHandle_1, &TIM_OCInitStruct, TIM_CHANNEL_2 );
	HAL_TIM_OC_ConfigChannel(&TimHandle_1, &TIM_OCInitStruct, TIM_CHANNEL_3 );
	HAL_TIM_OC_ConfigChannel(&TimHandle_1, &TIM_OCInitStruct, TIM_CHANNEL_4 );

	__HAL_TIM_ENABLE(&TimHandle_1);
	HAL_TIM_PWM_Start(&TimHandle_1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TimHandle_1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&TimHandle_1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&TimHandle_1, TIM_CHANNEL_4);


	//ou TIM_CHANNEL_ALL...=> tests

	if(HAL_TIM_OC_Init(&TimHandle_3) != HAL_OK){

	}
	HAL_TIM_OC_ConfigChannel(&TimHandle_3, &TIM_OCInitStruct, TIM_CHANNEL_1 );
	HAL_TIM_OC_ConfigChannel(&TimHandle_3, &TIM_OCInitStruct, TIM_CHANNEL_2 );
	HAL_TIM_OC_ConfigChannel(&TimHandle_3, &TIM_OCInitStruct, TIM_CHANNEL_3 );
	HAL_TIM_OC_ConfigChannel(&TimHandle_3, &TIM_OCInitStruct, TIM_CHANNEL_4 );

	__HAL_TIM_ENABLE(&TimHandle_3);
	HAL_TIM_PWM_Start(&TimHandle_3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TimHandle_3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&TimHandle_3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&TimHandle_3, TIM_CHANNEL_4);


	//mise � 0 de tous les timers
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_1, 0);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_2, 0);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_3, 0);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_4, 0);

	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_1, 0);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_2, 0);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_3, 0);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_4, 0);

	//mettre duty � x*PWM_PERIOD_TIM avec x entre 0 et 1 !

}

void MC_pwm_timer_set_duty(TIM_HandleTypeDef tim_handle, int channel, uint16_t duty){
	duty = MIN(PWM_PERIOD_TIM, duty); //duty ne peut etre plus grand que la periode
	__HAL_TIM_SET_COMPARE(&tim_handle, channel, (uint32_t) duty);
}

//CALIBRATION DES ESC
void MC_esc_calibration(void)
{
	//MC_init_pwm_tim1_tim3(); (Penser à appeler cette fonction au préalabre)
	//3 bips = Alim ok
	HAL_Delay(100);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_1, PWM_MAX_MOTOR_ON);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_2, PWM_MAX_MOTOR_ON);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_3, PWM_MAX_MOTOR_ON);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_4, PWM_MAX_MOTOR_ON);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_1, PWM_MAX_MOTOR_ON);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_2, PWM_MAX_MOTOR_ON);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_3, PWM_MAX_MOTOR_ON);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_4, PWM_MAX_MOTOR_ON);


	//1 bip = PWM MAX ok
	HAL_Delay(100);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_1, PWM_MIN_MOTOR_OFF);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_2, PWM_MIN_MOTOR_OFF);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_3, PWM_MIN_MOTOR_OFF);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_4, PWM_MIN_MOTOR_OFF);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_1, PWM_MIN_MOTOR_OFF);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_2, PWM_MIN_MOTOR_OFF);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_3, PWM_MIN_MOTOR_OFF);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_4, PWM_MIN_MOTOR_OFF);
	//1 bip = PWM MIN ok
	HAL_Delay(3000);
	//Il faut ensuite rester entre le PWM Min et Max
}

//FONCTIONS DE CONTROLE MOTEUR


void MC_f1_m1_PE9(uint16_t TIME){ // moteur 1_1
	TIME = MIN(TIME, PWM_LIMIT);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_1, TIME);
}

void MC_f1_m2_PE11(uint16_t TIME){
	TIME = MIN(TIME, PWM_LIMIT);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_2, TIME);
}

void MC_f1_m3_PE13(uint16_t TIME){
	TIME = MIN(TIME, PWM_LIMIT);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_3, TIME);
}

void MC_f1_m4_PE14(uint16_t TIME){
	TIME = MIN(TIME, PWM_LIMIT);
	MC_pwm_timer_set_duty(TimHandle_1, TIM_CHANNEL_4, TIME);
}

void MC_f2_m1_PC6(uint16_t TIME){
	TIME = MIN(TIME, PWM_LIMIT);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_1, TIME);
}

void MC_f2_m2_PC7(uint16_t TIME){
	TIME = MIN(TIME, PWM_LIMIT);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_2, TIME);
}

void MC_f2_m3_PC8(uint16_t TIME){
	TIME = MIN(TIME, PWM_LIMIT);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_3, TIME);
}

void MC_f2_m4_PC9(uint16_t TIME){
	TIME = MIN(TIME, PWM_LIMIT);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_4, TIME);
}

void MC_PID_correction(void){
	//TODO revoir les signes en fonction du positionnement moteur
	//TODO ajouter les pid tofs.
	drone_data->motor_cmd.m11 = -drone_data->pid_correction.Z_pid + drone_data->pid_correction.yaw_pid + drone_data->pid_correction.roll_pid - drone_data->pid_correction.pitch_pid;
	drone_data->motor_cmd.m12 = -drone_data->pid_correction.Z_pid - drone_data->pid_correction.yaw_pid - drone_data->pid_correction.roll_pid - drone_data->pid_correction.pitch_pid;
	drone_data->motor_cmd.m13 = -drone_data->pid_correction.Z_pid - drone_data->pid_correction.yaw_pid + drone_data->pid_correction.roll_pid + drone_data->pid_correction.pitch_pid;
	drone_data->motor_cmd.m14 = -drone_data->pid_correction.Z_pid + drone_data->pid_correction.yaw_pid - drone_data->pid_correction.roll_pid + drone_data->pid_correction.pitch_pid;

	drone_data->motor_cmd.m21 = +drone_data->pid_correction.Z_pid + drone_data->pid_correction.yaw_pid + drone_data->pid_correction.roll_pid + drone_data->pid_correction.pitch_pid;
	drone_data->motor_cmd.m22 = +drone_data->pid_correction.Z_pid - drone_data->pid_correction.yaw_pid - drone_data->pid_correction.roll_pid + drone_data->pid_correction.pitch_pid;
	drone_data->motor_cmd.m23 = +drone_data->pid_correction.Z_pid - drone_data->pid_correction.yaw_pid + drone_data->pid_correction.roll_pid - drone_data->pid_correction.pitch_pid;
	drone_data->motor_cmd.m24 = +drone_data->pid_correction.Z_pid + drone_data->pid_correction.yaw_pid - drone_data->pid_correction.roll_pid - drone_data->pid_correction.pitch_pid;

}

void MC_update_motors(void){
	//TODO a modifier en fonction de MC_PID_correction
	MC_f1_m1_PE9(drone_data->motor_cmd.m11 + PWM_MIN_MOTOR_OFF);
	MC_f1_m2_PE11(drone_data->motor_cmd.m12 + PWM_MIN_MOTOR_OFF);
	MC_f1_m3_PE13(drone_data->motor_cmd.m13 + PWM_MIN_MOTOR_OFF);
	MC_f1_m4_PE14(drone_data->motor_cmd.m14 + PWM_MIN_MOTOR_OFF);

	MC_f2_m1_PC6(drone_data->motor_cmd.m21 + PWM_MIN_MOTOR_OFF);
	MC_f2_m2_PC7(drone_data->motor_cmd.m22 + PWM_MIN_MOTOR_OFF);
	MC_f2_m3_PC8(drone_data->motor_cmd.m23 + PWM_MIN_MOTOR_OFF);
	MC_f2_m4_PC9(drone_data->motor_cmd.m24 + PWM_MIN_MOTOR_OFF);
}

void MC_put_all_motors_off(void){
	MC_f1_m1_PE9(PWM_MIN_MOTOR_OFF);
	MC_f1_m2_PE11(PWM_MIN_MOTOR_OFF);
	MC_f1_m3_PE13(PWM_MIN_MOTOR_OFF);
	MC_f1_m4_PE14(PWM_MIN_MOTOR_OFF);
	MC_f2_m1_PC6(PWM_MIN_MOTOR_OFF);
	MC_f2_m2_PC7(PWM_MIN_MOTOR_OFF);
	MC_f2_m3_PC8(PWM_MIN_MOTOR_OFF);
	MC_f2_m4_PC9(PWM_MIN_MOTOR_OFF);
}

void MC_test_all_motors(void)
{
	uint16_t val = 1200;
	//MC_init_pwm_tim1_tim3(); (Penser à appeler cette fonction au préalabre)
	MC_f1_m1_PE9(val);
	MC_f1_m2_PE11(val);
	MC_f1_m3_PE13(val);
	MC_f1_m4_PE14(val);
	HAL_Delay(3000);
	MC_put_all_motors_off();
	MC_f2_m1_PC6(val);
	MC_f2_m2_PC7(val);
	MC_f2_m3_PC8(val);
	MC_f2_m4_PC9(val);
	HAL_Delay(3000);
	MC_put_all_motors_off();
}

void MC_test_motor_one_by_one(void)
{
	uint16_t val = 1200;

	//Moteur 1
	MC_f1_m1_PE9(val);
	HAL_Delay(1500);
	MC_f1_m1_PE9(PWM_MIN_MOTOR_OFF);
	//Moteur 2
	MC_f1_m2_PE11(val);
	HAL_Delay(1500);
	MC_f1_m2_PE11(PWM_MIN_MOTOR_OFF);
	//Moteur 3
	MC_f1_m3_PE13(val);
	HAL_Delay(1500);
	MC_f1_m3_PE13(PWM_MIN_MOTOR_OFF);
	//Moteur 4
	MC_f1_m4_PE14(val);
	HAL_Delay(1500);
	MC_f1_m4_PE14(PWM_MIN_MOTOR_OFF);


	//Moteur 1
	MC_f2_m1_PC6(val);
	HAL_Delay(1500);
	MC_f2_m1_PC6(PWM_MIN_MOTOR_OFF);
	//Moteur 2
	MC_f2_m2_PC7(val);
	HAL_Delay(1500);
	MC_f2_m2_PC7(PWM_MIN_MOTOR_OFF);
	//Moteur 3
	MC_f2_m3_PC8(val);
	HAL_Delay(1500);
	MC_f2_m3_PC8(PWM_MIN_MOTOR_OFF);
	//Moteur 4
	MC_f2_m4_PC9(val);
	HAL_Delay(1500);
	MC_f2_m4_PC9(PWM_MIN_MOTOR_OFF);
}



void MC_test_progressive_pwm(void)
{
	for(int i=50; i<100;i++)
	{
		MC_f2_m1_PC6(i);
		HAL_Delay(100);
	}
	MC_f2_m1_PC6(PWM_MIN_MOTOR_OFF);
	HAL_Delay(1000);
	for(int j=50; j<100;j++)
	{
		MC_f2_m2_PC7(j);
		HAL_Delay(100);
	}
	MC_f2_m2_PC7(PWM_MIN_MOTOR_OFF);
	HAL_Delay(1000);
	for(int k=50; k<100;k++)
	{
		MC_f2_m3_PC8(k);
		HAL_Delay(100);
	}
	MC_f2_m3_PC8(PWM_MIN_MOTOR_OFF);
	HAL_Delay(1000);
	for(int x=50; x<100;x++)
	{
		MC_f2_m4_PC9(x);
		HAL_Delay(100);
	}
	MC_f2_m4_PC9(PWM_MIN_MOTOR_OFF);
}

void test_moteur_PC6(uint16_t TIME){
	TIME = MIN(TIME, PWM_LIMIT);
	MC_pwm_timer_set_duty(TimHandle_3, TIM_CHANNEL_1, TIME);
}

void MC_test_props(void)
{
	uint16_t val = 1200;
	MC_f1_m1_PE9(val);
	MC_f1_m2_PE11(val);
	HAL_Delay(3000);
	MC_put_all_motors_off();
	MC_f1_m3_PE13(val);
	MC_f1_m4_PE14(val);
	HAL_Delay(3000);
	MC_put_all_motors_off();
	MC_f2_m1_PC6(val);
	MC_f2_m2_PC7(val);
	HAL_Delay(3000);
	MC_put_all_motors_off();
	MC_f2_m3_PC8(val);
	MC_f2_m4_PC9(val);
	HAL_Delay(3000);
	MC_put_all_motors_off();
}
