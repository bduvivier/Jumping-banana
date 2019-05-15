#include <GL/glut.h>
#include <stdio.h>
#include "personnage.h"
#include "loadMap.h"
#include "deplacement.h"
#include "drawMap.h"
#include "jeu.h"
#include "scrolling.h"

  int k = 0;            /*variable servant à faire changer automatiquement les serpents de direction*/


void deplacementgauche (char map[MaxX][MaxY], Singe singe) { /*fonction permettant de déplacer le singe d'un carré vers la gauche*/

	int i, j;        /*variables servant à stocker les coordonnées du singe, pour plus de facilité*/

	i=singe->cood.xp;
	j=singe->cood.yp;

	if (map[i][j-1]!='-' && map[i][j-1]!='#' && map[i][j-1] !='1'){    /*fonction collision detecte si, à la position suivante, il u-y a un mur, un ennemi ou une plateforme*/
		if (map[i][j-1]=='0'){											/*incremente la variable nourriture et score si ramasse une banane*/
			singe->n++;
      singe->score++;
		}
		singe->cood.yp--;							/*modifie les coordonnées du singe afin de mettre à jour celles-ci*/
		map[i][j]=' ';								/*modifie le tableau physique afin de déplacer le singe*/
		map[i][j-1]='X';              /*remplace le X par un expace vide, et met le X dans la position suivante du tableau*/
	}

  else if (map[i][j-1] == '1'){        /*détecte s'il y a un ennemi à la position suivante*/
    singe->cood.yp = singe->cood.yp+3; /*met à jour les coordonnées du singe*/
    map[i][j]=' ';                     /*fait reculer le singe de deux cases d'un seul coup*/
    map[i][j+3]='X';
    singe->v--;                       /*décrémente le nombre de vie su singe de 1*/
  }
}

void deplacementdroite (char map[MaxX][MaxY], Singe singe) {  /*idem mais vers la droite, et avec le scrolling*/
	int i, j;

	i=singe->cood.xp;
	j=singe->cood.yp;

	if (map[i][j+1] !='-' && map[i][j+1] !='#' && map[i][j+1] !='1'){
		if (map[i][j+1]=='0'){
			singe->n++;
      singe->score++;
		}
		singe->cood.yp++;
		map[i][j]=' ';
		map[i][j+1]='X';
	}

  else if (map[i][j+1] == '1'){
    singe->cood.yp = singe->cood.yp-3;
    map[i][j]=' ';
    map[i][j-3]='X';
    singe->v--;
  }
  if (j==bord_camera){                /*détecte si le singe touche le bord de la caméra*/
    bord_camera++;                    /*si oui, déplace le bord de la caméra d'une position vers la droite*/
    gCameraX += Square_size;          /*incrémente la position de la caméra sur l'axe des X*/
    scrolling();                      /*appel de la fonction scrollng qui va déplacer la caméra d'un carré vers la droite*/
  }
}


void retombe (char map[MaxX][MaxY], Singe singe) {  /*singe tombe à la verticale d'un carré si il n'y a ni mur, ni plateforme en dessous*/
		int i, j;
		i=singe->cood.xp;
		j=singe->cood.yp;
    if (map[i+1][j] !='-' && map[i+1][j] !='#' && map[i+1][j] !='1'){
			if (map[i+1][j]=='0'){
				singe->n++;
        singe->score++;
			}
			map[i][j]=' ';
			map[i+1][j]='X';
			singe->cood.xp++;
			Dessiner_singe(map); /*dessine le singe au carré suivant*/
		}

    else if (map[i+1][j] == '1'){
      singe->cood.yp = singe->cood.yp-3;
      map[i][j]=' ';
      map[i][j-3]='X';
      singe->v--;
    }
}


void retombe_droite (char map[MaxX][MaxY], Singe singe){  /*singe retombe d'un carré vers la droite s'il a sauté vers la droite avant*/
  int i, j;
  i=singe->cood.xp;
  j=singe->cood.yp;
  if (map[i+1][j+1] !='-' && map[i+1][j+1] !='#' && map[i+1][j+1] !='1'){
    if (map[i+1][j+1]=='0'){
      singe->n++;
      singe->score++;
    }
    map[i][j]=' ';
    map[i+1][j+1]='X';
    singe->cood.xp++;
    singe->cood.yp++;
    Dessiner_singe(map);
  }

  else if (map[i+1][j+1] == '1'){        /*détecte s'il y a un ennemi à la position suivante*/
    singe->cood.yp = singe->cood.yp-3;
    map[i][j]=' ';
    map[i][j-3]='X';
    singe->v--;
  }

  if (j==bord_camera){                 /*scrolling à nouveau*/
    bord_camera++;
    gCameraX += Square_size;
    scrolling();
  }
}


