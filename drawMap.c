
#include <GL/glut.h>


#include <stdio.h>
#include <stdlib.h>


#include "loadMap.h"
#include "drawMap.h"
#include "personnage.h"

void drawWall(char map[MaxX][MaxY])			/*fonction qui affiche les murs et les plateformes*/
{
	for (int j = 0; j < MaxX; j++)        /*boucle pour afficher ligne par ligne*/
	{
		for (int i = 0; i < MaxY; i++)     /*boucle pour afficher colonne par colonne*/
		{
			if(map[j][i] == '#')    /*si rencontre un # dans le tableau, dessine un mur vert*/
			{
				glColor3f(0.5f,1.0f,0.5f);         /*couleur du mur(vert ici*/
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f); /* pour le mettre à l'endroit*/

				glBegin(GL_QUADS);               /*commencement de la création d'un carré*/
				glVertex2f(0.0f, 0.0f);          /*dessine un point à la coordonnée (0,0), et le relie aux suivant*/
				glVertex2f(Square_size, 0.0f);
				glVertex2f(Square_size,Square_size);
				glVertex2f(0.0f,Square_size);
				glEnd();                        /*fin de la création du carré*/
			}
			if (map[j][i] == '-')                   /*idem que fonction précédente, mais pour les plateformes*/
			{
				glColor3f(0.647059f,0.164706f,0.164706f);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size, j*Square_size,0.0f);

				glBegin(GL_QUADS);
				glVertex2f(0.0f, 0.0f);
				glVertex2f(Square_size, 0.0f);
				glVertex2f(Square_size,Square_size);
				glVertex2f(0.0f,Square_size);
				glEnd();
			}
		}
  }
}
void Dessiner_singe (char map [MaxX][MaxY]){   /*idem, mais pour le personnage en orange*/
	for (int j = 0; j < MaxX; j++)
	{
		for (int i = 0; i < MaxY; i++)
		{
			if (map[j][i] == 'X')
			{
        glColor3f(1.0f,0.5f,0.0f);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size, j*Square_size,0.0f);
				glBegin(GL_POLYGON);

				glVertex2f(0.0f,0.0f);
				glVertex2f(Square_size, 0.0f);
				glVertex2f(Square_size, Square_size);
				glVertex2f(0.0f, Square_size);
				glEnd();
			}
		}
	}
}

void Dessiner_bananes (char map[MaxX][MaxY]){   /*idem mais pour les bannanes (triangles minuscules)*/
	for (int j = 0; j < MaxX; j++)
	{
		for (int i = 0; i < MaxY; i++)
		{
			if (map[j][i]== '0'){
				glColor3f(1.0f,0.5f,0.0f);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size, j*Square_size,0.0f);

				glBegin(GL_TRIANGLES);
				glVertex2f(10.0f,0.0f);
				glVertex2f(16.0f,0.0f);
				glVertex2f(13.0f,13.0f);
				glEnd();

			}
		}
	}
}

void Dessiner_ennemis (char map [MaxX][MaxY]){ /*idem mais pour les ennemis en rouge*/
	for (int j = 0; j < MaxX; j++)
 {
	 for (int i = 0; i < MaxY; i++)
	 {
		 if (map[j][i]=='1'){

			 glColor3f(1.0f,0.0f,0.0f);
			 glMatrixMode(GL_MODELVIEW);
			 glLoadIdentity();
			 glTranslatef(i*Square_size, j*Square_size,0.0f);
			 glBegin(GL_POLYGON);

			 glVertex2f(0.0f,0.0f);
			 glVertex2f(Square_size, 0.0f);
			 glVertex2f(Square_size, Square_size);
			 glVertex2f(0.0f, Square_size);
			 glEnd();
		 }
		}
	}
}
