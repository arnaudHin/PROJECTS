/**
 * @file PostmanDSMonitorSupervisor.c
 * @brief Ce fichier reçoit et envoie des messages sur les cannaux de 
 * 		  Communication Intercoeur.
 * @date Mai 2021
 * @authors Robin
 * @version 1.0
 */

#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>
#include <termios.h>
#include <signal.h>
#include <assert.h>
#include <pthread.h>

#include "IntercoreProtocol.h"
#include "PostmanDSMonitorSupervisor.h"

//////////////////////////////////////////////////////////////////////////////
//								Structures									//
//////////////////////////////////////////////////////////////////////////////

enum {RET_CODE_BASE = -20};

/**
 * @brief Structure des codes retournés par le Port de Communication.
 */
typedef enum
{
	RET_OK = 0,
	RET_ERR_UNKNOWN_BAUD = RET_CODE_BASE,
	RET_ERR_OPEN	= RET_CODE_BASE -1,
	RET_ERR_CLOSE	= RET_CODE_BASE -2,
	RET_ERR_SET_TTY	= RET_CODE_BASE -3,
} enComPortRet;

//////////////////////////////////////////////////////////////////////////////
//								Variables									//
//////////////////////////////////////////////////////////////////////////////

static int16_t fileDescriptor0;	// Le port série fd0
static int16_t fileDescriptor1;	// Le port série fd1
static char *portName0;	// Le pointeur du port série à associer
static char *portName1;	// Le pointeur du port série à associer

static uint8_t bufferAsk[MIN_ASK_MSG];

static pthread_mutex_t mutexWrite;	//Création du mutex

//////////////////////////////////////////////////////////////////////////////
//						Prototypes fonctions privées						//
//////////////////////////////////////////////////////////////////////////////

/**
 * Fonction ttyConfig PostmanDSMS
 * 
 * @brief	Configure le port série passé en paramètre du TeleTYpewriter (TTY).
 * 
 * @param fd : le descripteur de fichier pour le port série Unix à configurer
 * @param speed : la vitesse de transmission du port série
 * @param parity : le bit de parité
 * 
 * @return RET_OK si tout s'est bien déroulé
 */
static uint16_t PostmanDSMS_ttyConfig(uint16_t fd, uint32_t speed, uint8_t parity);

/**
 * Fonction baudrateToUnix PostmanDSMS
 * 
 * @brief	Convertit la valeur de vitesse de transmission passée en paramètre 
 * 			en valeur compréhensible par le TTY.
 * 
 * @param speed : la vitesse de transmission du port série à convertir
 * @return la vitesse convertie en valeur lisible par le TTY
 */
static uint32_t PostmanDSMS_baudrateToUnix(uint32_t speed);

/**
 * Fonction setBlocking PostmanDSMS
 * 
 * @brief	Configure le blocage du port série ou non en fonction du 2e parametre.
 * 
 * @param fd : le descripteur de fichier pour le port série Unix à configurer
 * @param speed : la variable qui indique si oui on non on doit bloquer
 */
static void PostmanDSMS_setBlocking (uint16_t fd, uint8_t should_block);

//////////////////////////////////////////////////////////////////////////////
//							Fonctions publiques								//
//////////////////////////////////////////////////////////////////////////////

void PostmanDSMS_new()
{
	portName0 = "/dev/ttyRPMSG0";	// Le pointeur du port série à associer
	portName1 = "/dev/ttyRPMSG1";	// Le pointeur du port série à associer

int check = pthread_mutex_init(&mutexWrite, NULL);
	if (check == -1){
		int codeErreur = errno;
	}
}

void PostmanDSMS_start()
{

	/* Ouverture des ports série */
	fileDescriptor0 = open(portName0, O_RDWR | O_NOCTTY | O_SYNC);
	if (fileDescriptor0 < 0)
	{
		perror("Impossible d'ouvrir le port série.\n");
		fprintf(stderr, "%s\n", portName0);
		exit(errno);
	}

	fileDescriptor1 = open(portName1, O_RDWR | O_NOCTTY | O_SYNC);
	if (fileDescriptor1 < 0)
	{
		perror("Impossible d'ouvrir le port série.\n");
		fprintf(stderr, "%s\n", portName1);
		exit(errno);
	}


	/* Configuration pour fd0 : de la vitesse à 115200 bps, 8n1 (pas de bit de parité) et pas de blocage */
	PostmanDSMS_ttyConfig (fileDescriptor0, 115200, 0);
	PostmanDSMS_setBlocking (fileDescriptor0, 0);

	/* Configuration pour fd1 : de la vitesse à 115200 bps, 8n1 (pas de bit de parité) et pas de blocage */
	PostmanDSMS_ttyConfig (fileDescriptor1, 115200, 0);
	PostmanDSMS_setBlocking (fileDescriptor1, 0);

}

void PostmanDSMS_stop()
{
	
	/* Fermeture des ports série */
	close(fileDescriptor0);
	close(fileDescriptor1);

}

void PostmanDSMS_free()
{

}

