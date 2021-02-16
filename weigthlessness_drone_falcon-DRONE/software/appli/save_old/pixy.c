
/*
 * pixy.c
 *
 *  Created on: 8 févr. 2020
 *      Author: Arnaud & Pierre
 *      ESEO 2020
 *      Club ESEODRONE
 */

//https://docs.pixycam.com/wiki/doku.php?id=wiki:v1:porting_guide

///*** SPI CONFIGURATION BUS ***///
/*
Spi config :
-> Data envoyé du uC en "most significant bit first" = big endian
-> SCK bas si inactif
-> bits sont cadensés par les fronts montants de l'horloge
-> "Esclave" séléctionné par un état bas en SS
-> 3.3V en sortie, 5v tolérétion
-> Scutation pour recevoit data
-> Pixy envoie données en 16 bits en little endian (least significant bit first)
ex : si pixy doit envoyer 0xaa55, elle va envoyer 0x55 puis 0xaa (car 16 bits= 2 octets)

-> pour séparer deux trames consécutives, on utilise le "sync word" 0xaa55.
Cela signifie donc que une nouvelle image est envoyée par :
deux sync word 0xaa55 consécutifs
ou
0xaa55 puis 0xaa56 ce qui indique que l'image est un codebar couleur

IMPORTANT : SPI est un bus communiquant en simultané ; dc une fonction getByte() au lieu de
retourner une data recue, va prendre en param une data à envoyer en sortie
16 bits en big indian.
La communication SPI admet une queue circulaire


nucléo f407 SPI1 :
SS = GPIOA4
MOSI = GPIOA7
MISO = GPIOA6
SCK = GPIOA5

*/


///*** PROTOCOLE DE SERIE ***///
//issue de la doc
/*
BLOCK

Bytes    16-bit word    Description
----------------------------------------------------------------
0, 1     y              sync: 0xaa55=normal object, 0xaa56=color code object
2, 3     y              checksum (sum of all 16-bit words 2-6, that is, bytes 4-13)
4, 5     y              signature number
6, 7     y              x center of object
8, 9     y              y center of object
10, 11   y              width of object
12, 13   y              height of object

CAMERA LUMINOSITE (little indian)
Bytes    16-bit word   Description
----------------------------------------------------------------
0, 1     y             camera brightness sync (0xfe00)
2        n             brightness value

LED (little indian)
Bytes    16-bit word   Description
----------------------------------------------------------------
0, 1     y             LED sync (0xfd00)
2        n             red value
3        n             green value
4        n             blue value

*/

/*

On recoit des paquets de 16 bits





 */


#include "systick.h"
#include "pixy.h"
#include "stm32f4_gpio.h"


//*************************************
// VARIABLES ET DEFINE
//*************************************

#define PIXY_ARRAYSIZE              100
#define PIXY_NB_BLOCKS				3
#define PIXY_START_WORD             0xaa55 //
#define PIXY_START_WORD_CC          0xaa56
#define PIXY_START_WORDX            0x55aa
#define PIXY_SERVO_SYNC             0xff
#define PIXY_CAM_BRIGHTNESS_SYNC    0xfe
#define PIXY_LED_SYNC               0xfd
#define PIXY_SYNC_BYTE              0x5a
#define PIXY_SYNC_BYTE_DATA         0x5b

///PORTS SPI 1
#define SPI_CAM_PORT_SS  GPIOA
#define SPI_CAM_PIN_SS	GPIO_PIN_4
#define SPI_CAM_SS_SET()	HAL_GPIO_WritePin(SPI_CAM_PORT_SS, SPI_CAM_PIN_SS, 1)
#define SPI_CAM_SS_RESET()	HAL_GPIO_WritePin(SPI_CAM_PORT_SS, SPI_CAM_PIN_SS, 0)

#define SPI_CAM_PORT	GPIOA
#define SPI_CAM_PIN_MISO	GPIO_PIN_6
#define SPI_CAM_PIN_MOSI	GPIO_PIN_7
#define SPI_CAM_PIN_SCK		GPIO_PIN_5


//DATA
typedef enum
{
    NORMAL_BLOCK,
    CC_BLOCK // color code block
} BlockType_e;

typedef struct
{
  uint16_t signature;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t angle; // angle is only available for color coded blocks
} Block_t;


//COMMUNICATION EN ROUTINE

