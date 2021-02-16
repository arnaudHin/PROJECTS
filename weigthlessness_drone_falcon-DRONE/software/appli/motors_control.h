#ifndef MOTORS_CONTROL_H_
#define MOTORS_CONTROL_H_

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_hal.h"
#include "macro_types.h"
#include "stm32f4_uart.h"
#include "stm32f4_sys.h"
#include "stm32f4_spi.h"
#include "stm32f4_gpio.h"
#include "stm32f4_timer.h"
#include "drone_def.h"


/***********************************************************PORTS INIT***********************************************************/
#define PWM_MOT_11 GPIOC, GPIO_PIN_6
#define PWM_MOT_12 GPIOC, GPIO_PIN_7
#define PWM_MOT_13 GPIOC, GPIO_PIN_8
#define PWM_MOT_14 GPIOC, GPIO_PIN_9

#define PWM_MOT_21 GPIOE, GPIO_PIN_9
#define PWM_MOT_22 GPIOE, GPIO_PIN_11
#define PWM_MOT_23 GPIOE, GPIO_PIN_13
#define PWM_MOT_24 GPIOE, GPIO_PIN_14

/***********************************************************PWM***************************************************************/
//MACROS DE Mr POIRAUD
#define TIM1_8_9_10_11_CLK    			168000000	//Fr�quence des �v�nements d'horloge pour les timers 1, 8, 9, 10, 11
#define TIM2_3_4_5_6_7_12_13_14_CLK    	84000000	//Fr�quence des �v�nements d'horloge pour les timers 2, 3, 4, 5, 6, 7, 12, 13 et 14

//L'horloge du timer 3 est a 84MHz
//Si l'on veut une PWM a 20kHz (inaudible) et 100 pas de rapports cycliques possibles, il faut prediviser par 42 :
//168MHz/84 = 2MHz -> 500ns par pas... * 100 pas = 20kHz de frequence PWM
#define PWM_FREQ_TIM	10000 	//Fr�quence du signal PWM, en Hz
#define	PWM_PERIOD_TIM	2000	//Nombre jusqu'auquel le timer va compter durant une p�riode PWM

#define	PWM_PRESC_TIM_3	((TIM2_3_4_5_6_7_12_13_14_CLK / PWM_FREQ_TIM) / PWM_PERIOD_TIM)	//Pr�diviseur : nombre d'�v�nements qui provoquent +1 sur le d�compte du timer
#define	PWM_PRESC_TIM_1	((TIM1_8_9_10_11_CLK / PWM_FREQ_TIM) / PWM_PERIOD_TIM)	//Pr�diviseur : nombre d'�v�nements qui provoquent +1 sur le d�compte du timer

/********************************************************MACROS********************************************************/
#define PWM_MIN_MOTOR_OFF	1000 //A redéfinir
#define PWM_MAX_MOTOR_ON	2000
#define PWM_LIMIT			1200

/********************************************************PROTOTYPES DE FONCTION********************************************************/
void MC_init_pwm_tim1_tim3(drone_data_t * drone_data_);
void MC_pwm_timer_set_duty(TIM_HandleTypeDef tim_handle, int channel, uint16_t duty);
void MC_esc_calibration(void);
void MC_f1_m1_PE9(uint16_t TIME);
void MC_f1_m2_PE11(uint16_t TIME);
void MC_f1_m3_PE13(uint16_t TIME);
void MC_f1_m4_PE14(uint16_t TIME);
void MC_f2_m1_PC6(uint16_t TIME);
void MC_f2_m2_PC7(uint16_t TIME);
void MC_f2_m3_PC8(uint16_t TIME);
void MC_f2_m4_PC9(uint16_t TIME);
void MC_put_all_motors_off(void);
void MC_update_motors(void);
void MC_PID_correction(void);
void MC_test_progressive_pwm(void);
void MC_test_all_motors(void);
void MC_test_props(void);

#endif /*MOTORS_CONTROL_H*/

/*
 * Explications :
 * - Le timer compte des �v�nements...
 * - Nous disposons d'une horloge � 84MHz...
 * - Tout les X �v�nements (les X p�riodes d'horloge), le timer compte +1.... Ce X est le pr�diviseur. (PWM_PRESC)
 * - Le timer va compter jusqu'� "PWM_PERIOD"... Puis revenir � 0. Et ainsi de suite.
 * - La dur�e qu'il met � compter jusqu'� cette PWM_PERIOD nous donne la p�riode du signal PWM... L'inverse est la fr�quence !
 * 				P�riode du signal PWM 	= (PWM_PERIOD	*	PWM_PRESC)/84MHz
 * 	Exemple :				50�s	 	= (100			*	42)/84MHz
 * 	 			Fr�quence du signal PWM = 84MHz/(PWM_PERIOD	*	PWM_PRESC)
 * 	Exemple :				50�s	 	= 84MHz/(100		*	42)
 */

//==========================
/*
 PWM_MOT_11 GPIOC, GPIO_PIN_6 => TIM3_CH1
 PWM_MOT_12 GPIOC, GPIO_PIN_7 => TIM3_CH2
 PWM_MOT_13 GPIOC, GPIO_PIN_8 => TIM3_CH3
 PWM_MOT_14 GPIOC, GPIO_PIN_9 => TIM3_CH4

 PWM_MOT_21 GPIOE, GPIO_PIN_9 =>  TIM1_CH1
 PWM_MOT_22 GPIOE, GPIO_PIN_11 => TIM1_CH2
 PWM_MOT_23 GPIOE, GPIO_PIN_13 => TIM1_CH3
 PWM_MOT_24 GPIOE, GPIO_PIN_14 => TIM1_CH4
*/

//CALIBRATION ESC FONCTIONNELLE DU 9/09/2020
/*
  	MC_init_pwm_tim1_tim3();
	//3 bips = Alim ok
	HAL_Delay(500);
	test_moteur_PC6(PWM_MAX_MOTOR_ON);
	//1 bip = PWM MAX ok
	HAL_Delay(1000);
	test_moteur_PC6(PWM_MIN_MOTOR_OFF);
	//1 bip = PWM MIN ok
	//On reste entre les PWM MIN et MAX
	HAL_Delay(1000);
	test_moteur_PC6(70);
	HAL_Delay(2000);
	test_moteur_PC6(50);
	HAL_Delay(2000);
	test_moteur_PC6(55);
	HAL_Delay(2000);
	test_moteur_PC6(60);
	HAL_Delay(2000);
	test_moteur_PC6(70);
	*/
