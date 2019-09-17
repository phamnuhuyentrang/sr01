#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct application{
  char name[100];
  char path[100];
  int nbArg;
  char **arguments;
} application;

void setInfo(FILE *, application *, int);
void gestionnaire(int signal, siginfo_t* info, void *ucontext);

int main(void){
  FILE * fapplis;
  application * tabApplis;
  int i = 0, j = 0, app = 0; // Pour les boucles
  int nbrApplis = 0;


  struct sigaction gestionnaireSig;
  gestionnaireSig.sa_sigaction = &gestionnaire;   //poser la gestionnaire de signal
  gestionnaireSig.sa_flags = SA_SIGINFO;    
  sigemptyset(&gestionnaireSig.sa_mask);    //vider la masque
  sigaction(SIGUSR1, &gestionnaireSig, NULL);

  printf("Début du programme\n");
  if ((fapplis = fopen("/Users/bipham/Downloads/Exercices/SR01/Projet 2_SR01/Exo2/list_appli.txt", "r+")) == NULL){
    printf("Erreur lors de l'ouverture du fichier");
    return EXIT_FAILURE;
  }

  // Lire le nombre d'applis
  fseek(fapplis,20,SEEK_SET);
  fscanf(fapplis,"%d",&nbrApplis);


  pid_t pid[nbrApplis]; 

  // Commencer à récupérer les arguments

  if ( (tabApplis = malloc(nbrApplis * sizeof(*tabApplis))) == NULL){
    printf("Problème d'allocation mémoire 1\n");
  }

  for (app= 0; app < nbrApplis; app++){
    // Infos application
    setInfo(fapplis, tabApplis, app);
  }

    // Lancement des applis
  switch(fork())
  {
  case 0:
      for(i=0;i<nbrApplis;i++)
      {
        pid[i]=fork();
        switch(pid[i])
        {
          case -1:
              printf("Error creating main child\n");
              exit(1);
              break;
          case 0:
                printf("%d\n",(tabApplis + i)->nbArg);
                printf("%s\n",(tabApplis +i)->path);
                for (j=0;j<(tabApplis +i)->nbArg;j++){
                  printf("%s\n",(tabApplis +i)->arguments[j]);
                }
                execv((tabApplis + i)->path, (tabApplis +i)->arguments);
                exit(EXIT_SUCCESS);
                break;
          default :
              waitpid(pid[i],NULL,0);
              printf("Application %s terminée\n",(tabApplis + i)->name);
              break;
        }
      }
      break;
  default:
    wait(NULL);
    printf("All done !! bye bye\n");
    break;
  }
  // Retour processus fils
  fclose(fapplis);
  return EXIT_SUCCESS;
}

void setInfo(FILE * fapplis, application * tabApplis, int arg){
  int i, nbArguments,tailleBuffer,numArg;
  char buffer[100];
  fseek(fapplis,1,SEEK_CUR);
  fscanf(fapplis,"name=%s",(tabApplis + arg)->name);
  //printf("%s\n",(tabApplis + arg)->name);
  fgets(buffer, 100, fapplis);
  fscanf(fapplis,"path=%s",(tabApplis + arg)->path);
  //printf("%s\n",(tabApplis + arg)->path);
  fgets(buffer, 100, fapplis);
  fscanf(fapplis,"nombre_arguments=%d",&((tabApplis + arg)->nbArg));
  //printf("%d\n",(tabApplis + arg)->nbArg);
  fgets(buffer, 100, fapplis);
  nbArguments = (tabApplis + arg)->nbArg;
  if (nbArguments >0){
      (tabApplis + arg)->arguments = (char**) malloc(nbArguments*sizeof(char*));
      fgets(buffer, 100, fapplis);
      for (numArg = 0; numArg < nbArguments; numArg++){
        fgets(buffer, 100, fapplis);
        tailleBuffer = strlen(buffer);
        for (i = 0; i < tailleBuffer; i++){
          // Pour placer le nom des arguments
          (tabApplis + arg)->arguments[numArg] = buffer;
        }
        //printf("numarg %d = %s\n", numArg, (tabApplis + arg)->arguments[numArg]);
      }
  }
      // Pour sauter la ligne entre les programmes
      fgets(buffer, 100, fapplis);
}

  void gestionnaire(int signal, siginfo_t* info, void *ucontext){
  int i;
  if(info->si_pid == pid[0] && signal == SIGUSR1){  //on verifie si c'est le signal de power_manager 
    for(i=0; i<= nbrApplis; i++)
      kill(pid[i], SIGUSR1);    
    
    exit(0);    
  }         
}
