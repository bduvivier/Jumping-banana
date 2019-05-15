#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "score.h"
#include "interface.h"
#include "personnage.h"
#include "jeu.h"

void initialiser_highscore(){  /*fonction allouant l'espace mémoire pour chaque structure HighScore*/
  int i = 0;

  while (i<5){   /*boucle de 5 intération car 5 highscore*/
    highscore[i] = malloc(sizeof(struct HighScore)); /*alloue l'espace mémoire pour chaque structure HighScore*/
    i++;
  }

  lire_highscore();  /*appel de la fonction lire_highscore une fois l'espace mémoire alloué*/
}

void lire_highscore(){ /*fonction chargeant le fichier score.txt dans les différentes structures*/
  int i = 0;
  FILE *f;
  f=fopen("score.txt","r"); /*ouvre le fichier texte*/

  if (f == NULL)  /*vérifie que le fichier n'est pas vide*/
    printf("le fichier est vide");

    else {
      while (i<5){  /*boucle chargeant ligne par ligne le fichier score.txt*/
      fscanf(f, "%s %i", highscore[i]->nom, &highscore[i]->scorefinal); /*lit le fichier*/
      i++;
      }
      fclose(f); /*ferme le fichier une fois celui-ci chargé*/
    }
}

void ecrire_highscore(){   /*fonction permettant d'écrire dans le fichier texte*/
  int i=0;

  FILE *f;
  f = fopen("score.txt","w");

  if (f == NULL)
    printf("Le fichier n'a pas pu être ouvert\n");

  else {

    while (i<5){ /*boucle écrivant le contenu des structures HighScore dans le fichier texte*/

    fprintf(f, "%s %i\n", highscore[i]->nom, highscore[i]->scorefinal); /*écrit dans le fichier le contenu de la structure*/
    i++;
    }

    fclose(f);
  }
}

void modifier_highscore (int score, char nouveau_nom[]){  /*fonction mettant à jour le contenu des structures HighScore*/
  int i = 0;
  int score_tempo;        /*variable temportaire stockant tour à tour chaque score inférieur au score obtenu*/
  char nom_tempo[30];     /*même chose, mais pour les pseudonymes*/

  while (i<5){ /*boucle qui va permettre de placer le score obtenu à la bonne position du highscore, tout en mofifiant la position des autres scores*/
    if (score > highscore[i]->scorefinal || score == highscore[i]->scorefinal){ /*compare le score obtenu avec chaque score du highscore*/
      score_tempo = score;                       /*si le score obtenu est supérieur à celui d'une autre personne, la boucle va le placer au bon endroit*/
      score = highscore[i]->scorefinal;          /*elle va également déplacer les scores qui sont inférieurs au score obtenu lors des itérations suivantes*/
      highscore[i]->scorefinal = score_tempo;    /*cela se fait en stockant chaque score qui doit descendre d'un cran dans une variable temportaire*/
                                                 /*compare alors chaque score qui doit descendre avec le score suivant à chaque tour de boucle restant*/

      strcpy(nom_tempo, nouveau_nom);            /*même chose avec les pseudonymes */
      strcpy(nouveau_nom, highscore[i]->nom);    /*la différence est l'utilisation de strcpy pour copier le contenu d'un tableau dans un autre*/
      strcpy(highscore[i]->nom, nom_tempo);
    }
    i++;
  }
}


void entrer_score() {  /*fonction permettant d'écrire son nom dans le terminal, et d'appeler les fonctions suivantes*/

  char nouveau_nom[30];      /*variable stockant temportairement le nom entré par l'utilisateur*/
  int score = (singe->score + singe->v + timer); /*le score final est composé de la somme du nombre de bananes collectées, du nombre de vies restantes et du temps restant*/


  printf("Entrez votre pseudo (sans espace) pour le tableau des scores\n");
  scanf("%s", nouveau_nom);



  modifier_highscore(score, nouveau_nom); /*appel de la fonction pour mettre à jour les structures HighScore si un nouveau score est supérieur à un ancien score*/

  ecrire_highscore();   /*appel de la fonction mettant à jour le fichier texte score.txt*/

  }
