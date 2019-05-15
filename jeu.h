#ifndef _JEU_H_
#define _JEU_H_

#include <stdio.h>
#include <stdlib.h>

#include "personnage.h"
#include "loadMap.h"

void nouvelle_partie(void); /*lance ine nouvelle partie en (ré)initialisant différentes variables*/

void retour_debut_niveau(void); /*singe retourne au début du niveau s'il n'a pas récolté toutes les bananes une fois arrivé au bout*/

void deplacement(int key, int x, int y);  /*fonction permettant d'utiliser les fleches pour diriger le singe*/

void jeu(void); /* fonction coordonnant toutes les fonctions présentes dans la partie jeu*/

void deplacement_ennemis(int x);  /*fonction déplaçant automatiquement le serpent*/

void saut_singe (int x);          /*fonction contenant les appel de fonction sautDroite et sautGauche*/
                                 /*sélectionne laquelle activer selon la direction vers laquelle le singe est tourné*/

void singe_retombe (int x);    /*fonction contenant les appels de fonction retombe_droite et retombe_gauche*/
                               /*sélectionne laquelle activer selon la direction vers laquelle le singe est tourné*/

void tombe_plateforme (int x);  /*singe tombe d'une plateforme si se déplace trop loin à gauche ou à droite*/

void Timer(int x);   /*fonction décrémentant une variable toutes les secondes*/

int timer; /*variable indiquant le temps restant pour gagner des points bonus*/

#endif
