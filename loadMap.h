#ifndef _LOADMAP_H_
#define _LOADMAP_H_

#include <stdbool.h>


#define MaxX 39                     /*la map faisant 39 lignes et 182 colones*/
#define MaxY 182
#define Square_size 20.0            /*taille de la longuer du côté d'un carré*/

bool loadMap(char map[MaxX][MaxY]);  /*fonction stockant le fichier texte avec la map dans un tableau*/
char map[MaxX][MaxY];                /*déclaration du tableau servant à stocker la map*/

#endif
