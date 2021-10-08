/**
 * @file DispatcherDSMonitorSupervisorTest.c
 * @brief n
 * @date Juin 2021
 * @authors Robin Leprince
 * @version 1.0
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>


#include "../../src/comDSMonitorSupervisor/DispatcherDSMonitorSupervisor.c"
#include "../cmocka-x86_64/include/cmocka.h"

/* Fonctions Setup et Teardown */
static int setUp(void **state) {
    return 0;
}

static int tearDown(void **state) {
    return 0;
}

/* Tests de DispatcherDSMS New, Start, Stop, Free */
static void testDispatcherDSMSNew(void **state)
{
	DispatcherDSMS_new();
	assert_int_equal(myDispatcherDSMS.currentState, S_DSMS_DEATH);
	assert_int_equal(myDispatcherDSMS.session, false);
	DispatcherDSMS_free();
}

static void testDispatcherDSMSStart(void **state)
{
	messageToReadAck.command=ACK_NO_MA;
	DispatcherDSMS_new();
	DispatcherDSMS_start();
	assert_int_equal(myDispatcherDSMS.currentState, S_DSMS_WAITING_ORDER);
	DispatcherDSMS_stop();
	DispatcherDSMS_free();
}

static void testDispatcherDSMSStop(void **state)
{
	DispatcherDSMS_new();
	DispatcherDSMS_start();
	DispatcherDSMS_stop();
	assert_int_equal(myDispatcherDSMS.currentState, S_DSMS_DEATH);
	DispatcherDSMS_free();
}

static void testDispatcherDSMSFree(void **state)
{
	DispatcherDSMS_new();
	DispatcherDSMS_start();
	DispatcherDSMS_stop();
	DispatcherDSMS_free();
	assert_int_equal(myDispatcherDSMS.currentState, S_DSMS_DEATH);
	assert_int_equal(myDispatcherDSMS.session, false);
}

static void testDispatcherDSMSToggleCaptureOn(void **state)
{
	/* Initialisation */
	DispatcherDSMS_new();
	DispatcherDSMS_start();

	/* Assignation aux valeurs d'entrées */
	myDispatcherDSMS.currentState = S_DSMS_WAITING_ORDER;
	myDispatcherDSMS.session = false;

	/* Appel de la fonction à tester */
	DispatcherDSMS_toggleCapture();

	/* Vérification des valeurs par rapport à celles attendues */
	assert_int_equal(myDispatcherDSMS.currentState, S_DSMS_RUNNING);
	assert_int_equal(myDispatcherDSMS.session, true);

	/* Desctrution */
	DispatcherDSMS_stop();
	DispatcherDSMS_free();
}

static void testDispatcherDSMSToggleCaptureOff(void **state)
{
	/* Initialisation */
	DispatcherDSMS_new();
	DispatcherDSMS_start();

	/* Assignation aux valeurs d'entrées */
	myDispatcherDSMS.currentState = S_DSMS_RUNNING;
	myDispatcherDSMS.session = true;

	/* Appel de la fonction à tester */
	DispatcherDSMS_toggleCapture();
	
	/* Vérification des valeurs par rapport à celles attendues */
	assert_int_equal(myDispatcherDSMS.currentState, S_DSMS_WAITING_ORDER);
	assert_int_equal(myDispatcherDSMS.session, false);

	/* Desctrution */
	DispatcherDSMS_stop();
	DispatcherDSMS_free();
}

// static void testRun(void **state)
// {
// 	/* Initialisation */
// 	DispatcherDSMS_new();
// 	DispatcherDSMS_start();

// 	/* Assignation aux valeurs d'entrées */
// 	myDispatcherDSMS.currentState = S_DSMS_RUNNING;

// 	/* Appel de la fonction à tester */
// 	DispatcherDSMS_run();

// 	/* Vérification des appels aux fonctions bouchonnées */
// 	expect_function_call(__wrap_PostmanDSMS_read);
// 	expect_function_call(__wrap_ntercoreProtocol_decodeMessage);

// 	/* Desctrution */
// 	DispatcherDSMS_stop();
// 	DispatcherDSMS_free();
// }



/* Tableau des tests de DispatcherDSMS */
static const struct CMUnitTest dispatcherDSMS[] =
{
	/* Tests de New, Start, Stop, Free */
	cmocka_unit_test(testDispatcherDSMSNew),
	cmocka_unit_test(testDispatcherDSMSStart),
	cmocka_unit_test(testDispatcherDSMSStop),
	cmocka_unit_test(testDispatcherDSMSFree),

	/* Tests de ToggleCapture */
	cmocka_unit_test(testDispatcherDSMSToggleCaptureOn),
	cmocka_unit_test(testDispatcherDSMSToggleCaptureOff),

};

/* Fonction du groupe de tests */
int DispatcherDSMSRunTests()
{
	return cmocka_run_group_tests_name("Test du module DispatcherDSMS", dispatcherDSMS, setUp, tearDown);
}