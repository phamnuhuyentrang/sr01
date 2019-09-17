#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nombre_etu 35
typedef struct Etudiant
{
	int ide;
	char nom[20];
	char prenom[20];
	float moyenne;
} etudiant;
int main(){
	FILE *fp1, *fp2, *fp3, *fp4; 
	etudiant t1[35], t2[35], t3[35],etu[35], t;
	int i,j,k;
	
	/* ouvrir le fichier SR01.txt */
	i=0;	
	fp1=fopen("SR01.txt", "r");
	fseek(fp1, 14, SEEK_CUR);
	while (fscanf(fp1,"%d",&t1[i].ide) != EOF){
		while (!(' ')){
			continue;
		}
		fscanf(fp1, "%d", &t1[i].ide);		
		fscanf(fp1, "%s", t1[i].nom);
		fscanf(fp1, "%s", t1[i].prenom);			
		fscanf(fp1, "%f", &t1[i].moyenne);		
		i++;
	}
	fclose(fp1);

	/* ouvrir le fichier LO21.txt */
	i=0;
	fp2=fopen("LO21.txt", "r");
	fseek(fp2, 14, SEEK_CUR);
	while (fscanf(fp2,"%d",&t2[i].ide) != EOF){
		while (!(' ')){
			continue;
		}
		fscanf(fp2, "%d", &t2[i].ide);
		fscanf(fp2, "%s", t2[i].nom);
		fscanf(fp2, "%s", t2[i].prenom);
		fscanf(fp2, "%f", &t2[i].moyenne);
		i++;
	}
	fclose(fp2);

	/* ouvrir le fichier NF16.txt */
	i=0;
   	fp3=fopen("NF16.txt", "r");
	fseek(fp3, 14, SEEK_CUR);
	while (fscanf(fp3,"%d",&t3[i].ide) != EOF){
		while (!(' ')){
			continue;
		}
		fscanf(fp3, "%d", &t3[i].ide);
		fscanf(fp3, "%s", t3[i].nom);			
		fscanf(fp3, "%s", t3[i].prenom);
		fscanf(fp3, "%f", &t3[i].moyenne);		
		i++;
	}
	fclose(fp3);

	/* calculer les moyenne des étudiants */
	for (i=0;i<nombre_etu;i++){
		for (j=0;j<nombre_etu;j++){
			if (t1[i].ide==t2[j].ide){
				for (k=0;k<nombre_etu;k++){
					if (t2[j].ide==t3[k].ide){
						etu[i].ide = t1[i].ide;
						strcpy(etu[i].nom, t1[i].nom);
						strcpy(etu[i].prenom, t1[i].prenom);
						etu[i].moyenne = (t1[i].moyenne + t2[j].moyenne + t3[k].moyenne)/3;
					}
				}
			}
		}
	}
	for (i=0; i<nombre_etu; i++){
		printf("%-2d\t %-12s\t %-12s\t %-12.2f\n", etu[i].ide, etu[i].nom, etu[i].prenom, etu[i].moyenne);
	}

	/* trier des notes par ordre décroissant */
	for (i=0; i<nombre_etu; i++)
	{
    	for (j=(i + 1); j<nombre_etu; j++)
    	{
     		if (etu[i].moyenne < etu[j].moyenne)
       		{
        		t = etu[i];
        		etu[i] = etu[j];
        		etu[j] = t;
        	}
    	}
	}
	
    printf("\n \n");

    /* fichier "Fichier_final.txt" contient les moyennes des étudiants */
    fp4=fopen("Fichier_final.txt", "w");
    fprintf(fp4, "%s \n", "Nb_etudiant = 35");
    fprintf(fp4, "%s\n", "\n \n");
    for (i=0;i<nombre_etu;i++){
    	fprintf(fp4,"%-2d\t %-12s\t %-12s\t %-12.2f\n", etu[i].ide, etu[i].nom, etu[i].prenom, etu[i].moyenne);
    }
    fclose(fp4);
    return 0;
}