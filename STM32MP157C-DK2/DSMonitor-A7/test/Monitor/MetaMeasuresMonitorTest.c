/**

 * @file MetaMesuresMonitorTest.c

 * @brief 

 * @date Juin 2021

 * @authors Robin Leprince

 * @version 1.0

 */

#include <stdarg.h>

#include <stddef.h>

#include <setjmp.h>

#include <unistd.h>

#include <assert.h>

#include "../../src/monitor/MetaMeasuresMonitor.c"

#include "../cmocka-x86_64/include/cmocka.h"

/* Fonctions Setup et Teardown */

static int setUp(void **state) {

    return 0;

}

static int tearDown(void **state) {

    return 0;

}

/* Tests de MetaMeasuresMonitor New, Start, Stop, Free */

static void testMetaMeasuresMonitorNew(void **state)

{

        MetaMeasuresMonitor_new();

        assert_int_equal(myMetaMeasuresMonitor.currentState, S_MMM_DEATH);

  

        MetaMeasuresMonitor_free();

}

static void testMetaMeasuresMonitorStart(void **state)

{

        MetaMeasuresMonitor_new();

        MetaMeasuresMonitor_start();


        assert_int_equal(myMetaMeasuresMonitor.currentEvent, E_MMM_START);

        MetaMeasuresMonitor_stop();

        MetaMeasuresMonitor_free();

}

static void testMetaMeasuresMonitorStop(void **state)

{

        MetaMeasuresMonitor_new();

        MetaMeasuresMonitor_start();

        MetaMeasuresMonitor_stop();

        assert_int_equal(myMetaMeasuresMonitor.currentEvent, E_MMM_STOP);

        MetaMeasuresMonitor_free();

}

static void testMetaMeasuresMonitorFree(void **state)

{

        MetaMeasuresMonitor_new();

        MetaMeasuresMonitor_start();

        MetaMeasuresMonitor_stop();

        MetaMeasuresMonitor_free();

        assert_int_equal(myMetaMeasuresMonitor.currentState, S_MMM_DEATH);

}

 /* Tests de MetaMeasuresMonitor StartMetaMeasures, StopMetaMeasures */

static void testStartMetaMeasures(void **state)

{

        /* Initialisation */

        MetaMeasuresMonitor_new();

        MetaMeasuresMonitor_start();

        /* Assignation aux valeurs d'entrées */

        SessionId sessionId = 206;

        /* Appel de la fonction à tester */

    expect_function_call(__wrap_ProxyMeasuresProcessorSupervisor_askStartSession);

        /* Vérification des valeurs par rapport à celles attendues */

	expect_value(__wrap_ProxyMeasuresProcessorSupervisor_askStartSession,id,sessionId);

        assert_int_equal(myMetaMeasuresMonitor.currentState, E_MMM_START_MM);

        /* Desctrution */

        MetaMeasuresMonitor_stop();

        MetaMeasuresMonitor_free();

}


static void testGetMetaMeasuresMonitor(void **state)

{

        /* Vérification des appels aux fonctions bouchonnées */

        expect_function_call(__wrap_MetaMeasuresMonitor_getClockCycleCount);
        
        will_return(__wrap_MetaMeasuresMonitor_getClockCycleCount,0);

        expect_function_call(__wrap_MetaMeasuresMonitor_getTasksPerCycleCount);
                
        will_return(__wrap_MetaMeasuresMonitor_getTasksPerCycleCount,0);

        expect_function_call(__wrap_MetaMeasuresMonitor_getCPUPercentagePerTask);

        will_return(__wrap_MetaMeasuresMonitor_getCPUPercentagePerTask,0);

        assert_int_equal(myMetaMeasuresArray->clockCycleCount, 0);

        assert_int_equal(myMetaMeasuresArray->tasksPerCycleCount, 0);

        assert_int_equal(myMetaMeasuresArray->percentagePerTask, 0);




}

// /* Tableau des tests de MetaMeasuresMonitor */

static const struct CMUnitTest metaMeasuresMonitorTest[] =

{

        /* Tests de New, Start, Stop, Free */

        cmocka_unit_test(testMetaMeasuresMonitorNew),

        cmocka_unit_test(testMetaMeasuresMonitorStart),

        cmocka_unit_test(testMetaMeasuresMonitorStop),

        cmocka_unit_test(testMetaMeasuresMonitorFree),

        cmocka_unit_test(testGetMetaMeasuresMonitor),

};

/* Fonction du groupe de tests */

int metaMeasuresMonitorRunTests()

{

        return cmocka_run_group_tests_name("Test du module MetaMeasuresMonitor", metaMeasuresMonitorTest, setUp, tearDown);

}
