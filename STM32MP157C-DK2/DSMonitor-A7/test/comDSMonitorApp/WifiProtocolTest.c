/**

 * @file WifiProtocolTest.c

 * @brief Test de la classe WifiProtocol

 * @date Juin 2021

 * @authors Ibrahima Ndiaye

 * @version 1.0

*/
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../src/comDSMonitorApp/WifiProtocol.c"
#include "../cmocka-x86_64/include/cmocka.h"


/* ------------------------ FONCTIONS SETUP ET TEARDOWN ------------------------*/

static int setUp(void **state) {
    return 0;
}

static int tearDown(void **state) {
    return 0;
}


/**

 * @brief Test de la fonction decodeCommandeSize. 

 */

static void WifiProtocol_decodeCommandSizeTest(void **state)
{
    uint8_t bufferToReadTest[13];
    M_MessageToReadFromDSApp_t messageToReadTest;


    uint16_t indextest = 0;
    uint8_t cmd = START_SESSION;
    bufferToReadTest[0] = cmd;

    uint8_t size = 0;
    bufferToReadTest[1] = size;
    bufferToReadTest[2] = size;

    bufferToReadTest[3] = SOC;
    bufferToReadTest[4]= CONTINUOUS;

   
   WifiProtocol_decodeCommandSize(bufferToReadTest,&messageToReadTest);
   


   assert_int_equal(messageToReadTest.commandMsg,START_SESSION);
   assert_int_equal(messageToReadTest.sizeMsg,0);
   
   }

static void WifiProtocol_encode(void **state)
{
    uint8_t  dataToWriteBuffer[50];
    M_MessageToReadFromDSApp_t messageFromDSApp;

    messageFromDSApp.commandMsg=START_SESSION;
    messageFromDSApp.sizeMsg=255;
    messageFromDSApp.sessionInformationMsg.sessionId=10;
    messageFromDSApp.sessionInformationMsg.modeId=SOC;
    messageFromDSApp.sessionInformationMsg.subModeId=CONTINUOUS;
    messageFromDSApp.sessionInformationMsg.time=255;
    messageFromDSApp.sessionInformationMsg.sensorsArray.sensorNb=1;
    messageFromDSApp.sessionInformationMsg.sensorsArray.sensorActive[1]=true;
    messageFromDSApp.sessionInformationMsg.sensorsArray.sensorActive[2]=false;
    messageFromDSApp.sessionInformationMsg.sensorsArray.sensorActive[3]=false;
    messageFromDSApp.sessionInformationMsg.sensorsArray.sensorActive[4]=false;
    messageFromDSApp.sessionInformationMsg.sensorsArray.sensorActive[5]=false;
    messageFromDSApp.sessionInformationMsg.sensorsArray.sensorActive[6]=false;
    messageFromDSApp.sessionInformationMsg.sensorsArray.sensors[0]=TEMP;
    messageFromDSApp.sessionInformationMsg.sensorsArray.periodSensor[0]=2;

    WifiProtocol_encodeToDSAppStoreBeginSession(dataToWriteBuffer,&messageFromDSApp);

    assert_int_equal(dataToWriteBuffer[0], START_SESSION);
    assert_int_equal(dataToWriteBuffer[1], 0);
    assert_int_equal(dataToWriteBuffer[2], 255);
    assert_int_equal(dataToWriteBuffer[3], 0);
    assert_int_equal(dataToWriteBuffer[4], 10);
    assert_int_equal(dataToWriteBuffer[5], SOC);
    assert_int_equal(dataToWriteBuffer[6], CONTINUOUS);


}





/**

 * @brief Test de la fonction decodeData. 

 */

/*static void WifiProtocol_decodeDataStop(void **state)
{
    
    uint16_t indexStart=0;;
    uint8_t bufferToReadTest[6];
   M_MessageToReadFromDSApp_t messageToReadTest;
    
    uint8_t aa;
    Time timeStop;
    for (size_t i = 0; i < sizeof(uint64_t); i++)
            {
                aa = *(bufferToReadTest + index);
                timeStop = (timeStop << 8) | aa;
                index += sizeof(uint8_t);
            }
*/
    //uint8_t *bufferToReadFromDS;
    //M_MessageToReadFromDSApp_t *messageToReadfromDS;

    // uint8_t * cmd = calloc(1, sizeof(uint8_t) );
    // *cmd = (uint8_t) START_SESSION;
    // memcpy(bufferToReadFromDS, cmd, sizeof(uint8_t));

    // SessionId* sessId = calloc(1, sizeof(SessionId) );
    // *sessId = (SessionId) 1;
    // memcpy(bufferToReadFromDS+indexStart, sessId, sizeof(SessionId));

    // ModeId_e * mode = calloc(1, sizeof(ModeId_e) );
    // *mode = (ModeId_e) SOC;
    // memcpy(bufferToReadFromDS, cmd, sizeof(ModeId_e));

    // SubModeId_e * smode = calloc(1, sizeof(SubModeId_e) );
    // *cmd = (SubModeId_e) CONTINUOUS;
    // memcpy(bufferToReadFromDS, cmd, sizeof(SubModeId_e));

    // messageToReadfromDS->commandMsg=START_SESSION;

    //WifiProtocol_decodeData(bufferToReadFromDS,messageToReadfromDS,messageToReadfromDS->commandMsg);

    // assert_int_equal(messageToReadfromDS->sessionInformationMsg.sessionId,1);

    // assert_int_equal(messageToReadfromDS->sessionInformationMsg.modeId,SOC);

    // assert_int_equal(messageToReadfromDS->sessionInformationMsg.subModeId,CONTINUOUS);



/**

 * @brief Test de la fonction WifiProtocol_encodeToDSAppStoreBeginSession
 * 

 */






static const struct CMUnitTest tests[] = 
{
	cmocka_unit_test(WifiProtocol_decodeCommandSizeTest),
	cmocka_unit_test(WifiProtocol_encode),

};

int wifiprotocol_tests() 
{
	return cmocka_run_group_tests_name("Test de la classe wifiprotocol ", tests, setUp, tearDown);
}

