#include "changerNiveau.h"
#include "personnage.h"
#include "loadMap.h"
#include "scrolling.h"


void niveau_suivant(void){
  niveau++;                    /*incrémente la variable niveau*/
  singe->cood.xp=37;           /*ré-initialise certaines variables du singe*/
  singe->cood.yp=2;            /*position et nombre de bananes collectées*/
  singe->n=0;
  gCameraX = 0;									/*ré-initialise la position de la caméra$*/
  scrolling();                  /*replace la caméra au début*/
  bord_camera = 30;             /* ré-initialise l'endroit où le scrolling va s'activer au début*/
  loadMap(map);                 /*charge la map du niveau suivant dans le tableau*/
  initialisation_E();           /*ré-initialise les ennemis*/
}
