#include "fonction.h"

int main(void){
  int choixMenu;
  char* filename[3];

  do {
    system("clear");
    printf("1: pour somme\n");
    printf("2: pour produit\n");
    printf("3: pour quitter\n");
    switch (choixMenu) {
      case '1':
        my_exec(choixMenu, creationMatrice(filename));
        sleep(5);
        break;
      case '2':
        my_exec(choixMenu, creationMatrice(filename));
        sleep(5);
        break;
      default:
        printf("Veuillez choisir un numero entre 1 et 2.\n");
        break;
    }

  } while (choixMenu!=3); 

}

