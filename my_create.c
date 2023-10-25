#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	//Verschiedene Berechtigung für Dateien 
	//IRUSR: Leserecht für Eigentümer
	//IWUSR: Schreibrecht für Eigentümer
	//IPGRP: Leserecht für Gruppe
	//IWFRP: Schreibrecht für Gruppe
	//IROTH: Leserecht für andere Benutzer
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

	//Deklaration
	const char *new_file; //Zeiger new_file
	int fd;
	ssize_t size; //size speichert Größe Text
	char *str;

	//Solange es nicht genau 2 Arguments eingegeben werden, kommt diese Meldung (0te Argument)
	if(argc != 3) 
	{
		printf("Bitte geben Sie die Argumente in dem Format [Dateiname] [Text] ein!\n\n");
		return EXIT_FAILURE;
	}

	//Die erste Eingabe wird als die Dateiname (Char) gespeichert
	//Die zweite Eingabe wird als Text (String) gespeichert
	else 
	{
		new_file = argv [1];
		str = argv[2]; 
	}

	//size initialisieren mit der Länge des Strings
	size = strlen(str);

	//Datei wird geöffnet
	//Pointer new_file: Dateiname
	//O_RDWR: Datei kann gelesen und geschrieben werden
	//O_EXCL: sicherstellt, ob eine Datei mit demselben Namen vorhanden ist; Wenn bereits vorhanden, Fehler
	//O_CREAT: Datei erstellen
	//mode: Berechtigung der Datei festlegen
	fd = open(new_file, O_RDWR | O_EXCL | O_CREAT, mode);

	//Fehlercode (-1) weil Datei nicht geöffnet werden kann
	if(fd == -1)
	{
		perror("Fehler bei open ");
		//Fehlernummer wird in der erstellten Datei ausgegeben
		fprintf(stderr, "%s\n", strerror(errno)); //errno: Fehlernummer; stderr: Dateideskriptor 2 für Fehlerausgabe
		return EXIT_FAILURE;
	}

	//vergleicht ob Text verloren gegangen ist 
	if(write(fd, str, size) !=size)
	{
		perror("Fehler bei write()");
		fprintf(stderr, "%s\n", strerror(errno));
	}

	return EXIT_FAILURE;
}