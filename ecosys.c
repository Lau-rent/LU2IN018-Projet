#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"


/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
	if(0>x || 0>y || SIZE_X<x || SIZE_Y<y){
		printf("Les coordonnées saisies sont incorectes");
		exit;
	}
	*liste_animal=ajouter_en_tete_animal(*liste_animal,creer_animal(x,y,energie));
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  /*A Completer*/
  assert(liste);
  assert(animal);
  Animal *precd = *liste;
  if(animal != *liste){
  	while(precd->suivant != animal){
  		precd=precd->suivant;
  	}
  	precd->suivant=animal->suivant;
  }
  else{
  	*liste=animal->suivant;
  }
  free(animal);
  return;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
	while(liste){
		Animal *tmp = liste->suivant;
		free(liste);
		liste = tmp;
	}
  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    Animal *ap = la;
    while (ap) {
        if (rand() / (float)RAND_MAX < p_ch_dir) {  // changement de direction avec une probabilité p_ch_dir
            ap->dir[0] = rand() % 3 - 1;
            ap->dir[1] = rand() % 3 - 1;
        }
        // déplacer l'animal selon sa direction
        // Et vérifiez que les nouvelles coordonnées de l'animal sont bien dans les limites de taille du tableau
        ap->x = (ap->x + ap->dir[0] + SIZE_X) % SIZE_X; 
        ap->y = (ap->y + ap->dir[1] + SIZE_Y) % SIZE_Y;
        ap = ap->suivant;
    }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
    Animal *ap = liste_animal!= NULL ? *liste_animal : NULL;
    while (ap) {
        if (rand() / (float)RAND_MAX < p_reproduce) {  // reproduction d'un animal avec probabilité p_reproduce
            ajouter_animal(ap->x, ap->y, ap->energie/2, liste_animal); // créer un nouvel animal avec la moitié de l'énergie de son parent
            ap->energie=ap->energie/2;// diviser énergie de parent par 2
        }
        ap = ap->suivant;
    }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*A Completer*/
	if(liste_proie != NULL){
	    	Animal *animal = *liste_proie;
	    	bouger_animaux(animal); 
	    	animal = *liste_proie;
	    	while(animal){
	    		animal->energie -= 1;
	    		if(monde[animal->x][animal->y] >= 0){
        			animal->energie += 5.0;
        			monde[animal->x][animal->y] = temps_repousse_herbe;
     			}
	    	  	if(animal->energie < 0){//j'enleve l'animal dont l'energie est inferieur a zero
	    	    		Animal *temporaire = animal;
	    	    		animal = animal->suivant;
	    	    		enlever_animal(liste_proie, temporaire);
	    	  	}else{
	    	    		animal = animal->suivant;
	    	  	} 
		}
	}
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
	while(l != NULL){
		if(l->x == x && l->y == y){
		return l;
		}
		l = l->suivant;
	}
	return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
	if(liste_predateur != NULL){
		Animal *loup = *liste_predateur;
		bouger_animaux(loup);
		loup = *liste_predateur;
		Animal *mouton;
		while(loup != NULL){
			loup->energie -= 0.45;
		     	if(liste_proie != NULL){
				mouton=animal_en_XY(*liste_proie, loup->x, loup->y);
				if(mouton != NULL){
					loup->energie += mouton->energie;
					enlever_animal(liste_proie, mouton);
				}  
			}
			if(loup->energie < 0){
				Animal *temporaire = loup;
				loup = loup->suivant;
				enlever_animal(liste_predateur, temporaire);
			}
			else{
				loup = loup->suivant;
			} 
		}  
	}
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
	for(int i = 0; i < SIZE_X; i++){
		for(int j = 0; j < SIZE_Y; j++){
			monde[i][j]++;
		}
	}
}

void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur, Animal *liste_proie) {
    FILE *f=fopen(nom_fichier, "w"); // ouverteur fichier en mode écriteur
   
    fprintf(f,"<proies>\n"); // écrit la première ligne dans le fichier 
    Animal *tmp=liste_proie; 
    while (tmp) { // écrit chaque proie dans le fichier
        fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n",tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
        tmp=tmp->suivant;
    }
    fprintf(f,"</proies>\n"); 
    fprintf(f,"<predateurs>\n");
    tmp=liste_predateur;
    while (tmp) { // écrit chaque predateur dans le fichier
        fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n",tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
        tmp=tmp->suivant;
    }
    fprintf(f,"</predateurs>\n");
    fclose(f);
}

void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie) {

    FILE *f=fopen(nom_fichier, "r");
    if (f==NULL) {
        printf("Erreur lors de l’ouverture de %s\n",nom_fichier);
        // ou bien : 
        // fprintf(stderr, "Erreur lors de l’ouverture de %s\n",nom_fichier)
        return;
    }
    char buffer[256];
    int x_lu, y_lu, dir_lu[2];
    float e_lu;

    fgets(buffer, 256, f); //lecture de <proies>
    assert(strncmp(buffer, "<proies>",(long unsigned int)8)==0);
    fgets(buffer, 256, f); //lecture de la ligne contenant la premiere proie
    
    while (strncmp(buffer,"</proies>",(long unsigned int)9)!=0) {
        sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f\n", &x_lu, &y_lu, &dir_lu[0], &dir_lu[1], &e_lu);
        Animal *a_lu=creer_animal(x_lu, y_lu, e_lu);
        a_lu->dir[0]=dir_lu[0];
        a_lu->dir[1]=dir_lu[1];
        // insertion en tête de la liste
        a_lu->suivant=*liste_proie;
        *liste_proie = a_lu;
        fgets(buffer, 256, f); //lecture de la ligne contenant la proie suivante
    }
    fgets(buffer, 256, f); //lecture de <predateurs>
    assert(strncmp(buffer, "<predateurs>",(long unsigned int)12)==0);

    fgets(buffer, 256, f); //lecture de la ligne contenant le premier predateur
    while (strncmp(buffer,"</predateurs>",(long unsigned int)13)!=0) {
        sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f\n", &x_lu, &y_lu, &dir_lu[0], &dir_lu[1], &e_lu);
        Animal *a_lu=creer_animal(x_lu, y_lu, e_lu);
        a_lu->dir[0]=dir_lu[0];
        a_lu->dir[1]=dir_lu[1];
        // insertion en tête de la liste
        a_lu->suivant=*liste_predateur;
        *liste_predateur = a_lu;
        fgets(buffer, 256, f); //lecture de la ligne contenant le predateur suivant
    }
    fclose(f);
}

