


#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "loadMap.h"
#include "drawMap.h"
#include "personnage.h"
#include "jeu.h"
#include "changerNiveau.h"
#include "scrolling.h"
#include "ecran.h"



void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}

void handleResize(int width,int heigth)
{
	glViewport(0, 0, width, heigth);
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	glOrtho( 0.0, 800, 800, 0.0, 1.0, -1.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glPushMatrix();
}

void affichage()								/*fonction principale d'affichage*/
{
	glClearColor(1.0f,1.0f,1.0f,0.0f);  /*couleur du fond (blanc ici)*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	selection_ecran();									/*appel de la fonction pour sélectionner un écran*/
																			/*au début du jeu, le premier écran qui s'affiche est le menu*/
  glFlush();													/*force l'affichage*/
}

void update (int x){				/*met à jour l'écran de jeu pour permettre au scrolling de fonctionner*/

	affichage();
	glutTimerFunc( 1000 / 60, update, 0 );

}

int	main(int argc, char **argv)	{

		glutInit(&argc,	argv)	;	        /* initialise glut*/
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);/*type de fenêtre */
 	  glutInitWindowPosition(600,100); /*fenêtre centrée */
    glutInitWindowSize(800,880);     /*taille de la fenêtre*/
		glutCreateWindow("jumping banana");/* créé une fenêtre*/
		initRendering();
		glutDisplayFunc(affichage);        /*callback de la fonction affichage*/

		nouvelle_partie();               /*initialise plusieurs variables*/ /* si je fais pas ça, segmentation fault car gcameraX et Y pas initialisé*/
		menu = true;                     /*met menu à true pour démarrer le jeu sur le menu*/
		jeu_actif=false;								/*met jeu_actif à false pour désactiver la partie jeu*/
		glutTimerFunc(0,Timer,0);       /*active le timer indiquant le temps restant*/

    glutReshapeFunc(handleResize);
		glutTimerFunc(500, deplacement_ennemis,0);  /*lance un timer permettant de déplacer automatiquement le serpent sur la carte*/
		glutTimerFunc( 1000 / 60, update, 0 );     /*timer appelant la fonction update*/
		glutMainLoop()	; /*Fonction assurant la boucle principale d'affichage*/
return	0	;
}
