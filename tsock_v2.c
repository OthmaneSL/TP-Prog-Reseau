/* librairie standard ... */
#include <stdlib.h>
/* pour getopt */
#include <unistd.h>
/* déclaration des types de base */
#include <sys/types.h>
/* constantes relatives aux domaines, types et protocoles */
#include <sys/socket.h>
/* constantes et structures propres au domaine UNIX */
#include <sys/un.h>
/* constantes et structures propres au domaine INTERNET */
#include <netinet/in.h>
/* structures retournées par les fonctions de gestion de la base de
données du réseau */
#include <netdb.h>
/* pour les entrées/sorties */
#include <stdio.h>
/* pour la gestion des erreurs */
#include <errno.h>


void construire_message(char *message, char motif, int lg) 
{
	int i;
	for (i=0;i<lg;i++) message[i] = motif;
}

void sourceUDP(int port, char * host, int nb_msg, int lg_msg)
{
	/* envoie des données */
    int sock;
    if ((sock=socket(AF_INET,SOCK_DGRAM,0)) ==-1) {
		printf("échec de creation de socket UDP\n");
    	exit(1);
	}

	/* Configuration */
	struct hostent *hp;
	struct sockaddr_in adr_distant;

	memset((char*)& adr_distant,0,sizeof(adr_distant));
	adr_distant.sin_family=AF_INET;
	adr_distant.sin_port=port;

	if (hp=gethostbyname(host)==NULL)
	{
		printf("erreur gethostbyname\n");
		exit(1);
	}
	memcpy((char*)&(adr_distant.sin_addr.s_addr),
			hp-> h_addr,
			hp->h_length);
	
	/* Construire le message */
	char * message = malloc(lg_msg*sizeof(char)); 
	construire_message(message, 'a', lg_msg);

	/* Envoie les données */
   	sendto(sock,message,lg_msg,0,,sizeof());
	/* Fermeture de la socket */
	if (close(sock)==-1) {	
		printf("échec de destruction de socket UDP\n");
    	exit(1);
	}	
}



void puitUDP()
{
	/* Recoit les données */

	/*creation du socket*/

	/*construction de l'adresse locale*/

	/*association de l'adresse locale*/

	/*reception du message*/
	
	/*destructio du socket*/
}
    

void main (int argc, char **argv)
{
	int c;
	extern char *optarg;
	extern int optind;
	int nb_message = -1; /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
	int source = -1 ; /* 0=puits, 1=source */
	int proto = -1; /* 0= UDP, 1=TCP*/
	int Port = atoi(argv[argc-1]);
	char *Host = "localhost";
	while ((c = getopt(argc, argv, "pn:us")) != -1) {
		switch (c) {
		case 'p':
			if (source == 1) {
				printf("usage: cmd [-p|-s][-n ##]\n");
				exit(1);
			}
			source = 0;
			break;

		case 's':
			if (source == 0) {
				printf("usage: cmd [-p|-s][-n ##]\n");
				exit(1) ;
			}
			source = 1;
			break;

		case 'n':
			nb_message = atoi(optarg);
			break;
		case 'u':
            proto=0;
            printf("on est en UDP\n");
            break;
            

		default:
			printf("usage: cmd [-p|-s][-n ##]\n");
			break;
		}
	}

	if (source == -1) {
		printf("usage: cmd [-p|-s][-n ##]\n");
		exit(1) ;
	}

	if (source == 1)
		printf("on est dans le source\n");
	else
		printf("on est dans le puits\n");

	if (nb_message != -1) {
		if (source == 1)
			printf("nb de tampons à envoyer : %d\n", nb_message);
		else
			printf("nb de tampons à recevoir : %d\n", nb_message);
	} else {
		if (source == 1) {
			nb_message = 10 ;
			printf("nb de tampons à envoyer = 10 par défaut\n");
		} else
		printf("nb de tampons à envoyer = infini\n");

	}
	if (proto ==0) {
		sourceUDP(Port,Host,1,3);
	}
}

