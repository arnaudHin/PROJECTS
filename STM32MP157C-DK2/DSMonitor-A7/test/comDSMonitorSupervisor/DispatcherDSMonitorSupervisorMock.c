/**
 * @file DispatcherDSMonitorSupervisorTest.c
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

#include "../../src/common.h"
#include "../cmocka-x86_64/include/cmocka.h"

int __wrap_PostmanDSMS_read(uint8_t *bufferToRead, uint16_t sizeToRead)
{
	/* On vérifie que la fonction mockée a bien été appelée */
	function_called();	

	/* On vérifie que le 1er parametre de la fonction est entré */
	check_expected_ptr(bufferToRead);
	
	/* On vérifie que le 2me parametre de la fonction est entré */
	check_expected(sizeToRead);
}

int __wrap_DispatcherDSMS_run()
{
    function_called();
}

int __wrap_ProxyMeasuresProcessorApp_storeMeasuresArray()
{
    function_called();
}

int __wrap_IntercoreProtocol_decodeMessage(uint8_t *bufferToRead, M_MessageAnswer_t *messageToRead)
{
	/* On vérifie que la fonction mockée a bien été appelée */
	function_called();
	
	/* On vérifie que le 1er parametre de la fonction est entré */
	check_expected_ptr(bufferToRead);

	/* On vérifie que le 2me parametre de la fonction est entré */
	check_expected_ptr(messageToRead);
}