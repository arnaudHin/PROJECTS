/**
 * @file : commun.h
 * @brief :
 * @version
 * @date : May 11, 2021
 * @author: Arnaud
 */


#ifndef INC_COMMUN_H_
#define INC_COMMUN_H_

#include <stdint.h>
#include <stdbool.h>


//////////////////////////////////////////////////////////////////////////////////
//				Define						//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//				Types						//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @typedef
 */
typedef uint16_t SessionId;

/**
 * @typedef
 */
typedef uint16_t Size;

/**
 * @typedef
 */
typedef float SensorMeasure;

/**
 * @typedef
 */
typedef uint32_t TimeMeasure;


//////////////////////////////////////////////////////////////////////////////////
//				Types énumérés					//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @enum
 * @brief
 */
typedef enum{
    DAV_OK = 0,/**< DAV_OK */
    DAV_ERROR  /**< DAV_ERROR */
}DavidsonStatus_e;

/**
 * @enum
 * @brief
 */
typedef enum{
	SENSOR_CONNECTED = 0,/**< SENSOR_CONNECTED */
	SENSOR_NOTCONNECTED  /**< SENSOR_NOTCONNECTED */
}SensorConnectionStatus_e;

/**
 * @enum
 * @brief
 */
typedef enum{
	CONNECTED = 0,/**< CONNECTED */
	NOTCONNECTED  /**< NOTCONNECTED */
}SensorBoardConnectionStatus_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
	APP	= 0,/**< APP */
	MONITOR,/**< MONITOR */
} Location_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
	SOC = 0,/**< SOC */
	SST,    /**< SST */
	SAT,    /**< SAT */
	SSTI,   /**< SSTI */
} ModeId_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
	CONTINUOUS = 0,/**< CONTINUOUS */
	INSTANT,       /**< INSTANT */
} SubModeId_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
	TEMP=0,   /**< TEMP */
	PRES,     /**< PRES */
	HUMI,     /**< HUMI */
	ACCE,     /**< ACCE */
	GYRO,     /**< GYRO */
	MAGN,     /**< MAGN */
	NB_SENSORS/**< NB_SENSORS */
} SensorId_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
	P_50_MS=0,/**< P_50_MS */
	P_100_MS, /**< P_100_MS */
	P_500_MS, /**< P_500_MS */
	P_1000_MS,/**< P_1000_MS */
	P_5000_MS,/**< P_5000_MS */
} Period_e;

/**
 * @enum
 * @brief
 */
typedef enum
{
	ASK_START=1,	/* Ask start Session 		*/       /**< ASK_START */
	ASK_STOP, 		/* Ask stop Session 		*/       /**< ASK_STOP */
	ASK_NEW_MSG, 		/* Ask MeasuresArray 		*/   /**< ASK_NEW_MSG */
	ACK_MA, 		/* Acquitte MeasuresArray 	*/    /**< ACK_MA */
	ACK_SBC_OK, 		/* Acquitte SB connection 	*//**< ACK_SBC_OK */
	ACK_SBC_KO		/* Acquitte SB connection 	*/  /**< ACK_SBC_KO */
} CMD_e;


//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////

/**
 * @struct
 * @brief
 */
typedef struct
{
	uint8_t sensorNb;
	bool sensorsActive[NB_SENSORS];
	SensorId_e sensors[NB_SENSORS];
	Period_e periodSensor[NB_SENSORS];
} SensorsArray_t;

/**
 * @struct
 * @brief
 */
typedef struct
{
	SensorId_e sensorId;
	SensorMeasure measure[3];
} MeasureArray_t;


/**
 * @struct
 * @brief
 */
typedef struct
{
	SessionId sessionId;
	ModeId_e modeId;
	SubModeId_e subModeId;
	SensorsArray_t sensorsArray;
} S_DataToRead_t;

/**
 * @struct
 * @brief
 */
typedef struct
{
	SessionId sessionId;
	TimeMeasure time;
	uint8_t sensorNb;
	MeasureArray_t measuresArray[NB_SENSORS];
} S_DataToWrite_t;


/**
 * @struct
 * @brief
 */
typedef struct
{
	CMD_e command;
	Size size;
	S_DataToRead_t dataToRead;
} S_MessageToRead_t;


/**
 * @struct
 * @brief
 */
typedef struct
{
	CMD_e command;
	Size size;
	S_DataToWrite_t dataToWrite;
} S_MessageToWrite_t;





#endif /* INC_COMMUN_H_ */
