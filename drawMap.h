#ifndef _DRAWMAP_H_
#define _DRAWMAP_H_

#include "loadMap.h"


void drawWall(char map[MaxX][MaxY]);           /*dessine les murs et les plateformes*/
void Dessiner_singe (char map [MaxX][MaxY]);   /*idem pour le singe*/
void Dessiner_bananes (char map[MaxX][MaxY]);  /*idem pour les bananes*/
void Dessiner_ennemis (char map [MaxX][MaxY]); /*idem pour les ennemis*/

int nbre_bananes;               /*variable comptant le nombre de bananes restantes dans le niveau*/
int nbre_ennemis;               /*variable comptant le nombre d'ennemis présents dans le niveau actuel*/

#endif