//static int send(uint8_t *data, int len);
//SPI émet comme il recoit donc besoin d'envoyer une routine avec un argument
//cette fonction est celle de la blibliothèque stm32f4_spi.h
//extern SPi_lib_getbyte(uint8_t out);


static int skipStart = 0;
static BlockType_e type_block; //declare var de type enumeration BlockType
static Block_t *point_blocks[PIXY_NB_BLOCKS]; //pointeur de structure type Block_t
//variables de la circulation de queue (en SPI circulation constante de données : cycle)


#define SEND_BUFFER_SIZE	128
typedef struct
{
	uint8_t datas[SEND_BUFFER_SIZE];
	uint8_t read_index;
	uint8_t write_index;
	uint16_t nb_datas;
}buffer_t;
static volatile buffer_t send_buffer;


static volatile uint32_t t = 0;
static uint16_t pixy_spi_exchange_word(void);
static void pixy_parse_msg(uint16_t word_received);
static uint8_t maj_datas_struct_normal_block(uint16_t word_receveid, Block_t *block_temp);
static int pixy_add_datas_to_send_in_buffer(uint8_t *data, int len);

void pixy_process_ms(void)
{
	uint16_t word16;
	uint8_t w = 1;
	pixy_add_datas_to_send_in_buffer(&w, 1);
	word16 = pixy_spi_exchange_word();
	pixy_parse_msg(word16);

	if(t)
		t--;



}

/*
void pixy_process_ms(void)
{
    uint16_t word16;
    do
    {
        word16 = pixy_spi_exchange_word();
        pixy_parse_msg(word16);

    }while(send_buffer.nb_datas > 0);

    if(t)
        t--;
}
*/
//*************************************
// PIXY INIT
//*************************************
void pixy_init(void)
{
	send_buffer.nb_datas = 0;
	send_buffer.read_index = 0;
	send_buffer.write_index = 0;
	Systick_add_callback_function(&pixy_process_ms);

	//point_blocks = (Block_t *)malloc(sizeof(Block_t)*PIXY_ARRAYSIZE);
	//Broche SS
	BSP_GPIO_PinCfg(SPI_CAM_PORT_SS,SPI_CAM_PIN_SS, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_MEDIUM, 0);
	SPI_CAM_SS_SET(); //mise Ã  Ã©tat haut

	//SPI1
	SPI_Init(SPINUM);
	//baudrate
	SPI_setBaudRate(SPINUM, SPI_BAUDRATEPRESCALER_256);
	//656kHz (168MHz / 256 comme prescaler)
}


//*************************************
// PIXY PROCESS MAIN
//*************************************
void pixy_process_main(void)
{
	uint8_t w = 0;
	pixy_add_datas_to_send_in_buffer(&w, 1);

	static bool_e blue = FALSE;
	//SetLED(1, 1, 0);


	if(!t)
	{
		t = 1000;
		blue = !blue;
		SetLED(1, 1, blue);
	}


}


//*************************************
// PIXY Fonctions de dialogue SPI
//*************************************

//Cette fonction declenche deux echanges d'octet :
// Si des donnees sont en attente d'envoi : elle envoit un octet de synchro + un octet de dataz
// Sinon, elle envoie un octet de synchro et un octet nul.
// Les deux octets recus lors de ces 2 echanges sont assembl�s en un mot sur 16 bits et renvoy�s en retour.

static uint16_t pixy_spi_exchange_word(void)
{
	//en big endian car Pixy envoie en 16 bits
	uint16_t data16_received;
	uint8_t data8;
	uint8_t first_data_to_send = 0;
	uint8_t second_data_to_send = 0;

	if (send_buffer.nb_datas) //si n'est pas vide
	{
		first_data_to_send = PIXY_SYNC_BYTE_DATA;
		second_data_to_send = send_buffer.datas[send_buffer.read_index];		//on consomme un octet dans le buffer circulaire
		send_buffer.nb_datas--;
		send_buffer.read_index = (send_buffer.read_index+1)%SEND_BUFFER_SIZE;
	}
	else
	{
		first_data_to_send = PIXY_SYNC_BYTE;
		second_data_to_send = 0;
	}

	SPI_CAM_SS_RESET(); //mise a l'etat bas pour que pixy ecoute

		SPI_WriteAndReadNoRegister(SPINUM, &data8, first_data_to_send);	//On envoie pixy sync byte pour dire qu'on a rien � envoyer.
		data16_received = data8;
		data16_received <<= 8;
		SPI_WriteAndReadNoRegister(SPINUM, &data8, second_data_to_send);
		data16_received |= data8;

	SPI_CAM_SS_SET();

	return data16_received;
}



