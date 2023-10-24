#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

	char string[100];
	int statval;
	while(1){
		printf("\n");
		printf("\n");
		printf("Kommando: ");
		scanf("%s",string);
		if(strcmp(string, "q") == 0){
			return EXIT_SUCCESS;
		}
		printf("\n");
		errno = 0;
		int id;
		if((id = fork()) > 0){
			wait(&statval);
			printf("\n");
                	printf("\n");
			printf("Vater: \n");
			printf("res: %d errno: %d; status: %d", id, errno, WEXITSTATUS(statval));
		}else{
			printf("Sohn: \n");
			char *args[] = {"",NULL};
			int s = execv(string, args);
			printf("res: %d; errno: %d",s, errno);
			exit(s);
		}
	}


   return EXIT_SUCCESS;
}
