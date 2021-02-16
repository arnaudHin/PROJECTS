
/* 
* This file is part of VL53L1 Platform 
* 
* Copyright (c) 2016, STMicroelectronics - All Rights Reserved 
* 
* License terms: BSD 3-clause "New" or "Revised" License. 
* 
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions are met: 
* 
* 1. Redistributions of source code must retain the above copyright notice, this 
* list of conditions and the following disclaimer. 
* 
* 2. Redistributions in binary form must reproduce the above copyright notice, 
* this list of conditions and the following disclaimer in the documentation 
* and/or other materials provided with the distribution. 
* 
* 3. Neither the name of the copyright holder nor the names of its contributors 
* may be used to endorse or promote products derived from this software 
* without specific prior written permission. 
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
* 
*/

#include <vl53l1x/low_layer/platform/vl53l1_platform.h>
#include "config.h"

#ifdef USE_VL53L1X

	#include "stm32f4_i2c.h"

	#include <string.h>
	#include <time.h>
	#include <math.h>

//	#define USE_I2C_DELAY

	#define I2C_MAX_NB_ERROR	1
	#define I2C_TIME_OUT_BASE   10
	#define I2C_TIME_OUT_BYTE   1



	int8_t VL53L1_WrByte(VL53L1_DEV Dev, uint16_t index, uint8_t data) {
		bool_e status;
		Uint8 nbError = 0;

		do{
			status = HAL_I2C_Mem_Write(I2C_get_phandler(Dev->I2cHandle),Dev->I2cDevAddr,index,I2C_MEMADD_SIZE_16BIT,&data,1,I2C_TIMEOUT);
			//memoryOk = I2C_Write_reg16(Dev->I2cHandle, Dev->I2cDevAddr, index, data);
		}while(status && nbError++ < I2C_MAX_NB_ERROR);

		#ifdef USE_I2C_DELAY
			time32_t beginTimeBoot = global.absolute_time;
			while(global.absolute_time - beginTimeBoot < 2);
		#endif

		return status;
	}

	int8_t VL53L1_WrWord(VL53L1_DEV Dev, uint16_t index, uint16_t data) {
		Uint8 datas[2] = {((data >> 8) & 0xFF), ((data) & 0xFF)};
		bool_e status;
		Uint8 nbError = 0;

		do{
			status = HAL_I2C_Mem_Write(I2C_get_phandler(Dev->I2cHandle),Dev->I2cDevAddr,index,I2C_MEMADD_SIZE_16BIT,datas,2,I2C_TIMEOUT);
			//memoryOk = I2C_Write(Dev->I2cHandle, Dev->I2cDevAddr, (Uint8 *) indexs, 2, datas, 2);
		}while(status && nbError++ < I2C_MAX_NB_ERROR);

		#ifdef USE_I2C_DELAY
			time32_t beginTimeBoot = global.absolute_time;
			while(global.absolute_time - beginTimeBoot < 2);
		#endif

		return status;
	}

	int8_t VL53L1_WrDWord(VL53L1_DEV Dev, uint16_t index, uint32_t data) {
		Uint8 datas[4] = {((data >> 24) & 0xFF), ((data >> 16) & 0xFF), ((data >> 8) & 0xFF), ((data) & 0xFF)};
		bool_e status;
		Uint8 nbError = 0;

		do{
			status = HAL_I2C_Mem_Write(I2C_get_phandler(Dev->I2cHandle),Dev->I2cDevAddr,index,I2C_MEMADD_SIZE_16BIT,datas,4,I2C_TIMEOUT);
			//memoryOk = I2C_Write(Dev->I2cHandle, Dev->I2cDevAddr, (Uint8 *) indexs, 2, datas, 4);
		}while(status && nbError++ < I2C_MAX_NB_ERROR);

		#ifdef USE_I2C_DELAY
			time32_t beginTimeBoot = global.absolute_time;
			while(global.absolute_time - beginTimeBoot < 2);
		#endif

		return status;
	}

	int8_t VL53L1_RdByte(VL53L1_DEV Dev, uint16_t index, uint8_t *data) {
		bool_e status;
		Uint8 nbError = 0;

		do{
			status = HAL_I2C_Mem_Read(I2C_get_phandler(Dev->I2cHandle),Dev->I2cDevAddr,index,I2C_MEMADD_SIZE_16BIT,data,1,I2C_TIMEOUT);
			//memoryOk = I2C_Read(Dev->I2cHandle, Dev->I2cDevAddr, (Uint8 *) indexs, 2, data, 1);
		}while(status && nbError++ < I2C_MAX_NB_ERROR);

		#ifdef USE_I2C_DELAY
			time32_t beginTimeBoot = global.absolute_time;
			while(global.absolute_time - beginTimeBoot < 2);
		#endif

		return status;
	}

	int8_t VL53L1_RdWord(VL53L1_DEV Dev, uint16_t index, uint16_t *data) {
		Uint8 datas[2];
		bool_e status;
		Uint8 nbError = 0;
		do{
			status = HAL_I2C_Mem_Read(I2C_get_phandler(Dev->I2cHandle),Dev->I2cDevAddr,index,I2C_MEMADD_SIZE_16BIT,datas,2,I2C_TIMEOUT);
			//memoryOk = I2C_Read(Dev->I2cHandle, Dev->I2cDevAddr, (Uint8 *) indexs, 2, datas, 2);
		}while(status && nbError++ < I2C_MAX_NB_ERROR);// on boucle meme si memoryOK est true ???

		#ifdef USE_I2C_DELAY
			time32_t beginTimeBoot = global.absolute_time;
			while(global.absolute_time - beginTimeBoot < 2);
		#endif

		if(data)
			*data = ((((Uint16)datas[0]) << 8) | datas[1]);

		return status;
	}

	int8_t VL53L1_RdDWord(VL53L1_DEV Dev, uint16_t index, uint32_t *data) {
		Uint8 datas[4];
		bool_e status;
		Uint8 nbError = 0;

		do{
			status = HAL_I2C_Mem_Read(I2C_get_phandler(Dev->I2cHandle),Dev->I2cDevAddr,index,I2C_MEMADD_SIZE_16BIT,datas,4,I2C_TIMEOUT);
			//memoryOk = I2C_Read(Dev->I2cHandle, Dev->I2cDevAddr, (Uint8 *) indexs, 2, datas, 4);
		}while(status && nbError++ < I2C_MAX_NB_ERROR);

		#ifdef USE_I2C_DELAY
			time32_t beginTimeBoot = global.absolute_time;
			while(global.absolute_time - beginTimeBoot < 2);
		#endif

		if(data)
			*data = ((((Uint32)datas[0]) << 24) | (((Uint32)datas[1]) << 16) | (((Uint32)datas[2]) << 8) | datas[3]);
		return status;
	}

	int8_t VL53L1_WaitMs(VL53L1_Dev_t *pdev, int32_t wait_ms){
		HAL_Delay(wait_ms);
		//volatile time32_t begin = global.absolute_time;
		//while(global.absolute_time - begin < wait_ms);
		return 0;
	}

#endif
