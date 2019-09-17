#include "fonction.h"

char** creationMatrice(char ** filename){
  FILE *file1, *file2;
  int **x, **y;
  int N, i, j;
  char choix;

  filename[0] = "mat1";
  filename[1] = "mat2";

  printf("la taille de la matrice:  \n");
  scanf("%d", &N);

  sprintf(filename[2], "%d", N);

  x = malloc(N * sizeof(*x));
  y = malloc(N * sizeof(*y));
  for (i = 0; i < N; i++){
    x[i] = malloc(N * sizeof(**x));
    y[i] = malloc(N * sizeof(**y));
  }

    system("clear");

    printf("matrice 1\n");
    for (i = 0; i < N; i++){
      for (j = 0; j < N; j++){
        printf("coef %d,%d : ", i, j);
        scanf("%d", &x[i][j]);
      }
    }
    printf("matrice 2\n");
    for (i = 0; i < N; i++){
      for (j = 0; j < N; j++){
        printf("coef %d,%d : ", i, j);
        scanf("%d", &y[i][j]);
      }
    }

  if ( (file1 = fopen(filename[0], "wb")) == NULL)
    exit(EXIT_FAILURE);
  if ( (file2 = fopen(filename[1], "wb")) == NULL)
    exit(EXIT_FAILURE);

  for (i = 0; i < N; i++){
    fwrite(x[i], sizeof(int), N, file1);
    fwrite(y[i], sizeof(int), N, file2);
  }

  fclose(file1);
  fclose(file2);

  for (i = 0; i < 3; i++){
    free(x[i]);
    free(y[i]);
  }
  free(x);
  free(y);
  
  return filename;
}

void my_exec(int choix, char** filename){
  char* somme[] = {"gcc", "-o", "somme", "Somme.c", NULL};
  char* produit[] = {"gcc", "-o", "produit", "Produit.c", NULL};
  char* argument[5];
  argument[1] = filename[0];
  argument[2] = filename[1];
  argument[3] = filename[2];
  argument[4] = NULL;

  do{
    printf("Faire somme ou produit de 2 matrices?\n");
    printf("Tapez 1 si vous choisissez somme et 2 si produit\n");
    scanf("%d",&choix);
  }
  while (choix !=1 && choix !=2);
  switch(choix){
    case 1:
      argument[0] = "somme";
      execv("./somme", argument);
      sleep(1);
      break;
    case 2:
      argument[0] = "produit";
      execv("./produit", argument);
      sleep(1);
      break;
  }
}
