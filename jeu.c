
#include <stdio.h>
#include <GL/glut.h>
#include <stdbool.h>

#include "jeu.h"
#include "loadMap.h"
#include "drawMap.h"
#include "personnage.h"
#include "deplacement.h"
#include "interface.h"



bool LEFT = false;       /*variable booléenne permettant d'activer le déplacement vers la gauche du singe*/
bool RIGHT = false;      /*idem pour le déplacement vers la droite*/
bool UP = false;         /*idem pour le saut et la chute du singe*/

int direction = 1;       /*variable indiquant dans quelle direction sont tourné les personnages*/
int active_saut=0;       /*variable qui permet de sauter jusq'à un certain point*/
bool singe_doit_retomber = false;    /*variable indiquant que le saut est terminé, et que le personnage doit retomber*/
bool chute_plateforme = false;       /*variable servant à indiquer que le personnage peut chuter verticalement d'une plateforme*/


void deplacement (int key, int x, int y) {  /*fonction permettant d'utiliser les fleches pour diriger le singe*/

	switch(key){

	case GLUT_KEY_LEFT:      /*si on appuie sur la flèche de gauche, met left à true et indique que le singe est dirigé vers la gauche*/
	LEFT = true;
	direction = 0;
	break;

	case GLUT_KEY_RIGHT:   /*idem pour la droite*/
	RIGHT = true;
	direction = 1;
	break;

	case GLUT_KEY_UP:     /*idem pour le saut*/
	UP = true;
	break;

	}
}


void singe_retombe (int x){             /*singe retombe en diagonale après un saut*/
	if (singe_doit_retomber == true) {    /*retombe si la variable est à true, et donc si le singe a fini son saut*/
		if(direction==1)                    /*retombe vers la droite si le personnage a sauté vers la droite*/
			retombe_droite (map,singe);       /*appel de la fonction pour retomber d'un carré vers la droite*/

		if (direction==0)                   /*retombe vers la gauche si le signe a sauté vers la gauche*/
			retombe_gauche(map,singe);

		glutTimerFunc(150,singe_retombe,0); /*rappelle la fonction singe_retombe après 150 millisecondes*/
	}
}

void tombe_plateforme (int x){         /*singe tombe d'une plateforme si se déplace trop loin*/
  if (chute_plateforme == true){       /* et si la variable est à true, c'est à dire si le personnage dépasse une plateforme
																			  en se déplaçant
																				vers la gauche ou vers la droite, et
																				non en sautant*/
			retombe (map,singe);
			glutTimerFunc(150, tombe_plateforme, 0);  /*rappelle la fonction tombe_plateforme après 150 millisecondes*/
	}
}


void saut_singe (int x) {             /*fonction permettant de faire sauter le singe en diagonale*/

	if (active_saut<10){								/*singe va sauter de 10 cases puis ne plus sauter*/
		if (direction == 1){             /*saute vers la droite si direction = 1*/
		sautDroite(map,singe);           /*appel de la fonction permettant de faire sauter le singe d'un carré vers la droite*/
		active_saut++;                   /*incrémente la variable à chaque rappel de la fonction saut_singe tant qu'elle est < 5*/
		}

		else if (direction == 0){       /*saute vers la gauche si direction = 0*/
		 sautGauche(map,singe);
		 active_saut++;
	 }

		glutTimerFunc(150, saut_singe,0);  /*rappelle la fonction saut_singe après 150 millisecondes*/
	}
	if (active_saut==10){									/*singe retombe à la fin de son saut*/
		singe_doit_retomber = true;         /*met la variable à true pour permettre au singe de retomber à la fin de son saut*/
		glutTimerFunc(0,singe_retombe,0);   /*appelle une première fois la fonction singe_retombe pour faire tomber le singe après un saut*/
	}
}



void deplacement_ennemis(int x){                    /*fonction déplaçant automatiquement le serpent*/

	deplacement_serpents(map,serpent);               /*appel de la fonction déplaçant un enemi d'un carré*/
	glutTimerFunc(500, deplacement_ennemis,0);			/*timer appelant la fonction deplacement_ennemis toutes les 500 millisecondes*/
}




void jeu(char map[MaxX][MaxY], Singe singe) {  /* fonction coordonnant toutes les fonctions présentes dans la partie jeu*/

	drawWall(map);								/*appel de la fonction pour dessiner la map*/
	Dessiner_singe(map);          /*appel de la fonction pour dessiner le singe*/
	Dessiner_bananes(map);        /* idem pour les bananes*/
	Dessiner_ennemis(map);        /*idem pour l'ennemi*/
	interface();                  /*idem pour l'interface*/

	glutSpecialFunc(deplacement);	/*appel de la fonction pour utiliser les flèches pour se déplacer*/


	if (LEFT == true)  /*si appuie sur flèche de gauche: se déplace vers la gauche*/
	{
		deplacementgauche(map, singe);   /*appel de la fontion pour déplacer le personnage vers la gauche d'un carré*/
		singe_doit_retomber = false;     /*met la variable à false pour désactiver la chute en diagonale si le singe tombe d'une plateforme*/
		chute_plateforme = true;         /*met la variable à true pour activer la chute verticale d'une plateforme*/
		glutTimerFunc(0,tombe_plateforme,0); /*appelle une première fois la foncton tombe_plateforme pour que le singe tombe verticalementd'une plateforme*/
		LEFT = false;                    /*remet left à false une fois terminé pour permettre de diriger le singe dans une autre direction par après*/
	}

	if (RIGHT == true)	/*idem mais vers la droite*/
	{
		deplacementdroite(map, singe);
		singe_doit_retomber = false;
		chute_plateforme = true;
		glutTimerFunc(0,tombe_plateforme,0);
		RIGHT = false;
	}

	if (UP == true)			        /*si appluie du la flèche du haut, saute de 5 cases, mais nombre de case est temporaire*/
	{
	 active_saut=0;             /*initialise la variable à chaque fois qu'on appuie sur la touche saut pour lui permettre de resauter à nouveau*/
	 singe_doit_retomber = false; /*remet la variable à false pour pouvoir sauter à nouveau sans retomber directement après 1 case*/
	 chute_plateforme = false; /*désactive la chute verticale pour permettre la chute en diagonale après un saut*/
   glutTimerFunc(0, saut_singe,0); /*premier appel de la fonction saut_singe*/

		UP = false;
	}

	glutPostRedisplay();     /*permet d'utiliser la fonction jeu à plusieurs reprise*/
}
