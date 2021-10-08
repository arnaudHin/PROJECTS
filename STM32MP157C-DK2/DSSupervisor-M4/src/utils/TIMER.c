/**
 * @file : TIMER.c
 * @brief :
 * @version
 * @date : May 11, 2021
 * @author: Arnaud
 */

#include "utils/TIMER.h"
#include "utils/GPIOS.h"
#include "stm32mp1xx_hal.h"
#include "stm32mp1xx_hal_tim.h"
#include "sensorsManager/SensorManager.h"



static TIM_HandleTypeDef tim4_handle;


//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////

extern void TIMER4_init(){

	TIM_ClockConfigTypeDef clockConfig = {0};

	__HAL_RCC_TIM4_CLK_ENABLE();

	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);

	tim4_handle.Instance = TIM4;
	tim4_handle.Init.Prescaler = 1000;
	tim4_handle.Init.Period = 64000;
	tim4_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	tim4_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim4_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(&tim4_handle);

	clockConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

	HAL_TIM_ConfigClockSource(&tim4_handle, &clockConfig);

	HAL_TIM_Base_Start(&tim4_handle);

}

extern void TIMER4_run(){
	HAL_TIM_Base_Start_IT(&tim4_handle);
}


extern void TIMER4_stop(){
	__HAL_TIM_DISABLE(&tim4_handle);
}


void TIM4_IRQHandler(){

	HAL_TIM_IRQHandler(&tim4_handle);

	TIMER4_user_handler_it_1ms();
}





