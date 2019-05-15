CC=gcc
CFLAGS=-lglut -lGLU -lGL
OBJ=deplacement.c drawMap.c interface.c jeu.c loadMap.c main.c personnage.c changerNiveau.c scrolling.c ecran.c score.c

jumping : $(OBJ)
					$(CC) $(OBJ) -o jumping $(CFLAGS)

deplacement.o : deplacement.c deplacement.h drawMap.h personnage.h loadMap.h jeu.h scrolling.h
			$(CC) deplacement.c $(CFLAGS)

drawMap.o : drawMap.c drawMap.h loadMap.h personnage.h
			$(CC) drawMap.c $(CFLAGS)

interface.o : interface.c interface.h personnage.h changerNiveau.h
			$(CC) interface.c $(CFLAGS)

jeu.o : jeu.c jeu.h loadMap.h drawMap.h personnage.h deplacement.h interface.h changerNiveau.h ecran.h scrolling.h score.h
				$(CC) jeu.c $(CFLAGS)

loadMap.o : loadMap.c loadMap.h changerNiveau.h
				$(CC) loadMap.c $(CFLAGS)

main.o : main.c loadMap.h drawMap.h personnage.h jeu.h changerNiveau.h scrolling.h ecran.h
				$(CC) main.c $(CFLAGS)

personnage.o : personnage.c personnage.h loadMap.h
				$(CC) personnage.c $(CFLAGS)

changerNiveau.o : changerNiveau.c changerNiveau.h loadMap.h personnage.h scrolling.h
				$(CC) changerNiveau.c $(CFLAGS)

scrolling.o : scrolling.c scrolling.h
				$(CC) scrolling.c $(CFLAGS)

ecran.o : ecran.c ecran.h interface.h personnage.h loadMap.h jeu.h score.h
				$(CC) scrolling.c $(CFLAGS)
				
score.o : score.c score.h interface.h personnage.h jeu.h
				$(CC) score.c $(CFLAGS)

clean :
	rm ∗.o
	rm jumping
