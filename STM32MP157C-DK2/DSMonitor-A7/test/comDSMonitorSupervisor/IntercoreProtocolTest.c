/**

 * @file IntercoreProtocolTest.c

 * @brief Test de la classe IntercoreProtocol

 * @date Juin 2021

 * @authors Justine Petton

 * @version 1.0
*/

#include "../../src/comDSMonitorSupervisor/IntercoreProtocol.c"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <unistd.h>
#include "../cmocka-x86_64/include/cmocka.h"

/* ------------------------ FONCTIONS SETUP ET TEARDOWN ------------------------*/

static int setUp(void **state) {
    return 0;
}

static int tearDown(void **state) {
    return 0;
}

/**

 * @brief Test de la fonction decodeMessage

 */
static void test_IntercoreProtocol_decodeMessage(void **state)
{
    int byteIndex = 0;
    
    uint8_t bufferToReadTest[3];
    M_MessageAnswer_t messageToReadTest;
    uint16_t bytesToDecode=3;
    
	
	uint8_t * cmdT = calloc(1, sizeof(uint8_t));
	*cmdT = (CMD_e) ACK_MA;
	memcpy(bufferToReadTest, cmdT, sizeof(uint8_t));		// 1 octets
	byteIndex+=sizeof(uint8_t);
	free(cmdT);

	Size * sizeR = calloc(1, sizeof(Size));
	*sizeR = (Size) 23;
	memcpy(bufferToReadTest + byteIndex, sizeR, sizeof(Size));		// 2 octets
	byteIndex+=sizeof(Size);
	free(sizeR);
	
	IntercoreProtocol_decodeMessage(bufferToReadTest, &messageToReadTest, bytesToDecode);
	
	assert_int_equal(messageToReadTest.command,ACK_MA);
	assert_int_equal(messageToReadTest.size,23);
	
}



static const struct CMUnitTest tests[] = 
{
	cmocka_unit_test(test_IntercoreProtocol_decodeMessage),
	//cmocka_unit_test(test_IntercoreProtocol_decodeMessage2),
};

int IntercoreProtocol_tests() 
{
	return cmocka_run_group_tests_name("Test de la classe wifiprotocol ", tests, setUp, tearDown);
}
