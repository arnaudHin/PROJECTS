#include <stdio.h>
#include <stdlib.h>

#include "WifiProtocol.h"
#include "../common.h"

static M_MessageAnswer_t myMessageAnswer;
static uint8_t * myDataBufferToWrite;

extern void ProxyMeasuresProcessorApp_storeMeasuresArray(M_DataAnswer_t * data)
{
    uint16_t sizeMessage;
    uint32_t size = 61; //61
    
    myMessageAnswer.command = STORE_MA;
    myMessageAnswer.size = size;  

    myMessageAnswer.dataToRead = *data;
    myMessageAnswer.dataToRead.sensorNb = 6;

    sizeMessage = sizeof(uint8_t) + sizeof(uint16_t) + myMessageAnswer.size;
    myDataBufferToWrite = calloc(1, sizeMessage);

    WifiProtocol_encodeToDSAppStoreMeasuresArray(myDataBufferToWrite, &myMessageAnswer); 

    PostmanDSMonitorApp_write(myDataBufferToWrite, sizeMessage);

    free(myDataBufferToWrite);
}