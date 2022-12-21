#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define ENERGIE 30.0

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/


float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;


int main(void) {
 
	/* A completer. Part 2:
	* exercice 4, questions 2 et 4 
	* exercice 6, question 2
	* exercice 7, question 3
	* exercice 8, question 1
	*/
	   
	/*
	Animal *liste_proie = NULL;
	Animal *liste_predateur = NULL;
	Animal *a1 = creer_animal(15, 15, 10.0);
	liste_proie=a1;
	   
	printf("liste_proie contient %d elements\n",compte_animal_it(liste_proie));
	reproduce(&liste_proie,p_reproduce_proie);
	printf("liste_proie contient %d elements\n",compte_animal_it(liste_proie));
   	*/
   
	srand(time(NULL));
   	
	int monde[SIZE_X][SIZE_Y];
	int i, j;
	for(i = 0; i < SIZE_X; i++){
		for(j = 0; j < SIZE_Y; j++){
			monde[i][j] = 0;
		}
	}

	int x, y;
	float energie;
	Animal *liste_proie;
	for(i = 0; i < NB_PROIES; i++){
		x = rand()%SIZE_X;
		y = rand()%SIZE_Y;
		energie = ENERGIE;
		liste_proie = ajouter_en_tete_animal(liste_proie,  creer_animal(x, y, energie));
	}

	Animal *liste_predateurs;
	for(i = 0; i < NB_PREDATEURS; i++){
		x = rand()%SIZE_X;
		y = rand()%SIZE_Y;
		energie = ENERGIE;
		liste_predateurs = ajouter_en_tete_animal(liste_predateurs,  creer_animal(x, y, energie));
	}

	i = 0;
	FILE *f = fopen("Evol_Pop.txt", "w");
	afficher_ecosys(liste_proie, liste_predateurs);
	while(i<500 && (liste_proie != NULL) && (liste_predateurs != NULL)){
		rafraichir_predateurs(&liste_predateurs, &liste_proie);
		rafraichir_proies(&liste_proie, monde);
		reproduce(&liste_predateurs, p_reproduce_predateur);
		reproduce(&liste_proie, p_reproduce_proie);
		rafraichir_monde(monde);
		usleep(T_WAIT*6);
		fprintf(f, "%d %d %d\n", i, compte_animal_it(liste_proie), compte_animal_it(liste_predateurs));
		i++;
		afficher_ecosys(liste_proie, liste_predateurs);
		clear_screen();	
	}
	fclose(f);

	liberer_liste_animaux(liste_proie);
	liberer_liste_animaux(liste_predateurs);

  return 0;
}

