/*
 * tests_methods.c

 *
 *  Created on: 23 juin 2020
 *      Author: Arnaud
 */


#include "tests_methods.h"
#include "motors_control.h"
#include "mpu6050.h"


///   BLUETOOTH   ///
void test_ble(){

    	uint8_t a = UART_get_next_byte(UART6_ID);
		if(a == 'a'){
			HAL_GPIO_WritePin(LEDS_GPIO, LED_RED_PIN, SET);
		}

		//BLUETOOTH
		if(compt < 2000 && compt >= 0){
			HAL_GPIO_WritePin(LEDS_GPIO, LED_RED_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, RESET);
			BLUETOOTH_envoi_caractere('c');
		}
		else if(compt < 4000 && compt > 2000){
			HAL_GPIO_WritePin(LEDS_GPIO, LED_RED_PIN, RESET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, SET);
			envoiCaractere('a');
		}
		else if(compt < 6000 && compt > 4000){
			HAL_GPIO_WritePin(LEDS_GPIO, LED_RED_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, RESET);
			//envoiTrame("martin");
		}
		else if(compt > 6000 && compt < 8000){
			HAL_GPIO_WritePin(LEDS_GPIO, LED_BLUE_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_RED_PIN, SET);
			compt = 0;
		}
}


///   MOTEURS PWM   ///
void puiss_mot_test_PC6(){
		if(compt < 3000 && compt >= 0){
			test_moteur_PC6(55);
			HAL_GPIO_WritePin(LEDS_GPIO, LED_RED_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, RESET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_GREEN_PIN, RESET);

		}
		else if(compt < 6000 && compt > 3000){
			test_moteur_PC6(57);
			HAL_GPIO_WritePin(LEDS_GPIO, LED_BLUE_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_RED_PIN, RESET);
		}
		else if(compt < 9000 && compt > 6000){
			test_moteur_PC6(59);
			HAL_GPIO_WritePin(LEDS_GPIO, LED_RED_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, RESET);
		}
		else if(compt < 12000 && compt > 9000){
			test_moteur_PC6(61);
			HAL_GPIO_WritePin(LEDS_GPIO, LED_BLUE_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_RED_PIN, RESET);
		}
		else if(compt < 15000 && compt > 12000){
			test_moteur_PC6(63);
			HAL_GPIO_WritePin(LEDS_GPIO, LED_RED_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, RESET);
		}
		else if(compt < 18000 && compt > 15000){
			test_moteur_PC6(65);
			HAL_GPIO_WritePin(LEDS_GPIO, LED_BLUE_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_RED_PIN, RESET);
		}
		else if(compt > 18000 && compt < 20000){
			test_moteur_PC6(0);

			HAL_GPIO_WritePin(LEDS_GPIO, LED_BLUE_PIN, RESET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_RED_PIN, RESET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_GREEN_PIN, SET);
		}
}


void test_tofs(){

		uint16_t dist0 ;
		uint16_t dist1 ;
		uint16_t dist2 ;
		uint16_t dist3 ;
		uint16_t dist4 ;

		dist0 = VL53L1X_get_distance(0);
		dist1 = VL53L1X_get_distance(1);
		dist2 = VL53L1X_get_distance(2);
		dist3 = VL53L1X_get_distance(3);
		dist4 = VL53L1X_get_distance(4);

		if( (dist0<100 && dist0 > 0) || (dist1<100 && dist1 > 0) || (dist2<100 && dist2 > 0) ||( dist3<100 && dist3 > 0)|| ( dist4<100 && dist4 > 0)){
			HAL_GPIO_WritePin(LEDS_GPIO,LED_RED_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, RESET);
		}
		else{
			HAL_GPIO_WritePin(LEDS_GPIO,LED_RED_PIN, RESET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, SET);
		}

}

void test_tof_1(){

		uint16_t dist0 ;

		dist0 = VL53L1X_get_distance(0);

		if(dist0<100 ){
			HAL_GPIO_WritePin(LEDS_GPIO,LED_RED_PIN, SET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, RESET);

		}
		else{
			HAL_GPIO_WritePin(LEDS_GPIO,LED_RED_PIN, RESET);
			HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, SET);
		}

}




void TEST_pwms(){
/*
	PWM_TIMER_set_duty(TimHandle_1, TIM_CHANNEL_1, 25);
	PWM_TIMER_set_duty(TimHandle_1, TIM_CHANNEL_2, 50);
	PWM_TIMER_set_duty(TimHandle_1, TIM_CHANNEL_3, 75);
	PWM_TIMER_set_duty(TimHandle_1, TIM_CHANNEL_4, 100);

	PWM_TIMER_set_duty(TimHandle_3, TIM_CHANNEL_1, 25);
	PWM_TIMER_set_duty(TimHandle_3, TIM_CHANNEL_2, 50);
	PWM_TIMER_set_duty(TimHandle_3, TIM_CHANNEL_3, 75);
	PWM_TIMER_set_duty(TimHandle_3, TIM_CHANNEL_4, 100);
*/

	//PWM_TIMER_set_duty(TimHandle_3, TIM_CHANNEL_1, 75);

}







void test_moteur_PC6_2(){

	if(compt < 100 && compt >= 0){
		test_moteur_PC6(40);
		HAL_GPIO_WritePin(LEDS_GPIO, LED_RED_PIN, SET);
		HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, RESET);
		HAL_GPIO_WritePin(LEDS_GPIO,LED_GREEN_PIN, RESET);

	}
	else if(compt < 200 && compt > 100){
		test_moteur_PC6(50);
		HAL_GPIO_WritePin(LEDS_GPIO, LED_BLUE_PIN, SET);
		HAL_GPIO_WritePin(LEDS_GPIO,LED_RED_PIN, RESET);
	}
	else if(compt < 5000 && compt > 200){
		test_moteur_PC6(59);
		HAL_GPIO_WritePin(LEDS_GPIO, LED_RED_PIN, SET);
		HAL_GPIO_WritePin(LEDS_GPIO,LED_BLUE_PIN, RESET);
	}
}










