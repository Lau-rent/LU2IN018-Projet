#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ecosys.h"

	float p_ch_dir=0.01;
	float p_reproduce_proie=0.4;
	float p_reproduce_predateur=0.5;
	int temps_repousse_herbe=-15;
	

int main(void){

	
	srand(time(NULL));
	Animal *liste_proie = NULL;
  	Animal *liste_predateur = NULL;
  	int energie=10;
	
  	for(int i = 0; i < 20; i++){
  		int x1 = (rand()%20);
  		int y1 = (rand()%50);
  		ajouter_animal(x1,y1,energie,&liste_proie);
  		int x2 = (rand()%20);
  		int y2 = (rand()%50);
  		ajouter_animal(x2,y2,energie,&liste_predateur);
  	}
  	printf("liste_proie contient %d elements\n",compte_animal_it(liste_proie));
  	printf("liste_predateur contient %d elements\n",compte_animal_it(liste_predateur));
  	afficher_ecosys(liste_proie,liste_predateur);
  	
  	ecrire_ecosys("liste_animaux.txt",liste_proie,liste_predateur);
  	
  	
  	liberer_liste_animaux(liste_proie);
  	liberer_liste_animaux(liste_predateur);
  	

	//Je teste lire_ecosys
	
	Animal *liste_lire = NULL;
  	Animal *liste_lire2 = NULL;
	
  	lire_ecosys("liste_animaux.txt",&liste_lire,&liste_lire2);
  	afficher_ecosys(liste_lire,liste_lire2);
  	
	printf("liste_lire contient %d elements\n",compte_animal_rec(liste_lire));
  	printf("liste_lire2 contient %d elements\n",compte_animal_rec(liste_lire2));
  	
  	liberer_liste_animaux(liste_lire);
  	liberer_liste_animaux(liste_lire2);
  	
  	
  	//Je teste la fonction enlever_animal
  	
  	Animal *liste_p = NULL;
  	Animal *a1 = creer_animal(0,10, energie);
  	Animal *a2 = creer_animal(15,35, energie);
 	Animal *a3 = creer_animal(2,42, energie);
 	Animal *a4 = creer_animal(18,13, energie);
  
 	a1->suivant=a2;
 	a2->suivant=a3;
 	a3->suivant=a4;
  	liste_p=a1;
  	
  	printf("liste_p contient %d element\n",compte_animal_it(liste_p));
  	enlever_animal(&liste_p,a2);
  	printf("liste_p contient %d element\n",compte_animal_it(liste_p));
  	enlever_animal(&liste_p,a3);
  	printf("liste_p contient %d element\n",compte_animal_it(liste_p));
  	
  	liberer_liste_animaux(liste_p);
  	
  	printf("--------------------FIN--------------------\n");
	return 0;
}
