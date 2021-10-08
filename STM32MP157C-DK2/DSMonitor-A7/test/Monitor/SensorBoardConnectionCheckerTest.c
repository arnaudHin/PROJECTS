/*

* @autor : Arnaud HINCELIN 
*/

#include "../../src/monitor/SensorBoardConnectionChecker.c"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <unistd.h>
#include "../cmocka-x86_64/include/cmocka.h"


static int setUp(void ** state){
    return 0;
}

static int tearDown(void ** state){
    return 0;
}



static void testSensorBoardConnectionCheckernew(void ** state){

    SensorBoardConnectionChecker_New();

    SBConnection_Checker_t * SBConnectionChekerTest = SensorBoardConnectionChecker_Get();

    assert_int_equal(SBConnectionChekerTest->myState, S_NEW);

    assert_int_equal(SBConnectionChekerTest->myState, S_WAITING_GUI);
}



static const struct CMUnitTest SensorBoardConnectionCheckerTests[] = {

        cmocka_unit_test(testSensorBoardConnectionCheckernew)

    };


int SensorBoardConnectionCheckerRunTests(){
    return cmocka_run_group_tests_name("Tests du module SensorBoard", SensorBoardConnectionCheckerTests, setUp, tearDown);
}







