#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc , char *argv[])
{
	int	sock, s_client, c, read;
	unsigned int port;
	char nachricht[2000];
	struct sockaddr_in	server, client;
	struct hostent	*host;
    
	//Prüfen der eingaben
	if(argc != 2)    
    {
		printf("\n%s [Port-Id] \n\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	if(atoi(argv[1]) < 1)
    {
		printf("\nPort Falsch angegeben!\n\n");
		return EXIT_FAILURE;
	}
    
	port = (unsigned) atoi(argv[1]);
	
	printf("\nServer starten....\n\n");
	// Socket
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)   
    {
		printf("\nSocket konnte nicht erzeugt werden!\n\n");
		return EXIT_FAILURE;
	}

	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);
	
	//Port binden
	if(bind(sock,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		printf("\nDer Port konnte nicht an den Socket gebunden werden!\n\n");
		return EXIT_FAILURE;
	}
	printf("\nPort erfolgreich an den Socket gebunden\n\n");
	
	//Anfrage-Kapazität festlegen
	listen(sock, 1);
	while(1)
    {
		//auf Verbindung warten
		printf("\nWarten....\n\n");
		c = sizeof(struct sockaddr_in);
		
		//Verbindung von client
		s_client = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
		if (s_client < 0)
		{
			printf("\nVerbindung mit client nicht erfolgreich!\n\n");
		}
		printf("\nVerbindung mit client erfolgreich\n\n");
		
		//Nachricht von Client
		read = recv(s_client, nachricht, 2000, 0);
		if(read > 0 )
		{
			//Antwort
			printf("\nNchricht: %s\n", nachricht);
			if( send(s_client , "SERVER" , strlen("SERVER") , 0) < 0)
            {
				printf("\nSenden Fehlgeschlagen!\n\n");
				return EXIT_FAILURE;
			}
			printf("\nSenden: SERVER\n");
		}

        else if(read == 0)
        {
			printf("\nVerbindung mit client Beendet\n\n");
		}

        else if(read == -1)
		{
			printf("\nNachricht fehlerhaft!\n\n");
			return EXIT_FAILURE;
		}
	}
	close(sock);
	return EXIT_SUCCESS;
	
}