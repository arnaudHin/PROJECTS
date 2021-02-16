/*
 * pixy.h
 *
 *  Created on: 3 mars 2020
 *      Author: arnaud
 */

#ifndef SENSORS_PIXY_H_
#define SENSORS_PIXY_H_

#define SPINUM SPI1


#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_hal.h"
#include "macro_types.h"
#include "stm32f4_uart.h"
#include "stm32f4_sys.h"
#include "stm32f4_spi.h"


//PROTOTYPE

void pixy_process_main(void);
void pixy_init(void);
void pixy_process_ms(void);

void pixyCam_Init(void);
void test_pixy(void);
int SetLED(unsigned char r, unsigned char g, unsigned char b);
int SetServos(uint16_t s0, uint16_t s1);




#endif /* SENSORS_PIXY_H_ */
