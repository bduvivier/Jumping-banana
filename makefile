CC=gcc
CFLAGS=-lglut -lGLU -lGL
OBJ=deplacement.c drawMap.c interface.c jeu.c loadMap.c main.c personnage.c

jumping : $(OBJ)
					$(CC) $(OBJ) -o jumping $(CFLAGS)

deplacement.o : deplacement.c deplacement.h drawMap.h personnage.h loadMap.h
			$(CC) deplacement.c $(CFLAGS)

drawMap.o : drawMap.c drawMap.h loadMap.h personnage.h
			$(CC) drawMap.c $(CFLAGS)

interface.o : interface.c interface.h personnage.h
			$(CC) interface.c $(CFLAGS)

jeu.o : jeu.c jeu.h loadMap.h drawMap.h personnage.h deplacement.h interface.h
				$(CC) jeu.c $(CFLAGS)

loadMap.o : loadMap.c loadMap.h
				$(CC) loadMap.c $(CFLAGS)

main.o : main.c loadMap.h drawMap.h personnage.h jeu.h
				$(CC) main.c $(CFLAGS)

personnage.o : personnage.c personnage.h
				$(CC) personnage.c $(CFLAGS)

clean :
	rm ∗.o
	rm jumping
