
#include <stdio.h>
#include <GL/glut.h>
#include <stdbool.h>

#include "jeu.h"
#include "loadMap.h"
#include "drawMap.h"
#include "personnage.h"
#include "deplacement.h"
#include "interface.h"
#include "changerNiveau.h"
#include "ecran.h"
#include "scrolling.h"
#include "score.h"

bool LEFT = false;       /*variable booléenne permettant d'activer le déplacement vers la gauche du singe*/
bool RIGHT = false;      /*idem pour le déplacement vers la droite*/
bool UP = false;         /*idem pour le saut du singe*/

int direction = 1;       /*variable indiquant dans quelle direction est tourné le  singe*/
int active_saut=0;       /*variable qui permet de sauter jusqu'à un certain point*/
bool singe_doit_retomber = false;    /*variable indiquant que le saut est terminé, et que le personnage doit retomber*/
bool chute_plateforme = false;       /*variable servant à indiquer que le personnage peut chuter verticalement d'une plateforme*/


void Timer(int x){  /*décrémente une variable tt les secondes pour indiquer le temps restant*/

	if (jeu_actif && timer!=0)   /*pour éviter que le timer ne continue de diminuer quand on est dans le menu, et ne descende en dessous de 0*/
		timer--;				/*décrémentation de la variable tant qu'on est dans le jeu. Celle-ci est mise sur pause lorsqu'on est dans un autre écran*/
	glutTimerFunc(1000,Timer,0); /*rappel de la fonction Timer pour décrémenter la variable toutes les secondes*/

}

void nouvelle_partie(void){       /*lance une nouvelle partie*/
	jeu_actif=true;									/*met la variable à true pour activer la partie jeu*/
	game_over=false;               /*met les autres variables à false pour ne pas afficher les autres écrans*/
	menu=false;
	controles=false;
	score_actif=false;
	niveau = 1;                     /*indique que le niveau du début est le niveau 1*/
	timer=999;											/*initialise le timer à 999*/
	initialiser_highscore();        /*charge le ficier texte score.txt dans les structures highscore*/
	loadMap(map);                   /*charge la map dans un tableau*/
	initialiser();          /*initialise le singe (coordonnées, score, etc)*/
	initialisation_E();   /*initialise le serpent*/
	gCameraX = 0;									/*initialise la position de la caméra$*/
	bord_camera = 30;             /*initialise l'endroit où le scrolling va s'activer au début*/
	scrolling();                  /*replace la caméra au début*/

}

void retour_debut_niveau(void){ /*retour au début du niveau si toutes les bananes n'ont pas été collectées lorsque le singe arrive au bout*/
	singe->cood.xp=37;						/*remet les coordonnées du singe au début du niveau*/
  singe->cood.yp=2;
	map[37][179]=' ';             /*modifie le tableau physique pour remettre le singe à la bonne position*/
	map[37][2]='X';
	gCameraX = 0;									/*initialise la position de la caméra$*/
	bord_camera = 30;             /*initialise l'endroit où le scrolling va s'activer au début*/
	scrolling();                  /*replace la caméra au début*/
	Dessiner_singe(map);          /*redescine le singe à la bonne position*/
}


void deplacement (int key, int x, int y) {  /*fonction permettant d'utiliser les fleches pour diriger le singe*/

	switch(key){

	case GLUT_KEY_LEFT:      /*si on appuie sur la flèche de gauche, met left à true et indique que le singe est dirigé vers la gauche*/
	LEFT = true;
	direction = 0; /*indique que le singe est dirigé vers la gauche*/
	singe->vitesse = 230; /*(ré)initialise la vitesse de saut du singe pour si jamais il tombe d'une plateforme*/
	break;

	case GLUT_KEY_RIGHT:   /*idem pour la droite*/
	RIGHT = true;
	direction = 1;
	singe->vitesse = 230; /*(ré)initialise la vitesse de saut du singe*/
	break;

	case GLUT_KEY_UP:     /*idem pour le saut*/
	UP = true;
	singe->vitesse = 90; /*(ré)initialise la vitesse de saut du singe*/
	break;

	}
}


void singe_retombe (int x){             /*singe retombe en diagonale après un saut*/
	if (singe_doit_retomber == true) {    /*retombe si la variable est à true, et donc si le singe a fini son saut*/
		if(direction==1){                    /*retombe vers la droite si le personnage a sauté vers la droite*/
			retombe_droite (map,singe);       /*appel de la fonction pour retomber d'un carré vers la droite*/

		}

		else if (direction==0){                   /*retombe vers la gauche si le signe a sauté vers la gauche*/
			retombe_gauche(map,singe);
		}

		if (singe->vitesse>15)							/*vérifie si la condition est remplie pour que la variable singe->vitesse ne devienne pas négative, ni=0*/
			singe->vitesse-=15;								/*décrémente la variable pour que le singe accélère au fur et à mesure qu'il descend*/

		glutTimerFunc(singe->vitesse,singe_retombe,0); /*rappelle la fonction singe_retombe après singe->vitesse millisecondes*/
	}
}


