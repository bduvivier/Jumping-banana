
#ifndef _PERSONNAGE_H_
#define _PERSONNAGE_H_


struct Cood {   /*Structure permettant de stocker la position des différents personnages sur l’axe des X et des Y*/
int xp;         /*coordonnées x = ligne à laquelle on se trouve*/
int yp;         /*coordonnées y = colonne à laquelle on se trouve*/
};


struct Personnage {                   /*structure stockant toutes les variables utiles pour le singe*/
struct Cood cood;                     /*variable stockant la structure Cood*/
int v;                                /*nombre de vies restantes*/
int n;                                /*nombre de banane collectées*/
int score;                            /*score obtenu*/
int vitesse;                          /*vitesse du singe, variable non utilisée pour l'instant*/
};

typedef struct Personnage *Singe;     /* créé un nouveau type qui correspond à un type pointeur vers la structure Personnage*/
Singe singe;                          /*variable de type pointeur vers la structure Personnage*/
Singe initialiser (void);             /*declaration de la fonction pour initialiser le singe (variables de la structure Personnage)*/

struct ennemi {                       /*structure stockant la structure coordonnées pour les ennemis. Il y aura peut être d'autres variables dans celle-ci*/
  struct Cood cood;
};

typedef struct ennemi *Ennemi;       /* créé un nouveau type qui correspond à un type pointeur vers la structure ennemi*/
Ennemi serpent;                      /*variable de type pointeur vers la structure ennemi*/
Ennemi initialisation_E (void);      /*declaration de la fonction pour initialiser le singe (variables de la structure Personnage)*/



#endif
