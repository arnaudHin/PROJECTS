/**
 * @file : PostmanSupervisor.c
 * @brief :
 * @version
 * @date : May 28, 2021
 * @author: Arnaud
 */

#include "virt_uart.h"
#include <stdbool.h>
#include <string.h>
#include "commun.h"
#include "utils/IPCC.h"
#include "utils/GPIOS.h"
#include "openamp.h"
#include "comSupervisor/PostmanSupervisor.h"
#include "comSupervisor/DispatchSupervisor.h"
#include "processorSupervisor/MeasuresProcsessorSupervisor.h"
#include "comSupervisor/InterCoreProtocol.h"

#define MAX_BUFFER_SIZE 512



//////////////////////////////////////////////////////////////////////////////////
//				Structures					//
//////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////
//				Variables Privées				//
//////////////////////////////////////////////////////////////////////////////////

static VIRT_UART_HandleTypeDef huart0;
static VIRT_UART_HandleTypeDef huart1;

static __IO FlagStatus VirtUart0RxMsg = RESET;
static uint8_t VirtUart0ChannelBuffRx[MAX_BUFFER_SIZE];
static uint16_t VirtUart0ChannelRxSize = 0;

static __IO FlagStatus VirtUart1RxMsg = RESET;
static uint8_t VirtUart1ChannelBuffRx[MAX_BUFFER_SIZE];
static uint16_t VirtUart1ChannelRxSize = 0;

//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Privées			//
//////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////
//				Fonctions Publiques				//
//////////////////////////////////////////////////////////////////////////////////
extern bool PostmanSupervisor_Recept(){

	OPENAMP_check_for_message();

	if(VirtUart0RxMsg || VirtUart1RxMsg){
	    //TOGGLE_LED(LED6_RED);
		return true;
	}
	return false;
}

extern DavidsonStatus_e PostmanSupervisor_Init(){

	DavidsonStatus_e status = DAV_ERROR;

	status = IPCC_Init();
	if(status != DAV_OK){
	    return status;
	}

	status = (DavidsonStatus_e) MX_OPENAMP_Init(RPMSG_REMOTE, NULL);
	if(status != DAV_OK){
	    return status;
	}

	if (VIRT_UART_Init(&huart0) != VIRT_UART_OK) {
	    return DAV_ERROR;
	}

	if (VIRT_UART_Init(&huart1) != VIRT_UART_OK) {
	    return DAV_ERROR;
	}

	/*Need to register callback for message reception by channels*/
	if(VIRT_UART_RegisterCallback(&huart0, VIRT_UART_RXCPLT_CB_ID, VIRT_UART0_RxCpltCallback) != VIRT_UART_OK){
	    return DAV_ERROR;
	}
	if(VIRT_UART_RegisterCallback(&huart1, VIRT_UART_RXCPLT_CB_ID, VIRT_UART1_RxCpltCallback) != VIRT_UART_OK)
	{
	    return DAV_ERROR;
	}

	return DAV_OK;
}


extern void PostmanSupervisor_Write(uint8_t * buffer, uint16_t bytesToSend){

	VirtUart1ChannelRxSize = bytesToSend; //Taille Vuart buffer
	memcpy(VirtUart1ChannelBuffRx, buffer, bytesToSend); //Allocation mémoire Vuart buffer

	VIRT_UART_Transmit(&huart1, VirtUart1ChannelBuffRx, VirtUart1ChannelRxSize); //Transsmission Vuart
}

extern void PostmanSupervisor_Read(uint8_t * buffer, uint16_t bytesToRead){

	/*Canal 0 : Demande de nouveaux messages (START / STOP) */
	if (VirtUart0RxMsg) {

		memcpy(buffer, VirtUart0ChannelBuffRx, bytesToRead);

		if( bytesToRead <= 3 && (*VirtUart0ChannelBuffRx) == 1 ){

		    VirtUart0ChannelRxSize = 3;
		    VIRT_UART_Transmit(&huart0, VirtUart0ChannelBuffRx, VirtUart0ChannelRxSize);
		}
		else if(bytesToRead <= 3){

		    VirtUart0ChannelRxSize = 3;
		    VIRT_UART_Transmit(&huart0, VirtUart0ChannelBuffRx, VirtUart0ChannelRxSize);
		    VirtUart0RxMsg = RESET;
		}
		else{

		    VirtUart0RxMsg = RESET;
		}
	}

	/* Canal 1 : Demande de nouveaux messages (MA et SB) */
	else if (VirtUart1RxMsg) {

		VirtUart1RxMsg = RESET;

		memcpy(buffer, VirtUart1ChannelBuffRx, bytesToRead);
	}

}


void VIRT_UART0_RxCpltCallback(VIRT_UART_HandleTypeDef *huart)
{
    /* copy received msg in a variable to sent it back to master processor in main infinite loop*/
    VirtUart0ChannelRxSize = huart->RxXferSize < MAX_BUFFER_SIZE? huart->RxXferSize : MAX_BUFFER_SIZE-1;
    memcpy(VirtUart0ChannelBuffRx, huart->pRxBuffPtr, VirtUart0ChannelRxSize);
    VirtUart0RxMsg = SET;
}

void VIRT_UART1_RxCpltCallback(VIRT_UART_HandleTypeDef *huart)
{
    /* copy received msg in a variable to sent it back to master processor in main infinite loop*/
    VirtUart1ChannelRxSize = huart->RxXferSize < MAX_BUFFER_SIZE? huart->RxXferSize : MAX_BUFFER_SIZE-1;
    memcpy(VirtUart1ChannelBuffRx, huart->pRxBuffPtr, VirtUart1ChannelRxSize);
    VirtUart1RxMsg = SET;
}








