/**
 * @file DispatcherDSMonitorAppTest.c
 * @brief code test de DispatcherDSMonitorApp
 * @date juin 2021
 * @authors Ibrahima Ndiaye
 * @version 1 
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/comDSMonitorApp/ProxyMonitorGUI.c"
#include "../cmocka-x86_64/include/cmocka.h"


/* ------------------------ FONCTIONS SETUP ET TEARDOWN ------------------------*/

static int setUp(void **state) {
    return 0;
}

static int tearDown(void **state) {
    return 0;
}

static void test_ProxyGUI_setError(void **state)
{


    //Verification de l'appel de la fonction
    expect_function_call(__wrap_WifiProtocol_encodeToDSAppMonitorGUI);
    

    ProxyMonitorGUI_setError();
    
}

static const struct CMUnitTest tests[] = 
{
	cmocka_unit_test(test_ProxyGUI_setError)

};

int proxy_tests() 
{
	return cmocka_run_group_tests_name("Test de la classe wifiprotocol ", tests, setUp, tearDown);
}
