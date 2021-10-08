/**
 * @file : TIMER.h
 * @brief :
 * @version
 * @date : May 11, 2021
 * @author: Arnaud
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @fn void TIMER4_init()
 * @brief

 */
extern void TIMER4_init();

/**
 * @fn void TIMER4_run()
 * @brief
 */
extern void TIMER4_run();

/**
 * @fn void TIMER4_stop()
 * @brief
 */
extern void TIMER4_stop();

/**
 * @fn void TIM4_IRQHandler()
 * @brief
 */
void TIM4_IRQHandler();


#endif /* INC_TIMER_H_ */
