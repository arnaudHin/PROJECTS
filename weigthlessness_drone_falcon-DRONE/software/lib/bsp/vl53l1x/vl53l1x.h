/*
 * VL53_becon.h

 *
 *  Created on: 3 nov. 2019
 *      Author: Guillaume
 */

#ifndef VL53_BEACON_H_
#define VL53_BEACON_H_
#include "config.h"
#include "macro_types.h"

typedef enum
{
	TIMESLOT_ASK_BEGIN = 0,
	TIMESLOT_ASK_END = VL53_NB-1,
	TIMESLOT_WAIT_TIME_DURING_MEASUREMENTS = 20,
	//TIMESLOT_GET_BEGIN = 21,
	//TIMESLOT_GET_END = 21+VL53_NB-1,
	TIMESLOT_NB
}timeslot_e;

/*
 * initialise le module et les capteurs
 */
bool_e VL53L1X_init();

/*
 * recupère les info des capteurs VL53
 */
timeslot_e VL53L1X_process_it();

/*
 *
 */
void VL53L1X_process_main(void);


uint16_t VL53L1X_get_distance(uint8_t id);


#endif /* VL53_BEACON_H_ */
