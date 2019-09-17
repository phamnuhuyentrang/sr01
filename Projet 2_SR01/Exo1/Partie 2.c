#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main () {
	int f =0;
	while (f < 4){
		fork();
		f++;
	}
	//afficher le pid du processus et le pid de son père une seule fois
	printf("pid %d ppid %d \n",getpid(),getppid());
	return 0;
}