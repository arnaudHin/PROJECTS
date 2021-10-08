/**
 * @file : InterCoreProtocol.h
 * @brief :
 * @version
 * @date : May 28, 2021
 * @author: Arnaud
 */


#include "commun.h"


//////////////////////////////////////////////////////////////////////////////////
//				Prototypes de fonctions Publiques		//
//////////////////////////////////////////////////////////////////////////////////


/**
 * @fn void InterCodeProtocol_encodeMessage(uint8_t*, S_MessageToWrite_t*)
 * @brief
 * @param buffer
 * @param msg
 */
extern void InterCoreProtocol_encodeMessage(uint8_t * buffer, S_MessageToWrite_t * msg);



/**
 * @fn void InterCodeProtocol_decodeMessage(uint8_t*, S_MessageToRead_t*)
 * @brief
 * @param buffer
 * @param msg
 */
extern void InterCoreProtocol_decodeMessage(uint8_t * buffer, S_MessageToRead_t * msg, uint16_t sizeToDecode);
