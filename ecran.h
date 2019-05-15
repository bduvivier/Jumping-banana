#ifndef _ECRAN_H_
#define _ECRAN_H_

#include <stdbool.h>
void clavier_menu (unsigned char key, int x, int y);  /*fonction permettant d'utiliser le clavier pour sélectionner un écran*/
void selection_ecran(void);         /*fonction permettant de sélectionner différents écran*/
void afficher_highscore();          /*affiche l'écran des highscore*/
void afficher_game_over (void);     /*affiche l'écran de game over*/
void afficher_menu(void);           /*affiche le menu*/
void afficher_controles(void);      /*affiche les règles du jeu et les contrôles*/

bool menu;                        /*différentes variables booléennes permettant d'activer l'affichage d'un seul écran à la fois*/
bool jeu_actif;
bool game_over;
bool controles;
bool score_actif;


#endif
