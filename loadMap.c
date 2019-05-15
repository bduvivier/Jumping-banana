#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "loadMap.h"
#include "changerNiveau.h"



bool loadMap(char map[MaxX][MaxY])		/*fonction qui ouvre le fichier txt et charge la carte dans le tableau*/
{
    FILE *f = NULL;

    if (niveau==1)              /*charge le niveau 1 si niveau=1*/
    f = fopen("map.txt", "r");

    else if (niveau == 2)      /*charge le niveau 2 si niveau=2*/
    f = fopen("map2.txt", "r");

    if(f == NULL)            /*envoie un message d'erreur si le fichier est vide*/
    {
        printf("file empty");
        return false;
    }
    char c;
	int i,j;

	for(i = 0; i < MaxX; i++)         /*double boucle stockant chaque caractère du fichier texte dans le tableau map*/
		{
			for(j = 0; j < MaxY; j++)
			{
				c = fgetc(f);
				map[i][j] = c;
			}
			fgetc(f);
		}

	    fclose(f);

	    printf("\n");

		for(i = 0; i < MaxX; i++)     /*double boucle affichant la map dans le terminal*/
		{
			for(j = 0; j < MaxY; j++)
			{
				printf("%c", map[i][j]);
			}
			printf("\n");
		}

 return true;
 }
