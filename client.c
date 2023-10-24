#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {

	int	sock;
	unsigned int port;
	struct sockaddr_in	server;
	struct hostent	*host;
    
	//Prüfen der eingaben
	if(argc != 3)
    {
		printf("\n%s [Namen des Zielrechners] [Port-Id] \n\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	if(atoi(argv[2]) < 1)
    {
		printf("\n Port Falsch angegeben!\n\n");
		return EXIT_FAILURE;
	}
	port = (unsigned) atoi(argv[2]);
	
	host = gethostbyname(argv[1]);

	if(host == NULL)    
    {
		printf("\n Host Falsch angegeben!\n\n");
		return EXIT_FAILURE;
	}

	// Socket
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)    
    {
		printf("\n Socket konnte nicht erzeugt werden!\n\n");
		return EXIT_FAILURE;
	}

	//sockaddr_in server Füllen
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	bcopy(host->h_addr, &server.sin_addr, host->h_length);

	//Verbindung herstellen
	if(connect(sock,(struct sockaddr*) &server,sizeof(server)) < 0)    
    {
		printf("\n Verbindung konnte nicht hergestellt werden!\n\n");
		return EXIT_FAILURE;
	}

	//Senden
	if( send(sock , "CLIENT" , strlen("CLIENT") , 0) < 0)
    {
		printf("\n Senden Fehlgeschlagen!\n\n");
		return EXIT_FAILURE;
	}
	printf("\nSenden: CLIENT\n");
	
	//Empfangen
	char antwort[2000];
	if( recv(sock , antwort , 2000 , 0) < 0)
    {
		printf("\n Empfangen Fehlgeschlagen!\n\n");
		return EXIT_FAILURE;
	}
	printf("\nAntwort: %s\n",antwort);
		
	close(sock);

	return EXIT_SUCCESS;
}