#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BLOCKSIZE 128

int main(int argc, char **argv){


    const char *new_file;
    int fd;
    int n;
    char buffer[BLOCKSIZE];
    char *str;
    void *puffer;
    ssize_t size;
    off_t laenge;

    if(argv[1] == NULL) {
    printf("Bitte geben Sie die Argumente in dem Format [Dateiname] [Text] ein!\n\n");
    }
    else {new_file = argv [1];}


    if(argc<2){
    return EXIT_FAILURE;
    }

    if(argc < 3) {
    str = "";
    }
    else { str = argv[2]; }

    size = strlen(str);


    fd = open(new_file, O_RDWR);

    if(fd== -1){
    perror("Fehler bei open ");

    return EXIT_FAILURE;
    }


    struct stat attribut;
    stat(new_file, &attribut);

    laenge = attribut.st_size;

    lseek(fd, 0, SEEK_END);

    if(write(fd, "                     ", size) !=size){
    perror("Fehler bei write()");
    }

    if(write(fd, str, size) !=size){
    perror("Fehler bei write()");
    }

    lseek(fd, 0, SEEK_SET);

    if((n = read(fd, buffer, BLOCKSIZE)) > 0){
        printf("\nInhalt:\n\n%s\n\n", buffer);
        return EXIT_SUCCESS;
        }
        else {
        printf("\nKein Inhalt in dieser Datei!\n\n");

    return EXIT_FAILURE;
    }


       return EXIT_SUCCESS;


}