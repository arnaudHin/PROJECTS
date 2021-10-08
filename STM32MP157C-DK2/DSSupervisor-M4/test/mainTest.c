/**
 * @file mainTest.c
 *
 * @brief Launch Example program with one active object
 *
 * @date June 2021

 * @author Ibrahima Ndiaye
 *
 * @version 0.1
 *
 * @copyright innov'B1
 * Based on template written by Matthias BRUN
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka/cmocka.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*----------------------- TEST SUITES DECLARATIONS -----------------------*/
/**
 * @def Test suites number
 *
 * TODO : Update when a test suite is added
 */
#define TEST_SUITES_NB 1


/* List of test suites to execute */
int (* testSuites[])(void) =
        {
                //todo
        };

static void testRunner();
static void displayHelp(char * nom);


/**
 * @brief Main function of test program
 *
 */
int main(int argc, char * argv[])
{
    if ( (argc > 1) )
    {
        if (!strcmp(argv[1], "-text")) {
            cmocka_set_message_output(CM_OUTPUT_STDOUT);
        } else
        if (!strcmp(argv[1], "-subunit")) {
            cmocka_set_message_output(CM_OUTPUT_SUBUNIT);
        } else
        if (!strcmp(argv[1], "-tap")) {
            cmocka_set_message_output(CM_OUTPUT_TAP);
        } else
        if (!strcmp(argv[1], "-xml")) {
            cmocka_set_message_output(CM_OUTPUT_XML);
        } else {
            displayHelp(argv[0]);
        }
    }
    testRunner();
    return 0;
}


/**
 * @brief Launch every test suite
 *
 */
static void testRunner()
{
    int i;
    for (i = 0; i < TEST_SUITES_NB; i++)
    {
        testSuites[i]();
    }
}


/**
 * @brief Display help when using test program
 *
 */
static void displayHelp(char * nom)
{
    printf("Test suite\n");
    printf("Usage : %s [-text] [-subunit] [-tap] [-xml]\n", nom);

    exit(0);
}
