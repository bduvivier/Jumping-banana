#include "interface.h"
#include "personnage.h"
#include <GL/glut.h>
#include <stdio.h>






void afficher_interface(char *string,float x,float y,float z)     /*code de Ossama Hossam, voir racourci interface + raccourci interface aussi*/
{                                                                 /*fonction permettant d'afficher du texte*/
  char *c;
  glRasterPos3f(x, y,z);                                          /*sert à positionner le texte selon des coordonnées x, y et z*/

  for (c=string; *c != '\0'; c++)                                /* boucle affichant le texte caractère par caractère*/
  {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);         /*fonction affichant un caractère*/
  }
}



void interface(void) {                  /*fonction regroupant tous les appels de la fonction pour afficher du texte*/

 int nbre_banane = singe->n;            /*voir raccourci afficher score */
 char banane[3];
 sprintf(banane, "%d", nbre_banane);    /* marche pas avec snprintf mais apparemment snprintf est mieux pour éviter overflow*/

 int nbre_vie = singe->v;               /*charge la valeur de la variable v (nbre de vie) dans une variable*/
 char vie[2];                           /*créé un tableau de caractère*/
 sprintf(vie, "%d", nbre_vie);          /*stocke le nombre de vie sous forme de caractère dans le tableau*/

 int score_total = singe->score;        /*idem ici, et pour le nombre de banane*/
 char score[3];
 sprintf(score, "%d", score_total);

  glLoadIdentity();
	glColor3f(0.0f,1.0f,0.0f);                            /*couleur du texte*/
	afficher_interface("Bananes collectees: ",35,50,0);   /*appel de la fontion pour afficher du texte. Affiche "Bananes collectées"*/

  glLoadIdentity();
	glColor3f(0.0f,1.0f,0.0f);
	afficher_interface(banane,240,50,0);               /* même idée, mais au lieu de mettre une chaine de caractère en argument, je met un tableau de caractère*/
                                                    /*affiche le contenu du tableau créé au dessus, c'est à dire le nombre de bananes collectées*/
                                                    /*le contenu du tableau varie donc au cours du jeu pour afficher le nombre de bananes collectées*/
  glLoadIdentity();                                 /*idem pour la suite, mais pour le score et le nombre de vie*/
	glColor3f(0.0f,1.0f,0.0f);
	afficher_interface("Score: ",650,50,0);

  glLoadIdentity();
	glColor3f(0.0f,1.0f,0.0f);
	afficher_interface(score ,715,50,0);

  glLoadIdentity();
	glColor3f(0.0f,1.0f,0.0f);
	afficher_interface("Vies:",400,50,0);

  glLoadIdentity();
	glColor3f(0.0f,1.0f,0.0f);
	afficher_interface(vie,460,50,0);
}
