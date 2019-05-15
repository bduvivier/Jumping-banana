#include <GL/glut.h>
#include "ecran.h"
#include "interface.h"
#include "personnage.h"
#include "loadMap.h"
#include "jeu.h"
#include <stdbool.h>
#include "score.h"
#include "gameover.c"


void afficher_game_over(void){       /*fonction chargeant un fichier créé avec gimp, et affichant une image*/

  glColor3f(1.0f,1.0f,1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  GLuint texture;
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  gluBuild2DMipmaps( GL_TEXTURE_2D, GAMEOVER.bytes_per_pixel,
      GAMEOVER.width, GAMEOVER.height,GL_RGB, GL_UNSIGNED_BYTE,
      GAMEOVER.pixel_data );

  glEnable(GL_TEXTURE_2D);

  glTranslatef(Square_size, Square_size,0.0f);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);  glVertex2f(800, -20);
    glTexCoord2f(1.0, 1.0);  glVertex2f(-20, -20);
    glTexCoord2f(1.0, 0.0);  glVertex2f(-20, 800);
    glTexCoord2f(0.0, 0.0);  glVertex2f(800, 800);
    glEnd();

  glDisable(GL_TEXTURE_2D);
}


void afficher_controles(void){      /*fonction afficgant du texte comme pour l'interface*/

  glLoadIdentity();
  glColor3f(0.52f,0.37f,0.26f);
  afficher_interface("Utilisez les croix directionnelles pour diriger le singe",50,100,0); /*appel de la fonction afficher_interface pour afficher du texte*/

  glLoadIdentity();
  glColor3f(0.52f,0.37f,0.26f);
  afficher_interface("Appuyez sur m pour revenir au menu",50,200,0);

  glLoadIdentity();
  glColor3f(0.52f,0.37f,0.26f);
  afficher_interface("Recoltez toutes les bananes pour terminer le niveau",50,300,0);

  glLoadIdentity();
  glColor3f(0.52f,0.37f,0.26f);
  afficher_interface("Evitez les ennemis",50,400,0);

}

void afficher_highscore (){  /*fonction affichant du texte comme pour l'interface*/
  char tableau[4];
  int i =0;

  int position_y = 200; /*position y du texte*/

  glLoadIdentity();
  glColor3f(0.52f,0.37f,0.26f);
  afficher_interface("HIGHSCORE",350,100,0);

  while (i<5){  /*boucle qui va afficher les 5 highscores les un en dessous des autres*/

  glLoadIdentity();
  glColor3f(0.52f,0.37f,0.26f);
  afficher_interface(highscore[i]->nom,30,position_y,0);
  sprintf(tableau, "%d", highscore[i]->scorefinal);
  glLoadIdentity();
  glColor3f(0.52f,0.37f,0.26f);
  afficher_interface(tableau,200,position_y,0);

  i++;  /*incrémente i pour afficher le contenu de la structure suivante, et donc le highscore suivant*/
  position_y += 100; /*pour afficher les scores l'un en dessous de l'autre*/
  }
}

void afficher_menu(void){      /*fonction affichant du texte comme pour l'interface*/
  glLoadIdentity();
  glColor3f(0.52f,0.37f,0.26f);
  afficher_interface("MENU",350,100,0);

  glLoadIdentity();
  glColor3f(0.752941f,0.752941f,0.752941f);
  afficher_interface("Nouvelle partie(appuyez sur n)",260,150,0);

  glLoadIdentity();
  glColor3f(0.137255f,0.556863f,0.419608f);
  afficher_interface("Reprendre (appuyez sur r)",260,250,0);

  glLoadIdentity();
  glColor3f(0.196078f,0.196078f,0.8f);
  afficher_interface("Scores (appuyez sur s)",260,350,0);

  glLoadIdentity();
  glColor3f(1.0f,0.5f,0.0f);
  afficher_interface("Controles (appuyez sur c)",260,450,0);

  glLoadIdentity();
  glColor3f(1.0f,0.0f,0.0f);
  afficher_interface("Quitter (appuyez sur escape)",260,550,0);
}


void clavier_menu (unsigned char key, int x, int y){  /*fonction permettant de sélectionner un écran à l'aide d'un clavier*/
  switch(key){
  	case 'r':             /*reprend la partie là où le joueur l'avait laissée si appuie sur r*/
  	 jeu_actif = true;    /*met la variables booléenne correspondante à true, et les autres à false*/
     menu = false;        /*de manière à n'afficher qu'un seul écran à la fois*/
     game_over=false;     /*même chose pour les autres cas*/
     controles=false;
     score_actif=false;
  	 break;
    case 'n':            /*lance une nouvelle partie si appuie sur n*/
      jeu_actif= true;
      menu = false;
      game_over = false;
      controles=false;
      score_actif=false;
      nouvelle_partie(); /*appel de la fonction pour ré-initialiser toutes les variables (personnages, ennemis, caméra, etc)*/
      break;
  	case 's':           /*affiche le tableau des scores si appuie sur s*/
      jeu_actif=false;
      menu=false;
      game_over=false;
      controles=false;
      score_actif=true;
  	  break;
  	case 'c':          /*affiche les règles et les contrôles si appuie sur c*/
      jeu_actif = false;
      menu = false;
      game_over=false;
      controles = true;
      score_actif=false;
     	break;
    case 'm':         /*affiche le menu si appuie sur m*/
      jeu_actif=false;
      menu=true;
      game_over=false;
      controles=false;
      score_actif=false;
      break;
    case 27 :    /*permets de quitter le jeu en cloturant le programme si appuie sur escape*/
      exit(0);
  break;
	}
}

void selection_ecran(void){       /*la fonction affichage étant dans un callback, la fonction selection_ecran va être appelée à plusieurs reprises*/

  glutKeyboardFunc(clavier_menu);  /*callback de la fonction pour naviguer entre les différents écrans à l'aide du clavier*/

  if (menu == true){      /*si la variable menu est à true, autorise l'appel de la fonction afficher_menu*/
    afficher_menu();      /*même chose pour les autres */
  }
  if (jeu_actif==true){
    jeu();
  }
  if (game_over==true){
    afficher_game_over();
  }
  if (controles == true){
    afficher_controles();
  }
  if (score_actif == true){
  	afficher_highscore();
  }
}
