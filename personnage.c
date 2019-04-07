#include "personnage.h"
#include "stdio.h"
#include "stdlib.h"

Singe initialiser (void) {             /*fonction permettant d'initialiser les variables du singe (coordonnées de départ, etc)*/
Singe singe;                           /*créé une variable singe qui est de type pointeur vers la structure personnage*/
singe = malloc(sizeof(Singe));         /*alloue l'espace mémoire pour créer la variable singe */
singe->cood.xp=37;                     /*initialise les coordonnées X et y du singe*/
singe->cood.yp=2;                      /* x = la ligne à laquelle il se trouve, et y = la colonne*/
singe->n=0;                            /*nbre de banane collectées*/
singe->v=3;                            /*nombre de vies restantes*/
singe->score=0;                        /* score (nbre de bananes collectées + nbre d'ennemis tués)*/
singe->vitesse=0;                      /*variable qui sera peut-être utilisés plus tard pour gérer la fonction gravité lors d'un saut*/
return singe;
}

Ennemi initialisation_E (void) {      /*idem mais pour un serpent*/
  Ennemi serpent;
  serpent = malloc (sizeof(Ennemi));
  serpent->cood.xp= 37;
  serpent->cood.yp=28;
  return serpent;
}
