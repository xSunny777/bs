#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BLOCKSIZE 128 //Macro Blocksize wird definiert

int main(int argc, char **argv)
{

    const char *new_file; //Zeiger auf Zeichenkette in der Dateiname gespeichert wird
    int fd;
    int n;
    char buffer[BLOCKSIZE]; //Zeichnepuffer(Array), der Blocksize Zeichen(128) speichern kann
    char *str; //Zeiger auf Zeichenkette in der Text gespeichert wird
    //void *puffer; 
    ssize_t size; //Größe text in Zeichen wird gespeichert
    off_t laenge; //Länge Datei in BYtes wird gespeichert

    //Geprüft, ob kein Dateiname eingegeben wurde
    if(argv[1] == NULL) 
    {
        printf("Bitte geben Sie die Argumente in dem Format [Dateiname] [Text] ein!\n\n");
    }

    //Wenn Dateiname angegeben wurde, wird Aurgument 1 in Nwe_File gespeichert
    else 
    {
        new_file = argv [1];
    } 

    //Falls nur Dateiname eingegebn, gibt Exit_Failure zurück
    if(argc < 2)
    { 
        return EXIT_FAILURE;
    }

    //Keinen Text eingegeben -> String wird auf leere Zeichenkette gesetzt
    if(argc < 3) 
    { 
        str = "";
    }

    //Wenn Dateiname und Text richtig eingegeben wurden, wird text string argument 2 zugewiesen
    else 
    { 
        str = argv[2]; 
    } 

    size = strlen(str); //Größe text wird in size gespeichert


    fd = open(new_file, O_RDWR); //Datei Nwe_File wird im Lese- Schreibmodus geöffnet

    //Wenn -1 -> Datei konnte nicht geöffnet werden
    if(fd == -1)
    { 
        perror("Fehler bei open ");

        return EXIT_FAILURE;
    }

    struct stat attribut; //Struct wird deklariert, um Informationen über die Datei zu erhalten
    stat(new_file, &attribut); //Informationen über Datei werden aufgerufen und in attribut gespeichert

    laenge = attribut.st_size; //Größe der Datei in Bytes wird in laenge gespeichert

    lseek(fd, 0, SEEK_END); //Um in Datei zu schreiben wird Dateizeiger ans Ende der Daetei bewegt

    //Lerrezeichen in der größe des Textes werden versucht in die Datei zu schreiben, um zu gucken, ob genug Platz ist
    if(write(fd, "                     ", size) !=size)
    { 
        perror("Fehler bei write()"); //Sonst gibt Fehler aus
    }

    //Leerzeichen von davor werden durch Text ersetzt
    if(write(fd, str, size) !=size)
    { 
        perror("Fehler bei write()"); //Sonst gibt Fehler aus
    }

    lseek(fd, 0, SEEK_SET); //Dateizeiger wird wieder auf Anfang der Datei gesetzt, um diese lesen zu können

    //Bis zu blocksize(128) Zeichen werden in den Buffer gelesen
    if((n = read(fd, buffer, BLOCKSIZE)) > 0)
    {
        printf("\nInhalt:\n\n%s\n\n", buffer); //Gelseene Zeichen in buffer werden hier ausgegeben
        return EXIT_SUCCESS;
    }

    else 
    { //Sonst Fehlermeldung
        printf("\nKein Inhalt in dieser Datei!\n\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}