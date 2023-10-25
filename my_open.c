#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	//Solange es nicht genau 1 Arguments eingegeben werden, kommt diese Meldung (0te Argument)
	if(argc != 2) 
	{
		printf("Bitte geben Sie die Argumente in dem Format [Dateiname] ein!\n\n");
		return EXIT_FAILURE;
	}

	int c;
	FILE *file;
	//Lesemodus, öffnet die Datei (Argument 1)
	file = fopen(argv[1], "r");

	//Überprüft, ob das Öffnen der Datei erfolgreich war
	//file zeigt auf die Dateiname 
	if (file) 
	{
		printf("\n");
			//Solange es noch Zeichen gibt, gibt er die aus
    		while ((c = getc(file)) != EOF)
			{
        		putchar(c);	
    		}
			//file close
    		fclose(file);
    		printf("\n");
	}
	
	//Fehlermeldung; file zeigt auf NULL
	else
	{
		perror("Fehler bei open "); //Fehlermeldung auf stderr
		fprintf(stderr, "%s\n", strerror(errno)); ////Fehlernummer wird in der erstellten Datei ausgegeben
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}