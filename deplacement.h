#include "personnage.h"
#include "loadMap.h"




void deplacementgauche (char map[MaxX][MaxY], Singe singe);  /*fonction pour déplacer le singe vers la gauche*/

void deplacementdroite (char map[MaxX][MaxY], Singe singe); /*idem mais vers la droite*/


void saut (char map[MaxX][MaxY], Singe singe);            /*saut vertical, cette fonction sera peut être utilisée plus tard, mais pas ici*/

void sautDroite (char map[MaxX][MaxY], Singe singe);      /*singe saute d'une case vers la droite*/


void sautGauche (char map[MaxX][MaxY], Singe singe);     /*idem mais vers la gauche*/


void retombe (char map[MaxX][MaxY], Singe singe);        /*singe tombe à la verticale d'un carré si il n'y a ni mur, ni plateforme en dessous*/

void retombe_droite (char map[MaxX][MaxY], Singe singe);  /*singe retombe d'une case vers la droite*/

void retombe_gauche (char map[MaxX][MaxY], Singe singe);  /*ïdem vers la gauche*/


void deplacement_serpents (char map[MaxX][MaxY], Ennemi serpent);  /*déplace le serpent automatiquement de gauche à droite*/
