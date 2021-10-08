/**

 * @file SessionManagerTest.c

 * @brief Test de la classe SessionManager

 * @date Juin 2021

 * @authors Ibrahima Ndiaye

 * @version 1.0

*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <unistd.h>
#include <assert.h>

#include "../../src/monitor/SessionManager.c"
#include "../cmocka-x86_64/include/cmocka.h"

/* Fonctions Setup et Teardown */
static int setUp(void **state) {
    return 0;
}

static int tearDown(void **state) {
    return 0;
}



static void testSessionManager_StopSession(void **state)
{
    int stopTime=1234;

    expect_function_call(__wrap_ProxySessionArchiver_storeEndSession);

    expect_value(__wrap_ProxySessionArchiver_storeEndSession,aTime,stopTime);

    expect_function_call(__wrap_ProxyMeasuresProcessorSupervisor_askStopSession);
    SessionManager_stopSession(stopTime);
    
    
}
static const struct CMUnitTest tests[] = 
{
	cmocka_unit_test(testSessionManager_StopSession),

};

int sessionManager_tests() 
{
	return cmocka_run_group_tests_name("Test de la classe session Manager ", tests, setUp, tearDown);
}


