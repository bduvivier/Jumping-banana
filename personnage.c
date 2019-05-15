#include "personnage.h"
#include "loadMap.h"
#include "stdio.h"
#include "stdlib.h"

void initialiser (void) {             /*fonction permettant d'initialiser les variables du singe (coordonnées de départ, etc)*/

singe = malloc(sizeof(struct Personnage));         /*alloue l'espace mémoire */
singe->cood.xp=37;                     /*initialise les coordonnées X et y du singe*/
singe->cood.yp=2;                      /* x = la ligne à laquelle il se trouve, et y = la colonne*/
singe->n=0;                            /*nbre de banane collectées dans le niveau*/
singe->v=10;                            /*nombre de vies restantes*/
singe->score=0;                        /* score (nbre de bananes collectées au total*/
singe->vitesse=90;                    /*vitesse du saut qui diminuera quand le singe monte, et augmentera quand le singe descend*/
}

void initialisation_E (void) {      /*idem mais pour les serpent*/

  int k = 0;

	for (int i = 0; i < MaxX; i++)      /*double boucle parcourant le tableau map*/
	{
		for (int j = 0; j < MaxY; j++)
		{
			if (map[i][j] == '1')          /*si il trouve un '1' à cette position : */
			{

        serpent[k] = malloc (sizeof(struct ennemi));  /*alloue un espace mémoire pour une stucture ennemi*/
                                                      /*stocke l'addresse de cette structure à la position k du tableau serpent*/
        serpent[k]->cood.xp= i;                       /*initialise les coordonnées du serpent en fonction de leur position dans le tableau map*/
        serpent[k]->cood.yp= j;
        k++;                                          /*incrémente la position à laquelle sera stocké l'addresse de l'ennemi suivant*/
			}
		}
	}
}
