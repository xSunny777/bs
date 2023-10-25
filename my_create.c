#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv){

	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

	const char *new_file;
	int fd;
	ssize_t size;
	char *str;

	if(argc != 3) {
		printf("Bitte geben Sie die Argumente in dem Format [Dateiname] [Text] ein!\n\n");
		return EXIT_FAILURE;
	}
	else {new_file = argv [1];}

	if(argc < 3) {
		str = "";
	}
	else { str = argv[2]; }

	size = strlen(str);

	fd = open(new_file, O_RDWR | O_EXCL | O_CREAT, mode);

	if(fd== -1){
		perror("Fehler bei open ");
		fprintf(stderr, "%s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if(write(fd, str, size) !=size){
		perror("Fehler bei write()");
		fprintf(stderr, "%s\n", strerror(errno));
	}


	return EXIT_FAILURE;


}
