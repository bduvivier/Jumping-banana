


#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "loadMap.h"
#include "drawMap.h"
#include "personnage.h"
#include "jeu.h"


void initRendering()
{
	glEnable(GL_DEPTH_TEST);


}
void handleResize(int width,int heigth)
{
	glViewport(0, 0, width, heigth);
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();



	gluOrtho2D(0, width, heigth, 0);
}

void affichage()
{
	glClearColor(1.0f,1.0f,1.0f,0.0f);  /*couleur du fond (blanc ici)*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	jeu(map, singe);                    /*appel de la fonction jeu qui coordonne notamment les déplacements*/
  glFlush();													/*force l'affichage*/

}

int	main(int argc, char **argv)	{

		loadMap(map);                   /*charge la map dans un tableau*/
		singe = initialiser();          /*initialise le singe (coordonnées, score, etc)*/
		serpent = initialisation_E();   /*initialise le serpent*/


		glutInit(&argc,	argv)	;	        /* initialise glut*/
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);/*type de fenêtre */
 	  glutInitWindowPosition(600,100); /*fenêtre centrée */
    glutInitWindowSize(800,800);     /*taille de la fenêtre*/
		glutCreateWindow("jumping banana");/* créé une fenêtre*/
		initRendering();
		glutDisplayFunc(affichage);        /*callback de la fonction affichage*/
		//glutIdleFunc(affichage);        /* pas d'utilité à priori, mais je laisse ça au cas où*/

    glutReshapeFunc(handleResize);
		glutTimerFunc(500, deplacement_ennemis,0);  /*lance un timer permettant de déplacer automatiquement le serpent sur la carte*/

		glutMainLoop()	; /*Fonction assurant la boucle principale d'affichage*/
return	0	;
}
