#include "interface.h"
#include "personnage.h"
#include "changerNiveau.h"
#include "jeu.h"
#include <GL/glut.h>
#include <stdio.h>






void afficher_interface(char *string,float x,float y,float z)     /*fonction affichant du texte*/
{                                                                 /*fonction permettant d'afficher du texte*/
  char *c;
  glRasterPos3f(x, y,z);                                          /*sert à positionner le texte selon des coordonnées x, y et z*/

  for (c=string; *c != '\0'; c++)                                /* boucle affichant le texte caractère par caractère*/
  {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);         /*fonction affichant un caractère*/
  }
}



void interface(void) {   /*fonction regroupant tous les appels de la fonction pour afficher du texte*/
 char tableau [3];      /*tableau servant à stocker le contenu de variables entières*/

 sprintf(tableau, "%d", singe->n);                     /*stocke le contenu de la variable n dans le tableau de racactère*/
 glLoadIdentity();
 glColor3f(0.0f,1.0f,0.0f);                            /*couleur du texte*/
 afficher_interface("Bananes collectees: ",35,50,0);   /*appel de la fontion pour afficher du texte. Affiche "Bananes collectées"*/
 glLoadIdentity();                                   /* même idée, mais au lieu de mettre une chaine de caractère en argument, je met un tableau de caractère*/
 glColor3f(0.0f,1.0f,0.0f);                          /*affiche le contenu du tableau créé au dessus, c'est à dire le nombre de bananes collectées*/
 afficher_interface(tableau,240,50,0);               /*le contenu du tableau varie donc au cours du jeu pour afficher le nombre de bananes collectées*/

 sprintf(tableau, "%d", singe->v);           /*même chose pour les variables score, vie, niveau et le timer*/
 glLoadIdentity();
 glColor3f(0.0f,1.0f,0.0f);
 afficher_interface("Vies:",400,50,0);
 glLoadIdentity();
 glColor3f(0.0f,1.0f,0.0f);
 afficher_interface(tableau,460,50,0);

 sprintf(tableau, "%d", singe->score);
 glLoadIdentity();
 glColor3f(0.0f,1.0f,0.0f);
 afficher_interface("Score: ",650,50,0);
 glLoadIdentity();
 glColor3f(0.0f,1.0f,0.0f);
 afficher_interface(tableau ,715,50,0);

  sprintf(tableau, "%d", niveau);
  glLoadIdentity();
  glColor3f(0.0f,0.0f,0.0f);
  afficher_interface("Niveau ",385,18,0);
  glLoadIdentity();
	glColor3f(0.0f,0.0f,0.0f);
	afficher_interface(tableau,460,18,0);

  sprintf(tableau, "%d", timer);
  glLoadIdentity();
  glColor3f(0.0f,0.0f,0.0f);
  afficher_interface("Timer: ",100,18,0);
  glLoadIdentity();
	glColor3f(0.0f,0.0f,0.0f);
	afficher_interface(tableau,175,18,0);
}
