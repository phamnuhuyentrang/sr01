#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void main (int argc , char *argv[]) {

	FILE * fp;
	char c;
	while(1) {
		if(argc != 3) exit(EXIT_FAILURE);
	 	fp = fopen (argv[1], "r");
		if(fp == NULL) exit(EXIT_FAILURE);
		c = fgetc(fp);
		fclose(fp);
		if(c =='1') {
	        printf("[power manager] mise en veille en cours ...\n");
	         	/* ajoutez vos modification ici */
		 	fp = fopen (argv[1], "w"); 
		  	fputs("0", fp);
	   	  	fclose(fp);
			kill(getppid(), SIGUSR1);		//on n'envoie que SIGUSR1 de power_manager a ApplicationManager
	    }
	    sleep(atoi(argv[2]));
	}
}

