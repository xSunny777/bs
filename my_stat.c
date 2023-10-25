#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv){
	int fildes;
	struct stat buffer;
	int	status;
	if(argc != 2) {
			printf("Bitte geben Sie die Argumente in dem Format [Dateiname] ein!\n\n");
			return EXIT_FAILURE;
		}
	fildes = open(argv[1], O_RDWR);
	if(fildes == -1){
		perror("Fehler bei open ");
		return EXIT_FAILURE;
	}
	
	status = fstat(fildes, &buffer);
	if(status == -1){
		perror("Fehler beim auslesen ");
		return EXIT_FAILURE;
	}
	
	printf("ID of device containing file : %ld\n", buffer.st_dev);
	printf("inode number : %ld\n", buffer.st_ino);
	printf("protection : %d\n", buffer.st_mode);
	printf("number of hard links: %ld\n", buffer.st_nlink);
	printf("user ID of owner : %d\n", buffer.st_uid);
	printf("group ID of owner : %d\n", buffer.st_gid);
	printf("device ID : %ld\n", buffer.st_rdev);
	printf("File size : %ld\n", buffer.st_size);
	printf("blocksize : %ld\n", buffer.st_blksize);
	printf("number of 512B blocks allocated: %ld\n", buffer.st_blocks);
	printf("time of last access : %s\n",  asctime(localtime(&buffer.st_atime)));
	printf("time of last modification : %s\n", asctime(localtime(&buffer.st_mtime)));
	printf("time of last status change : %s\n", asctime(localtime(&buffer.st_ctime)));
	return EXIT_SUCCESS;
}