void tombe_plateforme (int x){         /*singe tombe d'une plateforme si se déplace trop loin*/
  if (chute_plateforme == true){       /* et si la variable est à true, c'est à dire si le personnage dépasse une plateforme
																			  en se déplaçant vers la gauche ou vers la droite, et non en sautant*/
			retombe (map,singe); /*appel de la fonction pour tomber d'un carré à la verticale*/

			if (singe->vitesse>15)
			singe->vitesse-=15;

			glutTimerFunc(singe->vitesse, tombe_plateforme, 0);  /*rappelle la fonction tombe_plateforme après 150 millisecondes*/
	}
}


void saut_singe (int x) {             /*fonction permettant de faire sauter le singe en diagonale*/

	if (active_saut<10){								/*singe va sauter de 10 cases puis ne plus sauter*/
		if (direction == 1){             /*saute vers la droite si direction = 1*/
		sautDroite(map,singe);           /*appel de la fonction permettant de faire sauter le singe d'un carré vers la droite*/
		active_saut++;                   /*incrémente la variable à chaque rappel de la fonction saut_singe tant qu'elle est < 10*/
		}

		else if (direction == 0){       /*saute vers la gauche si direction = 0*/
		 sautGauche(map,singe);
		 active_saut++;

	 }
	 	singe->vitesse+=15;              /*incrémente la variable pour que le singe ralentisse au fur et à mesure qu'il monte*/
		glutTimerFunc(singe->vitesse, saut_singe,0);  /*rappelle la fonction saut_singe après singe->vitesse millisecondes*/
	}
	if (active_saut==10){									/*indique que le singe est arrivé à la fin de son saut*/
		singe_doit_retomber = true;         /*met la variable à true pour permettre au singe de retomber à la fin de son saut*/
		glutTimerFunc(0,singe_retombe,0);   /*appelle une première fois la fonction singe_retombe pour faire tomber le singe après un saut*/
	}
}



void deplacement_ennemis(int x){                    /*fonction déplaçant automatiquement le serpent*/
	deplacement_serpents(map,serpent);               /*appel de la fonction déplaçant un enemi d'un carré*/
	glutTimerFunc(500, deplacement_ennemis,0);			/*timer appelant la fonction deplacement_ennemis toutes les 500 millisecondes*/
}




void jeu (void) {  /* fonction coordonnant toutes les fonctions présentes dans la partie jeu*/
	drawWall(map);								/*appel de la fonction pour dessiner la map*/
	Dessiner_singe(map);          /*appel de la fonction pour dessiner le singe*/
	Dessiner_bananes(map);        /* idem pour les bananes*/
	Dessiner_ennemis(map);        /*idem pour l'ennemi*/
	interface();                  /*idem pour l'interface*/
	glutSpecialFunc(deplacement);	/*appel de la fonction pour utiliser les flèches pour se déplacer*/
		if (nbre_bananes==0){           /*passe au niveau suivant quand il a récolté toutes les bananes*/
			if (niveau<2)                 /*vérifie cette condition car il n'y a que deux niveaux*/
			niveau_suivant();
			else{											/*permet d'entrer,sur le terminal, le pseudonyme dans le tableau des scores à la fin du jeu*/
		  jeu_actif=false;   /*désactive le jeu*/
			entrer_score();    /*appel de la fonction pour entrer son pseudonyme dans le terminal*/
			score_actif=true;  /*une fois le pseudonyme entré, l'écran du jeu disparait et l'écran des highscores apparait*/
			}
		}
		if (singe->v==0){            /*affiche l'écran de game over si le singe n'a plus de vie*/
			jeu_actif=false;           /*désactive le jeu*/
			game_over=true; }					/*active la variable pour afficher le game-over*/
		if (singe->cood.yp == 179) /*retour au début du niveau si toutes les bananes n'ont pas été collectées*/
			retour_debut_niveau();
		if (LEFT == true) {  /*si appuie sur flèche de gauche: se déplace vers la gauche*/
			deplacementgauche(map, singe);   /*appel de la fontion pour déplacer le personnage vers la gauche d'un carré*/
			singe_doit_retomber = false;     /*met la variable à false pour désactiver la chute en diagonale si le singe tombe d'une plateforme*/
			chute_plateforme = true;         /*met la variable à true pour activer la chute verticale d'une plateforme*/
			glutTimerFunc(0,tombe_plateforme,0); /*appelle une première fois la foncton tombe_plateforme pour que le singe tombe verticalementd'une plateforme*/
			LEFT = false; }                   /*remet left à false une fois terminé pour permettre de diriger le singe dans une autre direction par après*/
		if (RIGHT == true){	/*idem mais vers la droite*/
			deplacementdroite(map, singe);
			singe_doit_retomber = false;
			chute_plateforme = true;
			glutTimerFunc(0,tombe_plateforme,0);
			RIGHT = false; }
		if (UP == true)	{		        /*si appluie du la flèche du haut, saute de 10 cases*/
	 		active_saut=0;             /*initialise la variable à chaque fois qu'on appuie sur la touche saut pour lui permettre de resauter à nouveau*/
	 		singe_doit_retomber = false; /*remet la variable à false pour pouvoir sauter à nouveau sans retomber directement après 1 case*/
	 		chute_plateforme = false; /*désactive la chute verticale pour permettre la chute en diagonale après un saut*/
   		glutTimerFunc(0, saut_singe,0); /*premier appel de la fonction saut_singe*/
  		UP = false; }
		glutPostRedisplay();     /*permet de rappeler la fonction jeu à plusieurs reprise*/
}
