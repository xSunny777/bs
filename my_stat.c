#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
	int fildes;
	struct stat buffer; //Struktur wird dekklariert, um Informationen über Datei abzurufen
	int	status;

	//Falls Nicht genau ein Argument angegeben, gibt Fehlermeldung aus
	if(argc != 2) 
	{ 
			printf("Bitte geben Sie die Argumente in dem Format [Dateiname] ein!\n\n");
			return EXIT_FAILURE;
	}

	fildes = open(argv[1], O_RDWR); //öffnet Datei im Argument1 im Lese- Schreibemodus

	//Falls öffnen Datei fehlschlägt, gibt Fehlermldung aus
	if(fildes == -1)
	{  
		perror("Fehler bei open ");
		return EXIT_FAILURE;
	}
	
	status = fstat(fildes, &buffer); //fstat wird aufgerufen, um Informationen über Datei zu bekommen
	
	//Falls aufrufen Dateiinformationen fehlschlägt -> gibt Fehlermeldung
	if(status == -1)
	{
		perror("Fehler beim auslesen ");
		return EXIT_FAILURE;
	}
	
	//Hier werden die verschiedenen aufgerufenen Dateiinformationen von fstat ausgegeben
	printf("ID of device containing file : %ld\n", buffer.st_dev); //ID des Gerätes
	printf("inode number : %ld\n", buffer.st_ino); //Inode-Nummer der Datei (Kennung)
	printf("protection : %d\n", buffer.st_mode); //Schutzmodus der Datei
	printf("number of hard links: %ld\n", buffer.st_nlink); //Anzahl harter Links zur Datei
	printf("user ID of owner : %d\n", buffer.st_uid); //Benutzer ID des Eigentümers der Datei
	printf("group ID of owner : %d\n", buffer.st_gid); //Gruppen-ID des Eigentümers der Datei
	printf("device ID : %ld\n", buffer.st_rdev); //Geräte ID
	printf("File size : %ld\n", buffer.st_size); //Dateigröße in Bytes
	printf("blocksize : %ld\n", buffer.st_blksize); //Blockgröße des Dateisystems
	printf("number of 512B blocks allocated: %ld\n", buffer.st_blocks); //Anzahl der 512Byte Blöcke, die der Datei zugewiesen sind
	printf("time of last access : %s\n",  asctime(localtime(&buffer.st_atime))); //Zeit des letzen Zugriffs //Asctime stellt Zeit für Menschen lesbra da
	printf("time of last modification : %s\n", asctime(localtime(&buffer.st_mtime))); //Zeit der letzen ÄNderung der Datei
	printf("time of last status change : %s\n", asctime(localtime(&buffer.st_ctime))); //Zeit der letzen Statusänferun der Datei
	return EXIT_SUCCESS;
}