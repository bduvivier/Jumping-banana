#include <GL/glut.h>
#include <stdio.h>
#include "personnage.h"
#include "loadMap.h"
#include "deplacement.h"
#include "drawMap.h"

  int k = 0;            /*variable servant à faire changer automatiquement les serpents de direction*/


void deplacementgauche (char map[MaxX][MaxY], Singe singe)  { /*fonction permettant de déplacer le singe d'un carré vers la gauche*/

	int i, j;        /*variables servant à stocker les coordonnées du singe, pour plus de facilité*/

	i=singe->cood.xp;
	j=singe->cood.yp;

	if (map[i][j-1]!='-' && map[i][j-1]!='#'){    /*fonction collision detecte si, à la position suivante, il u-y a un mur ou une plateforme*/
		if (map[i][j-1]=='0'){											/*incremente la variable nourriture et score si ramasse une banane*/
			singe->n++;
      singe->score++;
		}
		singe->cood.yp--;							/*modifie les coordonnées du singe afin de mettre à jour celles-ci*/
		map[i][j]=' ';								/*modifie le tableau physique afin de déplacer le singe*/
		map[i][j-1]='X';              /*remplace le X par un expace vide, et met le X dans la position suivante du tableau*/
	}

}

void deplacementdroite (char map[MaxX][MaxY], Singe singe) {  /*idem mais vers la droite*/
	int i, j;

	i=singe->cood.xp;
	j=singe->cood.yp;

	if (map[i][j+1] !='-' && map[i][j+1] !='#'){
		if (map[i][j+1]=='0'){
			singe->n++;
      singe->score++;
		}
		singe->cood.yp++;
		map[i][j]=' ';
		map[i][j+1]='X';

	}

}

void saut (char map[MaxX][MaxY], Singe singe) { /*ïdem pour faire sauter le singe. Saute d'un carré*/
                                                /*saut vertical, cette fonction sera peut être utilisée plus tard, mais pas ici*/
	int i, j;

	i=singe->cood.xp;
	j=singe->cood.yp;

	if (map[i-1][j] !='-' && map[i-1][j] !='#'){
		if (map[i-1][j]=='0'){
			singe->n++;
      singe->score++;
		}
		singe->cood.xp--;
		map[i][j]=' ';
		map[i-1][j]='X';
	}

			Dessiner_singe(map);      /*appel de la fonction dessinant le singe pour le dessiner au carré suivant*/


}

void retombe (char map[MaxX][MaxY], Singe singe) {  /*singe tombe à la verticale d'un carré si il n'y a ni mur, ni plateforme en dessous*/
		int i, j;
		i=singe->cood.xp;
		j=singe->cood.yp;
    if (map[i+1][j] !='-' && map[i+1][j] !='#'){
			if (map[i+1][j]=='0'){
				singe->n++;
        singe->score++;
			}
			map[i][j]=' ';
			map[i+1][j]='X';
			singe->cood.xp++;


			Dessiner_singe(map);
		}
}

void retombe_droite (char map[MaxX][MaxY], Singe singe){  /*singe retombe d'un carré vers la droite s'il a sauté vers la droite avant*/
  int i, j;
  i=singe->cood.xp;
  j=singe->cood.yp;
  if (map[i+1][j+1] !='-' && map[i+1][j+1] !='#'){
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
}

void retombe_gauche (char map[MaxX][MaxY], Singe singe){   /*singe retombe d'un carré vers la gauche s'il a sauté vers la gauche avant*/
  int i, j;
  i=singe->cood.xp;
  j=singe->cood.yp;
  if (map[i+1][j-1] !='-' && map[i+1][j-1] !='#'){
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
}

void sautDroite (char map[MaxX][MaxY], Singe singe){    /*singe saute d'une case vers la droite*/
	int i,j;                                              /*cette fonction est appelée à 10 reprises pour le faire sauter de 10 cases*/
	i=singe->cood.xp;
	j=singe->cood.yp;

	if (map[i-1][j+1] !='-' && map[i-1][j-1] !='#'){
		if (map[i-1][j+1]=='0'){
			singe->n++;
      singe->score++;
		}
		singe->cood.xp--;
		singe->cood.yp++;
		map[i][j]=' ';
		map[i-1][j+1]='X';
	}

			Dessiner_singe(map);

}

void sautGauche (char map[MaxX][MaxY], Singe singe){  /*idem mais singe saute d'une case vers la gauche*/
	int i,j;
	i=singe->cood.xp;
	j=singe->cood.yp;

	if (map[i-1][j-1] !='-' && map[i-1][j-1] !='#'){
		if (map[i-1][j-1]=='0'){
			singe->n++;
      singe->score++;
		}
		singe->cood.xp--;
		singe->cood.yp--;
		map[i][j]=' ';
		map[i-1][j-1]='X';
	}

			Dessiner_singe(map);

}

void deplacement_serpents (char map[MaxX][MaxY], Ennemi serpent){  /*le serpent fait automatiquement des aller retour*/
   int i,j;
	 i=serpent->cood.xp;
	 j=serpent->cood.yp;


	 if (k<4){                        /*serpent se déplace vers la droite pendant 4 cases*/
		serpent->cood.yp++;							/*modifie les coordonnées du serpent afin de mettre à jour celles-ci*/
  	map[i][j]=' ';                  /*modifie le tableau physique afin de déplacer le serpent*/
  	map[i][j+1]='1';                /*suite*/
 		Dessiner_ennemis(map);          /*dessine l'ennemi à la case suivante*/
 		k++;
	 }
	 else if (k<8){                    /*idem mais le serpent se déplace vers la gauche pendant 4 cases*/
		serpent->cood.yp--;
 		map[i][j]=' ';
 		map[i][j-1]='1';
		Dessiner_ennemis(map);
		k++;
	 }
   else if (k==8){                  /*remise à 0 du compteur k pour que le serpent refasse de nouveau un allez-retour*/
     k=0;                           /*et ainsi de suite*/
   }


}