//cette fonction doit �tre appel�e au niveau de pr�emption de la t�che de fond !
//retourne 0 si le message a ete correctement insere dans le buffer d'envoi.
static int pixy_add_datas_to_send_in_buffer(uint8_t *data, int len)
{
	int ret = 0;

	if(send_buffer.nb_datas + len < SEND_BUFFER_SIZE)
	{
		for(uint16_t i = 0; i<len; i++)
		{
			send_buffer.datas[send_buffer.write_index] = data[i];
			send_buffer.write_index = (send_buffer.write_index+1)%SEND_BUFFER_SIZE;
		}

		__disable_irq();
		//section critique non pr�emptible.
		send_buffer.nb_datas += len;	//on d�clare que l'on vient d'ajouter 'len' octets au buffer d'envoi.
		__enable_irq();

	}
	else
	{
		ret = 1;		//pas assez de place dans le buffer !
	}


	return ret;
}
/*
static int send(uint8_t *data, int len){
    //Si pas de place = renvoi -1, sinon renvoi la taille du buffer
    int i;
    uint8_t trash;
    uint8_t datatosend = PIXY_SYNC_BYTE_DATA;
    uint16_t received16;
    SPI_CAM_SS_RESET();

    for(i=0;i<len;i++)
    {
        SPI_WriteAndReadNoRegister(SPINUM, &trash, &datatosend);
        received16 = trash;
        received16 <<= 8; //décale de 8 bits car
        SPI_WriteAndReadNoRegister(SPINUM, &trash, &data[i]);
        received16 |= trash;
    }

    SPI_CAM_SS_SET();

    return len; //renvoi taille de la data à envoyer
}

uint16_t getWord()
{
  // ordering is big endian because Pixy is sending 16 bits through SPI
  uint16_t w;
  uint8_t c, cout = 0;

  if (g_outLen)
  {
    w = getByte(PIXY_SYNC_BYTE_DATA);
    cout = g_outBuf[g_outReadIndex++];
    g_outLen--;
    if (g_outReadIndex==PIXY_OUTBUF_SIZE)
      g_outReadIndex = 0;
  }
  else
    w = getByte(PIXY_SYNC_BYTE); // send out sync byte
  w <<= 8;
  c = getByte(cout); // send out data byte
  w |= c;

  return w;
}

*/



//*************************************
//
//*************************************




//*************************************
// PIXY GET START
//*************************************
static void pixy_parse_msg(uint16_t word_received)
{
	typedef enum
	{
		WAIT_START,
		WAIT_NORMAL_OR_COLOR_BLOCK,
		RECEIVE_BLOCK
	}state_e;
	static state_e state = WAIT_START;
	static state_e previous_state = WAIT_START;
	bool_e entrance = (state != previous_state)?TRUE:FALSE;
	previous_state = state;

	switch(state)
	{
		case WAIT_START:
			//SetLED(50, 50, 50);
			if(word_received == PIXY_START_WORD)
				//SetLED(50, 50, 50);

				state = WAIT_NORMAL_OR_COLOR_BLOCK;
			break;

		case WAIT_NORMAL_OR_COLOR_BLOCK:

			if(word_received == PIXY_START_WORD)//deux 0xAA55 de suite : bloc normal
			{
				type_block = NORMAL_BLOCK;
				state = RECEIVE_BLOCK;
			}
			else if(word_received == PIXY_START_WORD_CC)
			{
				type_block = CC_BLOCK;
				state = RECEIVE_BLOCK;
			}
			else if(word_received == PIXY_START_WORDX)
			{

			}
			else
				state = WAIT_START;
			break;
		case RECEIVE_BLOCK:

			if(type_block == NORMAL_BLOCK){
				static Block_t *block_temp;
				static uint8_t cmpt_blocks = 0;

				if(maj_datas_struct_normal_block(word_received, block_temp)){

					//point_blocks
					//cmpt_blocks++;
				}
			}
			break;

		default:  break;

	}
}

