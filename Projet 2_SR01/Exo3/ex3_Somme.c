#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  FILE *fp1, *fp2;
  pid_t pid;
  int N, i, j;
  int *tab1, *tab2, **tab_pere;
  int tube[2];

  if (argc != 4){
    printf("Pas assez/trop d'arguments");
    return EXIT_FAILURE;
  }
  if ( (fp1 = fopen(argv[1], "rb")) == NULL ){
    return EXIT_FAILURE;
  }
  if ( (fp2 = fopen(argv[2], "rb")) == NULL){
    return EXIT_FAILURE;
  }
  N = atoi(argv[3]);

  tab1 = malloc(N * sizeof(*tab1));
  tab2 = malloc(N * sizeof(*tab2));
  tab_pere = malloc(N * sizeof(*tab_pere));
  for (i = 0; i < N; i++){
    tab_pere[i] = malloc(N * sizeof(**tab_pere));
  }

  for (i = 0; i < N; i++){
    pipe(tube);
    // Somme à faire
    if ( (pid=fork()) == 0){
      // On ferme la lecture
      close(tube[0]);
      // Tab contenant la somme
      int tab_fils[N];
      fread(tab1, sizeof(*tab1), N, fp1);
      fread(tab2, sizeof(*tab2), N, fp2);

      for (j = 0; j < N; j++){
        tab_fils[j] = tab1[j] + tab2[j];
        // printf("%d\n", tab_fils[j]);
      }
      // Envois au père
      write(tube[1], tab_fils, sizeof(tab_fils));
      // printf("%ld\n", sizeof(tab_fils));
      close(tube[1]);
      exit(0);
    } else {
      // Fermeture de l'écriture
      close(tube[1]);
      // On récupère le calcul
      read(tube[0], tab_pere[i], N*sizeof(**tab_pere));
      // printf("%ld", sizeof(*tab_pere));
      close(tube[0]);
    } 
  } // Fin boucle i

  // Affichage de la matrice
  printf("Matrice resultante :\n");
  for (i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      printf("%d\t", tab_pere[i][j]);
    }
    printf("\n");
  }

  fclose(fp1);
  fclose(fp2);
  for (i = 0; i < N; i++){
    free(tab_pere[i]);
  }
  free(tab_pere);
  free(tab1);
  free(tab2);
  
  return 0;
}