void retombe_gauche (char map[MaxX][MaxY], Singe singe){   /*singe retombe d'un carré vers la gauche s'il a sauté vers la gauche avant*/
  int i, j;
  i=singe->cood.xp;
  j=singe->cood.yp;
  if (map[i+1][j-1] !='-' && map[i+1][j-1] !='#' && map[i+1][j-1] !='1'){
    if (map[i+1][j-1]=='0'){
      singe->n++;
      singe->score++;
    }
    map[i][j]=' ';
    map[i+1][j-1]='X';
    singe->cood.xp++;
    singe->cood.yp--;

    Dessiner_singe(map);
  }
  else if (map[i+1][j-1] == '1'){
    singe->cood.yp = singe->cood.yp+3;
    map[i][j]=' ';
    map[i][j+3]='X';
    singe->v--;
  }
}

void sautDroite (char map[MaxX][MaxY], Singe singe){    /*singe saute d'une case vers la droite*/
	int i,j;                                              /*cette fonction est appelée à 10 reprises pour le faire sauter de 10 cases*/
	i=singe->cood.xp;
	j=singe->cood.yp;

	if (map[i-1][j+1] !='-' && map[i-1][j+1] !='#' && map[i-1][j+1]!= '1'){
		if (map[i-1][j+1]=='0'){
			singe->n++;
      singe->score++;
		}
		singe->cood.xp--;
		singe->cood.yp++;
		map[i][j]=' ';
		map[i-1][j+1]='X';
		Dessiner_singe(map);
  }

  else if (map[i-1][j+1] == '1'){        /*détecte s'il y a un ennemi à la position suivante*/
    singe->cood.yp = singe->cood.yp-3;
    map[i][j]=' ';
    map[i][j-3]='X';
    singe->v--;
  }

  if (j==bord_camera){                 /*scrolling à nouveau*/
    bord_camera++;
    gCameraX += Square_size;
    scrolling();
  }
}


void sautGauche (char map[MaxX][MaxY], Singe singe){  /*idem mais singe saute d'une case vers la gauche*/
	int i,j;
	i=singe->cood.xp;
	j=singe->cood.yp;

	if (map[i-1][j-1] !='-' && map[i-1][j-1] !='#' && map[i-1][j-1]!='1'){
		if (map[i-1][j-1]=='0'){
			singe->n++;
      singe->score++;
		}
		singe->cood.xp--;
		singe->cood.yp--;
		map[i][j]=' ';
		map[i-1][j-1]='X';
			Dessiner_singe(map);
  }

  else if (map[i-1][j-1] == '1'){
    singe->cood.yp = singe->cood.yp+3;
    map[i][j]=' ';
    map[i][j+3]='X';
    singe->v--;
  }
}


void deplacement_serpents (char map[MaxX][MaxY], Ennemi serpent[]){  /*le serpent fait automatiquement des aller retour*/
   int i,j,a,b;
   int l;
   for (l=0; l<nbre_ennemis; l++) {
	    i=serpent[l]->cood.xp;  /*stocke les coordonnées des ennemis dans la variable i et j pour plus de facilité*/
	    j=serpent[l]->cood.yp;
      a=singe->cood.xp;       /*idem avec les coordonnées du singe dans les variables a et b*/
      b=singe->cood.yp;

	    if (k<(4*nbre_ennemis)){                 /*serpent se déplace vers la droite pendant 4 cases*/
          if (map[i][j+1] == 'X'){        /*détecte s'il y a le singe à la position suivante*/
             singe->cood.yp = singe->cood.yp+3; /*met à jour les coordonnées du singe si le serpent le touche*/
             map[a][b]=' ';                     /*fait reculer le singe de trois cases d'un seul coup*/
             map[a][b+3]='X';
             singe->v--;                       /*enlève une vie au singe*/
          }
		      serpent[l]->cood.yp++;							/*modifie les coordonnées du serpent afin de mettre à jour celles-ci*/
  	      map[i][j]=' ';                  /*modifie le tableau physique afin de déplacer le serpent*/
  	      map[i][j+1]='1';                /*suite*/
 		      Dessiner_ennemis(map);          /*dessine l'ennemi à la case suivante*/
 		      k++;
	      }
	     else if (k<(8*nbre_ennemis)){     /*idem mais le serpent se déplace vers la gauche pendant 4 cases*/
         if (map[i][j-1] == 'X'){        
            singe->cood.yp = singe->cood.yp-3;
            map[a][b]=' ';
            map[a][b-3]='X';
            singe->v--;
          }
		     serpent[l]->cood.yp--;
 		     map[i][j]=' ';
 	       map[i][j-1]='1';
		     Dessiner_ennemis(map);
		     k++;
      }
     else if (k==(8*nbre_ennemis)){    /*remise à 0 du compteur k pour que le serpent refasse de nouveau un allez-retour*/
       k=0;                           /*et ainsi de suite*/
     }
  }
}