//*************************************
// MAJ DE DATA STRUCTURE BLOCK
//*************************************
static uint8_t maj_datas_struct_normal_block(uint16_t word_receveid, Block_t *block_temp){
		static uint8_t cmpt_data = 0;
		static uint32_t checksum = 0;
		static uint32_t sum = 0;

		switch (cmpt_data) {

			case 0:
				checksum = word_receveid;//première data qu'on recoit de la pixy
				cmpt_data++;
				break;
			case 1:
				*((uint16_t *)block_temp + cmpt_data-1) = word_receveid;
				sum += word_receveid;
				cmpt_data++;
				break;
			case 2:
				*((uint16_t *)block_temp + cmpt_data-1) = word_receveid;
				sum += word_receveid;
				cmpt_data++;
				break;
			case 3:
				*((uint16_t *)block_temp + cmpt_data-1) = word_receveid;
				sum += word_receveid;
				cmpt_data++;
				break;
			case 4:
				*((uint16_t *)block_temp + cmpt_data-1) = word_receveid;
				sum += word_receveid;
				cmpt_data++;
				break;
			case 5:
				*((uint16_t *)block_temp + cmpt_data-1) = word_receveid;
				sum += word_receveid;
				cmpt_data = 0;

				if(sum == checksum){
					return 1;
				}
				else{
					//(block_temp) -= 5;
					//((uint16_t *)block_temp) -= 5;
				}
				break;
			default: return 0; break;
		}
		return 0;
}





uint16_t pixyCam_getStart(void){

	uint16_t w, lastw;
	lastw = 0xffff;

	while(1){

		//w = getWord();
		if(w==0 && lastw==0){
			return 0; //pas de dÃ©part de code
		}
		else if(w==PIXY_START_WORD && lastw==PIXY_START_WORD){
			//Test si on a recu data qui coordonne les blocs
			type_block = NORMAL_BLOCK; //block normal
			return 1;
		}
		else if(w==PIXY_START_WORD_CC && lastw==PIXY_START_WORD){
			//Test si on recoit data qui coordonne les blocs couleurs
			type_block = CC_BLOCK; //block couleur
		}
		else if(w==PIXY_START_WORDX){
		//	SPI_WriteAndReadNoRegister(SPINUM,0,0);//attention...
		}

		lastw = w;
	}
}



//*************************************
// GET BLOCKS
//*************************************

uint16_t getBlocks(uint16_t maxBlocks){

	uint8_t i;
	uint16_t w, blockCount, checksum, sum;
	Block_t *block;

	if(!skipStart){
	 	if(pixyCam_getStart() == 0){
	 		return 0;
	 	}
	}
	else{
	 	skipStart = 0;
	}

	for(blockCount=0 ; blockCount<maxBlocks && blockCount<PIXY_ARRAYSIZE; ){
		checksum = getWord();
		if(checksum == PIXY_START_WORD){
			skipStart = 1;
			type_block = NORMAL_BLOCK;
			return blockCount;
		}
		else if(checksum == PIXY_START_WORD_CC){
			skipStart = 1;
			type_block = CC_BLOCK;
			return blockCount;
		}
		else if(checksum == 0){
			return blockCount;
		}
		block = point_blocks + blockCount;

		for(i=0, sum=0 ; i<sizeof(Block_t)/sizeof(uint16_t) ; i++ ){
			if(type_block == NORMAL_BLOCK && i>=5){
				block->angle = 0;
				break;
			}
			w = getWord();
			sum += w;
			*((uint16_t *)block + i) = w;
		}

		if(checksum == sum){
			blockCount++;
		}
		/*
		else{
			printf("checksum error")
		}
		*/

		w = getWord();
		if(w == PIXY_START_WORD){
			type_block = NORMAL_BLOCK;
		}
		else if(w == PIXY_START_WORD_CC){
			type_block = CC_BLOCK;
		}
		else{
			return blockCount;
		}
	}
	return 0;
}



//*************************************
// SET LEDS
//*************************************
int SetLED(unsigned char r, unsigned char g, unsigned char b)
{
  uint8_t outBuf[5];

  outBuf[0] = 0x00;
  outBuf[1] = PIXY_LED_SYNC;
  outBuf[2] = r;
  outBuf[3] = g;
  outBuf[4] = b;

  return pixy_add_datas_to_send_in_buffer(outBuf, 5);
}

//*************************************
//	SET SERVOS
//*************************************
int SetServos(uint16_t s0, uint16_t s1) {
	uint8_t outBuf[6];

	outBuf[0] = 0x00;
	outBuf[1] = PIXY_SERVO_SYNC;
	*(uint16_t *) (outBuf + 2) = s0;
	*(uint16_t *) (outBuf + 4) = s1;

	return pixy_add_datas_to_send_in_buffer(outBuf, 6);
}

//FIN CODE PIXY OFFICIEL
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
















