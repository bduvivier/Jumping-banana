#ifndef _SCORE_H_
#define _SCORE_H_

struct HighScore{             /*structure stockant les pseudonymes et les scores du highscore*/
  char nom[30];
  int scorefinal;
};

struct HighScore *highscore[5];   /*tableau de pointeurs qui pointent chacun vers une structure HighScore*/

void initialiser_highscore();  /*fonction allouant l'espace mémoire pour chaque structure HighScore*/

void lire_highscore();  /*fonction chargeant le fichier score.txt dans les différentes structures*/

void ecrire_highscore();  /*fonction permettant d'écrire dans le fichier texte*/

void modifier_highscore (int score, char nouveau_nom[]);   /*fonction mettant à jour le contenu des structures HighScore*/

void entrer_score();  /*fonction permettant d'écrire son nom dans le terminal, et d'appeler les fonctions suivantes*/


#endif
