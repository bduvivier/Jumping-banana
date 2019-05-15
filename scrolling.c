#include "scrolling.h"
#include <GL/glut.h>

void scrolling (void) {                      /*fonction déplaçant la caméra d'un carré vers la droite*/
  glMatrixMode( GL_MODELVIEW );
  glPopMatrix();
  glLoadIdentity();
  glTranslatef( -gCameraX, 0.f, 0.f );   /*modifie la position de la caméra en fonction de la valeur de gCameraX*/
  glPushMatrix();
}
