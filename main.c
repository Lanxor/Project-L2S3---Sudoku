#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "case.h"
#include "grille.h"
#include "regles.h"

#define DEBUG 0

int main(int argc, char *argv[])
{
	T_sudoku grille;
	initGrille(&grille);

	if( remplirGrilleF(&grille, argv[1]) ) {
		printf("Lecture du fichier \"%s\".\n", argv[1]);
	}
	else {
		printf("Pas de fichier appelé.\n");
		saisiGrille(&grille);
	}

	printf("Voici la grille.\n\n");
	afficherGrille(grille);

	char pause[1] = { 'O' };
	printf("Voulez-vous utiliser le mode pas à pas (o/n) ? ");
	scanf("%s", &pause);printf("\n\n");

	int candSeul, candUniques = 1;
	while( estSudoku(grille) ) {
		for(int numCase = 0; numCase < 81; ++numCase) {
			eliminationCandidats(&grille, numCase);
			considerationInterregion(&grille, numCase);
			candSeul = candidatsSeul(&grille, numCase);
			candUniques = candidatsUniques(&grille, numCase);
			if( (pause[0] == 'O' || pause[0] == 'o') && (candSeul == 1 || candUniques == 1) ) {
				if( DEBUG ) {
					afficherGrilleCandidats(grille);
				} else {
					afficherGrille(grille);
					printf("Appuyez sur la touche entrée pour continuer...\n");getchar();
				}
			}
			if( DEBUG ) {
				afficherGrilleCandidats(grille);
				getchar();
			}
		}
	}

	printf("Voici la grille Sudoku rempli.\n\n");
	afficherGrille(grille);
	printf("Programme fini.\n");
	return 0;
}
