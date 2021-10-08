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

#include "../../src/common.h"
#include "../cmocka-x86_64/include/cmocka.h"
#include "../../src/comDSMonitorApp/ProxySessionArchiver.h"
#include "../../src/comDSMonitorSupervisor/ProxyMeasuresProcessorSupervisor.h"


int __wrap_ProxySessionArchiver_storeEndSession(Time aTime)

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();

        check_expected(aTime);
}

int __wrap_ProxySessionArchiver_storeBeginSession(SessionId sessionId, ModeId_e modeId, SubModeId_e submodeId, SensorsArray_t sensorsArray, Time time)

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();

}

int __wrap_ProxyMeasuresProcessorSupervisor_askStartSession(M_DataOrder_t *dataToWrite)
{
    function_called();
}


int __wrap_ProxyMeasuresProcessorSupervisor_askStopSession()

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();
}

