#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv){

	if(argc != 2) {
		printf("Bitte geben Sie die Argumente in dem Format [Dateiname] ein!\n\n");
		return EXIT_FAILURE;
	}
	int c;
	FILE *file;
	file = fopen(argv[1], "r");
	if (file) {
		printf("\n");
    		while ((c = getc(file)) != EOF){
        		putchar(c);	
    		}
    		fclose(file);
    		printf("\n");
	}else{
		perror("Fehler bei open ");
		fprintf(stderr, "%s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}