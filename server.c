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
	char nachricht[1024];
	struct sockaddr_in server, client;
	struct hostent	*host;
    
	//Prüfen der eingaben
	if(argc != 2) //Solange es nicht genau 1 Argument eingegeben wird, kommt diese Meldung (0te Argument)
    {
		printf("\n%s [Port-Id] \n\n", argv[0]);
		return EXIT_FAILURE;
	}
	
    //atoi: ASCII to Integer; Port wird in positive ganzzahl umgewandelt
    //falls Port negativ, gibt Fehlermeldung
	if(atoi(argv[1]) < 1) //gilt ab Port 1024 (incl.1024)
    {
		printf("\nPort Falsch angegeben!\n\n");
		return EXIT_FAILURE;
	}

	port = (unsigned) atoi(argv[1]); //erste Argument= unsigned int port
	
	printf("\nServer starten....\n\n");
	// Socket
	sock = socket(AF_INET,SOCK_STREAM,0); //Stream-Socket, mit IPv4, Protokolltyp 0

    //Wenn Socket erfolgreich erstellt gibt positive ganze Zahl zurück
	if(sock < 0)   
    {
		printf("\nSocket konnte nicht erzeugt werden!\n\n");
		return EXIT_FAILURE;
	}

	//Serveradresse wird konfiguriert
	server.sin_family = AF_INET; //IPv4 Verbindung
	server.sin_addr.s_addr = INADDR_ANY; //Server akzeptiert alle verfügbaren Netzwerkinterface
	server.sin_port = htons(port); //Port wird festgelegt
	
	//Port binden
	if(bind(sock,(struct sockaddr *)&server, sizeof(server)) < 0) //Socket wird an definierten Port gebunden
	{
		printf("\nDer Port konnte nicht an den Socket gebunden werden!\n\n");//sonst Fehlermeldung
		return EXIT_FAILURE;
	}
	printf("\nPort erfolgreich an den Socket gebunden\n\n");//Bestätigungsmeldung
	
	//Anfrage-Kapazität festlegen: maximal eine Client-verbindung
	listen(sock, 1);

	while(1)
    {
		//auf Verbindung warten, unendlich lange
		printf("\nWarten....\n\n");//Sagt das er wartet
		c = sizeof(struct sockaddr_in); //Größe struct sockaddr_in
		
		//Socket S-Client wird erstellt (Verbindung von client)
        //c: richtige Größe und Adresse von Socket in s_client kopiert
		s_client = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
		if (s_client < 0) //Verbindung erfolgreich?
		{
			printf("\nVerbindung mit client nicht erfolgreich!\n\n"); //Fehlermeldung
		}
		printf("\nVerbindung mit client erfolgreich\n\n"); //Bestätigungsmeldung
		
		//Nachricht von Client empfangen und in puffer Nachricht schreiben
        //recv gibt die Anzahl der Bytes zurück
		read = recv(s_client, nachricht, 1024, 0);
		if(read > 0) //Wenn Nachricht empfangen wird 
		{
			//Antwort
			printf("\nNchricht: %s\n", nachricht); //Nachricht ausgeben
			if(send(s_client ,"SERVER" ,strlen("SERVER") ,0) < 0) //Senden
            {
				printf("\nSenden Fehlgeschlagen!\n\n");
				return EXIT_FAILURE;
			}
			printf("\nSenden: SERVER\n"); //an Client "SERVER" senden
		}

        else if(read == 0) //Keine Nachricht mehr von Client
        {
			printf("\nVerbindung mit client Beendet\n\n");
		}

        else if(read == -1) //Schiefgelaufen
		{
			printf("\nNachricht fehlerhaft!\n\n");
			return EXIT_FAILURE;
		}
	}
	close(sock); //Schließt Verbindung
	return EXIT_SUCCESS;
}