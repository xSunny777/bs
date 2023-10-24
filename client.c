#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> //includiert gethostbyname  &  getaddrinfo
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUF_SIZE 1024 //Legt größe puffer für daten fest 
int main(int argc, char *argv[]) {

	int	sock;
	unsigned int port;
	struct sockaddr_in server;
	struct hostent *host;
    
	//Prüfen der eingaben
	if(argc != 3) //Solange es nicht genau 2 Arguments eingegeben werden, kommt diese Meldung (0te Argument)
    {
		printf("\n%s [Namen des Zielrechners] [Port-Id] \n\n", argv[0]); 
		return EXIT_FAILURE;
	}
	
    //atoi: ASCII to Integer; Port wird in positive ganzzahl umgewandelt
    //falls Port negativ, gibt Fehlermeldung
	if(atoi(argv[2]) < 1) 
    {
		printf("\n Port Falsch angegeben!\n\n"); //Wenn port ungültig wird Fehlermeldung ausgegeben
		return EXIT_FAILURE;
	}
	port = (unsigned) atoi(argv[2]); //zweite Argument= unsigned int port
	
	host = gethostbyname(argv[1]); //Funktion wandelt Hostname in IP Adresse um

	if(host == NULL)    //Falls der Hostname nicht umgewandelt werden kann wird Fehlrmeldung ausgegeben
    {
		printf("\n Host Falsch angegeben!\n\n");
		return EXIT_FAILURE;
	}

	// Socket
    //stellt Verbindung zum Server her
	sock = socket(AF_INET,SOCK_STREAM,0); //Stream-Socket, mit IPv4, Protokolltyp 0
    
    //Wenn Socket erfolgreich erstellt gibt positive ganze Zahl zurück
	if(sock < 0)    
    {
		printf("\n Socket konnte nicht erzeugt werden!\n\n");
		return EXIT_FAILURE;
	}

	//Serveradresse wird konfiguriert
	server.sin_family = AF_INET; //IPv4 Verbindung
	server.sin_port = htons(port); //benutze Port 
	bcopy(host->h_addr, &server.sin_addr, host->h_length); //IP-Adresse Zielrechner Client wird in Struktur Server kopiert

	//Verbindung herstellen
	if(connect(sock,(struct sockaddr*) &server,sizeof(server)) < 0)    
    {
		printf("\n Verbindung konnte nicht hergestellt werden!\n\n"); //Gibt Fehlermeldung wenn fehlschlägt
		return EXIT_FAILURE;
	}

	//Senden
	if(send(sock ,"CLIENT" ,strlen("CLIENT") , 0) < 0)
    {
		printf("\n Senden Fehlgeschlagen!\n\n");
		return EXIT_FAILURE;
	}
	printf("\nSenden: CLIENT\n");
	
	//Empfangen
	char antwort[BUF_SIZE]; //Max Größe char
	if(recv(sock ,antwort ,BUF_SIZE ,0) < 0) //Wenn keine Nachricht ankommt, gibt Fehlermeldung
    {
		printf("\n Empfangen Fehlgeschlagen!\n\n");
		return EXIT_FAILURE;
	}
	printf("\nAntwort: %s\n",antwort);
		
	close(sock); //Schließt Verbindung

	return EXIT_SUCCESS;
}