 /**
  *
  * \file main.c

  */

/* Includes ------------------------------------------------------------------*/

#include <vl53l1x/vl53l1x.h>
#include "stm32f4xx_hal.h"

#include "macro_types.h"
#include "main.h"
#include "stm32f4_uart.h"
#include "stm32f4_sys.h"
#include "stm32f4_gpio.h"
#include "stm32f4_timer.h"
#include "systick.h"
#include "bluetooth.h"
#include "save_old/tests_methods.h"
#include "datas_process.h"
#include "mpu6050.h"
#include "motors_control.h"
#include "drone_def.h"
#include "regulation/regulation.h"
#include "dialog.h"

int main(void){
	HAL_Init();
	SYS_init();	//initialisation du systeme (horloge...)
	GPIO_Configure();

	//* UART DU PRINTF ==> Activation SEULEMENT si on utilise pas le bluetooth
	//SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//* LEDs F4
	BSP_GPIO_PinCfg(LEDS_GPIO, LED_GREEN_PIN | LED_ORANGE_PIN | LED_RED_PIN | LED_BLUE_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FAST, 0);
	BSP_GPIO_PinCfg(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FAST, 0);

	Systick_init();

	drone_data_t drone;

	drone.pid_correction.Z_pid = 0.0f;
	drone.pid_correction.pitch_pid = 0.0f;
	drone.pid_correction.roll_pid = 0.0f;
	drone.pid_correction.yaw_pid = 0.0f;
	drone.motor_cmd.m11 = 0;
	drone.motor_cmd.m12 = 0;
	drone.motor_cmd.m13 = 0;
	drone.motor_cmd.m14 = 0;
	drone.motor_cmd.m21 = 0;
	drone.motor_cmd.m22 = 0;
	drone.motor_cmd.m23 = 0;
	drone.motor_cmd.m24 = 0;
	drone.target_values.pitch_target = 0.0f;
	drone.target_values.roll_target = 0.0f;
	drone.target_values.yaw_target = 0.0f;
	drone.target_values.z_target = 1000;
	drone.x_correction = 0;
	drone.z_correction = 0;
	drone.pitch_correction = 0;
	drone.yaw_regulation = 1;
	drone.block_config = 0;
	drone.preset_pid = 0; //par défaut
	drone.process_data = 0;


	//* UART DU BLUETOOTH
	BLUETOOTH_init(&drone);

	//* dialog
	DIALOG_init(&DIALOG_callback_send_byte);

	//TESTS MOTEUR
	MC_init_pwm_tim1_tim3(&drone);
	MC_esc_calibration();
	//test_moteur_PC6(60);
	//MC_test_motor_one_by_one();
	//MC_f1_m1_PE9(1100);
	//MC_test_progressive_pwm();
	//MC_test_all_motors();
	//MC_put_all_motors_off();

	while (1){
		main_bluetooth();
		HAL_Delay(100);
	}
}












