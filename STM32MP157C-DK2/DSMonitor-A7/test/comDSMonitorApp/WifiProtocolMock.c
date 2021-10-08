#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "../../src/common.h"

#include "../../src/comDSMonitorApp/WifiProtocol.h"

#include "../cmocka-x86_64/include/cmocka.h"

void __wrap_WifiProtocol_encodeToDSAppMonitorGUI(DataToWrite myDataToWrite)
{
    /* Vérification de l'appel de fonction */
    function_called();

    /* Vérification du paramètre */
    check_expected(myDataToWrite);
}