void PostmanDSMS_read(uint8_t *bufferToRead, uint16_t sizeToRead)
{
	if(sizeToRead == MIN_ASK_MSG){
		/* Initialisation et configuration du message ASK_NEW_MSG à envoyer */	
		uint8_t * cmd = calloc(1, sizeof(uint8_t));
		*cmd = (uint8_t) ASK_NEW_MSG;
		memcpy(bufferAsk, cmd, sizeof(uint8_t));
		free(cmd);

		Size * size = calloc(1, sizeof(Size));
		*size = (Size) 0;
		memcpy(bufferAsk + sizeof(uint8_t), size, sizeof(Size));
		free(size);

		/* Ecriture sur le Canal 1 réservé à l'envoi de ASK_MA et ASK_SBC */
		ssize_t writeNb = write (fileDescriptor1, bufferAsk, MIN_ASK_MSG);
		usleep ((sizeof(bufferAsk) + 25) * MIN_ASK_MSG);
		
		/* Lecture sur le Canal 1 réservé à la réception de ACK_NO_MA, ACK_MA, ACK_SBC_KO et ACK_SBC_OK */
		ssize_t readNb = read (fileDescriptor1, bufferToRead, sizeToRead);
	}


	else if (sizeToRead > MIN_ASK_MSG) {
		ssize_t readNb = read (fileDescriptor1, bufferToRead, sizeToRead);
	}
	else{
		
	}

}

void PostmanDSMS_write(uint8_t *bufferToWrite, uint16_t sizeToWrite)
{
	pthread_mutex_lock(&mutexWrite); // Blocage des variables modifiées par ce thread

	/* Initialisation du message ACK à recevoir */
	uint8_t bufferAck[MIN_ACK_MSG];
	
	/* Ecriture sur le Canal 0 réservé à l'envoi d'ordres directs : ASK_START, ASK_STOP */
	ssize_t n = write (fileDescriptor0, bufferToWrite, sizeToWrite);
	usleep ((sizeof(bufferToWrite) + 25) * sizeToWrite);
	if (n == -1){
		int codeErreur = errno;
	}

	/* Lecture sur le Canal 0 réservé à la réception de ACK_START, ACK_STOP */
	n = read (fileDescriptor0, bufferAck, MIN_ACK_MSG);
	if (n == -1){
		int codeErreur = errno;
	}
	pthread_mutex_unlock(&mutexWrite); //Déblocage des variables bloquées
}

//////////////////////////////////////////////////////////////////////////////
//							Fonctions privées								//
//////////////////////////////////////////////////////////////////////////////

static uint16_t PostmanDSMS_ttyConfig(uint16_t fd, uint32_t speed, uint8_t parity)
{
	struct termios tty;

	if (tcgetattr(fd, &tty) != 0)
	{
		return -1;
	}

	uint32_t unix_speed = PostmanDSMS_baudrateToUnix(speed);

	cfsetispeed(&tty, unix_speed);
	cfsetospeed(&tty, unix_speed);

	/* Init 8,N,1 */
	tty.c_cflag |= (CLOCAL | CREAD);    // ignore les contrôles modem
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= CS8;         // caractères en 8-bit
	tty.c_cflag &= ~PARENB;     // pas de bit de parité
	tty.c_cflag &= ~CSTOPB;     // un seul stop bit
	tty.c_cflag &= ~CRTSCTS;    // pas de gestion de flux matérielle

	/* Init pour mode non-canonique  */
	tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	tty.c_oflag &= ~OPOST;

	/* Init pour lire les octets dès qu'ils sont dispos */
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 1;

	if (tcsetattr(fd, TCSANOW, &tty) != 0)
	{
		return -1;
	}

	return RET_OK;
}

static uint32_t PostmanDSMS_baudrateToUnix(uint32_t speed)
{
	uint32_t unix_speed;

	switch (speed)
	{
		case 50: unix_speed = B50; break;
		case 75: unix_speed = B75; break;
		case 110: unix_speed = B110; break;
		case 134: unix_speed = B134; break;
		case 150: unix_speed = B150; break;
		case 300: unix_speed = B300; break;
		case 600: unix_speed = B600; break;
		case 1200: unix_speed = B1200; break;
		case 1800: unix_speed = B1800; break;
		case 2400: unix_speed = B2400; break;
		case 4800: unix_speed = B4800; break;
		case 9600: unix_speed = B9600; break;
		case 19200: unix_speed = B19200; break;
		case 38400: unix_speed = B38400; break;
		case 57600: unix_speed = B57600; break;
		case 115200: unix_speed = B115200; break;
		case 230400: unix_speed = B230400; break;
		case 460800: unix_speed = B460800; break;
		case 500000: unix_speed = B500000; break;
		case 576000: unix_speed = B576000; break;
		case 921600: unix_speed = B921600; break;
		case 1000000: unix_speed = B1000000; break;
		case 1152000: unix_speed = B1152000; break;
		case 1500000: unix_speed = B1500000; break;
		case 2000000: unix_speed = B2000000; break;
		case 2500000: unix_speed = B2500000; break;
		case 3000000: unix_speed = B3000000; break;
		case 3500000: unix_speed = B3500000; break;
		case 4000000: unix_speed = B4000000; break;
		default: unix_speed = -1; break;
	}
	return unix_speed;
}

static void PostmanDSMS_setBlocking (uint16_t fd, uint8_t should_block)
{
		struct termios tty;
		memset (&tty, 0, sizeof tty);
		if (tcgetattr (fd, &tty) != 0)
		{
			//TRACE ("Erreur %d depuis tggetattr\n", errno);
			return;
		}

		tty.c_cc[VMIN]  = should_block ? 1 : 0;
		tty.c_cc[VTIME] = 5;	// 0,5 seconde de délai de lecture 

		if (tcsetattr (fd, TCSANOW, &tty) != 0){
			//TRACE ("Erreur %d de mise en place des attributs\n", errno);
		}
}
