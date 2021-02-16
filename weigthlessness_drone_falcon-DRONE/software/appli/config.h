/*
 * config.h
 *  Created on: 8 nov. 2016
 *      Author: Nirgal
 */

#ifndef APPLI_CONFIG_H_
#define APPLI_CONFIG_H_

#define USE_DIALOG				1

#define USE_SCREEN_TFT_ILI9341 	0

#define USE_BSP_TIMER			1

#define USE_I2C					1
#define USE_VL53L1X				1
#define VL53L1X_I2C				I2C1
#define VL53_NB					5
#define VL_0					GPIOD, GPIO_PIN_2
#define VL_1					GPIOD, GPIO_PIN_3
#define VL_2					GPIOE, GPIO_PIN_10
#define VL_3					GPIOE, GPIO_PIN_12
#define VL_4					GPIOD, GPIO_PIN_10


#define USE_MPU6050				1
#define MPU6050_VCC_GPIO		GPIOD
#define MPU6050_VCC_PIN			GPIO_PIN_1

#define LEDS_GPIO				GPIOD
#define LED_GREEN_PIN			GPIO_PIN_12
#define LED_ORANGE_PIN			GPIO_PIN_13
#define LED_RED_PIN				GPIO_PIN_14
#define LED_BLUE_PIN			GPIO_PIN_15


#define BLUETOOTH_UART_ID		UART2_ID


#define HCLK_FREQUENCY_HZ		168000000	//168Mhz, Max: 168Mhz
#define PCLK1_FREQUENCY_HZ		42000000	//42Mhz,  Max: 42Mhz
#define PCLK2_FREQUENCY_HZ		84000000	//84Mhz,  Max: 84Mhz
#define CPU_EXTERNAL_CLOCK_HZ	8000000		//8Mhz,   Fréquence de l'horloge externe


#define USE_UART1				1
#define USE_UART2				1
#define UART1_BAUDRATE			230400
#define UART2_BAUDRATE			230400

#define DEFAULT_PRINTF_UART		UART2_ID

#endif /* APPLI_CONFIG_H_ */
