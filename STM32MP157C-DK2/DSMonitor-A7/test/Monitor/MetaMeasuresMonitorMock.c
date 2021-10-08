/**

 * @file MetaMesuresMonitorMock.c

 * @brief 

 * @date Juin 2021

 * @authors Robin Leprince

 * @version 1.0

 */

#include <stdarg.h>

#include <stddef.h>

#include <setjmp.h>

#include <stdio.h>

#include "../../src/monitor/MetaMeasuresMonitor.h"

#include "../../src/comDSMonitorApp/ProxySessionArchiver.h"

#include "../cmocka-x86_64/include/cmocka.h"

int __wrap_MetaMeasuresMonitor_new()

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();

        return 0;

}

int __wrap_MetaMeasuresMonitor_start(SessionId sessionId)

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();
        
        check_expected(sessionId);

        return 0;

}

int __wrap_MetaMeasuresMonitor_getMetaMeasuresMonitor()

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();

}

int __wrap_MetaMeasuresMonitor_getClockCycleCount()

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();

            return (int)mock();  

}

int __wrap_MetaMeasuresMonitor_getTasksPerCycleCount()

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();

            return (int)mock();  

}

int __wrap_MetaMeasuresMonitor_getCPUPercentagePerTask()

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();

    return (int)mock();  
}

int __wrap_MetaMeasuresMonitor_run()

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();

}

int __wrap_ProxySessionArchiver_storeMetaMeasures(MetaMeasuresArray_t *metaMeasuresArray, Location_e location)

{

        /* On vérifie que la fonction mockée a bien été appelée */

        function_called();

        

        /* On vérifie que le 1er parametre de la fonction est entré */

        check_expected_ptr(metaMeasuresArray);

        /* On vérifie que le 2me parametre de la fonction est entré */

        check_expected(location);

}
